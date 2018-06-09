#include<list>
#include<vector>
#include<algorithm>
#include<stack>
#include<iostream>
#include<cstdio>
#define MAX_BEADS 1000

using namespace std;

void DFS_path(int first, vector<int> &path, vector<list<int>> connected){
    stack<int> S;   
    S.push(first);
    
    int next = connected[first].front();
    
    connected[first].erase(connected[first].begin());
    connected[next].erase(find(connected[next].begin(),connected[next].end(),first));
    //connected[first].remove(next);
    //connected[next].remove(first);

    while(!S.empty()){
        if(!connected[next].empty()){
            S.push(next);
            int next2 = connected[next].front();
            
            connected[next].erase(connected[next].begin());
            connected[next2].erase(find(connected[next2].begin(),connected[next2].end(),next));
            //connected[next].remove(next2);
            //connected[next2].remove(next);

            next = next2;
        }
        else{
            path.push_back(next);
            next = S.top();
            S.pop();
        }

    }
    path.push_back(first);
}

int main(){
    int case_number;
    scanf("%d", &case_number);
    int print_number = 1;
    
    while(case_number --){
        // read data
        int N;
        scanf("%d", &N);
        
        int first;
        int degrees[MAX_BEADS] = {0};
        vector<list<int>> connected(1000);
        
        for(int i = 0; i < N; i++){
            int first_b, second_b;
            scanf("%d %d", &first_b, &second_b);
            
            connected[first_b].push_back(second_b);
            connected[second_b].push_back(first_b);
            
            degrees[first_b]++;
            degrees[second_b]++;
            
            if(i == 0){
                first = first_b;
            }
        }
        
        //judge if it's an euler cycle
        bool euler_cycle = true;
        for(int i = 0; i < N; i++){
            if(degrees[i]%2 == 1){
                euler_cycle = false;
                break;
            }
        }
        
        //record the path
        vector<int> path;
        if(euler_cycle){
            DFS_path(first, path, connected);
        }
        
        //final print
        printf("Case #%d\n", print_number);
        print_number++;
        
        if(!euler_cycle) printf("some beads may be lost\n");
        else{
            for(int k = 0; k < N; k++) {
                printf("%d %d\n", path[N - k], path[N - k - 1]);
            }
        }
        
        if(case_number) printf("\n");
    }
    return 0;
}