#include<stdio.h>
#include<iostream>
#include<cmath>
#define EPS 0.0001
#define PI 3.141592653589793238463

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
    
} point[3];

// angle for 3 points(first as peak)
double angle(Point center, Point p1, Point p2){
    pair<double, double> u = make_pair(p1.x - center.x, p1.y - center.y);
    pair<double, double> v = make_pair(p2.x - center.x, p2.y - center.y);
    
    return acos((u.first * v.first + u.second * v.second) /
                (hypot(u.first, u.second) * hypot(v.first, v.second))) * 180 / PI;
    
}

// equal for double
bool deq(double a, double b){
    return fabs(a - b) < EPS;
}

int main(){
    
    while(scanf("%lf %lf %lf %lf %lf %lf", &point[0].x, &point[0].y,
                                           &point[1].x, &point[1].y,
                                           &point[2].x, &point[2].y) == 6){
        
        double angle1, angle2, angle3;
        
        angle1 = angle(point[0], point[1], point[2]);
        angle2 = angle(point[1], point[2], point[0]);
        angle3 = angle(point[2], point[0], point[1]);
        
        int ans = 0;
        for(int i = 3; i < 1001; i++){
            double angle4 = 180./i;  // angle123 should be multiple of angle4
            if (deq(remainder(angle1 / angle4, 1), 0) || deq(remainder(angle1 / angle4, 1), 1))
                if (deq(remainder(angle2 / angle4, 1), 0) || deq(remainder(angle2 / angle4, 1), 1))
                    if (deq(remainder(angle3 / angle4, 1), 0) || deq(remainder(angle3 / angle4, 1), 1)){
                        ans = i;
                        break;
                    }
            
        }
        
        printf("%d\n", ans);
        
    }
    return 0;
}