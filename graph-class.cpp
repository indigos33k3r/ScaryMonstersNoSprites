//graph-class.cpp
#include "graph-class.hpp"
#include <cstdlib>
#include <iostream>
#include <fstream>

//Graph constructor.
//Allocates memory needed by the adjacency matrix and initializes it.
Graph::Graph(nodeIndex_t numNodes, bool bDirected)
{
	m_numNodes = numNodes;
	m_adjacencyMatrix = new edgeWeight_t[(numNodes * numNodes)];

	m_numEdges = 0;
	for (nodeIndex_t y = 0; y < numNodes; y++)
	{
		for (nodeIndex_t x = 0; x < numNodes; x++)
		{
			//initialize all edge weights to 0 meaning unconnected
			m_adjacencyMatrix[(y * numNodes) + x] = 0;
		}
	}
	m_bDirected = bDirected;
}

Graph::Graph(const char *iFile, bool bDirected)
{

	nodeIndex_t start, end;
	edgeWeight_t cost;
		
	std::ifstream inf(iFile);
	
	if (inf.good())
	{
		//if at least the first line is good, we can initialize the graph like above
		inf >> m_numNodes;
		m_adjacencyMatrix = new edgeWeight_t[(m_numNodes * m_numNodes)];
		
		m_numEdges = 0;
		for (nodeIndex_t y = 0; y < m_numNodes; y++)
		{
			for (nodeIndex_t x = 0; x < m_numNodes; x++)
			{
				//initialize all edge weights to 0 meaning unconnected
				m_adjacencyMatrix[(y * m_numNodes) + x] = 0;
			}
		}
		m_bDirected = bDirected;
	
		//read in edge weights and add them to the graph
		while (true)
		{
			inf >> start >> end;
			inf >> cost;
		
			if (!inf) break;

			setEdge(start, end, cost);
		}
	}
	else
	{
		throw 0;
	}
}

//Graph destructor. Frees allocated memory.
Graph::~Graph()
{
	delete [] m_adjacencyMatrix;
}

//Returns number of vertices
nodeIndex_t Graph::V() const
{
	return m_numNodes;
}

//Returns number of edges
nodeIndex_t Graph::E() const
{
	return m_numEdges;
}

//Returns whether or not two vertices have an edge connecting them
bool Graph::adjacent(nodeIndex_t x, nodeIndex_t y) const
{
	if (getEdge(x, y))
		return true;
	else
		return false;
}

//Returns a vector containing the vertex indices of a given vertex.
std::vector<nodeIndex_t> Graph::neighbors(nodeIndex_t x) const
{
	std::vector<nodeIndex_t> v;
	for (nodeIndex_t i = 0; i < m_numNodes; i++)
	{
		if (adjacent(x, i))
			v.push_back(i);
	}
	return v;
}

//Returns the weight of an edge between two given vertices.
//0 weight means they are not connected.
edgeWeight_t Graph::getEdge(nodeIndex_t x, nodeIndex_t y) const
{
	if (x >= m_numNodes || y >= m_numNodes)
		return 0;

	return m_adjacencyMatrix[(y * m_numNodes) + x];
}

//Sets the weight of an edge and returns whether or not it was sucessful.
bool Graph::setEdge(nodeIndex_t x, nodeIndex_t y, edgeWeight_t w)
{
	if (x >= m_numNodes || y >= m_numNodes)
		return false;

	//update edge count, doesn't care about directedness of the graph
	if (getEdge(x, y) && w == 0)
		m_numEdges--;
	else if (!getEdge(x, y) && w != 0)
		m_numEdges++;

	m_adjacencyMatrix[(y * m_numNodes) + x] = w;
	if (!m_bDirected)
		 m_adjacencyMatrix[(x * m_numNodes) + y] = w; //set edge in opposide direction too

	return true;
}

//Removes an edge from the graph and returns whether sucessful.
bool Graph::removeEdge(nodeIndex_t x, nodeIndex_t y)
{
	if (!getEdge(x, y))
		return false;
	else
	{
		m_adjacencyMatrix[(y * m_numNodes) + x] = 0;
		if (!m_bDirected)
			m_adjacencyMatrix[(x * m_numNodes) + y] = 0; //remove edge in opposide direction as well

		m_numEdges--;
		return true;
	}
}

