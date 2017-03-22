/* Travelling Salesman Project
 * ACMS 60212
 * Node.hpp
 * class contains info for each city used as point in travelling salesman simulations
 */

#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <boost/functional/hash.hpp>

class Node {

   public:
      Node(std::string,double,double);
      std::string getName() const;
      double getLat() const;
      double getLon() const;
      bool operator==(const Node &) const;

   private:
      std::string cityName;
      double lat;
      double lon;

};

Node::Node(std::string newCity, double newLat, double newLon) {
   cityName = newCity;
   lat = newLat;
   lon = newLon;
}

std::string Node::getName() const {
   return cityName;
}

double Node::getLat() const {
   return lat;
}

double Node::getLon() const {
   return lon;
}

// overload equality operator for use in unordered_set
bool Node::operator==(const Node &other) const {
   return (cityName == other.cityName
            && lat == other.lat
            && lon == other.lon);
}

// key hashing function
// so Node class can be used in an unordered_set
//       (implemented with a hash table)
struct NodeHasher {
   std::size_t operator()(const Node& n) const {
      // use boost functions for optimizations
      using boost::hash_value;
      using boost::hash_combine;

      // start with a hash value of 0
      std::size_t seed = 0;

      // modify "seed" by XORing and bit-shifting in
      // one member of "Key" after the other:
      hash_combine(seed,hash_value(n.getName()));
      hash_combine(seed,hash_value(n.getLat()));
      hash_combine(seed,hash_value(n.getLon()));

      return seed;
   }
};

#endif
