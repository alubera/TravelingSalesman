/* Travelling Salesman Project
 * ACMS 60212
 * Graph.hpp
 * class will act as data structure to hold all points that travelling salesman will hit
 * all cities are held in an unordered_set to try for most efficient lookups
 */

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <cctype>
#include <cassert>
#include <exception>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <iostream>
#include "Node.hpp"

class Graph {
 
   public:
      Graph();
      Graph(const std::string &);
      void addCity(std::string,double,double);
      void const printCities();
      double const calcDist(std::string,std::string);

   private:
      std::unordered_set<Node,NodeHasher> cities;    // set to hold all city info
   
};

Graph::Graph() {};

// non-default constructor will take a file name and read it
Graph::Graph(const std::string &filename) {

   std::ifstream fp(filename);
   std::string line, key, value;
   std::string city;
   double lon, lat;
   int i = 0;

   // this parsing is kinda janky...but it gets the job done
   while (getline(fp,line)) {

      // do all of this for each line in the JSON file
      key.clear();
      value.clear();
      auto s_itr = line.begin();
      // increment string pointer until it hits first character
      while (!isalpha(*s_itr) && s_itr != line.end()) {
         ++s_itr;
      }
      // if line is garbage then move on to the next one
      if (s_itr == line.end())
         continue;
      // add alpha characters to key (see what json key for line is)
      while (isalpha(*s_itr))
         key += *(s_itr++);
      // move on to next line if it is not one we want
      if (key != "city" && key != "latitude" && key != "longitude")
         continue;
      // increment string pointer until it hits next alpha character
      while (!isalnum(*s_itr) && *s_itr != '-')
         ++s_itr;
      // add alpha characters to key (see what json key for line is)
      while (isalnum(*s_itr) || isspace(*s_itr) || *s_itr == '-' || *s_itr == '.' || *s_itr == '\'')
         value += *(s_itr++);

      // insert found info into node in cities set
      if (key == "city") {
         city = value;
      } else if (key == "latitude") {
         lat = std::stod(value);
      } else if (key == "longitude") {
         lon = std::stod(value);
      }

      ++i;
      if (i%3 == 0) {
         addCity(city,lat,lon);
         i = 0;
      }      
   }
}

void Graph::addCity(std::string city, double lat, double lon) {
   // just insert new city into graph with given params
   Node temp(city,lat,lon);
   cities.insert(temp);
}

void const Graph::printCities() {
   // go through all cities printing out relevant info
   for (const auto& city: cities) {
      std::cout << city.getName();
      std::cout << "\tLat: " << city.getLat();
      std::cout << "\tLon: " << city.getLon();
      std::cout << std::endl;
   }
}

double const Graph::calcDist(std::string city1, std::string city2) {
   // John will handle this one
}

#endif
