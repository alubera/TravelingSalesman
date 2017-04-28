/* Travelling Salesman Project
 * ACMS 60212
 * Traverse.hpp
 * collection of functions to help with traversals
 */

#ifndef TRAVERSE_HPP
#define TRAVERSE_HPP

#include "Graph.hpp"
#include "bfs_time_visitor.hpp"

#include <fstream>

void bfs_example(Graph myGraph, std::ofstream& myFile) {

   UGraph& ug = myGraph.getGraphRef();

   int graphSize = num_vertices(ug);

   std::vector<Size> dtime(graphSize);

   Size time = 0;
   bfs_time_visitor<Size*> vis(&dtime[0], time);
   breadth_first_search(ug,vertex(0,ug),visitor(vis));

   // sort vertices by their discover time in new vector
   std::vector<Size> discover_order(graphSize);
   for (int i = 0; i < graphSize; ++i) discover_order[i] = i;
   std::sort(discover_order.begin(),discover_order.end());

   // get city names from Graph
   const auto& names = myGraph.getCityNames();

   // get city lats and lons from Graph
   const auto& lats = myGraph.getCityLats();
   const auto& lons = myGraph.getCityLons();



   // print city names in order
   std::cout << "order of discovery:\n";
   for (auto it = discover_order.begin(); it != discover_order.end(); ++it) {
      std::cout << names[*it] << std::endl;
      std::cout << lats[*it] << " " << lons[*it] << std::endl;
   }

   for (auto it = discover_order.begin(); it != discover_order.end(); ++it) {
      myFile << lats[*it] << " " << lons[*it] << '\n';
   }
   // write lat lon to text file 

}

void mst_example(Graph myGraph)
{
   UGraph& ug = myGraph.getGraphRef();

   int graphSize = num_vertices(ug);

   std::vector < Vertex >
    p(graphSize);

   prim_minimum_spanning_tree(ug, &p[0]);

   for(auto ii = 0; ii < p.size(); ++ii)
   {
      if(p[ii] != ii)
      {
         std::cout << "parent[" << ii << "] = " << p[ii] << std::endl;
      }
      else
      {
         std::cout << "parent[" << ii << "] = no parent" << std::endl;
      }
   }

}

#endif
