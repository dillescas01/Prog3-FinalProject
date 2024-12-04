#ifndef PROYECTOFINALP3_NODO_H
#define PROYECTOFINALP3_NODO_H

#include <iostream>
#include "Pelicula.h"

using std::string;

class Nodo {

public:
    string id;
    Pelicula pelicula;
    unordered_set<Nodo*> conexiones;

    Nodo(string id, Pelicula pelicula):
    id(id),
    pelicula(std::move(pelicula)) {}

    void agregarConexion(Nodo* nodoB){
        conexiones.insert(nodoB);
    }
};

#endif