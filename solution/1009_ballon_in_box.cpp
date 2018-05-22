#include<iostream>
#include<algorithm>
#include<cmath>

using namespace std;

const double PI  =3.141592653589793238463;

double distance_points(int i, int j, int *coordinate_points){
    double dis = pow(coordinate_points[3*i] - coordinate_points[3*j],2);
    dis += pow(coordinate_points[3*i + 1] - coordinate_points[3*j + 1],2);
    dis += pow(coordinate_points[3*i + 2] - coordinate_points[3*j + 2],2);
    
    return sqrt(dis);
}

double min_dis_toconor(int i, int *coordinate_points ,int *cornor){
    double distance = min(fabs(coordinate_points[3*i] - cornor[0]),fabs(coordinate_points[3*i] - cornor[3]));
    distance = min(distance, (double) fabs(coordinate_points[3*i + 1] - cornor[1]));
    distance = min(distance, (double) fabs(coordinate_points[3*i + 1] - cornor[4]));
    distance = min(distance, (double) fabs(coordinate_points[3*i + 2] - cornor[2]));
    distance = min(distance, (double) fabs(coordinate_points[3*i + 2] - cornor[5]));
    
    return distance;
}

int main(){
    
    int n_points;
    int box_number = 1;
    
    scanf("%d",&n_points);
    
    while(n_points){
        int cornor[6];
        int coordinate_points[3 * n_points];
        double max_volume = 0;
        int per[n_points];
        double r[n_points];
        
        scanf("%d %d %d %d %d %d", &cornor[0], &cornor[1], &cornor[2], &cornor[3], &cornor[4], &cornor[5]);
        for(int i = 0; i < n_points; i++){
            scanf("%d %d %d", &coordinate_points[i*3], &coordinate_points[i*3 + 1], &coordinate_points[i*3 + 2]);
            per[i] = i;
            r[i] = 0;
        }
        
        do{
            double volume = 0;
            
            for(int i = 0; i < n_points; i++){
                double radius = min_dis_toconor(per[i], coordinate_points, cornor);
                
                for(int k = i - 1; k >= 0; k--){
                    radius = min(radius, distance_points(per[i], per[k], coordinate_points) - r[per[k]]);
                }
                
                if (radius > 0) r[per[i]] = radius;
                else r[per[i]] = 0;
                
                volume += 4.0/3 * PI * pow(r[per[i]],3);
                
            }
            
            max_volume = max(volume, max_volume);
            
        }while(next_permutation(per, per + n_points));
        
        double rest = fabs(cornor[3] - cornor[0]) * fabs(cornor[4] - cornor[1]) * fabs(cornor[5] - cornor[2]);
        rest = round(rest - max_volume);
        
        printf("Box %d: %.0f\n\n",box_number, rest);
        box_number++;
        
        scanf("%d", &n_points);
    }
    
    return 0;
}