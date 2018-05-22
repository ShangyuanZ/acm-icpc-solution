#include<stdio.h>
#include<cmath>
#include<algorithm>

using namespace std;

int main(){
    
    int n_data; //number of case
    
    scanf("%d", &n_data);
    
    while(n_data--){
        
        int C,N; // capacity, number of packages
        
        scanf("%d %d",&C, &N);
        
        int position_x[N];
        int position_y[N]; 
        int weights[N]; // weight for each package
        
        int sum_weights[N + 1];
        int sum_distance[N];

        int mini_move[N + 1];
        
        mini_move[0] = 0;
        sum_weights[0] = 0;
        
        for (int i = 0; i < N; i ++){
            scanf("%d %d %d", &position_x[i], &position_y[i], &weights[i]);
            if(i == 0){
            	sum_weights[i + 1] = sum_weights[i] + weights[i];
            	sum_distance[i] = position_x[i] + position_y[i];
            }
            else{
            	sum_weights[i + 1] = sum_weights[i] + weights[i];
            	sum_distance[i] = sum_distance[i - 1] + fabs(position_x[i] - position_x[i - 1]) + fabs(position_y[i] - position_y[i - 1]);
            }
            
            mini_move[i + 1] = mini_move[i] + (position_x[i] + position_y[i]) * 2;
                      
            for (int k = i - 1; k >= 0; k--){
                if (sum_weights[i + 1] - sum_weights[k] > C) break;
                else{                    
                    int d2;
                    
                    d2 = mini_move[k] + (position_x[k] + position_y[k]);
                    
                    d2 += sum_distance[i] - sum_distance[k];
                    
                    d2 += position_x[i] + position_y[i];
                    
                    mini_move[i + 1] = min(mini_move[i + 1],d2);
                }       
            }
        }
        
        
        
        printf("%d\n",mini_move[N]);
        
        if (n_data) printf("\n");
        
    }
    
    return 0;
}