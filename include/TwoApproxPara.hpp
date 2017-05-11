/* Travelling Salesman Project
 * ACMS 60212
 * TwoApproxPara.hpp
 * compute the two-approximation (Double Minimum Spanning Tree) heuristic for TSP
 * PARALLEL VERSION
 */

#ifndef TWOAPPROXPARA_HPP
#define TWOAPPROXPARA_HPP

#include <omp.h>

#include "Traversals.hpp"

typedef property<edge_weight_t, double> Weight;
typedef adjacency_matrix<undirectedS,no_property,Weight> UGraph;

namespace heuristics {

void two_approx_parallel(Graph& myGraph, std::list<Node>& path, std::list<double>& weights, double& pathDist) {

   path.clear();
   weights.clear();

   UGraph& ug = myGraph.getGraphRef();
   auto cities = myGraph.getCityNodes();
   int graphSize = num_vertices(ug);

   // compute minimum spanning tree into new boost graph sturcture
   MultiGraph mst(graphSize);
   Traversals::compute_mst(ug,mst);

   // duplicate all edges so that an euler cycle can be constructed easily
   Traversals::dup_edges<MultiGraph>(mst);

   typedef typename graph_traits<MultiGraph>::vertex_descriptor VertexT;
   std::vector<VertexT> min_v_path;
   double minTrip = 0.0;

   // compute Eulerian Tour of double mst, starting from each vertex
   // mst can be reused, compute euler function needs to be looped
   // weights loop needs to be looped as well since there are never any weight accesses
   //    in compute euler function
   #pragma omp parallel
   {

   double totalDist;
   std::vector<Vertex> v_path;
   #pragma omp single
   std::cout << "number of threads: " << omp_get_num_threads() << std::endl;

   #pragma omp for
   for (int i = 0; i < num_vertices(ug); ++i) {
      Traversals::compute_euler<MultiGraph>(mst,v_path,i);
      totalDist = 0.0;
      for (auto it = v_path.begin()+1; it != v_path.end(); ++it) {
         totalDist += myGraph.getEdgeWeight(edge(*(it-1),*it,ug).first);
      }
//      std::cout << "TWOAPPROX: " << i << "\tdistance: " << totalDist << std::endl;
      #pragma omp critical
      if (totalDist < minTrip || min_v_path.empty()) {
//         std::cout << "\t\tNEW MIN FOUND" << std::endl;
         min_v_path = v_path;
         minTrip = totalDist;
      }
   }

   }  // parallel region

   pathDist = minTrip;
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
