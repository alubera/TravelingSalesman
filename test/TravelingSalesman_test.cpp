#define BOOST_TEST_DYN_LINK 
#define BOOST_TEST_MODULE myTest

#include <boost/test/included/unit_test.hpp>

#include "../include/Graph.hpp"
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


// struct to create an instance of the graph
struct TestFixture{
   Reader myReader{"../../data/cities.json"};
   std::vector<Node> res = myReader.getCities();
   Graph myGraph;

   TestFixture()
   : myGraph(res)
   {}

   ~TestFixture() = default;
};

BOOST_FIXTURE_TEST_SUITE(TestGraph, TestFixture)

// check that the calcDist function in the Graph class is working 
BOOST_AUTO_TEST_CASE(graph_initialization)
{
   	const int NUM_EDGES(499500);
   	const int NUM_CITIES(1000);

   	auto cities = myGraph.getCityNames();

   	BOOST_CHECK(myGraph.getNumEdges() == NUM_EDGES);
   	BOOST_CHECK(cities.size() == NUM_CITIES);
}


BOOST_AUTO_TEST_SUITE_END()
