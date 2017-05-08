/* Travelling Salesman Project
 * ACMS 60212
 * TwoApprox.hpp
 * compute the two-approximation (Double Minimum Spanning Tree) heuristic for TSP
 */

#ifndef TWOAPPROX_HPP
#define TWOAPPROX_HPP

#include "Traversals.hpp"

void two_approx(Graph myGraph, std::vector<Vertex>& path) {

   UGraph& ug = myGraph.getGraphRef();
   int graphSize = num_vertices(ug);

   // compute minimum spanning tree into new boost graph sturcture
   MultiGraph mst(graphSize);
   Traversals::compute_mst(ug,mst);

   // duplicate all edges so that an euler cycle can be constructed easily
   //Traversals::dup_edges(mst);
}


#endif
