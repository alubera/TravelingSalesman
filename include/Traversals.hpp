/* Travelling Salesman Project
 * ACMS 60212
 * Traverse.hpp
 * collection of functions to help with traversals
 */

#ifndef TRAVERSE_HPP
#define TRAVERSE_HPP

#include <fstream>
#include <algorithm>
#include <iterator>
#include <iostream>

#include "Graph.hpp"
#include "bfs_time_visitor.hpp"

// use namespace to clarify functions
namespace Traversals {

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

void mst_example(Graph myGraph) {

   UGraph& ug = myGraph.getGraphRef();
   auto cities = myGraph.getCityNames();

   int graphSize = num_vertices(ug);

   std::vector<Vertex> p(graphSize);

   prim_minimum_spanning_tree(ug, &p[0]);

   for(auto ii = 0; ii < p.size(); ++ii) {
      if(p[ii] != ii) {
         std::cout << "parent of " << cities[ii] << " ==> " << cities[p[ii]] << std::endl;
      } else {
         std::cout << "parent of " << cities[ii] << " ==> no parent" << std::endl;
      }
   }
/*      if(p[ii] != ii) {
         std::cout << "parent[" << ii << "] = " << p[ii] << std::endl;
      } else {
         std::cout << "parent[" << ii << "] = no parent" << std::endl;
      }
   }*/
}

void compute_mst(UGraph& ug, MultiGraph& mst) {

   int graphSize = num_vertices(ug);
   std::vector<Vertex> p(graphSize);

   prim_minimum_spanning_tree(ug, &p[0]);

   for (auto ii = 0; ii < p.size(); ++ii) {
      if (p[ii] != ii) {
         std::cout << "parent of " << ii << " ==> " << p[ii] << std::endl;
         Vertex u = vertex(ii,mst);
         Vertex v = vertex(p[ii],mst);
         add_edge(u,v,mst);
      }
   }
}



void edge_iterators(Graph myGraph) {

   UGraph& ug = myGraph.getGraphRef();
   auto cities = myGraph.getCityNames();
/*
   UGraph::adjacency_iterator vit, vend;
   std::tie(vit,vend) = boost::adjacent_vertices(0,ug);
   std::copy(vit,vend,std::ostream_iterator<Vertex>{std::cout,"\n"});
*/

   int startingCity = 0;
   Vertex v = vertex(startingCity,ug);

   UGraph::out_edge_iterator eit, eend;
   std::tie(eit,eend) = out_edges(startingCity,ug);

   for (eit; eit != eend; ++eit) {
      std::cout << cities[target(*eit,ug)] << " --> " << myGraph.getEdgeWeight(eit) << std::endl;
   }

/*   std::for_each(eit,eend,
      [&ug](Edge it)
         {std::cout << get(weights,ug) << '\n';});
*/
}

} // end namespace



#endif
