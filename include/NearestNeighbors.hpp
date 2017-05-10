/* Travelling Salesman Project
 * ACMS 60212
 * nearest_neighbors.hpp
 * nearest neighbors heuristic
 */


#ifndef NEARESTNEIGHBORS_HPP
#define NEARESTNEIGHBORS_HPP

#include <cstdlib>

#include "Traversals.hpp"


// function to run nearest neighbors algorithm
void nearest_neighbors(Graph& myGraph, std::list<Node>& path, std::list<double>& weights) {

   UGraph& ug = myGraph.getGraphRef();
   auto cities = myGraph.getCityNodes();

   // TODO: start from every city
   int starting_num = 0;
   std::vector<Vertex> v_path;
   v_path.push_back(vertex(starting_num,ug));

   std::list<Vertex> remaining_cities;
   // fill in list of cities
   // list is used for efficient removal of a city once it has been visited
   UGraph::vertex_iterator vi, vi_end;
   for (std::tie(vi,vi_end) = vertices(ug); vi != vi_end; ++vi) {
      remaining_cities.push_back(*vi);
   }

   // keep going until every city has been visited
   while (v_path.size() < num_vertices(ug)) {
      // remove last city visited from available
      remaining_cities.remove(v_path.back());

      double minDist(10000000.0); //initialize with arbitrarily large value
      // go through each remaining city to find closest to last in path
      Vertex closest_city;
      for (auto it = remaining_cities.begin(); it != remaining_cities.end(); ++it) {
         double new_weight = myGraph.getEdgeWeight(edge(v_path.back(),*it,ug).first);
         if (new_weight < minDist) {
            minDist = new_weight;
            closest_city = *it;
         }
      }
      v_path.push_back(closest_city);
   }
   // add starting city to end of path to complete circuit
   v_path.push_back(vertex(starting_num,ug));

   // fill path and weight lists
   for (auto it = v_path.begin(); it != v_path.end(); ++it) {
      path.push_back(cities.at(*it));
      if (it != v_path.begin()) {
         weights.push_back(myGraph.getEdgeWeight(edge(*(it-1),*it,ug).first));
      }
   }
}

#endif
