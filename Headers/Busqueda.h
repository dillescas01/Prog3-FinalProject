#ifndef BUSQUEDA_H
#define BUSQUEDA_H

#include <iostream>
#include <vector>
#include <limits>
#include "Pelicula.h"
#include "GrafosPeliculas.h"
//Manú más eficiente, provisional y funcional
using namespace std;

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
        cout << "¿Mostrar mas resultados? (s/n): ";
        char opcion;
        cin >> opcion;
        if (opcion == 's' || opcion == 'S') {
            mostrarResultados(resultados, indice, limite);
        }
    } else {
        cout << "No hay mas resultados." << endl;
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

void realizarBusqueda(GrafoPeliculas& grafo) {
    while (true) {
        cout << "\nSeleccione el tipo de busqueda:\n";
        cout << "1. Busqueda por Título\n";
        cout << "2. Busqueda por Palabra en Sinopsis\n";
        cout << "3. Busqueda General\n";
        cout << "4. Busqueda por Tag\n";
        cout << "5. Salir\n";
        cout << "Opcion: ";

        int opcion;

        // Validar entrada numérica
        cin >> opcion;
        if (cin.fail()) {
            cin.clear(); // Limpia el estado de error
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descarta la entrada inválida
            cout << "Entrada no valida. Por favor, ingrese un numero entre 1 y 5.\n";
            continue; // Regresar al inicio del bucle
        }

        // Control de flujo con switch
        int indice = 0;
        switch (opcion) {
            case 1: {
                cout << "Ingrese el titulo a buscar: ";
                string palabraBusqueda;
                cin.ignore(); // Limpiar el buffer
                getline(cin, palabraBusqueda);

                vector<Pelicula> resultados = grafo.busquedaPorTitulo(palabraBusqueda);
                cout << "Resultados de la busqueda por titulo '" << palabraBusqueda << "':\n";
                mostrarResultados(resultados, indice);
                break;
            }
            case 2: {
                cout << "Ingrese la palabra a buscar en la sinopsis: ";
                string palabraBusqueda;
                cin.ignore(); // Limpiar el buffer
                getline(cin, palabraBusqueda);

                vector<Pelicula> resultados = grafo.busquedaPorPalabraEnSinopsis(palabraBusqueda);
                cout << "Resultados de la busqueda por palabra en sinopsis '" << palabraBusqueda << "':\n";
                mostrarResultados(resultados, indice);
                break;
            }
            case 3: {
                cout << "Ingrese la palabra para la busqueda general: ";
                string palabraBusqueda;
                cin.ignore(); // Limpiar el buffer
                getline(cin, palabraBusqueda);

                vector<Pelicula> resultados = grafo.busquedaGeneral(palabraBusqueda);
                cout << "Resultados de la busqueda general '" << palabraBusqueda << "':\n";
                mostrarResultados(resultados, indice);
                break;
            }
            case 4: {
                cout << "Ingrese el tag a buscar: ";
                string palabraBusqueda;
                cin.ignore(); // Limpiar el buffer
                getline(cin, palabraBusqueda);

                vector<Pelicula> resultados = grafo.busquedaPorTag(palabraBusqueda);
                cout << "Resultados de la busqueda por tag '" << palabraBusqueda << "':\n";
                mostrarResultados(resultados, indice);
                break;
            }
            case 5: {
                cout << "Saliendo del programa de busqueda.\n";
                return; // Finaliza la función y sale del bucle
            }
            default: {
                cout << "Opción no valida. Por favor, ingrese un numero entre 1 y 5.\n";
                break; // Regresar al inicio del bucle
            }
        }
    }
}

#endif

