#define BOOST_TEST_DYN_LINK 
#define BOOST_TEST_MODULE myTest

#include <boost/test/included/unit_test.hpp>

#include "../include/Graph.hpp"
#include "../include/Node.hpp"
#include "../include/Reader.hpp"

/*
Function to check whether the predicted distance is within a 10km
bound of the true distance. We permit the predicted distance to be within
a certain range to allow for numerical inaccuracies that may arise in the 
computation.
*/
bool withinRange(double dist_pred, double dist_true)
{
	double lower_bound = dist_true - 5.0;
	double upper_bound = dist_true + 5.0;

	return !(dist_pred < lower_bound) && !(upper_bound < dist_pred); 
}

// struct to create an instance of the reader 
struct ReaderFixture{

   std::string myFile{"../../data/cities.json"};
   Reader myReader;

   ReaderFixture()
   : myReader(myFile)
   {}

   ~ReaderFixture() = default;
};

// struct to create an instance of the node
struct NodeFixture{

   std::string myCity{"myCity"};
   std::string myState{"myState"};
   double myLat{15.35};
   double myLon{-14.53};
   Node myNode;

   NodeFixture()
   : myNode(myCity, myState, myLat, myLon)
   {}

   ~NodeFixture() = default;
};

// struct to create an instance of the graph
struct GraphFixture{

   Reader myReader{"../../data/cities.json"};
   std::vector<Node> res = myReader.getCities();
   Graph myGraph;

   GraphFixture()
   : myGraph(res)
   {}

   ~GraphFixture() = default;
};


BOOST_FIXTURE_TEST_SUITE(TestReader, ReaderFixture)
BOOST_AUTO_TEST_CASE(reader_getter)
{
   auto cities = myReader.getCities();
   const int NUM_CITIES(1000);

   BOOST_CHECK(!cities.empty());
   BOOST_CHECK(cities.size() == NUM_CITIES);
}
BOOST_AUTO_TEST_SUITE_END()


BOOST_FIXTURE_TEST_SUITE(TestNode, NodeFixture)
BOOST_AUTO_TEST_CASE(node_getters)
{
   const std::string TEST_NAME("myCity");
   const std::string TEST_STATE("myState");
   const double TEST_LAT(15.35);
   const double TEST_LON(-14.53);

   auto name = myNode.getName();
   auto state = myNode.getState();
   auto lat = myNode.getLat();
   auto lon = myNode.getLon();

   BOOST_CHECK(name == TEST_NAME);
   BOOST_CHECK(state == TEST_STATE);
   BOOST_CHECK(lat == TEST_LAT);
   BOOST_CHECK(lon == TEST_LON);
}

BOOST_AUTO_TEST_CASE(node_equality)
{
   Node test_node("myCity", "myState", 15.35, -14.53);
   BOOST_CHECK(myNode == test_node);
}
BOOST_AUTO_TEST_SUITE_END()


BOOST_FIXTURE_TEST_SUITE(TestGraph, GraphFixture)
BOOST_AUTO_TEST_CASE(graph_getters)
{
	const int NUM_EDGES(499500);
	const int NUM_CITIES(1000);

	auto cities = myGraph.getCityNames();
   auto lons = myGraph.getCityLons();
   auto lats = myGraph.getCityLats();

	BOOST_CHECK(myGraph.getNumEdges() == NUM_EDGES);

	BOOST_CHECK(cities.size() == NUM_CITIES);
   BOOST_CHECK(!cities.empty());

   BOOST_CHECK(lons.size() == NUM_CITIES);
   BOOST_CHECK(!lons.empty());

   BOOST_CHECK(lats.size() == NUM_CITIES);
   BOOST_CHECK(!lats.empty());
}
BOOST_AUTO_TEST_SUITE_END()
