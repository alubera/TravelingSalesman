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
/*
   // TODO: try to figure out this env var thing
   std::string gitPath;
   gitPath = getenv("GIT_DIR");
  
   std::cout << gitPath << std::endl;
*/
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
   double totalDist;

   // output for nearest neighbors heuristic
   Writer nnWriter("../../output/nn.txt");
   heuristics::nearest_neighbors(myGraph,path,weights,totalDist);
   nnWriter.writePath(path,weights);
   std::cout << "STATUS: nearest neighbors output" << std::endl;

   // output for mst heuristic
   Writer dmstWriter("../../output/dmst.txt");
   heuristics::two_approx(myGraph,path,weights,totalDist);
   dmstWriter.writePath(path,weights);
   std::cout << "STATUS: double minimun spanning tree output" << std::endl;

}
