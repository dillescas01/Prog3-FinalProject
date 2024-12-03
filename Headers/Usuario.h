#ifndef PROYECTOFINALP3_USUARIO_H
#define PROYECTOFINALP3_USUARIO_H
#include <vector>
#include <string>
#include <iostream>
#include "ConstructorPelicula.h"
#include "GrafosPeliculas.h"
using namespace std;

class Usuario {
private:
    vector<int> likedMovies;           // Películas favoritas
    vector<int> watchLaterMovies;      // Películas para ver más tarde

public:
    // Función para marcar una película como favorita
    void marcarFavorito(int movieIndex) {
        likedMovies.push_back(movieIndex);
        cout << "Pelicula agregada a la lista de favoritos.\n";
    }

    // Función para marcar una película para ver más tarde
    void marcarVerMasTarde(int movieIndex) {
        watchLaterMovies.push_back(movieIndex);
        cout << "Pelicula agregada a la lista de ver mas tarde.\n";
    }

    // Mostrar las películas favoritas
    void mostrarFavoritos(const vector<Pelicula>& db) const {
        cout << "Peliculas Favoritas:\n";
        for (int index : likedMovies) {
            cout << db[index].getTitulo() << endl;
        }
    }

    // Mostrar las películas para ver más tarde
    void mostrarVerMasTarde(const vector<Pelicula>& db) const {
        cout << "Peliculas para ver mas tarde:\n";
        for (int index : watchLaterMovies) {
            cout << db[index].getTitulo() << endl;
        }
    }
};
#endif // PROYECTOFINALP3_USUARIO_H
