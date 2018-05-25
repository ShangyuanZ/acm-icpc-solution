#include<cstring>
#include<queue>
#include<vector>
#include<functional>
#include<array>
#include<iostream>

using namespace std;

const int MAX_N = 501;
const int INF = 10000000;

typedef pair<int, int> WeightNode;

//be aware of existence of multiple shortest path
int dijkstra(int S, int D, int (&graph) [MAX_N] [MAX_N], int *distance, array<vector<int>,MAX_N> &path){
	priority_queue<WeightNode, vector<WeightNode>, greater<WeightNode> >Q;

	for(int i = 0; i < MAX_N; i++){
		distance[i] = INF;
	}
	distance[S] = 0;
	Q.push(make_pair(0, S));

	while(!Q.empty()){
		int u = Q.top().second;
		Q.pop();

		if (u == D) break;

		for(int i = 0; i < MAX_N; i++){
			if (graph[u][i] > 0 && graph[u][i] < INF){
				int weight = graph[u][i];

				if(distance[i] >= distance[u] + weight){
					if (distance[i] == distance[u] + weight){
						distance[i] = distance[u] + weight;
						Q.push(make_pair(distance[i],i));
						path[i].push_back(u);
					}
					else{
						distance[i] = distance[u] + weight;
						Q.push(make_pair(distance[i],i));
						path[i].clear();
						path[i].push_back(u);//record path
					}					
				}
			}
		}
	}
	return distance[D];
}

void delete_edge(int S, int D, int (&graph) [MAX_N] [MAX_N], array<vector<int>,MAX_N> &path){ 
	for(int i = 0; i < path[D].size(); i++){
	 	
	 		graph[path[D][i]][D] = INF;
	 		int last_term = path[D][i];

	 		if (last_term != S) 
	 			delete_edge(S, last_term, graph, path);
	 		else{
	 			graph[S][D] = INF;
	 		}	 	
 	}
}


int main(){

	int graph[MAX_N][MAX_N];
	int distance[MAX_N];
	array<vector<int>, MAX_N> path;

	int n_nodes,n_paths;
	int S, D;
	int res;

	scanf("%d %d", &n_nodes, &n_paths);

	while(n_nodes != 0 && n_paths != 0){
		scanf("%d %d", &S, &D);
		int node1, node2, distance_nodes;

		memset(graph, INF, sizeof(graph[0][0]) * 501 * 501);
		for (int i = 0; i < n_nodes; i++){
			graph[i][i] = 0;
		}
		for (int i = 0; i < n_paths; i++){
			scanf("%d %d %d", &node1, &node2, &distance_nodes);
			graph[node1][node2] = distance_nodes;
		}

		memset(distance, INF, sizeof(distance));
		

		//find the shortest
		res = dijkstra(S, D, graph, distance, path);

		
		if (res != INF ){
			//eliminate the shortet
			delete_edge(S, D, graph, path);

			//find the almost shortest
			memset(distance, INF, sizeof(distance));
			for(int i = 0; i < MAX_N; i++){
				path[i].clear();
			}

			res = dijkstra(S, D, graph, distance, path);

			if (res != INF) printf("%d\n", res);
			else printf("-1\n");
		}
		else{
			printf("-1\n");
		}
		scanf("%d %d", &n_nodes, &n_paths);
	}

	return 0;
}