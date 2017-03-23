/* Travelling Salesman Project
 * ACMS 60212
 * Graph.hpp
 * class will act as data structure to hold all points that travelling salesman will hit
 * all cities are held in an unordered_set to try for most efficient lookups
 */

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <cctype>
#include <cassert>
#include <cmath>
#include <exception>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <tuple>
#include <iostream>

class Graph {
 
   public:
      Graph();
      Graph(const std::string &);
      void addCity(std::string,double,double);
      std::tuple<double,double> getCity(std::string);
      void const printCities();
      double const calcDist(std::string,std::string);

   private:
      // using strings as keys for easy lookup for distance calculations
      // tuple will hold long and lat coordinates
      std::unordered_map<std::string, std::tuple<double,double> > cities;
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
   cities[city] = std::make_tuple(lat,lon);
}

std::tuple<double,double> Graph::getCity(std::string name) {
   // returns tuple (lat,lon)
   // throw assert if city is not in graph
   auto got = cities.find(name);
   assert(got != cities.end());
   return got->second;
}

void const Graph::printCities() {
   // go through all cities printing out relevant info
   for (const auto& city: cities) {
      std::cout << city.first;
      std::cout << "\tLat: " << std::get<0>(city.second);
      std::cout << "\tLon: " << std::get<1>(city.second);
      std::cout << std::endl;
   }
}

double const Graph::calcDist(std::string city1, std::string city2) {

   auto got1 = cities.find(city1);
   auto got2 = cities.find(city2);
   assert(got1 != cities.end() && got2 != cities.end());

   const double EARTH_RADIUS = 6371.0;
   auto lat1 = std::get<0>(got1->second);
   auto lon1 = std::get<1>(got1->second);
   auto lat2 = std::get<0>(got2->second);
   auto lon2 = std::get<1>(got2->second);

   double dLat = (lat1 - lat2) * M_PI / 180;
   double dLon = (lon1 - lon2) * M_PI / 180;

   double hav_dist = ((1.0 - cos(dLat)) / 2.0) + cos(lat1 * M_PI / 180) * cos(lat2 * M_PI / 180)
   * ((1.0 - cos(dLon)) / 2.0);

   return 2.0 * EARTH_RADIUS * asin(sqrt(hav_dist));

}

#endif
