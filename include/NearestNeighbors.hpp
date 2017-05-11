/* Travelling Salesman Project
 * ACMS 60212
 * nearest_neighbors.hpp
 * nearest neighbors heuristic
 */


#ifndef NEARESTNEIGHBORS_HPP
#define NEARESTNEIGHBORS_HPP

#include <cstdlib>

#include "Traversals.hpp"

typedef property<edge_weight_t, double> Weight;
typedef adjacency_matrix<undirectedS,no_property,Weight> UGraph;
typedef graph_traits<UGraph>::vertex_descriptor Vertex;

namespace heuristics {

// function to run nearest neighbors algorithm
// TODO: fill in params info
void nearest_neighbors(Graph& myGraph, std::list<Node>& path, std::list<double>& weights, double& totalDist) {

   path.clear();
   weights.clear();

   UGraph& ug = myGraph.getGraphRef();
   auto cities = myGraph.getCityNodes();
   std::list<Vertex> remaining_cities;
   std::vector<Vertex> v_path, min_v_path;
   double minTotalDist = 0.0;

   // start from every city and see what path is shortest
   for (int i = 0; i < num_vertices(ug); ++i) {
      totalDist = 0.0;
      v_path.clear();
      v_path.push_back(vertex(i,ug));

      // fill in list of cities
      // list is used for efficient removal of a city once it has been visited
      remaining_cities.clear();
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
         // add closest city to path
         v_path.push_back(closest_city);
         totalDist += minDist;
      }
      // add starting city to end of path to complete circuit
      Vertex v = vertex(i,ug);
      totalDist += myGraph.getEdgeWeight(edge(v_path.back(),v,ug).first);
      v_path.push_back(v);
      
//      std::cout << "NN: " << i << "\tdistance: " << totalDist << std::endl;
      // keep path with minimum total distance
      if (totalDist < minTotalDist || min_v_path.empty()) {
//         std::cout << "\t\tNEW MIN FOUND" << std::endl;
         min_v_path = v_path;    // vector assignment operator is pretty cool :P
         minTotalDist = totalDist;
      }
   }

   totalDist = minTotalDist;
   // fill path and weight lists
   for (auto it = min_v_path.begin(); it != min_v_path.end(); ++it) {
      path.push_back(cities.at(*it));
      if (it != min_v_path.begin()) {
         weights.push_back(myGraph.getEdgeWeight(edge(*(it-1),*it,ug).first));
      }
   }
}

}  // end namespace

#endif
