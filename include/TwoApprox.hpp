/* Travelling Salesman Project
 * ACMS 60212
 * TwoApprox.hpp
 * compute the two-approximation (Double Minimum Spanning Tree) heuristic for TSP
 */

#ifndef TWOAPPROX_HPP
#define TWOAPPROX_HPP

#include "Traversals.hpp"

void two_approx(Graph myGraph, std::vector<std::string>& path) {

   UGraph& ug = myGraph.getGraphRef();
   auto cities = myGraph.getCityNames();
   int graphSize = num_vertices(ug);

   // compute minimum spanning tree into new boost graph sturcture
   MultiGraph mst(graphSize);
   Traversals::compute_mst(ug,mst);

   // duplicate all edges so that an euler cycle can be constructed easily
   Traversals::dup_edges<MultiGraph>(mst);

   std::cout << num_edges(mst) << std::endl;

   // compute Eulerian Tour of double mst
   typedef typename graph_traits<MultiGraph>::vertex_descriptor VertexT;
   std::vector<VertexT> v_path;
   Traversals::compute_euler<MultiGraph>(mst,v_path);

   for (auto it = v_path.begin(); it != v_path.end(); ++it) {
      std::cout << cities.at(*it);
      if (it+1 != v_path.end()) std::cout << "\t==>\n";
   } std::cout << std::endl;

   // playing around
/*
   typedef typename graph_traits<MultiGraph>::edge_descriptor EdgeT;
   std::set<EdgeT> visited_edges;

   typename graph_traits<MultiGraph>::out_edge_iterator ei, ei_end;
   while (visited_edges.size() < 2) {
      for (tie(ei,ei_end) = out_edges(0,mst); ei != ei_end; ++ei) {
         if (visited_edges.find(*ei) == visited_edges.end()) {
            visited_edges.insert(*ei);
            std::cout << visited_edges.size() << std::endl;
            break;
         } else {
            std::cout << "edge already visited" << std::endl;
         }
      }
   }*/
}

#endif
