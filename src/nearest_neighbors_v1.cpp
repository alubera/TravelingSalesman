#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include "../include/Graph.hpp"
#include "../include/Node.hpp"

class NearestNeighbors{

     public:
          void calc_nearest_neighbors();
	  std::vector<Node> get_ordered_cities();
	
     private:
          Node random_starting_city();
          Node find_closest_city();
          std::vector<Node> available_cities;
          std::vector<Node> ordered_cities; //list of cities created by nearest neighbors algorithm

};

Node NearestNeighbors::get_ordered_cities(){
     return ordered_cities;
}

Node NearestNeighbors:: random_starting_city(){
     int random_element = rand() % myGraph.getCityNames().size();
     return myGraph.getCityNames[random_element];
}

//***********//
Node NearestNeighbors::find_closest_city(Node current_city){

     double distance(10000.0); //initialize with arbitrarily large value
     Node closest_city;

     //access distances without recalculating??
/*
     for (auto i:available_cities){
          if (CalcDist(current_city, i) < distance){
               distance = CalcDist(current_city, i); //***CalcDist is private function***
               closest_city = i;
          }
     }
*/
     return closest_city;
}


//function to run nearest neighbors algorithm
void NearestNeighbors::calc_nearest_neighbors(){

     //find random city to start from
     Node current_city = random_starting_city();

     //for the remaining cities
     while (available_cities.size() != 0){
          ordered_cities.push_back(current_city);
          if (ordered_cities.size()==1000)
               break;
          available_cities.erase(std::remove(available_cities.begin(), available_cities.end(), current_city), available_cities.end());
          Node next_city = find_closest_city(current_city);
          current_city = next_city;
     }
}

