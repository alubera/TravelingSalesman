/* Travelling Salesman Project
 * ACMS 60212
 * Traverse.hpp
 * collection of functions to help with traversals
 */

#ifndef TRAVERSE_HPP
#define TRAVERSE_HPP

#include "Graph.hpp"
#include "bfs_time_visitor.hpp"

using namespace boost;

typedef graph_traits<UGraph>::vertex_descriptor Vertex;
typedef graph_traits<UGraph>::vertices_size_type Size;
typedef std::vector<Vertex>::iterator Piter;
typedef std::vector<Size>::iterator Iiter;

void bfs_example(Graph myGraph) {

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

   // print city names in order
   std::cout << "order of discovery:\n";
   for (auto it = discover_order.begin(); it != discover_order.end(); ++it) {
      std::cout << names[*it] << std::endl;
   }
}



#endif
