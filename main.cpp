// DUMMY DRIVER TO TEST CLASSES

#include <iostream>
#include "Node.hpp"
#include "Graph.hpp"

int main() {

/*   Graph myMap;

   myMap.addCity("city1",234.234,3.524);
   myMap.addCity("city2",5786.36,746.746);
   myMap.addCity("city3",346.2,986.5876);
*/

   Graph myMap("cities.json");

   myMap.printCities();
}
