#ifndef PROYECTO_PROGRAMACION3_UI_H
#define PROYECTO_PROGRAMACION3_UI_H

#include "GrafosPeliculas.h"
#include "Usuario.h"
#include <iostream>
#include <vector>
#include <string>

class Menu {
public:
    virtual void display() = 0;
    virtual void handleInput(Usuario& usuario, GrafoPeliculas* grafo) = 0;
};

// Menú de selección de películas
class MovieSelectionMenu : public Menu {
private:
    vector<Pelicula> peliculas;
    int page = 0;

public:
    MovieSelectionMenu(const vector<Pelicula>& peliculas) : peliculas(peliculas) {}

    void display() override {
        int start = page * 5;
        int end = start + 5;
        for (int i = start; i < end && i < peliculas.size(); ++i) {
            cout << i + 1 << ". " << peliculas[i].getTitulo() << endl;
        }

        cout << "\nOpciones:\n";
        cout << "1. Seleccionar Pelicula\n";
        if (end < peliculas.size()) {
            cout << "2. Ver las siguientes 5 peliculas\n";
        }
        if (page > 0) {
            cout << "3. Ver las 5 peliculas anteriores\n";
        }
        cout << "4. Regresar al Menu Principal\n";
        cout << "Ingrese su opcion: ";
    }

    void handleInput(Usuario& usuario, GrafoPeliculas* grafo) override {
        bool continuar = true;
        while (continuar) {
            display();

            int choice;
            while (true) {
                string input;
                getline(cin, input);
                try {
                    choice = stoi(input);
                    if (choice >= 1 && choice <= 4) {
                        break;
                    } else {
                        cout << "Opcion invalida. Intente de nuevo: ";
                    }
                } catch (const invalid_argument&) {
                    cout << "Opcion invalida. Intente de nuevo: ";
                }
            }

            switch (choice) {
                case 1: {
                    cout << "Ingrese el numero de la pelicula a seleccionar: ";
                    int movieChoice;
                    while (true) {
                        string input;
                        getline(cin, input);
                        try {
                            movieChoice = stoi(input);
                            if (movieChoice > 0 && movieChoice <= 5 &&
                                (page * 5 + movieChoice - 1) < peliculas.size()) {
                                break;
                            } else {
                                cout << "Opcion invalida. Intente de nuevo: ";
                            }
                        } catch (const invalid_argument &) {
                            cout << "Opcion invalida. Intente de nuevo: ";
                        }
                    }

                    int movieIndex = page * 5 + movieChoice - 1;
                    cout << "IMBD ID: " << peliculas[movieIndex].getId() << endl;
                    cout << "Pelicula seleccionada: " << peliculas[movieIndex].getTitulo() << endl;
                    cout << "Sinopsis: " << peliculas[movieIndex].getSinopsis() << endl;

                    int userChoice;
                    cout << "Opciones:\n1. Marcar como favorita\n2. Marcar como ver mas tarde\n3. Regresar a la busqueda\n4. Regresar al menu principal\n";
                    cout << "Ingrese su opcion: ";
                    while (true) {
                        string input;
                        getline(cin, input);
                        try {
                            userChoice = stoi(input);
                            if (userChoice >= 1 && userChoice <= 4) {
                                break;
                            } else {
                                cout << "Opcion invalida. Intente de nuevo: ";
                            }
                        } catch (const invalid_argument&) {
                            cout << "Opcion invalida. Intente de nuevo: ";
                        }
                    }

                    if (userChoice == 1) {
                        usuario.marcarFavorito(movieIndex);
                    } else if (userChoice == 2) {
                        usuario.marcarVerMasTarde(movieIndex);
                    } else if (userChoice == 3) {
                        continuar = true;
                    } else {
                        continuar = false;
                    }
                    break;
                }
                case 2:
                    if ((page + 1) * 5 < peliculas.size()) {
                        ++page; // Ver las siguientes 5 películas
                    }
                    break;
                case 3:
                    if (page > 0) {
                        --page; // Ver las 5 películas anteriores
                    }
                    break;
                case 4:
                    return; // Regresar al menú principal
            }
        }
    }
};

