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

BOOST_AUTO_TEST_SUITE(distance_check)

// check that the calcDist function in the Graph class is working 
BOOST_AUTO_TEST_CASE(distance_calculator)
{
   	Reader myReader("../../data/cities.json");
   	auto res = myReader.getCities();

   	Graph myGraph(res);

	// BOOST_CHECK(withinRange(myMap.calcDist("New York", "Boston"), 301.6));
	// BOOST_CHECK(withinRange(myMap.calcDist("Portland", "Tucson"), 3748.81));
	// BOOST_CHECK(withinRange(myMap.calcDist("Tulsa", "Tampa"), 1562.9));
}

BOOST_AUTO_TEST_SUITE_END()
