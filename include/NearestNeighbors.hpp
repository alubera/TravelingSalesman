/* Travelling Salesman Project
 * ACMS 60212
 * nearest_neighbors.hpp
 * nearest neighbors heuristic
 */


#ifndef NEARESTNEIGHBORS_HPP
#define NEARESTNEIGHBORS_HPP

#include <cstdlib>

#include "Traversals.hpp"

class NearestNeighbors{

   public:
      const std::list<Vertex>& get_visited_cities();
      void print_path(Graph&) const;
      void calc_nearest_neighbors(Graph&);

   private:
      // list of vertices for path created by nearest neighbors algorithm
      std::list<Vertex> path;
};

const std::list<Vertex>& NearestNeighbors::get_visited_cities(){
   return path;
}

void NearestNeighbors::print_path(Graph& myGraph) const {
   auto cities = myGraph.getCityNames();
   for (auto it = path.begin(); it != path.end(); ++it) {
      std::cout << cities.at(*it) << std::endl;
   }
}

// function to run nearest neighbors algorithm
void NearestNeighbors::calc_nearest_neighbors(Graph& myGraph){

   UGraph& ug = myGraph.getGraphRef();

   // TODO: start from every city
   int starting_num = 0;
   path.push_back(vertex(starting_num,ug));

   std::list<Vertex> remaining_cities;
   // fill in list of cities
   // list is used for efficient removal of a city once it has been visited
   UGraph::vertex_iterator vi, vi_end;
   for (std::tie(vi,vi_end) = vertices(ug); vi != vi_end; ++vi) {
      remaining_cities.push_back(*vi);
   }

   // keep going until every city has been visited
   while (path.size() < num_vertices(ug)) {
      // remove last city visited from available
      remaining_cities.remove(path.back());

      double minDist(10000000.0); //initialize with arbitrarily large value
      // go through each remaining city to find closest to last in path
      Vertex closest_city;
      for (auto it = remaining_cities.begin(); it != remaining_cities.end(); ++it) {
         double new_weight = myGraph.getEdgeWeight(edge(path.back(),*it,ug).first);
         if (new_weight < minDist){
            minDist = new_weight;
            closest_city = *it;
         }
      }
      path.push_back(closest_city);
   }
   // add starting city to end of path to complete circuit
   path.push_back(vertex(starting_num,ug));

   /*
   // now for each city
   while (visited_cities.size() < 1000) {
//convert current_city vertex into integer and pass integer instead??
Vertex next_city = edge_iterators(myGraph, current_city); //find the closest city to the current city
current_city = next_city; //move to that city
visited_cities.insert(current_city); //add city to ordered set
}*/
}

#endif
