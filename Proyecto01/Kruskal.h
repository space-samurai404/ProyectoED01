#pragma once

#include "Grafo.h"
#include "MinHeap.h"

struct Arista { //esto es porque no hicimos la clase arista pero yo si la ocupo xdd
    int origen;
    int destino;
    int peso;

    bool operator<(const Arista& otra) const {
        return peso < otra.peso;
    }
};

class Kruskal {
private:
    Grafo* grafo;

    int encontrar(int* padre, int x) {
        if (padre[x] != x)
            padre[x] = encontrar(padre, padre[x]);
        return padre[x];
    }

    void unir(int* padre, int x, int y) {
        padre[encontrar(padre, x)] = encontrar(padre, y);
    }

public:
    Kruskal(Grafo* grafo) {
        this->grafo = grafo;
    }

    Grafo hacerRecorrido() {
        int nodo = grafo->numNodos();
        Grafo aNuevo(grafo->dirigido);

        for (int i = 0; i < nodo; i++)
            aNuevo.agregarNodo(grafo->posiciones[i].x, grafo->posiciones[i].y);

        MinHeap<Arista> heap(nodo * nodo); //aqui inserto todo en el minhip
        for (int i = 0; i < nodo; i++) {
            for (int j = i + 1; j < nodo; j++) {
                if (grafo->hayArista(i, j)) {
                    heap.insert({ i, j, grafo->pesoArista(i, j) });
                }
            }
        }
            

        int* padre = new int[nodo];
        for (int i = 0; i < nodo; i++)
            padre[i] = i;

        while (!heap.isEmpty()) {
            Arista a = heap.removeFirst();
            if (encontrar(padre, a.origen) != encontrar(padre, a.destino)) {
                aNuevo.agregarArista(a.origen, a.destino, a.peso);
                unir(padre, a.origen, a.destino);
            }
        }

        delete[] padre;
        return aNuevo;
    }
};