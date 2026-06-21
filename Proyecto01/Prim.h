#pragma once

#include "Grafo.h"
#include "Stack.h"
#include "ArrayStack.h"

class Prim {
private:
	Grafo* grafo;

public:
	Prim(Grafo* grafo)
	{
		this->grafo = grafo; 
	}

	Grafo hacerRecorrido(int primerNodo){
		
		int nodo = grafo->numNodos(); 
		Grafo aNuevo(grafo->dirigido);


		for (int i = 0; i < nodo; i++){
			aNuevo.agregarNodo(grafo->posiciones[i].x, grafo->posiciones[i].y); 
		}

		bool* nodosVisitados = new bool[nodo];

		for (int i = 0; i < nodo; i++){
			nodosVisitados[i] = false; 
		}

		ArrayStack<int> pila(nodo); 

		nodosVisitados[primerNodo] = true;
		pila.push(primerNodo);


		while (!pila.isEmpty()) {
			int minPeso = -1;
			int origen = -1;
			int destino = -1;

			for (int i = 0; i < nodo; i++) {
				if (nodosVisitados[i]) {
					for (int j = 0; j < nodo; j++) {
						if (!nodosVisitados[j] && grafo->hayArista(i, j)) {
							int peso = grafo->pesoArista(i, j);
							if (minPeso == -1 || peso < minPeso) {
								minPeso = peso;
								origen = i;
								destino = j;
							}
						}
					}
				}
			}
			
			nodosVisitados[destino] = true;
			aNuevo.agregarArista(origen, destino, minPeso);
			
		}
		delete[] nodosVisitados;
		return aNuevo; 

	}
};