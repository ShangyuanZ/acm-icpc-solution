#include<stdio.h>
#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>
#define EPS 0.0001

using namespace std;

struct Point{
    double x,y;
    
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
    
} point[100];

double distance_pe(int i, pair<int,int> edge){ // distance point edge
    pair <double, double> u = make_pair(point[edge.first].x - point[edge.second].x, point[edge.first].y - point[edge.second].y); //line vector
    pair <double, double> ap = make_pair(point[i].x - point[edge.first].x, point[i].y - point[edge.first].y); // AP
    
    double dis = fabs(u.first * ap.second - u.second * ap.first);
    return dis / hypot(u.first, u.second);
}



int most_right(int i, int n){ // return the most right point index for point i
    for(int k = 0; k < n; k ++){
        if (k == i)  continue;
        bool not_this = false;
        
        for(int k2 = 0; k2 < n; k2 ++){
            if (k2 == i || k2 == k)  continue;
            
            pair <double, double> u = make_pair(point[k].x - point[i].x, point[k].y - point[i].y);
            pair <double, double> v = make_pair(point[k2].x - point[i].x, point[k2].y - point[i].y);
            
            if (u.first * v.second - u.second * v.first < 0){
                not_this = true;
                break;
            }
        }
        
        if(not_this) continue;
        else return k;
    }
    return i;
}

vector<int> jarvis(int n){
    vector<int> res;
    //find min
    Point p0 = point[0];
    int p0_index = 0;
    for (int i = 1; i < n; i++){
        if (p0 > point[i]){
            p0 = point[i];
            p0_index = i;
        }
    }
    
    res.push_back(p0_index);
    
    //sort
    int next = most_right(p0_index, n);
    
    while(next != p0_index){
        if(res.size() >= 2){
            int p1 = res[res.size() - 2];
            int p2 = res.back();
            
            pair <double, double> u = make_pair(point[p2].x - point[p1].x, point[p2].y - point[p1].y);
            pair <double, double> v = make_pair(point[next].x - point[p2].x, point[next].y - point[p2].y);
        
            
            if (u.first * v.second - u.second * v.first == 0){
                res.pop_back();
                res.push_back(next);
                next = most_right(next, n);
            }
            else{
                res.push_back(next);
                next = most_right(next, n);
            }
        }
        else{
             res.push_back(next);
             next = most_right(next, n);
             }
    }
    
    return res;
}

int main(){
    int n;
    int case_number = 1;
    scanf("%d", &n);
    
    while(n){
        //load points
        for(int i = 0; i < n; i++){
            scanf("%lf %lf", &point[i].x, &point[i].y);
        }
        
        vector<int> contour = jarvis(n);
        
        vector<double> res; //store the max distance for each point edge couple
        
        for(int j = 1; j < contour.size(); j ++){
            double max1 = 0;
            pair<int, int> edge1 = make_pair(contour[j - 1], contour[j]);
            for(int i = 0; i < contour.size(); i++){
                max1 = max(max1, distance_pe(contour[i], edge1));
            }
            res.push_back(max1);
        }
        
        double max1 = 0;
        pair<int, int> edge2 = make_pair(contour[0], contour.back());
        for(int i = 0; i < contour.size(); i++){
            max1 = max(max1, distance_pe(contour[i], edge2));
        }
        res.push_back(max1);
        
        
        double res_num = *min_element(res.begin(), res.end());
        printf("Case %d: %.2lf\n", case_number, res_num);
        
        scanf("%d", &n);
        case_number++;
        
        contour.clear();
        res.clear();
    }
    return 0;
}
