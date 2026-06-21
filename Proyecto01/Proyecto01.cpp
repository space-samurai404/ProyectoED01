// Proyecto01.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include "Grafo.h"
#include "Stack.h"
#include "ArrayStack.h"
#include "Matrix.h"
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "DFS.h"
#include "BFS.h"
#include "Dijkstra.h"
#include "Prim.h"
#include "kruskal.h"
#include <optional>

using std::runtime_error;
using std::cout;
using std::cin;
using std::getline;
using std::endl;
using namespace std;
using std::string;


int nodoEnPosicion(Grafo& grafo, sf::Vector2f mouse, float radio = 22.f) {
    for (int i = 0; i < grafo.numNodos(); i++) {
        sf::Vector2f d = mouse - grafo.posiciones[i];
        if (std::sqrt(d.x * d.x + d.y * d.y) <= radio)
            return i;
    }
    return -1;

}

void dibujarResaltado(sf::RenderWindow& ventana, Grafo& base, Grafo& resultado, sf::Font& fuente, sf::Color colorResaltado) {
    //1. Dibujar el grafo base en gris tenue
    for (int i = 0; i < base.numNodos(); i++)
        for (int j = i + 1; j < base.numNodos(); j++)
            if (base.hayArista(i, j))
                base.dibujarArista(ventana, base.posiciones[i], base.posiciones[j],
                    sf::Color(80, 80, 80), 1.f);

    // 2. Dibujar las aristas del resultado (DFS/BFS/Dijkstra/Prim/Floyd) resaltadas
    for (int i = 0; i < resultado.numNodos(); i++)
        for (int j = i + 1; j < resultado.numNodos(); j++)
            if (resultado.hayArista(i, j))
                resultado.dibujarArista(ventana, resultado.posiciones[i],
                    resultado.posiciones[j], colorResaltado, 4.f);

    // 3. Dibujar todos los nodos encima
    for (int i = 0; i < base.numNodos(); i++)
        base.dibujarNodo(ventana, i, fuente);
}


float CalculoDistancia(sf::Vector2f a, sf::Vector2f b) {
	float dx = b.x - a.x;
	float dy = b.y - a.y;
	return std::sqrt(dx * dx + dy * dy);
}

Grafo crearGrafoMenu(int cantNodos, float anchoLienzo, float altoLienzo, float distanciaConexion, int maxVecinos) {
	Grafo grafo(false); //no dirigido
	grafo.agregarNodo(450, 80);
	grafo.agregarNodo(200, 250);
	grafo.agregarNodo(700, 250);
	grafo.agregarNodo(300, 480);
	grafo.agregarNodo(600, 480);
	for (int i = 0; i < cantNodos; i++) {
        float x = 30 + rand() % (int)(anchoLienzo - 60); //posiciones para que sea aleatorio en el lienzo
        float y = 30 + rand() % (int)(altoLienzo - 60);
        grafo.agregarNodo(x, y);
		
	}

	std::vector<int> contadorVecinos(cantNodos, 0); //contador para limitar vecinos


	for (int i = 0; i < cantNodos; i++) {
		for (int j = i + 1; j < cantNodos; j++) {
            if (contadorVecinos[i] >= maxVecinos) {
                break;
            }
            if (contadorVecinos[j] >= maxVecinos) {
                continue;
            }

            float dist = CalculoDistancia(grafo.posiciones[i], grafo.posiciones[j]);
				if (dist <= distanciaConexion) {
					int peso = static_cast<int>(dist); //peso basado en la distancia
					grafo.agregarArista(i, j, peso);
					contadorVecinos[i]++;
					contadorVecinos[j]++;
				}
			}
		}
	
	return grafo;
}

int main()
{

        int dimensionx;
        int dimensiony;
        int cantNodos;
        int cantMaxVecinos;
        float distanciaConexion;
        int algoritmo;
        
        cout << "Ingrese las dimensiones de la ventana: "<<endl;
        cout << "Ingrese el ancho de la ventana:" << endl;
        cin >> dimensionx;
        cout << "\n";
        cout << "Ingrese el alto de la ventana:" << endl;
        cin >> dimensiony;
        cout << "\n";
        cout << "¿De cuantos nodos desea que sea el grafo?:" << endl;
        cin >> cantNodos;
        cout << "\n";
        cout << "¿Cual va a ser la cantidad maxima de vecinos?:" << endl;
        cin >> cantMaxVecinos;
        cout << "\n";
        cout << "¿Cual va a ser la distancia maxima de conexion entre nodos?:" << endl;
        cin >> distanciaConexion;
        cout << "\n";
        cout << "¿Que algoritmo quiere ejecutar?:" << endl;
        cout << "1). BFS" << endl << "2). DFS" << endl << "3). Dijkstra" << endl << "4). Prim" << endl<<"5). Kruskal" << endl;
        cin >> algoritmo;
        cout << "\n";

    sf::RenderWindow ventana(sf::VideoMode({ dimensionx, dimensiony }), "Grafo");
    ventana.setFramerateLimit(60);

    sf::Font fuente;
    if (!fuente.openFromFile("C:/Windows/Fonts/arial.ttf")) {
        // si no encuentra la fuente da error
        return -1;
    }

    // ── Grafo de prueba ──
    Grafo grafo(false); //no dirigido

    grafo=crearGrafoMenu(cantNodos, dimensionx, dimensiony, distanciaConexion, cantMaxVecinos);

    Grafo arbolBFS(false);
    Grafo arbolDFS(false);


    switch(algoritmo){
    case 1:
        BFS bfs(&grafo);
        Grafo arbolBFS = bfs.hacerRecorrido(0);
        break;
    case 2:
        DFS dfs(&grafo);
        Grafo arbolDFS = dfs.hacerRecorrido(0);
        break;

    case 3:
        Dijkstra dij(&grafo);
        Grafo arbolDIJ= dij.buscarCaminoCorto(0);
        break;

    case 4:
        Dijkstra dij(&grafo);
        Grafo arbolDIJ = dij.buscarCaminoCorto(0);
        break;
    }
   
    while (ventana.isOpen()) {
        
        while (const std::optional<sf::Event> evento = ventana.pollEvent()) {
            if (evento->is<sf::Event::Closed>())
                ventana.close();
        }

        ventana.clear(sf::Color::White);
        grafo.dibujar(ventana, fuente);
        ventana.display();
    }

    return 0;
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
