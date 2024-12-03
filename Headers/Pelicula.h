#ifndef PROYECTOFINALP3_PELICULA_H
#define PROYECTOFINALP3_PELICULA_H

#include <iostream>
#include <unordered_set>

using  std::string, std::unordered_set ;


class Pelicula {
private:
    string id;
    string titulo;
    string sinopsis;
    unordered_set<string> tags;

public:

    Pelicula()= default;

    Pelicula(string id, string title, string sinopsis, unordered_set<string> tags):
            id(std::move(id)),
            titulo(title),
            sinopsis(sinopsis),
            tags(tags) {}

    const string &getId() const {
        return id;
    }

    const string &getTitulo() const {
        return titulo;
    }

    const string &getSinopsis() const {
        return sinopsis;
    }

    const unordered_set<string> &getTags() const {
        return tags;
    }
    bool operator==(const Pelicula& other) const {
        return titulo == other.titulo;
    }
};
#endif
