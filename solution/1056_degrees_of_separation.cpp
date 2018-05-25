#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>

using namespace std;

template<int size1, int size2>

void BFS(int root, queue<int> &Q, bool *Visited, bool (&relation)[size1][size2], int *degree, int P, int &max_degree ){
	Q.push(root);

	while(!Q.empty()){
		int u = Q.front();
		Q.pop();

		if(Visited[u]) continue;

		Visited[u] = true;
		for(int i = 0; i < P; i++){
			if (relation[u][i] == 1){
				Q.push(i);

				if( degree[i] == 0 && i != root && i != u){
					degree[i] = degree[u] + 1;
					max_degree = max(max_degree, degree[i]);
				//	cout << "degree" << i << " " << degree[i] <<endl;
				}
			}
		}
	}
}

bool disconnected(int P, int *degree){
	int count = 0;
	for(int i = 0; i < P; i++){
		if (degree[i] == 0){
			count++;		
		}
	}
	
	if(count == 1){
		return false;
	}
	else return true;
}

int main(){

	int case_number = 1;
	int P,R;
	scanf("%d %d", &P, &R);

	while(P != 0 || R != 0){
		int max_degree =  0;
		queue <int> Q;
		bool Visited[50] = {0};
		bool relation[50][50] = {};
		int degree[50];
		//load data
		map<string, int> name_map;

		int name_number = 0;

		for(int i = 0; i < R; i++){

			string name1,name2;
			cin >> name1 >> name2;

			if(name_map.count(name1) == 0){
				name_map.insert(pair<string, int> (name1,name_number));
				name_number++;
			}

			if(name_map.count(name2) == 0){
				name_map.insert(pair<string, int> (name2,name_number));
				name_number++;
			}

			relation[name_map[name1]][name_map[name2]] = 1;
			relation[name_map[name2]][name_map[name1]] = 1;		
		}

		//bfs
		for(int i = 0; i < P; i++){
		//	cout << i << "hi"<< endl;
			memset(Visited,0,sizeof(Visited));
			memset(degree,0,sizeof(degree));
			BFS(i, Q, Visited, relation, degree, P, max_degree);
		}	

		if(disconnected(P, degree)){
			cout << "Network " << case_number << ": " << "DISCONNECTED" << endl << endl;
		}
		else{
			cout << "Network " << case_number << ": " << max_degree << endl << endl;
		}

		case_number++;
		scanf("%d %d", &P, &R);
	}
	return 0;
}