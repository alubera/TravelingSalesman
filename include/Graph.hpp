/* Travelling Salesman Project
 * ACMS 60212
 * Graph.hpp
 * class will act as data structure to hold all points that travelling salesman will hit
 * all cities are held in an unordered_set to try for most efficient lookups
 * READER NEEDS TO BE CALLED FIRST SO THAT GRAPH SIZE IS KNOWN
 */

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <cassert>
#include <cctype>
#include <cmath>
#include <exception>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include <boost/config.hpp>
#include <boost/graph/adjacency_matrix.hpp>

#include "Node.hpp"

using namespace boost;

typedef property<edge_weight_t, double> Weight;
typedef adjacency_matrix<undirectedS,no_property,Weight> UGraph;
typedef graph_traits<UGraph>::edge_iterator EdgeIterator;

class Graph {

   public:
      Graph(const std::vector<Node> &);

      // function to return the number of edges in the graph
      int getNumEdges();

      // function to return city names
      std::vector<Node> getCityNames();


   private:
      // boost graph (see typedef for adjacency matrix) will hold all distances
      UGraph ug;

      // implement a data structure so city names and ID's are known?
      const std::vector<Node> cityNames;

      // function will calculate distances for all edges in graph
      void calcAllEdges();

      // function calculates dist between two iterators from cityNames vector
      template <typename T> double const calcDist(T,T);
};

// non-default constructor will take a file name and read it
Graph::Graph(const std::vector<Node> &cities) 
         : ug(cities.size()),
            cityNames(cities) {

   calcAllEdges();
}

void Graph::calcAllEdges() {
   // add all edges between all cities in adj matrix
   auto start = cityNames.begin();
   for (auto it = start; it != cityNames.end(); ++it) {
      // since graph is undirected it only needs to be upper triangular
      // thus, skip all previously calculated cities in each inner loop
      for (auto jt = it+1; jt != cityNames.end(); ++jt) {
         // add edge between it and jt's indices (corresponding to those cities)
         // calculate distance between those two cities as weight
         double dist = calcDist(it,jt);
         add_edge(it-start,jt-start,Weight(10),ug);
      }
   }
}

int Graph::getNumEdges(){
   return num_edges(ug);
}

std::vector<Node> Graph::getCityNames()
{
   return cityNames;
}


// template function so that it can be used with auto iterators
template <typename T>
double const Graph::calcDist(T it1, T it2) {
   // computes the haversine distance between two cities
   const double EARTH_RADIUS(6371.0);
   auto lat1(it1->getLat() * M_PI / 180);
   auto lon1(it1->getLon() * M_PI / 180);
   auto lat2(it2->getLat() * M_PI / 180);
   auto lon2(it2->getLon() * M_PI / 180);

   double dLat(lat1 - lat2);
   double dLon(lon1 - lon2);

   double hav_dist = ((1.0 - cos(dLat)) / 2.0) + cos(lat1) * cos(lat2)
   * ((1.0 - cos(dLon)) / 2.0);

   return 2.0 * EARTH_RADIUS * asin(sqrt(hav_dist));

}

#endif
