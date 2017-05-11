/* Travelling Salesman Project
 * ACMS 60212
 * Christo.hpp
 * compute Christofides algorithm heuristic for Travelling Salesman Problem
 */

#ifndef TWOAPPROX_HPP
#define TWOAPPROX_HPP

#include "Traversals.hpp"

typedef property<edge_weight_t, double> Weight;
typedef adjacency_matrix<undirectedS,no_property,Weight> UGraph;

namespace heuristics {

void two_approx(Graph& myGraph, std::list<Node>& path, std::list<double>& weights, double& totalDist) {

   path.clear();
   weights.clear();
   totalDist = 0;

   UGraph& ug = myGraph.getGraphRef();
   auto cities = myGraph.getCityNodes();
   int graphSize = num_vertices(ug);

   // compute minimum spanning tree into new boost graph sturcture
   MultiGraph mst(graphSize);
   Traversals::compute_mst(ug,mst);

   // TODO:
   //       1. calculate set of vertices with odd degree in mst
   //       2. for subgraph using these vertices
   //       3. construct a minimum weight perfect matching in that subgraph
   //       4. unite matching and spanning tree to form a eulerian multigraph

   // compute Eulerian Tour of double mst, starting from each vertex
   // mst can be reused, compute euler function needs to be looped
   // weights loop needs to be looped as well since there are never any weight accesses
   //    in compute euler function
   typedef typename graph_traits<MultiGraph>::vertex_descriptor VertexT;
   std::vector<VertexT> v_path, min_v_path;
   double minTrip = 0.0;
   for (int i = 0; i < num_vertices(ug); ++i) {
      Traversals::compute_euler<MultiGraph>(mst,v_path,i);
      totalDist = 0.0;
      for (auto it = v_path.begin()+1; it != v_path.end(); ++it) {
         totalDist += myGraph.getEdgeWeight(edge(*(it-1),*it,ug).first);
      }
//      std::cout << "TWOAPPROX: " << i << "\tdistance: " << totalDist << std::endl;
      if (totalDist < minTrip || min_v_path.empty()) {
//         std::cout << "\t\tNEW MIN FOUND" << std::endl;
         min_v_path = v_path;
         minTrip = totalDist;
      }
   }

   totalDist = minTrip;
   // clean up output for writer class
   for (auto it = min_v_path.begin(); it != min_v_path.end(); ++it) {
      path.push_back(cities.at(*it));
      if (it != min_v_path.begin()) {
         weights.push_back(myGraph.getEdgeWeight(edge(*(it-1),*it,ug).first));
      }
   }

}

}  // end namespace

#endif
