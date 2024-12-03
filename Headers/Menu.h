#ifndef PROYECTOFINALP3_MENU_H
#define PROYECTOFINALP3_MENU_H
/*
#include <iostream>
#include <vector>
#include <limits>
#include <stdexcept>
#include <algorithm>
#include "Usuario.h"
#include "Pelicula.h"
#include "GrafosPeliculas.h"

using namespace std;

// Almacén global de películas
vector<Pelicula> peliculas;

// Función auxiliar para mostrar detalles de una película
void mostrarDetallesPelicula(const Pelicula& pelicula) {
    cout << "\n--- Detalles de la Película ---\n";
    cout << "Título: " << pelicula.getTitulo() << endl;
    cout << "Sinopsis: " << pelicula.getSinopsis() << endl;
    cout << "Tags: ";
    for (const auto& tag : pelicula.getTags()) {
        cout << tag << " ";
    }
    cout << endl;
}

// Clase base abstracta para menús
class Menu {
public:
    virtual void display() = 0;
    virtual void handleInput(Usuario& user) = 0;
};

// Función auxiliar para obtener entradas válidas
template<typename T>
T getValidatedInput(const string& prompt, T minVal, T maxVal) {
    T input;
    while (true) {
        cout << prompt;
        string line;
        getline(cin, line);
        try {
            input = static_cast<T>(stod(line)); // Usa `stod` para manejar enteros y floats.
            if (input >= minVal && input <= maxVal) {
                return input;
            } else {
                cout << "Entrada fuera de rango. Intente nuevamente.\n";
            }
        } catch (const exception&) {
            cout << "Entrada inválida. Intente nuevamente.\n";
        }
    }
}

// Menú de selección de películas
class MovieSelectionMenu : public Menu {
private:
    vector<int> indexes; // Ahora almacena índices de películas
    int page = 0;

public:
    explicit MovieSelectionMenu(const vector<int>& idx) : indexes(idx) {}

    void display() override {
        int start = page * 5;
        int end = min(start + 5, static_cast<int>(indexes.size()));

        cout << "\n--- Películas Disponibles ---\n";
        for (int i = start; i < end; ++i) {
            cout << i - start + 1 << ". ";
            cout << peliculas[indexes[i]].getTitulo() << endl;
        }

        cout << "\nOpciones:\n";
        cout << "1. Seleccionar película\n";
        if (end < indexes.size()) cout << "2. Ver las siguientes 5 películas\n";
        if (page > 0) cout << "3. Ver las 5 películas anteriores\n";
        cout << "4. Regresar al menú principal\n";
    }

    void handleInput(Usuario& user) override {
        bool continueSearching = true;

        while (continueSearching) {
            display();
            int choice = getValidatedInput<int>("Seleccione una opción: ", 1, 4);

            switch (choice) {
                case 1: {
                    int maxOption = min(static_cast<int>(indexes.size()) - page * 5, 5);
                    int movieChoice = getValidatedInput<int>(
                            "Seleccione el número de la película: ", 1, maxOption);

                    int movieIndex = indexes[page * 5 + movieChoice - 1];
                    mostrarDetallesPelicula(peliculas[movieIndex]);

                    int action = getValidatedInput<int>(
                            "\n1. Me gusta\n2. Ver más tarde\n3. Volver\nOpción: ", 1, 3);

                    if (action == 1) user.marcarFavorito(movieIndex);
                    else if (action == 2) user.marcarVerMasTarde(movieIndex);
                    break;
                }
                case 2:
                    if ((page + 1) * 5 < indexes.size()) ++page;
                    break;
                case 3:
                    if (page > 0) --page;
                    break;
                case 4:
                    continueSearching = false;
                    break;
                default:
                    cout << "Vuelve a intentarlo\n";
                    return;
            }
        }
    }
};

// Menú de búsqueda de películas
class MovieSearchMenu : public Menu {
public:
    void display() override {
        cout << "\n--- Buscar Películas ---\n";
        cout << "1. Buscar por título\n";
        cout << "2. Buscar por tags\n";
        cout << "3. Volver al menú principal\n";
    }

    void handleInput(Usuario &user) override {
        GrafoPeliculas grafoPeliculas;
        int option = getValidatedInput<int>("Seleccione una opción: ", 1, 3);

        switch (option) {
            case 1: {
                cout << "\nIngrese el título: ";
                string titulo;
                getline(cin, titulo);

                auto resultados = grafoPeliculas.busquedaPorTitulo(titulo, 5);
                procesarResultados(resultados, user);
                break;
            }
            case 2: {
                cout << "\nIngrese el tag: ";
                string tag;
                getline(cin, tag);

                auto resultados = grafoPeliculas.busquedaPorTag(tag);
                procesarResultados(resultados, user);
                break;
            }
            case 3:
                return;

            default:
                cout<<"Vuelve a intentarlo";
                return;
        }
    }

private:
    void procesarResultados(const vector<Pelicula> &resultados, Usuario &user) {
        if (resultados.empty()) {
            cout << "No se encontraron resultados.\n";
            return;
        }

        vector<int> indices; // Ahora almacena índices enteros
        for (const auto &pelicula: resultados) {
            auto it = find(peliculas.begin(), peliculas.end(), pelicula);
            if (it != peliculas.end()) {
                indices.push_back(distance(peliculas.begin(), it));
            }
        }

        if (indices.empty()) {
            cout << "No se encontraron índices válidos en el vector global.\n";
        } else {
            MovieSelectionMenu menu(indices);
            menu.handleInput(user);
        }
    }
};


// Menú Principal Modificado
class realizarBusqueda: public Menu {
public:
    void display() override {
        cout << "\n--- Menú Principal ---\n";
        cout << "1. Ver mis favoritos\n";
        cout << "2. Ver más tarde\n";
        cout << "3. Buscar películas\n";
        cout << "4. Salir\n";
    }

    void handleInput(Usuario &user) override {
        int option = getValidatedInput<int>("Seleccione una opción: ", 1, 4);

        switch (option) {
            case 1:
                user.mostrarFavoritos(peliculas);
                break;
            case 2:
                user.mostrarVerMasTarde(peliculas);
                break;
            case 3: {
                MovieSearchMenu menu;
                menu.display();
                menu.handleInput(user);
                break;
            }
            case 4:
                cout << "Gracias por usar la aplicación.\n";
                break;
            default:
                cout << "Vuelve a intentarlo\n";
                return;
        }
    }

};

*/
#endif // PROYECTOFINALP3_MENU_H