// Winter'24
// Instructor: Diba Mirza
// Student name: 
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <queue>
#include <sstream>
#include <unordered_map>
using namespace std;

#include "utilities.h"
#include "movies.h"

bool parseLine(string &line, string &movieName, double &movieRating);

int main(int argc, char** argv){
    if (argc < 2){
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[ 0 ] << " moviesFilename prefixFilename " << endl;
        exit(1);
    }

    ifstream movieFile (argv[1]);
 
    if (movieFile.fail()){
        cerr << "Could not open file " << argv[1];
        exit(1);
    }
  
    // Create an object of a STL data-structure to store all the movies
    
    priority_queue<movies, vector<movies>, utilities::alphabetical> alphabeticalMovies;
    set<movies, utilities::alphabetical_2> allMovies;
    string line, movieName;
    double movieRating;
    // Read each file and store the name and rating
    while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
            // Use std::string movieName and double movieRating
            // to construct your Movie objects
            // cout << movieName << " has rating " << movieRating << endl;
            // insert elements into your data structure

	    movies m(movieName, movieRating);
            alphabeticalMovies.push(m);
            allMovies.insert(m);
            
            
    }

    movieFile.close();

    if (argc == 2){
            while(!alphabeticalMovies.empty()){     
                alphabeticalMovies.top().printMovie();
                cout << endl;
		alphabeticalMovies.pop();
            }
            return 0;
    }

    ifstream prefixFile (argv[2]);

    if (prefixFile.fail()) {
        cerr << "Could not open file " << argv[2];
        exit(1);
    }

    vector<string> prefixes;
    unordered_map<string, priority_queue<movies, vector<movies>, utilities::numericalDecreasing>> map;
    while (getline (prefixFile, line)) {
        if (!line.empty()) {
            prefixes.push_back(line);
            movies prefix(line, 0.0);
          
	    priority_queue<movies, vector<movies>, utilities::numericalDecreasing> pq;
            auto it = allMovies.lower_bound(prefix);
	   
            while(it != allMovies.end()){
                string title = it->getTitle();
                if (title.substr(0, line.size()) == line) {
                  //  it->printMovie();
		  //  cout << endl;
                    pq.push(*it);
                    ++it;
                } else {
                    break;
                }
            }
            map[line] = pq; 
        }
    }


    vector<pair<string, movies>> bestMovies;
    //  For each prefix,
    //  Find all movies that have that prefix and store them in an appropriate data structure
    //  If no movie with that prefix exists print the following message
    for(int i = 0; i < prefixes.size(); i++){
        if(map.find(prefixes[i]) != map.end() && !map.find(prefixes[i])->second.empty()){
            bool first = true;
	    priority_queue<movies, vector<movies>,utilities::numericalDecreasing> pqCopy = map[prefixes[i]];
            while(!pqCopy.empty()){
                movies m = pqCopy.top();
                if(first){
                    bestMovies.push_back({prefixes[i], m});
                    first = false;
                }
                m.printMovie();
                cout << endl;
                pqCopy.pop();
            }
	    cout << endl;
        } else{
             cout << "No movies found with prefix "<< prefixes[i] << endl;
        }
    }

    //  For each prefix,
    //  Print the highest rated movie with that prefix if it exists.
    for(auto p : bestMovies){
        cout << "Best movie with prefix " << p.first << " is: " << p.second.getTitle() << " with rating " << std::fixed << std::setprecision(1) << p.second.getRating() << endl;

    }
    
    return 0;
}
/*
 *Runtime Complexity:O(mn(l+logn))
 Avg runtime: 0.109
 1k Movies, Large Prefix List: 0.115
 76k Movies, Medium Prefix List: 0.267


 Space Complexity: O(mn)
 
 I designed my algorithm for lower time complexity rather than space complexity. I focused on having faster searches. I used a hash-map, sets, and priority_queues which all have an element of sorting involved to reduce having to traverse through the entire movie list. I used a set to store all movies in order to be able to efficienty retrieve them when looking for words of a specific prefix. I, then, used a hashmap of type <string, priority_queue> to store such data. This made it easy to find each prefix in the hashmap. 
 * */

bool parseLine(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}
