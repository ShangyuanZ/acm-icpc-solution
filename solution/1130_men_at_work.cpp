#include<iostream>
#include<algorithm>
#include<queue>
#include<cstring>

using namespace std;

const int MAX_SIZE = 100;
const int MAX_TIME =  2520; // a cycle for state
const int dx[5] = {1, 0,  0, -1, 0};
const int dy[5] = {0, 1, -1,  0, 0};

int BFS(int road_state[MAX_SIZE][MAX_SIZE], int road_time[MAX_SIZE][MAX_SIZE], int road_size, int checked[MAX_SIZE][MAX_SIZE][MAX_SIZE]){
    queue<pair<pair<int, int>, int>> Q;
    pair<pair<int, int>,int > root;
    root = make_pair(make_pair(0,0),0);
    
    Q.push(root);
    
    while(!Q.empty()){
        pair<pair<int, int>,int > u = Q.front();
        Q.pop();
        
        if (checked[u.first.first][u.first.second][u.second])
            continue;
        else
            checked[u.first.first][u.first.second][u.second] = 1;
        
        if (u.first.first == road_size - 1 && u.first.second == road_size - 1)
            return u.second;
        
        
        
        for (int i = 0; i < 5; i++){
            if (u.first.first + dx[i] < 0 || u.first.first + dx[i] >= road_size || u.first.second + dy[i] < 0 || u.first.second - dy[i] >= road_size )
                continue;
            
            if (road_time [u.first.first + dx[i]] [u.first.second + dy[i]] == 0){
                if (road_state [u.first.first + dx[i]] [u.first.second + dy[i]] == 0)
                    continue;
                else{
                    Q.push(make_pair(make_pair(u.first.first + dx[i], u.first.second + dy[i]), (u.second + 1) % MAX_TIME) );
                    continue;
                }
            }
            
            //detect road state change
            int change_indice;
            int next_state;
            if (((u.second + 1 )/ road_time [u.first.first + dx[i]] [u.first.second + dy[i]]) % 2 == 1)
                change_indice = 1;
            else
                change_indice = 0;
            
            if(change_indice)
                next_state =  (road_state [u.first.first + dx[i]] [u.first.second + dy[i]] + 1) % 2;
            else
                next_state = road_state [u.first.first + dx[i]] [u.first.second + dy[i]];
            
            //judge
            if (next_state == 0) continue;
            else{
                Q.push(make_pair(make_pair(u.first.first + dx[i], u.first.second + dy[i]), (u.second + 1) % MAX_TIME) );
                continue;
            }
        }
    }
    
    return -1;
}

int main(){
    int road_size;
    
    int road_state[MAX_SIZE][MAX_SIZE];
    int road_time [MAX_SIZE][MAX_SIZE];
    int checked [MAX_SIZE][MAX_SIZE][MAX_SIZE];

    bool breakline = false;
    
    while(scanf("%d", &road_size) == 1){
        if(breakline) printf("\n");

        breakline = 1;
        //load data
        for (int i = 0; i < road_size; i++){
            getchar();
            for (int j = 0; j <  road_size; j++){
                char sign;
                scanf("%c", &sign);
                
                if(sign == '.') road_state[i][j] = 1;
                if(sign == '*') road_state[i][j] = 0;
            }
        }
        
        
        for (int i = 0; i < road_size; i++){
            for (int j = 0; j <  road_size; j++){
                scanf("%1d", &road_time[i][j]);
            }
        }
        
        memset(checked, 0, sizeof(checked[0][0][0]) * MAX_SIZE * MAX_SIZE * MAX_SIZE);
        
        //bfs
        int res = BFS(road_state, road_time, road_size, checked);
        
        if(res != -1) printf("%d\n", res);
        else printf("NO\n");
        
    }
    
    return 0;
}