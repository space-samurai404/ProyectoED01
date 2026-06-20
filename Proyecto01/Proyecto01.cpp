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

int main()
{

    sf::RenderWindow ventana(sf::VideoMode({ 900, 650 }), "Prueba de Dibujo - Grafo");
    ventana.setFramerateLimit(60);

    sf::Font fuente;
    if (!fuente.openFromFile("arial.ttf")) {
        // si no encuentra la fuente da error
        return -1;
    }

    // ── Grafo de prueba ──
    Grafo grafo(false); //no dirigido

    grafo.agregarNodo(450, 80);   
    grafo.agregarNodo(200, 250);  
    grafo.agregarNodo(700, 250);  
    grafo.agregarNodo(300, 480);  
    grafo.agregarNodo(600, 480);  

    grafo.agregarArista(0, 1, 9);
    grafo.agregarArista(0, 2, 3);
    grafo.agregarArista(1, 2, 6);
    grafo.agregarArista(1, 3, 5);
    grafo.agregarArista(2, 4, 2);
    grafo.agregarArista(3, 4, 1);
    grafo.agregarArista(0, 4, 7);

    // ── Loop principal ──
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
