#ifndef PROYECTOFINALP3_MENU_H
#define PROYECTOFINALP3_MENU_H

//Codigo alterntivo para Busqueda.h
#include <iostream>
#include <vector>
#include <limits>
#include "Usuario.h"
#include "Pelicula.h"
#include "GrafosPeliculas.h"

using namespace std;

// Almacén global de películas
vector<Pelicula> peliculas;

// Función auxiliar para mostrar detalles de una película
void mostrarDetallesPelicula(const Pelicula& pelicula) {
    cout << "Titulo: " << pelicula.getTitulo() << endl;
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
            input = static_cast<T>(stoi(line));
            if (input >= minVal && input <= maxVal) {
                break;
            } else {
                cout << "Entrada fuera de rango. ";
            }
        } catch (const invalid_argument&) {
            cout << "Entrada inválida. ";
        }
    }
    return input;
}

// Menú de selección de películas
class MovieSelectionMenu : public Menu {
private:
    vector<int> indexes; // Índices de las películas seleccionadas
    int page = 0;

public:
    MovieSelectionMenu(const vector<int>& idx) : indexes(idx) {}

    void display() override {
        int start = page * 5;
        int end = min(start + 5, static_cast<int>(indexes.size()));

        cout << "\nPelículas disponibles:\n";
        for (int i = start; i < end; ++i) {
            cout << i - start + 1 << ". ";
            mostrarDetallesPelicula(peliculas[indexes[i]]);
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
                    int movieChoice = getValidatedInput<int>(
                            "Seleccione el número de la película: ", 1, 5);
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
            }
        }
    }
};

// Menú de búsqueda de películas
class MovieSearchMenu : public Menu {
public:
    void display() override {
        cout << "\nBuscar películas:\n";
        cout << "1. Buscar por título\n";
        cout << "2. Buscar por tags\n";
        cout << "3. Volver al menú principal\n";
    }

    void handleInput(Usuario& user) override {
        GrafoPeliculas grafoPeliculas;
        int option = getValidatedInput<int>("Seleccione una opción: ", 1, 3);

        switch (option) {
            case 1: {
                cout << "\nIngrese el título: ";
                string titulo;
                getline(cin, titulo);

                auto resultados = grafoPeliculas.busquedaPorTitulo(titulo, 5);
                if (resultados.empty()) {
                    cout << "No se encontraron resultados.\n";
                } else {
                    vector<int> indices; // Vector para almacenar los índices
                    for (const auto& pelicula : resultados) {
                        // Busca la posición de la película en el vector global `peliculas`
                        auto it = find(peliculas.begin(), peliculas.end(), pelicula);
                        if (it != peliculas.end()) {
                            // Calcula el índice como la distancia desde el inicio
                            indices.push_back(distance(peliculas.begin(), it));
                        }
                    }

                    // Verifica si se encontraron índices válidos
                    if (indices.empty()) {
                        cout << "No se encontraron índices válidos en el vector global.\n";
                    } else {
                        MovieSelectionMenu menu(indices); // Pasa los índices al menú
                        menu.handleInput(user);
                    }
                }

                break;
            }
            case 2: {
                cout << "\nIngrese el tag: ";
                string tag;
                getline(cin, tag);

                auto resultados = grafoPeliculas.busquedaPorTag(tag);
                if (resultados.empty()) {
                    cout << "No se encontraron resultados.\n";
                } else {
                    MovieSelectionMenu menu(resultados);
                    menu.handleInput(user);
                }
                break;
            }
            case 3:
                return;
        }
    }
};

// Menú principal
class MainMenu : public Menu {
public:
    void display() override {
        cout << "\nMenú Principal:\n";
        cout << "1. Ver mis favoritos\n";
        cout << "2. Ver más tarde\n";
        cout << "3. Buscar películas\n";
        cout << "4. Salir\n";
    }

    void handleInput(Usuario& user) override {
        int option = getValidatedInput<int>("Seleccione una opción: ", 1, 4);

        switch (option) {
            case 1:
                user.mostrarFavoritos(peliculas); //aun no declarado bien en usuario
                break;
            case 2:
                user.mostrarVerMasTarde(peliculas); //aun no declarado bien en usuario
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
        }
    }
};

#endif // PROYECTOFINALP3_MENU_H