//Initializes the graph randomly based on the parameters provided
bool Graph::randomize(double edgeDensity, edgeWeight_t weightMin, edgeWeight_t weightMax)
{
	if (edgeDensity > 1.0 || edgeDensity < 0)
		return false;

	int densityDecider = static_cast<int>(edgeDensity * 100);

	for (nodeIndex_t y = 0; y < m_numNodes; y++)
	{
		for (nodeIndex_t x = 0; x < m_numNodes; x++)
		{
			if (x != y) //no self-connected nodes
			{
				int myRand = rand() % 100 + 1; //value between 1 and 100.
				if (myRand <= densityDecider)
				{
					setEdge(x, y, 
						static_cast<edgeWeight_t>(weightMin + rand()/(static_cast<edgeWeight_t>(RAND_MAX/(weightMax - weightMin))))
						);
				}
				else
					setEdge(x, y, 0); //unconnected
			}
		}
	}

	return true;
}

//Breadth first search algorithm.
//Finds the path from source->dest traversing the fewest edges.
std::vector<nodeIndex_t> Graph::BFS(nodeIndex_t source, nodeIndex_t dest) const
{
	std::vector<nodeIndex_t> closed;
	closed.resize(m_numNodes);

	std::vector<nodeIndex_t> parent;
	parent.resize(m_numNodes);
	for (nodeIndex_t i = 0; i < m_numNodes; i++)
	{
		parent[i] = i;
	}

	std::queue<nodeIndex_t> open;

	nodeIndex_t cursor = source; //just to initialize
	open.push(source); //first node we will explore
	while (open.size() > 0 && parent[dest] == dest)
	{
		cursor = open.front();
		open.pop();

		//std::cout << "Exploring node: " << cursor << std::endl;

		std::vector<nodeIndex_t> n = neighbors(cursor);
		for (nodeIndex_t i = 0; i < n.size(); i++)
		{
			//std::cout << "Found neighbor: " << n[i] << std::endl; 
			if (parent[n[i]] == n[i] && n[i] != source)
			{
				open.push(n[i]);
				parent[n[i]] = cursor;
			}
		}
	}

	//now we build a vector that represents the path from source to dest
	std::vector<nodeIndex_t> path;
	if (parent[dest] != dest) //did we find a path to dest?
	{
		nodeIndex_t i = dest;
		path.push_back(dest);
		while (i != source)
		{
			i = parent[i];
			path.push_back(i);
		}
	}

	return path;
}

//Dijkstra's shortest path algorithm. Returns the path from source->dest with lowest cost.
//Value passed back through dist is the cost of the whole path. 0 if none found.
std::vector<nodeIndex_t> Graph::Dijkstra(edgeWeight_t &dist, 
	nodeIndex_t source, nodeIndex_t dest) const
{
	std::vector<bool> visited(m_numNodes, false);
	std::vector<edgeWeight_t> distances(m_numNodes, 65535.0f);
	std::vector<nodeIndex_t> parent;
	parent.resize(m_numNodes);
	for (nodeIndex_t i = 0; i < m_numNodes; i++)
	{
		parent[i] = i;
		//every node is it's own parent for now. We'll adjust this as we find
		//distances.
	}

	nodeIndex_t cursor = source;
	distances[cursor] = 0.0f; //distance to self is none.
	bool bCanReach = true;
	while (!visited[dest] && bCanReach)
	{
		updateDistanceToNeighbors(cursor, distances, parent);
		visited[cursor] = true;
		bCanReach = getNextClosestUnvisited(cursor, visited, distances);
	}

	//now we build a vector that represents the path from source to dest
	std::vector<nodeIndex_t> path;
	if (parent[dest] != dest) //did we find a path to dest?
	{
		nodeIndex_t i = dest;
		path.push_back(dest);
		while (i != source)
		{
			i = parent[i];
			path.push_back(i);
		}
	}
	//std::cout << "Distance of path " << source << " to " << dest << " is " << distances[dest] << std::endl;
	if (path.size() > 0)
		dist = distances[dest];
	else
		dist = 0; //no path!
	
	return path;
}

