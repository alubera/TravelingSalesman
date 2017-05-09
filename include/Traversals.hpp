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
#include <list>
#include <unordered_set>
#include <set>

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

// function computes minimum spanning tree of ug
// then builds a new graph out of it (could be templated)
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

// function duplicates all edges in g
// g can be a generic boost graph type
template <typename GraphT>
void dup_edges(GraphT& g) {

   // local typedefs (since function is templated)
   typedef typename graph_traits<GraphT>::edge_iterator EdgeIteratorT;
   typedef typename graph_traits<GraphT>::edge_descriptor EdgeDescriptorT;

   EdgeIteratorT ei, ei_end;

   // first get all edges to duplicate in a list
   std::list<EdgeDescriptorT> all_edges;
   // if edges are added here then loop will be infinite
   for (std::tie(ei,ei_end) = edges(g); ei != ei_end; ++ei) {
      all_edges.push_back(*ei);
   }

   // then loop through list to dup edges in graph
   for (auto it = all_edges.begin(); it != all_edges.end(); ++it) {
      add_edge(target(*it,g),source(*it,g),g);
   }
}

template <typename GraphT, typename EdgeT = typename graph_traits<GraphT>::edge_descriptor, typename VertexT = typename graph_traits<GraphT>::vertex_descriptor>
EdgeT check_edge(const VertexT& u, const VertexT& v, const GraphT& g) {

   EdgeT e;
   bool exists;
   tie(e,exists) = edge(u,v,g);
   if (!exists) throw "Error: tried to use an edge that doesn't exist";
   return e;
}

// function will compute a Eulerian Tour in graph g
// a Eulerian Tour is a path that visits every edge exactly once
// it is assumed that every edge will have an even degree, so the tour will be a circuit
template <typename GraphT, typename EdgeT = typename graph_traits<GraphT>::edge_descriptor>
void compute_euler(const GraphT& g, std::vector<EdgeT>& path) {

   typedef typename graph_traits<GraphT>::vertex_descriptor VertexT;

   // TODO: try every vertex as start
   VertexT start_vertex = vertex(0,g);
   
   std::set<EdgeT> visited_edges;
   std::set<VertexT> used_vs;
   std::vector<VertexT> tmp;
   std::vector<VertexT> order;

   tmp.push_back(start_vertex);
   while (!tmp.empty()) {
      VertexT v = tmp.back();
      typename graph_traits<GraphT>::out_edge_iterator ei, ei_end;
      bool has_avail_edge = false;
      // loop through all edges, checking for unmarked
      for (tie(ei,ei_end) = out_edges(v,g); ei != ei_end; ++ei) {
         // if current edge is unmarked
         if (visited_edges.find(*ei) == visited_edges.end()) {
            has_avail_edge = true;
            //EdgeT e = *ei;
            visited_edges.insert(*ei);
            //EdgeT opposite_edge = edge(target(e,g),source(e,g),g).first;
            //visited_edges.insert(opposite_edge);
            if (v == target(*ei,g)) {
               tmp.push_back(source(*ei,g));
            } else {
               tmp.push_back(target(*ei,g));
            }
            break;
         }
      }
      if (!has_avail_edge) {
         // skip vertices that have already been used in path
         // this is called shortcutting
         if (used_vs.find(v) == used_vs.end()) {
            // add edge when there are two vertices to connect
            if (!order.empty()) {
               path.push_back(check_edge(order.back(),v,g));
               order.pop_back();
            }
            std::cout << v << std::endl;
            used_vs.insert(v);
            order.push_back(v);
         }
         tmp.pop_back();   // move on to next vertex that was visited
      }
   }
   // add last edge (should go back to first vertex)
   //path.push_back(check_edge(order.back(),start_vertex,g));
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
