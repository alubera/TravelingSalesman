/* Travelling Salesman Project
 * ACMS 60212
 * Node.hpp
 * class contains info for each city used as point in travelling salesman simulations
 */

#ifndef NODE_H
#define NODE_H

#include <tuple>
#include "boost_types.h"

class Node {

   public:
      /**
      * Constructor. Must take the name of the city and state and its respective coordinates
      * @param newCity is the name of the city
      * @param newState is the name of the state
      * @param newLat is the latitude
      * @param newLon is the longitude 
      */
      Node(std::string,std::string,double,double);
      /**
      * Function that returns the name of a node
      * @returns the name of the city of the node
      */
      std::string getName() const;
      /**
      * Function that returns the name of the state
      * @returns the name of the state of the node
      */
      std::string getState() const;
      /**
      * Function that returns the latitude
      * @returns latitude of node
      */
      double getLat() const;
      /**
      * Function that returns the longitude
      * @returns longitude of node
      */
      double getLon() const;
      /**
      * Overridden boolean operator
      * @param other is the Node that is the point of comparison
      * @returns boolean value whether the two nodes are the same
      */
      bool operator==(const Node &) const;

   private:
      std::string cityName;
      std::string stateName;
      double lat;
      double lon;

};

Node::Node(std::string newCity, std::string newState, double newLat, double newLon) 
      : cityName(newCity),
         stateName(newState),
         lat(newLat),
         lon(newLon) {}

std::string Node::getName() const {
   return cityName;
}

std::string Node::getState() const {
   return stateName;
}

double Node::getLat() const {
   return lat;
}

double Node::getLon() const {
   return lon;
}
/*
std::tuple<std::string,std::string,double,double> Node::getAll() const {
   return make_tuple(cityName,stateName,lat,lon);
}
*/
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
