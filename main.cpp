#include <iostream>
#include "headers/Repertorio.h"      // Para cargar las películas
#include "headers/GrafosPeliculas.h"  // Para el grafo
#include "headers/Usuario.h"         // Para el usuario
#include "headers/Busqueda.h"        // Para los menús

using namespace std;

int main() {
    // Cargar el repertorio de películas (Singleton)
    Repertorio* repertorio = Repertorio::getInstancia();
    repertorio->leerCSV("data_corregida.csv");

    // Crear el grafo de películas
    GrafoPeliculas grafoPeliculas;
    const auto& peliculas = repertorio->getPeliculas();
    for (const auto& par : peliculas) {
        grafoPeliculas.agregarPelicula(par.second);
    }

    // Crear un objeto Usuario
    Usuario usuario;

    // Mostrar mensaje de carga
    cout << "Cargando..." << endl;
    cout << "-------------------------------------------" << endl;

    // Menú Principal
    reaizarBusqueda mainMenu;

    while (true) {
        mainMenu.display(); // Mostrar menú principal
        mainMenu.handleInput(usuario, &grafoPeliculas); // Manejar la entrada del usuario
    }

    return 0;
}
