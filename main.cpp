#include <iostream>
#include "Headers/GrafosPeliculas.h"
#include "Headers/Repertorio.h"
#include "Headers/Busqueda.h"

using namespace std;

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