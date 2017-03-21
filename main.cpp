// DUMMY DRIVER TO TEST CLASSES

#include <iostream>
#include "Graph.hpp"

int main() {

   // try out manually adding cities...this should maybe be a private function
/*   Graph myMap;

   myMap.addCity("city1",234.234,3.524);
   myMap.addCity("city2",5786.36,746.746);
   myMap.addCity("city3",346.2,986.5876);
*/

   // non-default constructor reads in file
   Graph myMap("cities.json");

   // try out city get function
   //std::cout << std::get<0>(myMap.getCity("Detroit")) << std::endl;
   // this should throw an abort
   //std::cout << std::get<0>(myMap.getCity("oit")) << std::endl;

   // try out printing function (could be cleaner spacing)
   myMap.printCities();
}
