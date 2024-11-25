#ifndef PROYECTOFINALP3_CONSTRUCTORPELICULA_H
#define PROYECTOFINALP3_CONSTRUCTORPELICULA_H

#include <string>
#include <unordered_set>
#include <algorithm>
#include <stdexcept>
#include <regex>
#include "Pelicula.h"

using std::string;

class ConstructorPelicula {
private:
    string id;
    string title;
    string sinopsis;
    unordered_set<std::string> tags;

    void limpiarTexto(std::string& texto) {
        texto.erase(std::remove_if(texto.begin(), texto.end(),
                                   [](unsigned char c) { return std::isspace(c) && c != ' '; }), texto.end());
    }

public:
    ConstructorPelicula& conId(string i) {
        this->id = std::move(i);
        return *this;
    }
    ConstructorPelicula& contitle(std::string t) {
        limpiarTexto(t);
        if (t.empty()) {
            throw std::invalid_argument("El título no puede estar vacío");
        }
        this->title = std::move(t);
        return *this;
    }

    ConstructorPelicula& conSinopsis(std::string s) {
        if (s.length() > 1000000000) {
            throw std::invalid_argument("La sinopsis no puede exceder los 1000000000 caracteres");
        }
        this->sinopsis = std::move(s);
        return *this;
    }

    ConstructorPelicula& agregarTag(const std::string& tag) {
        std::string tagLimpio = tag;
        limpiarTexto(tagLimpio);
        if (!tagLimpio.empty()) {
            this->tags.insert(tagLimpio);
        }
        return *this;
    }

    ConstructorPelicula& conTags(const std::unordered_set<std::string>& nuevasTags) {
        for (const auto& tag : nuevasTags) {
            agregarTag(tag);
        }
        return *this;
    }

    Pelicula construir() {
        if (id.empty()) {
            throw std::runtime_error("No se puede construir una película sin ID");
        }
        if (title.empty()) {
            throw std::runtime_error("No se puede construir una película sin título");
        }
        return Pelicula(std::move(id), std::move(title), std::move(sinopsis), std::move(tags));
    }
};

#endif //PROYECTOFINALP3_CONSTRUCTORPELICULA_H
