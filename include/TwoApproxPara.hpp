/* Travelling Salesman Project
 * ACMS 60212
 * TwoApproxPara.hpp
 * compute the two-approximation (Double Minimum Spanning Tree) heuristic for TSP
 * PARALLEL VERSION
 */

#ifndef TWOAPPROXPARA_HPP
#define TWOAPPROXPARA_HPP

#include "Traversals.hpp"

typedef property<edge_weight_t, double> Weight;
typedef adjacency_matrix<undirectedS,no_property,Weight> UGraph;

namespace heuristics {

void two_approx_parallel(Graph& myGraph, std::list<Node>& path, std::list<double>& weights, double& totalDist) {

   path.clear();
   weights.clear();
   totalDist = 0;

   UGraph& ug = myGraph.getGraphRef();
   auto cities = myGraph.getCityNodes();
   int graphSize = num_vertices(ug);

   // compute minimum spanning tree into new boost graph sturcture
   MultiGraph mst(graphSize);
   Traversals::compute_mst(ug,mst);

   // duplicate all edges so that an euler cycle can be constructed easily
   Traversals::dup_edges<MultiGraph>(mst);

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
