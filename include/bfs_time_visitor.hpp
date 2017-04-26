
#ifndef BFS_TIME_VISITOR_HPP
#define BFS_TIME_VISITOR_HPP

#include "Graph.hpp"

template <typename TimeMap>
class bfs_time_visitor : public default_bfs_visitor {
   
   typedef typename property_traits<TimeMap>::value_type T;
   
   public:
      bfs_time_visitor(TimeMap tmap, T &t) : m_time(t), m_timemap(tmap) {}

   template <typename Vertex, typename Graph>
   void discover_vertex(Vertex u, const Graph &g) const {
      put(m_timemap,u,m_time++);
   }

   TimeMap m_timemap;
   T &m_time;
};

#endif
