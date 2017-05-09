/* Travelling Salesman Project
 * ACMS 60212
 * TwoApprox.hpp
 * compute the two-approximation (Double Minimum Spanning Tree) heuristic for TSP
 */

#ifndef TWOAPPROX_HPP
#define TWOAPPROX_HPP

#include "Traversals.hpp"

void two_approx(Graph& myGraph, std::list<Node>& path, std::list<double>& weights) {

   UGraph& ug = myGraph.getGraphRef();
   auto cities = myGraph.getCityNodes();
   int graphSize = num_vertices(ug);

   // compute minimum spanning tree into new boost graph sturcture
   MultiGraph mst(graphSize);
   Traversals::compute_mst(ug,mst);

   // duplicate all edges so that an euler cycle can be constructed easily
   Traversals::dup_edges<MultiGraph>(mst);

   // compute Eulerian Tour of double mst
   typedef typename graph_traits<MultiGraph>::vertex_descriptor VertexT;
   std::vector<VertexT> v_path;
   Traversals::compute_euler<MultiGraph>(mst,v_path);

   for (auto it = v_path.begin(); it != v_path.end(); ++it) {
      path.push_back(cities.at(*it));
      if (it != v_path.begin()) {
         weights.push_back(myGraph.getEdgeWeight(edge(*(it-1),*it,ug).first));
      }
   }
}

#endif
