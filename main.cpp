//
// Created by leo on 11/20/24.
//

#include <iostream>
#include "headers/GrafosPeliculas.h"
#include "headers/Repertorio.h"
#include "headers/Busqueda.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

int main(){
    Repertorio* repertorio = Repertorio::getInstancia();
    repertorio ->leerCSV("data_corregida.csv");

    GrafoPeliculas grafoPeliculas;
    const auto& peliculas = repertorio-> getPeliculas();
    for (const auto& par:peliculas){
        grafoPeliculas.agregarPelicula(par.second);
    }

    cout << "Cargando..." << endl;


    cout << "-------------------------------------------" << endl;

    realizarBusqueda(grafoPeliculas);

    return 0;
}