#include <string>
#include <vector>
#include <iostream>
using namespace std;

#pragma once
class movies{
    private:
        string title;
        double rating;
    public:
        movies();
        movies(string t, double r);

        string getTitle() const;
        double getRating() const;

        void printMovie() const;

};
