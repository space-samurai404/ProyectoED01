#pragma once

#include "Grafo.h"
#include "ArrayStack.h"
#include <iostream>
#include "Matrix.h"


class Dijkstra
{

private:
	Grafo* grafo; //Guarda la referencia del grafo a recorrer


public:

	Dijkstra(Grafo* grafo)
	{
		this->grafo = grafo; //Esto recibe un grafo y lo guarda para acceder e el grafo despues
	}

	Grafo buscarCaminoCorto(int primerNodo, int ultimoNodo)
	{

		int nodo;

		nodo = grafo->numNodos(); //Esto es para identificar y guardar la cantidad de nodos que tiene el grafo, los cuales recorrera


		int* calcularPeso = new int[nodo]; //Esto es para guardar el peso de cada nodo, el cual se va a ir actualizando a medida que se recorre el grafo

		int* nodoAnterior = new int[nodo]; //Esto es para guardar el nodo anterior de cada nodo, el cual calcula la ruta mas corta

		bool* nodoFijo = new bool[nodo]; //Esto es para definir cual nodo ya se fijo su peso para asi guardarlo como parte de la ruta mas corta


		for (int i = 0; i < nodo; i++)
		{

			calcularPeso[i] = INT_MAX; //Inicializa el peso de cada nodo como infinito, para que se actualice con el peso real a medida que se recorre el grafo

			nodoAnterior[i] = -1; //Esto para que se identifique que no tiene nodo anterior

			nodoFijo[i] = false; //Esto para indicar que ningun nodo se definido como en la ruta más corta


		}


		calcularPeso[primerNodo] = 0; //El peso del nodo inicial se define como 0, ya que es el punto de partida



		for (int i = 0; i < nodo; i++)
		{

			int nodoActual;
			int pesoMinimo;


			nodoActual = -1; //Esto es para identificar el nodo actual es el nodo con el peso minimo
			pesoMinimo = INT_MAX; //Esto es para identificar el peso minimo de los nodos restantes


			//Esto es para recorrer todos los nodos y encontrar el nodo con el peso minimo que no se haya fijado aun

			for (int i = 0; i < nodo; i++)
			{

				if (!nodoFijo[i] && calcularPeso[i] < pesoMinimo)
				{

					pesoMinimo = calcularPeso[i]; //Esto es para actualizar el peso minimo con el peso del nodo actual
					nodoActual = i; //Esto es para actualizar el nodo actual con el valor del nodo con el peso minimo

				}

			}



			if (nodoActual == -1) //Esto indica si no hay una ruta posible entre el nodo inicial y el nodo final 
			{
				break;
			}


			nodoFijo[nodoActual] = true; //Esto es para fijar el nodo actual como parte de la ruta mas corta


			if (nodoActual == ultimoNodo) //Esto es para identificar si el nodo actual es el nodo final, si es asi se termina el recorrido
			{
				break;
			}


			for (int vecino = 0; vecino < nodo; vecino++)
			{

				if (grafo->hayArista(nodoActual, vecino))
				{

					int peso = grafo->pesoArista(nodoActual, vecino);


					if (calcularPeso[nodoActual] != INT_MAX && calcularPeso[nodoActual] + peso < calcularPeso[vecino])
					{

						calcularPeso[vecino] = calcularPeso[nodoActual] + peso;

						nodoAnterior[vecino] = nodoActual;

					}

				}

			}


		}



		Grafo rutaCorta(grafo->dirigido); //Esto es para crear un nuevo grafo que contendra la ruta mas corta

		for (int i = 0; i < nodo; i++)
		{

			rutaCorta.agregarNodo(grafo->posiciones[i].x, grafo->posiciones[i].y); //Esto es para agregar los nodos que formaran parte de la ruta mas corta al nuevo grafo

		}


		//Todo el if indica que si el nodo final tiene un peso infinito, es decir, 
		//no se pudo encontrar una ruta entre el nodo inicial y el nodo final, se devuelve un grafo vacio

		if (calcularPeso[ultimoNodo] == INT_MAX)
		{

			delete[] calcularPeso;

			delete[] nodoAnterior;

			delete[] nodoFijo;

			return rutaCorta;
		}


		ArrayStack<int> pila(nodo); //Esto es para crear una pila con los nodos que formaran parte de la ruta mas corta

		int nodoActual;

		nodoActual = ultimoNodo; //Esto es para iniciar el recorrido desde el nodo final, esto porque al momento de construir el grafo se va a ir sacando los nodos de la pila, en forma de como se han ido agregando y como el final se agregar de ultimo sera el primero de salir en la pila


		while (nodoActual != -1)
		{

			pila.push(nodoActual); //Esto es para agregar el nodo actual a la pila
			nodoActual = nodoAnterior[nodoActual]; //Esto es para actualizar el nodo actual con su nodo anterior, esto para ir construyendo la ruta mas corta desde el nodo final hasta el nodo inicial por la forma de la pila

		}

		int nodoOrigen;


		nodoOrigen = pila.pop();



		while (!pila.isEmpty())
		{

			int ultimoNodo = pila.pop();

			rutaCorta.agregarArista(nodoActual, ultimoNodo, grafo->pesoArista(nodoActual, ultimoNodo));


			nodoActual = ultimoNodo;

		}


		delete[] calcularPeso;
		delete[] nodoAnterior;
		delete[] nodoFijo;

		return rutaCorta;


	}
};


//Este algoritmo recorre de manera manual todos los nodos calculando el peso de cada una, asi los clasifica e identifica 
//para despues calcular la ruta más corta, cuando ya lo hace los nodos que identifico para la ruta más corta los marca como
//nodos fijos que seran usados para construir la ruta, estos nodos son almacenados en un ArrayStack por lo que al momento de ir
//sacando cada nodo lo hara desde el nodo destino hasta el nodo inicial por el orden y comportamiento de la pila.
