/* Travelling Salesman Project
 * ACMS 60212
 * Reader.hpp
 * class will have functionality to read json file so that Graph class can make boost
 * graph...necessary because number of vertices is needed when boost graph is constructed
 */

#ifndef READER_HPP
#define READER_HPP

#include <cassert>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Node.hpp"

class Reader {

   public:

      /**
      * empty default constructor
      */
      Reader();

      /**
      * non-default constructor will take a file name and read it
      * @param filename is input data file
      */
      Reader(const std::string &filename);

      /**
      * function to return city Nodes
      * @return vector of Nodes for city info
      */
      std::vector<Node> getCities();

   private:
      /**
      * input file
      */
      std::ifstream fp;
};

Reader::Reader() {};

Reader::Reader(const std::string &filename) {

   fp.open(filename);
   assert(fp);
}

std::vector<Node> Reader::getCities() {

   // not necessary to hold info as a member var, hold it in Graph class
   std::vector<Node> cities;
   std::string line, key, value;
   std::string city, state;
   double lon, lat;
   int i(0), count(0);

   // this parsing is kinda janky...but it gets the job done
   // count var can manipulate how many cities are read in from data
   while (getline(fp,line) && count < 1000) {

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
      if (key != "city" && key!= "state" && key != "latitude" && key != "longitude")
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
      } else if (key == "state") {
         state = value;
      } else if (key == "latitude") {
         lat = std::stod(value);
      } else if (key == "longitude") {
         lon = std::stod(value);
      }

      ++i;
      if (i%4 == 0) {
         Node temp(city,state,lat,lon);
         cities.push_back(temp);
         ++count;
         i = 0;
      }
   }

   return cities;
}

#endif
