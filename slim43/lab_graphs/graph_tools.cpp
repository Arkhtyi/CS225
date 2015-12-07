/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph & graph, Vertex start, Vertex end)
{
	 queue<Vertex> q;
	 unordered_map<Vertex, Vertex> m; 
	 graph.setVertexLabel(start, "UNEXPLORED");
	 q.push(start);
	
	
	while(!q.empty()) {
		 Vertex v = q.front();
		 q.pop();
		 vector<Vertex> adj = graph.getAdjacent(v);
		for(auto vtx = adj.begin(); vtx != adj.end(); vtx++) {
			if(graph.getVertexLabel(*vtx) != "UNEXPLORED") {
				 graph.setEdgeLabel(v, *vtx, "UNEXPLORED");
				 graph.setVertexLabel(*vtx, "UNEXPLORED");
				 q.push(*vtx);
			 } else if(graph.getEdgeLabel(v, *vtx) != "UNEXPLORED") {
			 	graph.setEdgeLabel(v, *vtx, "UNEXPLORED");
			 }
	 	}
 	}
 	
	 //Shortest Path Algorithm
	 graph.setVertexLabel(start, "VISITED");
	 q.push(start);
	
	while(!q.empty()) {
		 Vertex v = q.front();
		 q.pop();
		 vector<Vertex> adj = graph.getAdjacent(v);
		for(auto vtx = adj.begin(); vtx != adj.end(); vtx++) {
			if(graph.getVertexLabel(*vtx) == "UNEXPLORED") {
				 graph.setEdgeLabel(v, *vtx, "DISCOVERY");
				 graph.setVertexLabel(*vtx, "VISITED");
				 q.push(*vtx);
				 m[*vtx] = v; //Mark the vertex's parent
			 } else if(graph.getEdgeLabel(v, *vtx) == "UNEXPLORED") {
			 	graph.setEdgeLabel(v, *vtx, "CROSS");
				 }
		}
	}
		//Determines min path by going to each nodes parent until it hits the root
	int count = 0;
	Vertex curr = end;
	while(curr != start) {
			 graph.setEdgeLabel(curr, m[curr], "MINPATH");
			 curr = m[curr]; //Set curr equal to its parent
			 count += 1;
	}
	
	return count;
}

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph & graph)
{
	
	
	queue<Vertex> Q;
	
	Vertex start = graph.getStartingVertex();
	
	graph.setVertexLabel(start, "UNEXPLORED");
	Q.push(start);
	Vertex tmp1;
	Vertex tmp2;
	
	
	while(!Q.empty()){
		Vertex v = Q.front();
		Q.pop();
		vector<Vertex> adj = graph.getAdjacent(v);
		for(auto vtx = adj.begin(); vtx != adj.end(); vtx++){
			if(graph.getVertexLabel(*vtx) != "UNEXPLORED"){
				graph.setEdgeLabel(v, *vtx, "UNEXPLORED");
				graph.setVertexLabel(*vtx, "UNEXPLORED");
				Q.push(*vtx);
			} else if(graph.getEdgeLabel(v, *vtx) != "UNEXPLORED"){
				graph.setEdgeLabel(v, *vtx, "UNEXPLORED");
			}
			
			tmp1 = v;
			tmp2 = *vtx;
						
		}
	
	}

	int minWeight = graph.getEdgeWeight(tmp1, tmp2);
	
	graph.setVertexLabel(start, "VISITED");
	Q.push(start);
	
	while(!Q.empty()){
		Vertex v = Q.front();
		Q.pop();
		
		vector<Vertex> adj = graph.getAdjacent(v);
		
		for(auto vtx = adj.begin(); vtx != adj.end(); vtx++){
			if(graph.getVertexLabel(*vtx) == "UNEXPLORED"){
				graph.setEdgeLabel(v, *vtx, "DISCOVERY");
				graph.setVertexLabel(*vtx, "VISITED");
				Q.push(*vtx);
			} else if(graph.getEdgeLabel(v, *vtx) == "UNEXPLORED"){
				graph.setEdgeLabel(v, *vtx, "CROSS");
			}
			
			int currWeight = graph.getEdgeWeight(v, *vtx);
			if(currWeight <= minWeight){
				minWeight = currWeight;
				tmp1 = v;
				tmp2 = *vtx;
			}
		}
	
	}

	graph.setEdgeLabel(tmp1, tmp2, "MIN");

    return minWeight;
    
   
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort (http://www.cplusplus.com/reference/algorithm/sort/)
 *  instead of creating a priority queue.
 */
void GraphTools::findMST(Graph & graph)
{
	struct edgeLess{
		bool operator()(const Edge a, const Edge b) const{
			return a.weight < b.weight;
		}
	};
	
	vector<Edge> edges = graph.getEdges();
	int numVerts = graph.getVertices().size();
	sort(edges.begin(), edges.end(), edgeLess());
	DisjointSets s;
	s.addelements(numVerts);
	
	for(auto edge = edges.begin(); edge != edges.end(); edge++){
		if(s.find(edge->source) != s.find(edge->dest)){
			graph.setEdgeLabel(edge->source, edge->dest, "MST");
			s.setunion(edge->source, edge->dest);
		}
	
	}
}
