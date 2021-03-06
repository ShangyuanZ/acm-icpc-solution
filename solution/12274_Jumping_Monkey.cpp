#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>

using namespace std;


bool checked[1 << 21]; //for bfs
int output[1 << 21];
int save_path[1 << 21];


bool bfs(long root, queue<long> Q, long *neighbor, int n){
	Q.push(root);

	while(!Q.empty()){
		int now = Q.front();
		Q.pop();

		for(int i = 0; i < n; i++){ //shot
			int next = 0;
			if(now & (1 << i)){
				for(int j = 0; j < n; j++) 
					if (now & (1 << j) && j != i)
						next = next | neighbor[j];

				
				if (checked[next] == 0){
					checked[next] = 1;
					output[next] = i;
					save_path[next] = now;

					Q.push(next);

					if(next == 0){
						return 1;
					}
				}
			}
		}
	}

	return 0;

}

int main(){

	long neighbor[21];
	queue<long> Q;
	bool exist;
	vector<int> answer;


	int n,m;
	scanf("%d %d", &n, &m);

	

	while(n != 0){
		//exist cycle
		if(n > m + 1){
			printf("Impossible\n");
			scanf("%d %d", &n, &m);
			continue;
		}

		//initialization
		memset(neighbor, 0, sizeof(neighbor));
		memset(checked, 0, sizeof(checked));
		memset(output, 0, sizeof(output));
		memset(save_path, 0, sizeof(save_path));
		while(!Q.empty()) Q.pop();
		answer.clear();
		

		//set edge
		for (int i = 0; i < m; i ++){
			int u,v;
			scanf("%d %d", &u, &v);

			neighbor[u] = neighbor[u] | (1 << v);
			neighbor[v] = neighbor[v] | (1 << u); 
		}

		//bfs
		checked[(1 << 21) - 1] = 1;
		int root = (1 << 21) - 1;

		exist = bfs(root, Q, neighbor, n);

		if(exist){
			for(int i = 0; save_path[i]; i = save_path[i])
				answer.push_back(output[i]);

			printf("%lu:", answer.size());
			for(int i = answer.size() - 1; i >= 0; i--){
				printf(" %d", answer[i]);
			}
			printf("\n");
		}
		else{
			printf("Impossible\n");
		}

		scanf("%d %d", &n, &m);
	}
	return 0;
}