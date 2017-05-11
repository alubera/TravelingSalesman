// DUMMY DRIVER TO TEST CLASSES

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>

#include "Graph.hpp"
#include "Reader.hpp"
#include "Writer.hpp"
#include "Traversals.hpp"
#include "TwoApprox.hpp"
#include "NearestNeighbors.hpp"
#include "NearestNeighborsPara.hpp"

int main(int argc, char** argv) {
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
   
   std::string dir_name;
   if (argc < 2) {   // assume user is in bin
      dir_name = "../..";
   } else {
      dir_name = argv[1];
   }

   // read json and set up graph
   Reader myReader(dir_name+"/data/cities.json");
   auto res = myReader.getCities();
   Graph myGraph(res);
   std::cout << "STATUS: json file read" << std::endl;

   // some reusable data structures
   std::list<Node> path;
   std::list<double> weights;
   double totalDist;

   // declare timers 
   auto start = std::chrono::system_clock::now();
   auto end = std::chrono::system_clock::now();

   // output for nearest neighbors heuristic
   Writer nnWriter(dir_name+"/output/nn.txt");
   double nn_time(0);
   for(int ii{0}; ii < 5; ++ii)
   {
      start = std::chrono::system_clock::now();
      heuristics::nearest_neighbors(myGraph,path,weights,totalDist);
      end = std::chrono::system_clock::now();
      nn_time += double(end - start);
   }

   nn_time /= 5;
   nnWriter.writePath(path,weights);
   std::cout << "STATUS: nearest neighbors output" << std::endl;
   std::cout << "MEAN EXECUTION TIME: " << nn_time << std::endl;

   // output for parallelized nearest neighbors heuristic
   Writer nnparaWriter(dir_name+"/output/nnpara.txt");
   double nnpara_time(0);
   for(int ii{0}; ii < 5; ++ii)
   {
      start = std::chrono::system_clock::now();
      heuristics::nearest_neighbors_parallel(myGraph,path,weights,totalDist);
      end = std::chrono::system_clock::now();
      nnpara_time += double(end - start);

   }
   nnpara_time /= 5;
   nnparaWriter.writePath(path,weights);
   std::cout << "STATUS: nearest neighbors output" << std::endl;   
   std::cout << "MEAN EXECUTION TIME: " << nnpara_time << std::endl;

   // output for mst heuristic
   Writer dmstWriter(dir_name+"/output/dmst.txt");
   double dmst_time(0);
   for(int ii{0}; ii < 5; ++ii)
   {
      start = std::chrono::system_clock::now();
      heuristics::two_approx(myGraph,path,weights,totalDist);
      end = std::chrono::system_clock::now();
      dmst_time += double(end - start);
   }
   dmst_time /= 5;
   dmstWriter.writePath(path,weights);
   std::cout << "STATUS: double minimun spanning tree output" << std::endl;
   std::cout << "MEAN EXECUTION TIME: " << dmst_time << std::endl;

}
