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
#include <vector>

#include "Node.hpp"

class Graph {

   public:
      /**
      *  Constructor. Must take vector of nodes to create underlying graph
      *  @param cities is a vector of nodes that will be used to make the graph
      *  @see Node
      */
      Graph(const std::vector<Node> &cities);

      /**
      *  function to return the number of edges in the graph
      *  @return number of edges in graph
      */
      int getNumEdges();

      /**
      *  function to return city names
      *  @return vector of city names in graph
      */
      const std::vector<std::string>& getCityNames();

      /**
      *  function to return city lons (used in visualization)
      *  @return vector of city longitudes
      */
      const std::vector<double>& getCityLons();

      /**
      *  function to return city lats (used in visualization)
      *  @return vector of city latitudes
      */
      const std::vector<double>& getCityLats();

      /**
      *  function to return weight of an edge
      *  @param ei is an out edge iterator
      *  @return the edge weight of passed iterator
      */
      double getEdgeWeight(UGraph::out_edge_iterator ei) const;

      /**
      *  Return reference to graph. This is used in traversal algorithms where
      *  direct reference to Boost graph is needed
      *  @return a reference to the underlying Boost graph
      */
      UGraph& getGraphRef() {return ug;}

   private:
      /**
      * boost graph variable that will hold all distances
      */
      UGraph ug;
      /**
      * vector that contains all the nodes in the graph 
      */
      const std::vector<Node> cityNodes;
      /**
      * vector that contains names of all cities in the graph
      */
      std::vector<std::string> cityNames;
      /**
      * vector that contains longitudes of all cities in the graph
      */
      std::vector<double> cityLons;
      /**
      * vector that contains latitudes of all cities in the graph
      */
      std::vector<double> cityLats;
      // property map used for accessing edge weights
      //WeightMap weights;

      /**
      * function to compute the distance for all edges in the graph
      */
      void calcAllEdges();
      
      /**
      * function to calculate the haversine distance between two nodes
      * @param T it1, it2 are iterators that iterate through the nodes in the graph
      * @return the distance between two nodes
      */
      template <typename T> double calcDist(T,T) const;
};

// non-default constructor will take a file name and read it
Graph::Graph(const std::vector<Node> &cities) 
         : ug(cities.size()),
            cityNodes(cities) {

   calcAllEdges();
   for (const auto& node : cityNodes) {
      cityNames.push_back(node.getName()+", "+node.getState());
      cityLats.push_back(node.getLat());
      cityLons.push_back(node.getLon());
   }
   //weights = get(edge_weight,ug);
}

void Graph::calcAllEdges() {
   // add all edges between all cities in adj matrix
   auto start = cityNodes.begin();
   for (auto it = start; it != cityNodes.end(); ++it) {
      // since graph is undirected it only needs to be upper triangular
      // thus, skip all previously calculated cities in each inner loop
      for (auto jt = it+1; jt != cityNodes.end(); ++jt) {
         // add edge between it and jt's indices (corresponding to those cities)
         // calculate distance between those two cities as weight
         double dist = calcDist(it,jt);
         add_edge(it-start,jt-start,Weight(dist),ug);
      }
   }
}

int Graph::getNumEdges() {
   return num_edges(ug);
}

const std::vector<std::string>& Graph::getCityNames() {
   return cityNames;
}

const std::vector<double>& Graph::getCityLons() {
   return cityLons;
}

const std::vector<double>& Graph::getCityLats() {
   return cityLats;
}

double Graph::getEdgeWeight(UGraph::out_edge_iterator ei) const {
   //auto weights = get(edge_weight,ug);
   return get(get(edge_weight,ug),*ei);
}

// template function so that it can be used with auto iterators
template <typename T>
double Graph::calcDist(T it1, T it2) const {

   // computes the haversine distance between two cities
   constexpr double EARTH_RADIUS = 6371.0;
   constexpr double PI = M_PI;

   auto lat1(it1->getLat() * PI / 180);
   auto lon1(it1->getLon() * PI / 180);
   auto lat2(it2->getLat() * PI / 180);
   auto lon2(it2->getLon() * PI / 180);

   double dLat(lat1 - lat2);
   double dLon(lon1 - lon2);

   double hav_dist = ((1.0 - cos(dLat)) / 2.0) + cos(lat1) * cos(lat2)
   * ((1.0 - cos(dLon)) / 2.0);

   return 2.0 * EARTH_RADIUS * asin(sqrt(hav_dist));

}

#endif
