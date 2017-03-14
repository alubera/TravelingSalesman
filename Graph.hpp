/* Travelling Salesman Project
 * ACMS 60212
 * Graph.hpp
 * class will act as data structure to hold all points that travelling salesman will hit
 * all cities are held in an unordered_set to try for most efficient lookups
 */

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <unordered_set>
#include "Node.hpp"

class Graph {
 
   public:
      Graph();
      void addCity(std::string,double,double);
      void const printCities();
      double const calcDist(std::string,std::string);

   private:
      std::unordered_set<Node,NodeHasher> cities;    // set to hold all city info
   
};

Graph::Graph() {};

void Graph::addCity(std::string city, double lat, double lon) {
   // just insert new city into graph with given params
   Node temp(city,lat,lon);
   cities.insert(temp);
}

void const Graph::printCities() {
   // go through all cities printing out relevant info
   for (const auto& city: cities) {
      std::cout << city.getName() << std::endl;
      std::cout << "\tLat: " << city.getLat() << std::endl;
      std::cout << "\tLon: " << city.getLon() << std::endl;
   }
}

double const Graph::calcDist(std::string city1, std::string city2) {
   // John will handle this one
}

#endif
