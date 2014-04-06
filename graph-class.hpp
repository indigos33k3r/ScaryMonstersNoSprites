//graph-class.hpp
#include <vector>
#include <queue>

typedef unsigned int nodeIndex_t;
typedef double edgeWeight_t;

struct Edge {
	nodeIndex_t start;
	nodeIndex_t end;
	edgeWeight_t cost;
	
	Edge() : start(0), end(0), cost(0) {}
	Edge(nodeIndex_t s, nodeIndex_t e, edgeWeight_t c) : start(s), end(e), cost(c) {}
}; //this struct only used by MST algorithm

class Graph
{
	public:
		Graph(nodeIndex_t numNodes, bool bDirected);
		Graph(const char *iFile, bool bDirected);
		~Graph();

		nodeIndex_t V() const; //Returns number of vertices
		nodeIndex_t E() const; //Returns number of edges
		bool adjacent(nodeIndex_t x, nodeIndex_t y) const;	
		std::vector<nodeIndex_t> neighbors(nodeIndex_t x) const; //Return vector of node indices
		bool removeEdge(nodeIndex_t x, nodeIndex_t y); //Removes an edge
		edgeWeight_t getEdge(nodeIndex_t x, nodeIndex_t y) const; //Gets weight of edge between x and y
		bool setEdge(nodeIndex_t x, nodeIndex_t y, edgeWeight_t w);	//Sets weight of edge between x and y. Returns whether successful

		//Generates a random graph based on params. Does NOT guarantee a constant number of edges for a given density.
		bool randomize(double density, edgeWeight_t weightMin, edgeWeight_t weightMax);

		//Search functions
		std::vector<nodeIndex_t> BFS(nodeIndex_t source, nodeIndex_t dest) const;
		std::vector<nodeIndex_t> Dijkstra(edgeWeight_t &dist, 
			nodeIndex_t source, nodeIndex_t dest) const;
		std::vector<nodeIndex_t> MST(edgeWeight_t &totalCost, nodeIndex_t root) const;

	private:
		edgeWeight_t *m_adjacencyMatrix; //Pointer to array of edge weights, treat like grid of VxV dimensions

	 	nodeIndex_t m_numNodes;

	 	//we'll keep a running count so this is cheap to look up
		nodeIndex_t m_numEdges; 

		//additional state and options
		bool m_bDirected;

		//There's probably a better way to get this behavior. I think vector can be
		//used like a queue...
		//used by BFS function
		std::queue<nodeIndex_t> queueFromVector(std::vector<nodeIndex_t> v) const
		{
			std::queue<nodeIndex_t> q;
			for (nodeIndex_t i = 0; i < v.size(); i++)
				q.push(v[i]);
			return q;
		};

		void updateDistanceToNeighbors(const nodeIndex_t cursor,
			std::vector<edgeWeight_t> &distances,
			std::vector<nodeIndex_t> &parent) const;

		//returns false if there are no more nodes to explore
		bool getNextClosestUnvisited(nodeIndex_t &cursor,
			std::vector<bool> &visited, 
			std::vector<edgeWeight_t> &distances) const;
			
		//returns true if any edges were added
		bool addEdgesToUnvisitedNeighbors(std::vector<Edge> &edges, 
			const std::vector<bool> &visited, nodeIndex_t cursor) const;
			
		//returns index of picked edge. -1 if none found
		int getLeastCostOpenEdge(const std::vector<Edge> &edges,
			const std::vector<bool> &visited) const;
};
