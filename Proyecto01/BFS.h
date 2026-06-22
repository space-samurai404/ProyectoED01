#pragma once

#include "Grafo.h"
#include "Queue.h"
#include "ArrayQueue.h"
#include <iostream>
#include "Matrix.h"

class BFS
{

private:

	Grafo* grafo; //Guarda la referencia del grafo a recorrer



public:

	BFS(Grafo* grafo)
	{
		this->grafo = grafo; //Esto recibe un grafo y lo guarda para acceder e el grafo despues
	}


	Grafo hacerRecorrido(int primerNodo)
	{

		int nodo;

		nodo = grafo->numNodos(); //Esto es para identificar y guardar la cantidad de nodos que tiene el grafo, los cuales recorrera


		Grafo nuevoArbol(grafo->dirigido); //Esto es para crear un nuevo grafo


		for (int i = 0; i < nodo; i++)
		{

			nuevoArbol.agregarNodo(grafo->posiciones[i].x, grafo->posiciones[i].y); //Esto es para agregar los nodos al nuevo grafo, con las mismas posiciones que el grafo original
		
		}


		bool* nodosVisitados = new bool[nodo]; //Esto es para reconocer si un nodo ya fue visitado


		for (int i = 0; i < nodo; i++)
		{

			nodosVisitados[i] = false;
		
		}


		nodosVisitados[primerNodo] = true;

		ArrayQueue<int> cola(nodo);
		cola.enqueue(primerNodo);


		while (!cola.isEmpty())
		{

			int nodoActual = cola.dequeue();

			for (int nodoVecino = 0; nodoVecino < nodo; nodoVecino++)
			{

				if (grafo->hayArista(nodoActual, nodoVecino) && !nodosVisitados[nodoVecino]) //Esto es para identificar si hay una arista entre nodos, ademas identifica si el nodo vecino encontrado ha sido visitado
				{

					nodosVisitados[nodoVecino] = true;

					int aristaMedida = grafo->pesoArista(nodoActual, nodoVecino);

					nuevoArbol.agregarArista(nodoActual, nodoVecino, aristaMedida); // Esto es para agregar la arista al nuevo grafo, para asi construir el arbol de expasion 

					cola.enqueue(nodoVecino);

				}

			}

		}

		delete[] nodosVisitados;

		return nuevoArbol;
	}
};

//Este algoritmo se parcer al DSF, pero este usa colas, haciendo que primero vaya por los nodos vecinos desde el nodo seleccionado
//(nodo inicial) para asi despues recorrer los nodos vecinos de los nodos vecinos del nodo inicial
//Haciendo un recorrido por niveles, hasta recorrer el arbol completo.
