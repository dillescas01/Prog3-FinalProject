# Proyecto Programación III: Busqueda de películas en plataforma de Streaming
## Integrantes:
- Diego Roger Illescas Castillo
- Miguel Fernando Ucañani Tintaya
- Leonardo Alberto Montesinos Damian
- Luciana Yangali Cáceres

## Explicación de los Headers:
1. Busqueda.h:
Contiene funciones para interactuar con el usuario y buscar películas en el sistema. Incluye opciones como búsqueda por título, palabras clave en la sinopsis, tags y una búsqueda general. También permite mostrar detalles de las películas y resultados en lotes navegables.

2. ConstructorPelicula.h:
Implementa un patrón de diseño Builder para crear objetos Pelicula de manera flexible y validada. Permite agregar datos como título, sinopsis, y tags, asegurándose de que la información sea válida antes de construir la película.

3. GrafoPeliculas.h:
Implementa un grafo donde cada nodo representa una película, y las conexiones modelan relaciones entre películas. También incluye métodos de búsqueda optimizados mediante índices inversos y normalización de texto.

4. Nodo.h:
Define un nodo del grafo, compuesto por un ID, un objeto Pelicula y conexiones con otros nodos (películas relacionadas). Permite establecer relaciones entre películas para recomendaciones o agrupaciones temáticas.

5. Pelicula.h:
Modelo principal para representar una película. Contiene atributos como ID, título, sinopsis y tags. Implementa métodos para acceder a esta información y permite comparar películas basándose en el título.

6. Repertorio.h:
Gestiona un repositorio único de películas usando el patrón Singleton. Incluye métodos para cargar datos desde archivos CSV y procesarlos, como dividir tags entre comillas y agregar películas al sistema.

7. Usuario.h:
Define las funcionalidades relacionadas con los usuarios del sistema, como su capacidad para realizar búsquedas personalizadas, guardar resultados favoritos, y posiblemente manejar perfiles o preferencias, integrándose con las funcionalidades del buscador.

Cada header organiza y encapsula una parte del sistema, asegurando modularidad y claridad en la implementación del buscador.

## Drive Video del Proyecto:
https://drive.google.com/drive/folders/16Fx7BUdneWP55IoIauK1LDxQnXsoY53c?usp=sharing 
