/* Travelling Salesman Project
 * ACMS 60212
 * Graph.hpp
 * class will act as data structure to hold all points that travelling salesman will hit
 * all cities are held in an unordered_set to try for most efficient lookups
 * READER NEEDS TO BE CALLED FIRST SO THAT GRAPH SIZE IS KNOWN
 */

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "Node.hpp"
#include <boost/config.hpp>
#include <boost/graph/adjacency_matrix.hpp>
#include <cctype>
#include <cassert>
#include <cmath>
#include <exception>
#include <string>
#include <tuple>
#include <iostream>
#include <vector>

using namespace boost;

typedef property<edge_weight_t, double> Weight;
typedef adjacency_matrix<undirectedS,no_property,Weight> UGraph;
//typedef graph_traits<UGraph>::edge_iterator EdgeIterator;

class Graph {

   public:
      Graph(const std::vector<Node> &);
/*      std::tuple<double,double> getCity(std::string);
      void const printCities();
      double const calcDist(std::string,std::string);
*/
   private:
      // boost graph (see typedef for adjacency matrix) will hold all distances
      UGraph ug;
      // implement a data structure so city names and ID's are known?
      const std::vector<Node> cityNames;
};

// non-default constructor will take a file name and read it
Graph::Graph(const std::vector<Node> &cities) 
         : ug(cities.size()),
            cityNames(cities) {
/*
   typename graph_traits<UGraph>::vertex_descriptor u,v;
   typedef typename UGraph::edge_property_type Weight;
   typename property_map<UGraph,edge_weight_t>::type weight = get(edge_weight,ug);
   typename graph_traits<UGraph>::edge_descriptor e1, e2;
   bool found;

   u = vertex(0,ug);
   v = vertex(1,ug);*/
   add_edge(0,1,Weight(10),ug);
}
/*
std::tuple<double,double> Graph::getCity(std::string name) {
   // returns tuple (lat,lon)
   // throw assert if city is not in graph
   auto got = cities.find(name);
   assert(got != cities.end());
   return got->second;
}

void const Graph::printCities() {
   // go through all cities printing out relevant info
   for (const auto& city: cities) {
      std::cout << city.first;
      std::cout << "\tLat: " << std::get<0>(city.second);
      std::cout << "\tLon: " << std::get<1>(city.second);
      std::cout << std::endl;
   }
}

double const Graph::calcDist(std::string city1, std::string city2) {
   // computes the haversine distance between two cities
   // throw assert if either cities is not in graph
   auto got1 = cities.find(city1);
   auto got2 = cities.find(city2);
   assert(got1 != cities.end() && got2 != cities.end());

   const double EARTH_RADIUS(6371.0);
   auto lat1(std::get<0>(got1->second) * M_PI / 180);
   auto lon1(std::get<1>(got1->second) * M_PI / 180);
   auto lat2(std::get<0>(got2->second) * M_PI / 180);
   auto lon2(std::get<1>(got2->second) * M_PI / 180);

   double dLat(lat1 - lat2);
   double dLon(lon1 - lon2);

   double hav_dist = ((1.0 - cos(dLat)) / 2.0) + cos(lat1) * cos(lat2)
   * ((1.0 - cos(dLon)) / 2.0);

   return 2.0 * EARTH_RADIUS * asin(sqrt(hav_dist));

}
*/
#endif
