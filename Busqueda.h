//
// Created by leo on 11/20/24.
//

#ifndef BUSQUEDA_H
#define BUSQUEDA_H

#include <iostream>
#include <vector>
#include "Pelicula.h"
#include "GrafosPeliculas.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

// Mostrar los resultados en lotes y permitir navegar por ellos
void mostrarResultados(const vector<Pelicula>& resultados, int& indice, int limite = 5) {
    // Mostrar los resultados en lotes de 'limite'
    for (int i = indice; i < indice + limite && i < resultados.size(); ++i) {
        cout << i + 1 << ". Titulo: " << resultados[i].getTitulo() << endl;
    }

    // Incrementar el índice para la próxima llamada
    indice += limite;

    // Verificar si hay más resultados para mostrar
    if (indice < resultados.size()) {
        cout << "¿Mostrar más resultados? (s/n): ";
        char opcion;
        cin >> opcion;
        if (opcion == 's' || opcion == 'S') {
            mostrarResultados(resultados, indice, limite);
        }
    } else {
        cout << "No hay más resultados." << endl;
    }
}

// Mostrar detalles de una película seleccionada
void mostrarDetallesPelicula(const Pelicula& pelicula) {
    cout << "Titulo: " << pelicula.getTitulo() << endl;
    cout << "Sinopsis: " << pelicula.getSinopsis() << endl;
    cout << "Tags: ";
    for (const auto& tag : pelicula.getTags()) {
        cout << tag << " ";
    }
    cout << endl;
}

// Realizar una búsqueda y mostrar los resultados
void realizarBusqueda(GrafoPeliculas& grafo) {
    while (true) {
        cout << "\nSeleccione el tipo de búsqueda:\n";
        cout << "1. Búsqueda por Título\n";
        cout << "2. Búsqueda por Palabra en Sinopsis\n";
        cout << "3. Búsqueda General\n";
        cout << "4. Búsqueda por Tag\n";
        cout << "5. Salir\n";
        cout << "Opción: ";

        int opcion;
        cin >> opcion;

        if (opcion == 5) {
            break;
        }

        cout << "Ingrese la palabra de búsqueda: ";
        string palabraBusqueda;
        cin.ignore();  // Limpiar el buffer
        getline(cin, palabraBusqueda);

        vector<Pelicula> resultados;

        if (opcion == 1) {
            resultados = grafo.busquedaPorTitulo(palabraBusqueda);
            cout << "Resultados de la búsqueda por título '" << palabraBusqueda << "':" << endl;
        } else if (opcion == 2) {
            resultados = grafo.busquedaPorPalabraEnSinopsis(palabraBusqueda);
            cout << "Resultados de la búsqueda por palabra en sinopsis '" << palabraBusqueda << "':" << endl;
        } else if (opcion == 3) {
            resultados = grafo.busquedaGeneral(palabraBusqueda);
            cout << "Resultados de la búsqueda general '" << palabraBusqueda << "':" << endl;
        } else if (opcion == 4) {
            resultados = grafo.busquedaPorTag(palabraBusqueda);
            cout << "Resultados de la búsqueda por tag '" << palabraBusqueda << "':" << endl;
        } else {
            cout << "Opción no válida. Inténtelo de nuevo.\n";
            continue;
        }

        int indice = 0;
        mostrarResultados(resultados, indice);

        // Permitir al usuario ver detalles de las películas seleccionadas
        while (true) {
            cout << "Seleccione el número de la película para ver más detalles (0 para volver): ";
            int seleccion;
            cin >> seleccion;

            if (seleccion == 0) {
                break;
            } else if (seleccion > 0 && seleccion <= resultados.size()) {
                mostrarDetallesPelicula(resultados[seleccion - 1]);
            } else {
                cout << "Selección no válida. Inténtelo de nuevo.\n";
            }
        }
    }
}

#endif // BUSQUEDA_H

