//
// Created by leo on 11/20/24.
//

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

class GrafoPeliculas {
private:
    unordered_map<string, Nodo*> nodos;

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

    void agregarPelicula(const Pelicula& pelicula) {
        string id = pelicula.getId();
        if (nodos.find(id) == nodos.end()) {
            nodos[id] = new Nodo(id, pelicula);
        }
    }

    void agregarConexion(const string& idA, const string& idB) {
        auto itA = nodos.find(idA);
        auto itB = nodos.find(idB);

        if (itA != nodos.end() && itB != nodos.end()) {
            itA->second->agregarConexion(itB->second);
            itB->second->agregarConexion(itA->second);
        }
    }

    vector<Pelicula> obtenerPeliculasConectadas(const string& id, int limite = 10) {
        vector<Pelicula> resultado;
        auto it = nodos.find(id);

        if (it != nodos.end()) {
            for (Nodo* nodoConectado : it->second->conexiones) {
                resultado.push_back(nodoConectado->pelicula);
                if (resultado.size() == limite) break;
            }
        }

        return resultado;
    }

    vector<Pelicula> busquedaPorTag(const string& tag, int limite = 20) {
        vector<Pelicula> resultado;
        for (const auto& [id, nodo] : nodos) {
            if (nodo->pelicula.getTags().find(tag) != nodo->pelicula.getTags().end()) {
                resultado.push_back(nodo->pelicula);
                if (resultado.size() == limite) break;
            }
        }
        return resultado;
    }

    vector<Pelicula> busquedaPorTitulo(const string& titulo, int limite = 10) {
        vector<Pelicula> resultado;
        for (const auto& [id, nodo] : nodos) {
            if (comparaIgnorandoCase(nodo->pelicula.getTitulo(), titulo)) {
                resultado.push_back(nodo->pelicula);
                if (resultado.size() == limite) break;
            }
        }
        return resultado;
    }

    vector<Pelicula> busquedaPorCaracteres(const string& caracteres, int limite = 5) {
        vector<Pelicula> resultado;
        for (const auto& [id, nodo] : nodos) {
            if (nodo->pelicula.getTitulo().find(caracteres) != string::npos) {
                resultado.push_back(nodo->pelicula);
                if (resultado.size() == limite) break;
            }
        }
        return resultado;
    }

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