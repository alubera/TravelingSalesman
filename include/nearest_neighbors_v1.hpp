/* Travelling Salesman Project
 * ACMS 60212
 * nearest_neighbors.hpp
 * nearest neighbors heuristic
 */


#ifndef NEARESTNEIGHBORS_HPP
#define NEARESTNEIGHBORS_HPP

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include "Graph.hpp"
#include "Node.hpp"

class NearestNeighbors{

    public:
        void calc_nearest_neighbors(Graph);
        std::vector<Vertex> get_visited_cities();
        void edge_iterators(Graph);

    private:
        std::set<Vertex> visited_cities; //ordered set for path created by nearest neighbors algorithm
};

Vertex NearestNeighbors::get_visited_cities(){
    return visited_cities;
}

//function to run nearest neighbors algorithm
void NearestNeighbors::calc_nearest_neighbors(Graph myGraph){

    UGraph& ug = myGraph.getGraphRef();

    //find random city vertex to start from
    int starting_num = rand() % 1000;
    Vertex current_city = vertex(starting_num, ug);
    visited_cities.insert(current_city);

    //now for each city
    while (visited_cities.size()<1000){
        //convert current_city vertex into integer and pass integer instead??
        Vertex next_city = edge_iterators(myGraph, current_city); //find the closest city to the current city
        current_city = next_city; //move to that city
        visited_cities.insert(current_city); //add city to ordered set
    }
}

Vertex NearestNeighbors::edge_iterators(Graph myGraph, int startingCity){

    EdgeIterator ei, ei_end;

    UGraph& ug = myGraph.getGraphRef();

    Vertex v = vertex(startingCity,ug);

    UGraph::out_edge_iterator eit, eend;
    std::tie(eit,eend) = out_edges(startingCity,ug);

    double min_edge_weight(10000000.0); //initialize with arbitrarily large value

    for (eit; eit != eend; ++eit) {
//     std::cout << target(*eit,ug) << myGraph.getEdgeWeight(eit) << std::endl;
        const bool is_visited = visited_cities.find( target(*eit, ug) ) != visited_cities.end();
        if (is_visited == false){ //only get edge weights for cities not visited
            double new_weight = myGraph.getEdgeWeight(eit);
            if (new_weight < min_edge_weight){
                min_edge_weight = new_weight;
                Vertex closest_city_vert = target(*eit, ug);
            }
        }
    }
	return closest_city_vert;

}



#endif
