#include<stdio.h>
#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>
#include<set>
#include<map>
#define EPS 0.0001
#define INF 1<<30

using namespace std;

struct Point{
    double x,y,k,q;
    
    Point(){
        x = 0.0; y = 0.0;
    }
    
    Point(double in_x, double in_y): x(in_x), y(in_y) {}
    
    bool operator == (Point pt2) const {
        return (fabs(x - pt2.x) < EPS
                && (fabs(y - pt2.y) < EPS));
    }
    
    bool operator > (Point pt2) const{ // p1 > p2 if p1 more right
        if ((x - pt2.x) > 0) return true;
        else return false;
    }
    
} point[100000];

int main(){
    int N,Q1,Q2,Q3,Q4,Q12,Q23,Q34,Q14,Q1234;
    set<double> set_angle;
    map<double, int> map_angle2;
    map<double, int> map_angle4;
    
    while(scanf("%d", &N) == 1){
        //vector
        set_angle.clear();
        map_angle2.clear();
        map_angle4.clear();
        
        Q1 = 0; Q2=0, Q3=0, Q4=0, Q12=0, Q23=0, Q34=0, Q14=0, Q1234=0;
        
        double C1, C2;
        C1 = 0;
        C2 = 0;
        for(int i = 0; i < N; i++){
            
            scanf("%lf %lf", &point[i].x, &point[i].y);
            if(i == 0){C1 = point[0].x, C2 = point[0].y;}
            point[i].x = point[i].x - C1;
            point[i].y = point[i].y - C2;
            if(point[i].x != 0){
                point[i].k = - point[i].y / point[i].x;
            }
            else point[i].k = INF; //whatever
            
            if(point[i].x == 0 && point[i].y == 0) {point[i].q = 1234; Q1234++;}
            else{
                if (point[i].x == 0 && point[i].y > 0) {point[i].q = 12; Q12++;}
                if (point[i].x == 0 && point[i].y < 0) {point[i].q = 34; Q34++;}
                if (point[i].y == 0 && point[i].x > 0) {point[i].q = 14; Q14++;}
                if (point[i].y == 0 && point[i].x < 0) {point[i].q = 23; Q23++;}
                else{
                    if (point[i].x > 0 && point[i].y > 0) {
                        Q1++;
                        point[i].q = 1;
                    }
                    
                    if (point[i].x > 0 && point[i].y < 0) {
                        point[i].q = 4;
                        Q4++;
                        set_angle.insert(point[i].k);
                        if(map_angle4.count(point[i].k) > 0) map_angle4[point[i].k]++;
                        else map_angle4[point[i].k] = 1;
                    }
                    if (point[i].x < 0 && point[i].y > 0) {
                        point[i].q = 2;
                        Q2++;
                        set_angle.insert(point[i].k);
                        if(map_angle2.count(point[i].k) > 0) map_angle2[point[i].k]++;
                        else map_angle2[point[i].k] = 1;
                    }
                    if (point[i].x < 0 && point[i].y < 0) {
                        Q3++;
                        point[i].q = 3;
                    }
                }
            }
        }
        
        //some variables
        int best_rank;
        int worst_rank;
        
        
        //slope == 0
        best_rank = Q1 + Q2 + Q12 + 1;
        worst_rank = best_rank + Q23 + Q14 + Q1234 - 1;
        
        int tmp_b = best_rank + Q14;
        int tmp_w = worst_rank - Q23;
        
        //other slope
        for (set<double>::iterator it=set_angle.begin(); it!=set_angle.end(); it++){
            //cout << * it << endl;
            if(map_angle2.count(*it) > 0){
                tmp_b -= map_angle2[*it];
            }
            
            if(map_angle4.count(*it) > 0){
                tmp_w += map_angle4[*it];
            }
            
            best_rank = min(best_rank, tmp_b);
            worst_rank = max(worst_rank, tmp_w);
            
            if(map_angle2.count(*it) > 0){
                tmp_w -= map_angle2[*it];
            }
            if(map_angle4.count(*it) > 0){
                tmp_b += map_angle4[*it];
            }
        }
        
        
        // slope == inf
        tmp_b = Q1 + Q4 + Q14 + 1;
        tmp_w = tmp_b + Q12 + Q34 + Q1234 - 1;
        best_rank = min(best_rank, tmp_b);
        worst_rank = max(worst_rank, tmp_w);
        
        //output
        printf("%d %d\n",best_rank, worst_rank);
    }
    
    return 0;
}