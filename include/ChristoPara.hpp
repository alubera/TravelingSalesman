/* Travelling Salesman Project
 * ACMS 60212
 * ChristoPara.hpp
 * compute Christofides algorithm heuristic for Travelling Salesman Problem
 * PARALLEL VERSION
 */

#ifndef CHRISTOPARA_HPP
#define CHRISTOPARA_HPP

#include <omp.h>

#include "Traversals.hpp"

typedef property<edge_weight_t, double> Weight;
typedef adjacency_matrix<undirectedS,no_property,Weight> UGraph;

namespace heuristics {

void christofides_parallel(Graph& myGraph, std::list<Node>& path, std::list<double>& weights, double& pathDist) {

   path.clear();
   weights.clear();

   UGraph& ug = myGraph.getGraphRef();
   auto cities = myGraph.getCityNodes();
   int graphSize = num_vertices(ug);

   // compute minimum spanning tree into new boost graph sturcture
   MultiGraph mst(graphSize);
   Traversals::compute_mst(ug,mst);

   // Steps in Christofides algo:
   //       1. calculate set of vertices with odd degree in mst
   //       2. form subgraph using these vertices
   //       3. construct a minimum weight perfect matching in that subgraph
   //       4. unite matching and spanning tree to form a eulerian multigraph
   typedef typename graph_traits<MultiGraph>::vertex_descriptor VertexT;
   std::list<VertexT> odd_vertices;
   std::map<int,int> v_map;
   Traversals::get_odd_vertices(mst,odd_vertices,v_map);

   // get vertices into vector of nodes so that new graph can be made
   std::vector<Node> odd_cities;
   for (auto it = odd_vertices.begin(); it != odd_vertices.end(); ++it) {
      odd_cities.push_back(cities.at(*it));
   }

   // make graph out of these found cities
   Graph oddGraph(odd_cities);

   // make a graph for the perfect matching on odd vertices
   MultiGraph perfect(oddGraph.getCityNodes().size());
   Traversals::perfect_matching(oddGraph,perfect);

   // combine mst and perfect
   Traversals::combine(mst,perfect,v_map);

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
