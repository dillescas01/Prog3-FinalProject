#ifndef PROYECTOFINALP3_USUARIO_H
#define PROYECTOFINALP3_USUARIO_H
#include <vector>
#include <string>
#include <iostream>
using namespace std;


class Usuario {
private:
    vector<int> likedMovies;
    vector<int> watchLaterMovies;

    bool yaEsFavorito(int movieIndex) const {
        for (int index : likedMovies) {
            if (index == movieIndex) {
                return true;
            }
        }
        return false;
    }
public:
    void marcarFavorito(int movieIndex) {
        likedMovies.push_back(movieIndex);
        cout << "Movie added to liked list.\n";
    }

    void marcarVerMasTarde(int movieIndex) {
        watchLaterMovies.push_back(movieIndex);
        cout << "Movie added to watch later list.\n";
    }

    /*void showLikedMovies(Database* db) const {
        cout << "Liked Movies:\n";
        for (int index : likedMovies) {
            MovieFactory::displayMovie(MovieFactory::FULL, db->getMovies()[index]);
        }
    }

    void showWatchLaterMovies(Database* db) const {
        cout << "Watch Later Movies:\n";
        for (int index : watchLaterMovies) {
            MovieFactory::displayMovie(MovieFactory::FULL, db->getMovies()[index]);
        }
    }
     */
};
#endif
