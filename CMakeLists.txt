cmake_minimum_required(VERSION 3.26)
project(ProyectoFinalP3)

set(CMAKE_CXX_STANDARD 20)

add_executable(proyectoP3 main.cpp
        main.cpp
        Headers/Usuario.h
        Headers/Repertorio.h
        Headers/GrafosPeliculas.h
        Headers/Pelicula.h
        Headers/ConstructorPelicula.h
        Headers/Nodo.h
        Headers/Busqueda.h
)

