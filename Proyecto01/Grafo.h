#pragma once
#include "Nodo.h"
#include "Matrix.h"
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

using std::vector;

class Grafo
{
public:
	Matrix<int> ady;
	vector<sf::Vector2f> posiciones;//clase de sfml que representa un vector 2D
	bool dirigido;

	Grafo(bool dirigido = false) {
		this->dirigido = dirigido;
	}

	int numNodos() {
		return posiciones.size();
	}

	void agregarNodo(float x, float y) {
		posiciones.push_back({ x, y });//agrega un elemento al final del vector
		if (numNodos() == 1) {
			ady = Matrix<int>(1, 1);
			ady.setValue(0, 0, 0);
		}
		else {
			ady.expand(0);
		}
	}

	void agregarArista(int org, int dest, int peso) {
		ady.setValue(org, dest, peso);
		if (!dirigido) {
			ady.setValue(dest, org, peso);
		}
	}

	void eliminarArista(int org, int dest, int peso) {
		ady.setValue(org, dest, 0);
		if (!dirigido) {
			ady.setValue(dest, org, 0);
		}
	}

	void elminarNodo(int index) {
		posiciones.erase(posiciones.begin() + index);
		ady.shrink(index);
	}

	bool hayArista(int i, int j) {
		return ady.getValue(i, j) != 0;
	}

	int pesoArista(int i, int j) {
		return ady.getValue(i, j);
	}







};

