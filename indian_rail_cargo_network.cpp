// C++ Implementation of Ford-Fulkerson Algorithm

#include<bits/stdc++.h>

using namespace std;

#define V 100

/* Returns true of there is a path from source 's' to sink 't' in residual graph.
Also fills parent[] to store the path */

bool bfs(int rGraph[V][V],int s, int t,int parent[])
{
	// Create a visited array and mark all vertices as not visited
	bool visited[V];
	memset(visited,0,sizeof(visited));

	// Create a queue, enque source vertex and mark source vertice as visited
	queue<int> q;
	q.push(s);
	visited[s] = true;
	parent[s] = -1;

	// Standard BFS Loop
	while (!q.empty())
	{
		int u = q.front();
		q.pop();

		for(int v = 0;v < V;v++)
		{
			if(visited[v] == false and rGraph[u][v] > 0)
			{
				q.push(v);
				parent[v] = u;
				visited[v] = true;
			}
		}
	}
	// If we reached sink in BFS starting from source, then return true, else false
	return (visited[t] == true);
}

// Returns the maximum flow from s to t in the given graph
int fordFulkerson(int graph[V][V],int s, int t)
{
	int u,v;

	/* Create a residual graph and fill the residual graph with
	   given capacities in the original graph as residual capacities
	   in residual graph
	*/

	int rGraph[V][V];
	/* Residual graph where rGraph[i][j] indicates 
	   residual capacity of edge from i to j (if there is an edge, If rGraph[i][j] is 0 then, there is not).
	*/

	for(u = 0;u < V;u++){
		for(v = 0;v < V;v++){
			rGraph[u][v] = graph[u][v];
		}
	}

	int parent[V]; // This array is filled by BFS and to store path
	int max_flow = 0; // There is no flow initially

	// Augment the flow while there is a path from source to sink
	while(bfs(rGraph,s,t,parent))
	{
		/* Find the minimal residual capacity of the edges along the 
		   path filled by BFS. Or we can say find the maximum flow
		   through the path found
		*/

		int path_flow = INT_MAX;
		for (v = t;v!=s;v=parent[v])
		{
			u = parent[v];
			path_flow = min(path_flow,rGraph[u][v]);
		}

		/* update residual capacities of the edges and reverse edges along the path */
		for(v = t;v!=s;v = parent[v])
		{
			u = parent[v];
			rGraph[u][v] -= path_flow;
			rGraph[v][u] += path_flow;
		}

		// Add path flow to overall flow
		max_flow += path_flow;
	}

	// Return the overall flow
	return max_flow;
}

// A C++ program for Dijkstra's single source shortest path algorithm
// The program is for adjacency matrix representation of the graph

// A utility function to find the vertex with minimum distance value, from the set of vertices not yet included in the shortest path tree
int minDistance(int dist[],bool sptSet[])
{
	// Initialize min value
	int min = INT_MAX, min_index;
	for(int v = 0;v < V;v++)
	{
		if (sptSet[v] == false and dist[v] <= min)
		{
			min = dist[v], min_index = v;
		}
	}

	return min_index;
}

// A utility function to print the constructed distance array
void printSolution(int dist[])
{
	printf("Vertex \t\t Distance from Source\n");
	for(int i = 0;i < V;i++)
		printf("%d \t\t %d\n",i,dist[i]);
}