// Menú de búsqueda
class MovieSearchMenu : public Menu {
public:
    void display() override {
        cout << "\nBuscar:\n";
        cout << "1. Buscar por Titulo\n";
        cout << "2. Buscar por tag\n";
        cout << "3. Buscar por palabra en sinopsis\n";
        cout << "4. Buscueda general\n";
        cout << "5. Regresar al Menu Principal\n";
        cout << "Ingrese su opcion: ";
    }

    void handleInput(Usuario& usuario, GrafoPeliculas* grafo) override {
        int option;
        while (true) {
            string input;
            getline(cin, input);
            try {
                option = stoi(input);
                if (option >= 1 && option <= 4 ) {
                    break;
                } else {
                    cout << "Opcion invalida. Intente de nuevo: ";
                }
            } catch (const invalid_argument&) {
                cout << "Opcion invalida. Intente de nuevo: ";
            }
        }

        switch (option) {
            case 1: {
                cout << "\nIngrese parte del nombre de la pelicula: ";
                string input;
                getline(cin, input);
                vector<Pelicula> resultados = grafo->busquedaPorTitulo(input);

                if (resultados.empty()) {
                    cout << "No se encontraron peliculas para la busqueda.\n";
                } else {
                    MovieSelectionMenu selectionMenu(resultados);
                    selectionMenu.handleInput(usuario, grafo);
                }
                break;
            }
            case 2: {
                cout << "\nIngrese la palabra: ";
                string tag;
                getline(cin, tag);
                vector<Pelicula> resultados = grafo->busquedaPorTag(tag);

                if (resultados.empty()) {
                    cout << "No se encontraron peliculas para el tag especificado.\n";
                } else {
                    MovieSelectionMenu selectionMenu(resultados);
                    selectionMenu.handleInput(usuario, grafo);
                }
                break;
            }
            case 3:{
                cout << "\nIngrese el tag de busqueda: ";
                string sinopsis;
                getline(cin, sinopsis);
                vector<Pelicula> resultados = grafo->busquedaPorPalabraEnSinopsis(sinopsis);

                if (resultados.empty()) {
                    cout << "No se encontraron peliculas con esa palabra en la sinopsis\n";
                } else {
                    MovieSelectionMenu selectionMenu(resultados);
                    selectionMenu.handleInput(usuario, grafo);
                }
                break;
            }
            case 4:{
                cout << "\nIngrese la palabra  de busqueda: ";
                string general;
                getline(cin, general);
                vector<Pelicula> resultados = grafo->busquedaGeneral(general);

                if (resultados.empty()) {
                    cout << "No se encontraron peliculas con esa palabra\n";
                } else {
                    MovieSelectionMenu selectionMenu(resultados);
                    selectionMenu.handleInput(usuario, grafo);
                }
                break;
            }

            case 5:
                return; // Regresar al menú principal
        }
    }
};

// Menú principal
class reaizarBusqueda: public Menu {
public:
    void display() override {
        cout << "\nMenu Principal:\n";
        cout << "1. Ver Peliculas Favoritas\n";
        cout << "2. Ver Peliculas Para Ver Mas Tarde\n";
        cout << "3. Buscar Peliculas\n";
        cout << "4. Salir\n";
        cout << "Ingrese su opcion: ";
    }

    void handleInput(Usuario& usuario, GrafoPeliculas* grafo) override {
        int option;
        while (true) {
            string input;
            getline(cin, input);
            try {
                option = stoi(input);
                if (option >= 1 && option <= 4) {
                    break;
                } else {
                    cout << "Opcion invalida. Intente de nuevo: ";
                }
            } catch (const invalid_argument&) {
                cout << "Opcion invalida. Intente de nuevo: ";
            }
        }

        switch (option) {
            case 1:
                cout <<"Mostrar favoritos: ";
                break;
            case 2:
                cout << "Mostrar ver más tarde: ";
                break;
            case 3: {
                MovieSearchMenu searchMenu;
                searchMenu.display();
                searchMenu.handleInput(usuario, grafo);
                break;
            }
            case 4:
                cout << "Saliendo...\n";
                exit(0);
        }
    }
};

#endif // PROYECTO_PROGRAMACION3_UI_H
