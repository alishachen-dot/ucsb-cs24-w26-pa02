#include "movies.h"

using namespace std;

movies::movies()
{
    title = "";
    rating = 0.0;
}

movies::movies(string t, double r)
{
    title = t;
    rating = r;
}

string movies::getTitle() const{
    return title;
}

double movies::getRating() const{
    	return rating;
}

void movies::printMovie() const{
    cout << title << ", " << rating;
}
