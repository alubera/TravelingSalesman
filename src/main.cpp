// DUMMY DRIVER TO TEST CLASSES

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "../include/Graph.hpp"
#include "../include/Reader.hpp"
#include "../include/Writer.hpp"
#include "../include/Traversals.hpp"
#include "../include/TwoApprox.hpp"
#include "../include/NearestNeighbors.hpp"

int main() {

<<<<<<< HEAD
   /*****************************************
   *  MOST OF THIS IS NOW DEPRECATED FOR NOW
   *////////////////////////////////////////
  
   // try out manually adding cities...this should maybe be a private function
/*   Graph myMap;

   myMap.addCity("city1",234.234,3.524);
   myMap.addCity("city2",5786.36,746.746);
   myMap.addCity("city3",346.2,986.5876);
*/

   // non-default constructor reads in file
//   Graph myMap("../../data/cities.json");

   // try out city get function
   //std::cout << std::get<0>(myMap.getCity("Detroit")) << std::endl;
   // this should throw an abort
   //std::cout << std::get<0>(myMap.getCity("oit")) << std::endl;

   // try out printing function (could be cleaner spacing)
//   myMap.printCities();

   /*************************************
   *  END DEPRECATED
   *///////////////////////////////////// 


   /**
=======
   // TODO: try to figure out this env var thing
/*
>>>>>>> c95f32695337afd67673fb6ea2e13ce936716ef2
   std::string gitPath;
   gitPath = getenv("GIT_DIR");
  
   std::cout << gitPath << std::endl;
   **/

   /**
   std::string file_path = __FILE__;
   std::string dir_path = file_path.substr(0, file_path.rfind("\\"));
   std::cout << dir_path << std::endl;
   **/


   // read json and set up graph
   Reader myReader("../../data/cities.json");
   auto res = myReader.getCities();
   Graph myGraph(res);
   std::cout << "STATUS: json file read" << std::endl;

   // some reusable data structures
   std::list<Node> path;
   std::list<double> weights;

   // output for nearest neighbors heuristic
   Writer nnWriter("../../output/nn.txt");
   nearest_neighbors(myGraph,path,weights);
   nnWriter.writePath(path,weights);
   std::cout << "STATUS: nearest neighbors output" << std::endl;

   // output for mst heuristic
   Writer dmstWriter("../../output/dmst.txt");
   two_approx(myGraph,path,weights);
   dmstWriter.writePath(path,weights);
   std::cout << "STATUS: double minimun spanning tree output" << std::endl;

}
