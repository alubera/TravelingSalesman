

#ifndef BOOST_TYPES_H
#define BOOST_TYPES_H

#include <boost/functional/hash.hpp>
#include <boost/config.hpp>
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

using namespace boost;

typedef property<edge_weight_t, double> Weight;
typedef adjacency_matrix<undirectedS,no_property,Weight> UGraph;
typedef graph_traits<UGraph>::edge_iterator EdgeIterator;
typedef graph_traits<UGraph>::vertex_descriptor Vertex;
typedef graph_traits<UGraph>::vertices_size_type Size;
typedef std::vector<Vertex>::iterator Piter;
typedef std::vector<Size>::iterator Iiter;


#endif
