//Minimum spanning tree assignment
//Brandon Foltz
//I'm compiling on Linux using g++ 4.6.4
//compile me on Linux with:
//g++ homework3.cpp graph-class.cpp -o homework3 -Wall -std=c++0x
//Style notes: Using tab width == 2 for indentation
//I left commented print statements in that I used for debugging. Feel free to
//uncomment them to get a detailed walkthrough of the search algorithms.
#include <iostream>
#include "graph-class.hpp"

//Prints out the content of a vector from back to front.
void printVec(std::vector<nodeIndex_t> v)
{
	for (unsigned int i = 0; i < v.size(); i++)
	{
		std::cout << "[" << i << "]=" << v[i] << "\n";
	}
}

int main()
{
	try {
		Graph g("sampledata.txt", false);
		std::cout << "Edges printed in the form of [child]=parent\n";
		edgeWeight_t totalCost = 0;
		printVec(g.MST(totalCost, 0));
		std::cout << "Total cost: " << totalCost << std::endl;
	}
	catch (int param) { std::cout << "Exception: " << param; }

	return 0;
}
