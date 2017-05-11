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

typedef property<edge_weight_t, double> Weight;
typedef adjacency_matrix<undirectedS,no_property,Weight> UGraph;
typedef graph_traits<UGraph>::vertex_descriptor Vertex;
typedef graph_traits<UGraph>::edge_descriptor Edge;
typedef graph_traits<UGraph>::edge_iterator EdgeIterator;
typedef graph_traits<UGraph>::vertices_size_type Size;

typedef adjacency_list<listS,vecS,undirectedS> MultiGraph;
typedef graph_traits<MultiGraph>::vertex_descriptor VertexM;
typedef graph_traits<MultiGraph>::edge_iterator EdgeIteratorM;

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

// function computes minimum spanning tree of ug
// then builds a new graph out of it (could be templated)
void compute_mst(UGraph& ug, MultiGraph& mst) {

   int graphSize = num_vertices(ug);
   std::vector<Vertex> p(graphSize);

   prim_minimum_spanning_tree(ug, &p[0]);

   for (auto ii = 0; ii < p.size(); ++ii) {
      if (p[ii] != ii) {
         VertexM u = vertex(ii,mst);
         VertexM v = vertex(p[ii],mst);
         add_edge(u,v,mst);
      }
   }
}

// function goes through all vertices in g and fills in list with those with odd degree
// g can be a generic boost graph type
// v_map will map new vertex number to original vertex number and will be used when
//    merging the graphs together again
template <typename GraphT, typename VertexT = typename graph_traits<GraphT>::vertex_descriptor>
void get_odd_vertices(const GraphT& g, std::list<VertexT>& odd_vertices, std::map<int,int>& v_map) {

   typedef typename graph_traits<GraphT>::vertex_iterator VertexIteratorT;
   VertexIteratorT vi, vi_end;

   // if edges are added here then loop will be infinite
   int v_count = 0;
   for (std::tie(vi,vi_end) = vertices(g); vi != vi_end; ++vi) {
      // add vertex if it has an odd degree
      if (out_degree(*vi,g)%2) {
         v_map[odd_vertices.size()] = v_count;
         odd_vertices.push_back(*vi);
      }
      ++v_count;
   }
}

// function computes perfect matching on graph ug 
// and builds a new graph out of it
// perfect matching will be approximate, not minimum
void perfect_matching(Graph& myGraph, MultiGraph& perfect) {
   
   auto ug = myGraph.getGraphRef();

   // we need a mapof edge weights to edge iterators
   std::map<double,EdgeIterator> all_edges;
   // also a set of vertices that have already been used
   std::set<Vertex> used_vertices;

   // iterate over all edges and put them into the mapping
   EdgeIterator ei, ei_end;
   for (tie(ei,ei_end) = edges(ug); ei != ei_end; ++ei) {
      all_edges[myGraph.getEdgeWeight(*ei)] = ei;
   }

   // traverse edges in order, trying to add smallest to graph first
   // ONLY add edge if neither vertex has been added yet
   for (auto it = all_edges.begin(); it != all_edges.end(); ++it) {
      Vertex u = source(*(it->second),ug);
      Vertex v = target(*(it->second),ug);
      if (used_vertices.find(u) == used_vertices.end() &&
          used_vertices.find(v) == used_vertices.end()) {
         add_edge(u,v,perfect);
         used_vertices.insert(u);
         used_vertices.insert(v);
         if (used_vertices.size() == num_vertices(ug)) break;
      }
   }
}

// function combines two graphs of the same type
// g2 will be added to g1
template <typename GraphT>
void combine(GraphT& g1, GraphT& g2, std::map<int,int>& v_map) {
   
   // got through edges in g2 and add them to g1
   typename graph_traits<GraphT>::edge_iterator ei, ei_end;
   for (std::tie(ei,ei_end) = edges(g2); ei != ei_end; ++ei) {
      add_edge(v_map[source(*ei,g2)],v_map[target(*ei,g2)],g1);
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

// function will compute a Eulerian Tour in graph g
// a Eulerian Tour is a path that visits every edge exactly once
// it is assumed that every edge will have an even degree, so the tour will be a circuit
// this function is also special because vertices already in the path will be skipped
template <typename GraphT, typename VertexT = typename graph_traits<GraphT>::vertex_descriptor>
void compute_euler(const GraphT& g, std::vector<VertexT>& path, int start) {

   typedef typename graph_traits<GraphT>::edge_descriptor EdgeT;

   VertexT start_vertex = vertex(start,g);
   
   std::set<EdgeT> visited_edges;
   std::set<VertexT> used_vs;
   std::vector<VertexT> tmp;
   path.clear();

   tmp.push_back(start_vertex);
   while (!tmp.empty() && (used_vs.size() < num_vertices(g))) {
      VertexT v = tmp.back();
      typename graph_traits<GraphT>::out_edge_iterator ei, ei_end;
      bool has_avail_edge = false;
      // loop through all edges, checking for unmarked
      for (tie(ei,ei_end) = out_edges(v,g); ei != ei_end; ++ei) {
         // if current edge is unmarked
         if (visited_edges.find(*ei) == visited_edges.end()) {
            has_avail_edge = true;
            visited_edges.insert(*ei);
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
            path.push_back(v);
            used_vs.insert(v);
         }
         tmp.pop_back();   // move on to next vertex that was visited
      }
   }
   // push start vertex to complete circuit
   path.push_back(start_vertex);
}


/*
void edge_iterators(Graph myGraph) {

   UGraph& ug = myGraph.getGraphRef();
   auto cities = myGraph.getCityNames();
   UGraph::adjacency_iterator vit, vend;
   std::tie(vit,vend) = boost::adjacent_vertices(0,ug);
   std::copy(vit,vend,std::ostream_iterator<Vertex>{std::cout,"\n"});

   int startingCity = 0;
   Vertex v = vertex(startingCity,ug);

   UGraph::out_edge_iterator eit, eend;
   std::tie(eit,eend) = out_edges(startingCity,ug);

   for (eit; eit != eend; ++eit) {
      std::cout << cities[target(*eit,ug)] << " --> " << myGraph.getEdgeWeight(eit) << std::endl;
   }

   std::for_each(eit,eend,
      [&ug](Edge it)
         {std::cout << get(weights,ug) << '\n';});
}*/

} // end namespace



#endif
