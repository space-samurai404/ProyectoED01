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

	

	int numNodos() {
		return posiciones.size();
	}







};