// Function that implements Dijkstra's single source shortest path
// for a graph represented using adjacency matrix representation
void dijkstra(int graph[V][V],int src,int parent[V])
{
	int dist[V]; // The output array. dist[i] will hold the shortest distance from src to i
	bool sptSet[V]; // sptSet[i] will be true if vertex i is included in the shortest path tree or shortest distance from src to i is finalized

	// Initialize all distances as INFINITE and sptSet[] as false
	for(int i = 0;i < V;i++)
	{
		dist[i] = INT_MAX, sptSet[i] = false;
	}

	// Distance of source vertex from itself is always 0
	dist[src] = 0;

	// parent of src is src
	parent[src] = src;

	// Find shortest path for all vertices
	for(int count = 0;count < V - 1;count++)
	{
		// Pick the minimum distance vertex from the set of vertices not yet processed.
		// u is always equal to src in the first iteration
		int u = minDistance(dist,sptSet);

		// Mark the picked vertex as processed
		sptSet[u] = true;

		// Update dist value of the adjacent vertices of the picked vertex as processed
		for(int v = 0;v < V;v++)
		{
			// Update dist[v] only if is not in sptSet, there is an edge from u to v
			// and the total weight of the path from src to v through u is smaller that current value of dist[v]
			if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
			{
				dist[v] = dist[u] + graph[u][v];
				parent[v] = u;
			}
		}
	}
	// print the costructed distance array
	//printSolution(dist);
}
int create_network(int network[V][V])
{
	int v,e;
	int src, dest, weight;

	cout << "Enter Number of Vertices\n";
	cin >> v;
	cout << "Enter Number of Edges\n";
	cin >> e;

	for(int i = 0;i < e;i++){
		cin >> src;
		cin >> dest;
		cin >> weight;
		network[src][dest] = weight;
	}

	return v;
}
void initialize_weight_network(int network[V][V],int num_vertices)
{
	for (int i = 0; i < num_vertices; ++i)
	{
		for (int j = 0; j < num_vertices; ++j)
		{
			network[i][j] = 0;
		}
	}
}
void display_network(int network[V][V],int num_vertices)
{
	for (int i = 0; i < num_vertices; ++i)
	{
		for (int j = 0; j < num_vertices; ++j)
		{
			cout << network[i][j] << "\t";
		}
		cout << "\n";
	}
}
void create_train(int network[V][V],int weight_network[V][V],int src, int dest,int number_of_wagons,int weight_of_wagon)
{
	int parent[V];
	dijkstra(network,src,parent);
	for(int u = dest;u != src;u = parent[u])
	{
		weight_network[parent[u]][u] += number_of_wagons*weight_of_wagon;
	}
}
void add_trains(int network[V][V],int weight_network[V][V])
{
	int number_of_trains = 0;
	int weight_of_wagon = 0;
	int number_of_wagons = 0;
	cout << "Enter number of trains\n";
	cin >> number_of_trains;
	cout << "Enter Weight of a wagon\n";
	cin >> weight_of_wagon;

	int src, dest;

	for (int i = 0; i < number_of_trains; ++i)
	{
		cout << "Enter Source :\t";
		cin >> src;
		cout << "Enter Destination :\t";
		cin >> dest;
		cout << "Enter Number of wagons:\t";
		cin >> number_of_wagons;

		create_train(network,weight_network,src,dest,number_of_wagons,weight_of_wagon);
	}

}
// Driver program to test above functions in the above example
int main(int argc, char const *argv[])
{
	// Let us create a graph shown in the above example

	//cout << "The maximum possible flow is " << fordFulkerson(graph,0,5);

	// Run Dijkstra
	//dijkstra(graph,0);

	int num_vertices = 6;
	int network[V][V];
	
	num_vertices = create_network(network);

	display_network(network,num_vertices);

	// Add all the trains
	int weight_network[V][V];
	initialize_weight_network(weight_network,num_vertices);

	cout << "\n";
	display_network(weight_network,num_vertices);

	add_trains(network,weight_network);

	int max_flow = 0;
	int option = 1;
	int src;
	int dest;
	int total_weight;

	cout << "Welcome to Menu Driven Program to check if you can transfer a courier between two stations\n";
	do{
		cout << "Enter Source :\t";
		cin >> src;

		cout << "Enter Destination :\t";
		cin >> dest;

		cout << "Enter Total weight to transfer:\t";
		cin >> total_weight;

		max_flow = fordFulkerson(weight_network,src,dest);

		if(total_weight <= max_flow)
		{
			cout << "Yes this weight can be delivered\n";
		}
		else
		{
			cout << "No! This weight can't be delivered\n";
		}

		cout << "Enter 1 to continue else 0\n";
		cin >> option;
	}
	while(option==1);
	max_flow = fordFulkerson(weight_network,0,5);


	// Let's create the rail network
	//int weight_of_wagon = 10;
	//int number_of_wagons = 20;

	return 0;
}