//Used by Dijkstra's algorithm. Helper function.
void Graph::updateDistanceToNeighbors(const nodeIndex_t cursor,
	std::vector<edgeWeight_t> &distances,
	std::vector<nodeIndex_t> &parent) const
{
	std::vector<nodeIndex_t> n = neighbors(cursor);
	for (nodeIndex_t i = 0; i < n.size(); i++)
	{
		//std::cout << "Dist to " << n[i] << " is " << distances[n[i]] << std::endl;
		edgeWeight_t tentativeDist = distances[cursor] + getEdge(cursor, n[i]);
		if (tentativeDist < distances[n[i]])
		{
			//std::cout << "Updated dist from " << cursor << " to " << n[i] << " to " << tentativeDist << std::endl;
			distances[n[i]] = tentativeDist;
			parent[n[i]] = cursor;
		}
		//std::cout << "Parent of " << n[i] << " is now " << parent[n[i]] << std::endl;
	}
}

//Another helper function used by Dijkstras algorithm.
bool Graph::getNextClosestUnvisited(nodeIndex_t &cursor,
	std::vector<bool> &visited, 
	std::vector<edgeWeight_t> &distances) const
{
	nodeIndex_t closestNode = cursor;
	edgeWeight_t lowestDist = 65535.0f;
	for (nodeIndex_t i = 0; i < m_numNodes; i++)
	{
		//we marked cursor visited before running this, so this implicitly checks
		//that the next closest node isn't the current cursor.
		if (distances[i] < lowestDist && visited[i] == false)
		{
			closestNode = i;
			lowestDist = distances[i];
			//std::cout << "Found a closer node: " << i << std::endl;
		}
	} 
	if (closestNode == cursor)
		return false; //no other nodes to explore!
	else
	{
		cursor = closestNode;
		//std::cout << "Next closest node is " << cursor << " at " << distances[cursor] << std::endl;
		return true;
	}
}

std::vector<nodeIndex_t> Graph::MST(edgeWeight_t &totalCost, nodeIndex_t root) const
{
	std::vector<bool> visited(m_numNodes, false);
	std::vector<Edge> edges;
	std::vector<nodeIndex_t> parent;
	parent.resize(m_numNodes);
	for (nodeIndex_t i = 0; i < m_numNodes; i++)
	{
		parent[i] = i;
	}
	
	//Magic happens here!
	nodeIndex_t cursor = root;
	visited[cursor] = true;
	int lce = 0; 
	while (lce != -1)
	{
		//add edges to unvisited neighboring nodes from cursor
		addEdgesToUnvisitedNeighbors(edges, visited, cursor);
		
		//find least expensive edge with unvisited END
		lce = getLeastCostOpenEdge(edges, visited);
		
		if (lce != -1)
		{
			//set end node to visited
			visited[edges[lce].end] = true;
		
			//set parent of unvisited end to the visited (start) node
			parent[edges[lce].end] = edges[lce].start;
		
			//set end of selected edge to cursor
			cursor = edges[lce].end;
		
			//remove the found edge from the set of edges
			edges.erase(edges.begin()+lce);
		}
	}
	
	//sum the cost of the edges found
	totalCost = 0.0f;
	for (nodeIndex_t i = 0; i < parent.size(); i++)
		totalCost += getEdge(i, parent[i]);
	
	return parent;
}

bool Graph::addEdgesToUnvisitedNeighbors(std::vector<Edge> &edges, 
	const std::vector<bool> &visited, nodeIndex_t cursor) const
{
	bool bModified = false;
	std::vector<nodeIndex_t> n = neighbors(cursor);
	for (unsigned int i = 0; i < n.size(); i++)
	{
		if (!visited[n[i]])
		{
			Edge e(cursor, n[i], getEdge(cursor, n[i]));
			edges.push_back(e);
			bModified = true;
			
			//std::cout << "Added available edge " << e.start << ":" << e.end << "\n";
		}
	}
	
	return bModified;
}

int Graph::getLeastCostOpenEdge(const std::vector<Edge> &edges,
	const std::vector<bool> &visited) const
{
	int lcEdge = -1;
	edgeWeight_t lc = 65535.0f;
	for (unsigned int i = 0; i < edges.size(); i++)
	{
		if (!visited[edges[i].end])
		{
			if (edges[i].cost < lc)
			{
				lcEdge = i;
				lc = edges[i].cost;
			}
		}
	}
	//if (lcEdge != -1)
		//std::cout << "LCE found, " << edges[lcEdge].start << ":" << edges[lcEdge].end << "\n";
	
	return lcEdge;
}
