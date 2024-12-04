#ifndef PROJECTO_PROGRA_3_GRAFOPELICULAS_H
#define PROJECTO_PROGRA_3_GRAFOPELICULAS_H
#include <iostream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <string>
#include <unordered_set>
#include "Pelicula.h"
#include "Nodo.h"
using std::string, std::unordered_map, std::vector, std::istringstream;

// Función para normalizar strings (elimina signos y convierte a minúsculas)
static string normalizarString(const string& str) {
    string resultado;
    for (char c : str) {
        if (isalnum(c) || isspace(c)) {
            resultado += tolower(c);
        }
    }
    return resultado;
}

class GrafoPeliculas {
private:
    unordered_map<string, Nodo*> nodos;               // Nodos de las películas
    unordered_map<string, vector<string>> indiceTags; // Índice inverso para tags

    // Función auxiliar para comparar strings ignorando mayúsculas/minúsculas
    static bool comparaIgnorandoCase(const string& a, const string& b) {
        return std::equal(a.begin(), a.end(), b.begin(), b.end(),
                          [](char a, char b) { return tolower(a) == tolower(b); });
    }

public:
    // Destructor para liberar memoria
    ~GrafoPeliculas() {
        for (const auto& [id, nodo] : nodos) {
            delete nodo;
        }
    }

    // Agregar una película al grafo
    void agregarPelicula(const Pelicula& pelicula) {
        string id = pelicula.getId();
        if (nodos.find(id) == nodos.end()) {
            nodos[id] = new Nodo(id, pelicula);

            // Actualizar el índice de tags
            for (const string& tag : pelicula.getTags()) {
                string tagNormalizado = normalizarString(tag);
                indiceTags[tagNormalizado].push_back(id);
            }
        }
    }

    // Agregar una conexión entre dos películas
    void agregarConexion(const string& idA, const string& idB) {
        auto itA = nodos.find(idA);
        auto itB = nodos.find(idB);

        if (itA != nodos.end() && itB != nodos.end()) {
            itA->second->agregarConexion(itB->second);
            itB->second->agregarConexion(itA->second);
        }
    }

    // Buscar películas por tag utilizando el índice
    vector<Pelicula> busquedaPorTag(const string& tag, int limite = 20) {
        vector<Pelicula> resultado;
        string tagNormalizado = normalizarString(tag);

        // Verificar si el tag existe en el índice
        if (indiceTags.find(tagNormalizado) != indiceTags.end()) {
            for (const string& id : indiceTags[tagNormalizado]) {
                if (resultado.size() == limite) break;
                resultado.push_back(nodos[id]->pelicula);
            }
        }

        return resultado;
    }

    vector<Pelicula> busquedaPorTitulo(const string& titulo, int limite = 10) {
        vector<Pelicula> resultado;
        unordered_set<string> palabrasConsulta;
        istringstream iss(titulo);
        string palabra;

        // Normalizar y dividir el input en palabras
        while (iss >> palabra) {
            palabrasConsulta.insert(normalizarString(palabra));
        }

        for (const auto& [id, nodo] : nodos) {
            unordered_set<string> palabrasTitulo;
            istringstream ist(normalizarString(nodo->pelicula.getTitulo()));
            while (ist >> palabra) {
                palabrasTitulo.insert(palabra);
            }

            // Verificar intersección de palabras
            for (const auto& palabra : palabrasConsulta) {
                if (palabrasTitulo.find(palabra) != palabrasTitulo.end()) {
                    resultado.push_back(nodo->pelicula);
                    break; // Evitar añadir duplicados
                }
            }

            if (resultado.size() == limite) break;
        }

        return resultado;
    }

    // Buscar películas por caracteres en el título
    vector<Pelicula> busquedaPorCaracteres(const string& caracteres, int limite = 5) {
        vector<Pelicula> resultado;
        for (const auto& [id, nodo] : nodos) {
            if (normalizarString(nodo->pelicula.getTitulo()).find(normalizarString(caracteres)) != string::npos) {
                resultado.push_back(nodo->pelicula);
                if (resultado.size() == limite) break;
            }
        }
        return resultado;
    }

    // Buscar películas por palabra en la sinopsis
    vector<Pelicula> busquedaPorPalabraEnSinopsis(const string& palabra, int limite = 10) {
        vector<Pelicula> resultado;
        for (const auto& [id, nodo] : nodos) {
            istringstream iss(nodo->pelicula.getSinopsis());
            string palabraSinopsis;
            while (iss >> palabraSinopsis) {
                if (comparaIgnorandoCase(palabraSinopsis, palabra)) {
                    resultado.push_back(nodo->pelicula);
                    break;
                }
            }
            if (resultado.size() == limite) break;
        }
        return resultado;
    }

    // Búsqueda general con prioridad
    vector<Pelicula> busquedaGeneral(string& consulta, int limite = 10) {
        vector<Pelicula> resultado;
        unordered_set<string> idsEncontrados;

        auto agregarResultadosUnicos = [&](const vector<Pelicula>& nuevosResultados) {
            for (const auto& pelicula : nuevosResultados) {
                if (idsEncontrados.insert(pelicula.getId()).second) {
                    resultado.push_back(pelicula);
                    if (resultado.size() == limite) return true;
                }
            }
            return false;
        };

        bool esTag = false;
        bool esTituloExacto = false;
        bool esPalabraSinopsis = false;

        if (!consulta.empty()) {
            if (consulta.front() == '#') {
                esTag = true;
                consulta.erase(0, 1);
            } else if (consulta.front() == '"' && consulta.back() == '"') {
                esTituloExacto = true;
                consulta = consulta.substr(1, consulta.length() - 2);
            } else if (consulta.front() == '*') {
                esPalabraSinopsis = true;
                consulta.erase(0, 1);
            }
        }

        // Aplicar la búsqueda según el tipo
        if (esTag) {
            agregarResultadosUnicos(busquedaPorTag(consulta, limite));
        } else if (esTituloExacto) {
            agregarResultadosUnicos(busquedaPorTitulo(consulta, limite));
        } else if (esPalabraSinopsis) {
            agregarResultadosUnicos(busquedaPorPalabraEnSinopsis(consulta, limite));
        } else {
            // Búsqueda general en orden de prioridad
            if (agregarResultadosUnicos(busquedaPorCaracteres(consulta, limite))) return resultado;
            if (agregarResultadosUnicos(busquedaPorPalabraEnSinopsis(consulta, limite))) return resultado;
            if (agregarResultadosUnicos(busquedaPorTag(consulta, limite))) return resultado;
            agregarResultadosUnicos(busquedaPorTitulo(consulta, limite));
        }

        return resultado;
    }
};

#endif //PROJECTO_PROGRA_3_GRAFOPELICULAS_H
