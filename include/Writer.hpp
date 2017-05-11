/* Travelling Salesman Project
 * ACMS 60212
 * Writer.hpp
 * class will have functionality to write output files for visuals in R
 */

#ifndef WRITER_HPP
#define WRITER_HPP

#include <cassert>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <list>

#include "Node.hpp"

class Writer {

   public:
      /**
      * empty default constructor
      */
      Writer();

      /**
      * non-default constructor will take filename and read it
      * @param filename is input file
      */
      Writer(const std::string& filename);

      /**
      * function to write path to output file
      * @param path is list of Nodes in path
      * @param weights is the edge weight
      */
      void writePath(std::list<Node>& path,std::list<double>& weights);

   private:
      /**
      * output file
      */
      std::ofstream fp;
};

Writer::Writer() {};

Writer::Writer(const std::string &filename) {

   fp.open(filename);
   assert(fp);
}

void Writer::writePath(std::list<Node>& path, std::list<double>& weights) {

   auto path_it = path.begin();
   auto weights_it = weights.begin();
   while (path_it != path.end()) {
      fp << path_it->getName() << ',' << path_it->getState() << ',' << path_it->getLat() << ',' << path_it->getLon() << ',';
      if (path_it == path.begin()) {
         fp << 0 << "\n";
      } else {
         fp << *(weights_it++) << "\n";
      }
      ++path_it;
   }
}

#endif
