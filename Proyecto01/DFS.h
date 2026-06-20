#pragma once

#include "Grafo.h"
#include "Stack.h"
#include "ArrayStack.h"

class DFS
{

private:

	Grafo* grafo; //Guarda la referencia del grafo a recorrer

public:

	DFS(Grafo* grafo) 
	{
		this->grafo = grafo; //Esto recibe un grafo y lo guarda para acceder e el grafo despues
	}

	
	Grafo hacerRecorrido(int primerNodo)
	{

		int nodo;

		int nodo = grafo->numNodos(); //Esto es para identificar y guardar la cantidad de nodos que tiene el grafo, los cuales recorrera


		Grafo aNuevo(grafo->dirigido); //Esto es para crear un nuevo grafo


		for (int i = 0; i < nodo; i++)
		{
			aNuevo.agregarNodo(grafo->posiciones[i].x, grafo->posiciones[i].y); //Esto es para agregar los nodos al nuevo grafo, con las mismas posiciones que el grafo original
		}


		bool* nodosVisitados = new bool[nodo]; //Esto es para reconocer si un nodo ya fue visitado

		for (int i = 0; i < nodo; i++)
		{
			nodosVisitados[i] = false; //Esto inicializa a todos los nodos en false, es decir, que no han sido visitados ya esto marca el inicio del recorrido
		}


		ArrayStack<int> pila(nodo); //Esto es para crear una pila, la cual es una de las estructuras adicionales segun el enunciado


		nodosVisitados[primerNodo] = true; //Esto es para marcar cual es nodo viditado como primero
		pila.push(primerNodo); //Esto es para agregar el nodo que se visito de primero a la pila para que se pueda usar en el recorrido


		while (!pila.isEmpty())
		{

			int nodoActual = pila.pop(); //Esto es para sacar el nodo que se encuentra en la cima de la pila

			for (int nodoVecino = nodo - 1; nodoVecino >= 0;nodoVecino--) //Esto es para recorrer los nodos vecinos 
			{

				if (grafo->hayArista(nodoActual, nodoVecino) && !nodosVisitados[nodoVecino]) //Esto es para identificar si hay una arista entre nodos, ademas identifica si el nodo vecino encontrado ha sido visitado
				{

					nodosVisitados[nodoVecino] = true;


					aNuevo.agregarArista(nodoActual, nodoVecino, grafo->pesoArista(nodoActual, nodoVecino)); // Esto es para agregar la arista al nuevo grafo, para asi construir el arbol de expasion 

					pila.push(nodoVecino); // Esto es para agregar el nodo vecino a la pila para el recorrido

				}

			}


			delete[] nodosVisitados;

			return aNuevo;

		}

	}


};

