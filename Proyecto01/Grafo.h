#pragma once
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


	Grafo(bool dirigido = false) : dirigido(dirigido) {
	
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

	void dibujarNodo(sf::RenderWindow& v, int i, sf::Font& fuente) {
		sf::Vector2f pos = posiciones[i];
		// circulo
		sf::CircleShape c(22.f);
		c.setOrigin({ 22.f, 22.f });
		c.setPosition(pos);
		c.setFillColor(sf::Color(70, 130, 180));
		c.setOutlineColor(sf::Color::Black);
		c.setOutlineThickness(2.f);
		v.draw(c);
		sf::Text t(fuente);
		t.setString(std::to_string(i));
		t.setCharacterSize(16);
		t.setFillColor(sf::Color::White);
		sf::FloatRect r = t.getLocalBounds();
		t.setOrigin({ r.position.x + r.size.x / 2, r.position.y + r.size.y / 2 });
		t.setPosition(pos);
		v.draw(t);
	}

	void dibujarArista(sf::RenderWindow& v,sf::Vector2f a, sf::Vector2f b,sf::Color color = sf::Color::Black,float grosor = 2.f) {
		sf::Vector2f dir = b - a;
		float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
		if (len == 0) return;

		sf::RectangleShape linea({ len, grosor }); 
		linea.setPosition(a);                      
		linea.setFillColor(color);
		linea.setRotation(sf::degrees(std::atan2(dir.y, dir.x) * 180.f / 3.14159f));
		

		v.draw(linea);
	}

	void dibujar(sf::RenderWindow& ventana, sf::Font& fuente) {
		//se dibujan primero las aristas
		for (int i = 0; i < numNodos(); i++)
			for (int j = i + 1; j < numNodos(); j++)
				if (hayArista(i, j))
					dibujarArista(ventana, posiciones[i], posiciones[j]);
		// y luego los nodos por encima
		for (int i = 0; i < numNodos(); i++)
			dibujarNodo(ventana, i, fuente);
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

