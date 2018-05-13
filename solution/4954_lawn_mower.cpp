#include<iostream>
#include<algorithm>
#include<string>

using namespace std;

int main(){
  // store data
  int nx, ny;
  float w;

  cin >> nx >> ny >> w;
 
  while(nx != 0 || ny != 0 || w != 0.0){

    float length[nx];
    float width[ny];

    for(int i = 0; i < nx; i++){
      cin >> length[i];
    }

    for(int i = 0; i < ny; i++){
      cin >> width[i];
    }
    
    sort(length, length + nx);
    sort(width, width + ny);
    // check the condition
    float range_len[2*nx];
    float range_wid[2*ny];

    for(int i = 0; i < 2*nx; i+=2){
      range_len[i] = length[i/2] - w/2;
      range_len[i + 1] = length[i/2] + w/2;
    }
    
    for(int i = 0; i < 2*ny; i+=2){
      range_wid[i] = width[i/2] - w/2;
      range_wid[i + 1] = width[i/2] + w/2;
    }
    
    bool res = true;
    
    for(int i = 1; i < 2*nx - 1; i+=2){
      if (range_len[i] < range_len[i + 1])
	res = false;
    }
    

    if (range_len[0] > 0) res = false;
    if (range_len[2*nx - 1]  < 75) res = false;
    
    for(int i = 1; i < 2*ny - 1; i+=2){
      if (range_wid[i] < range_wid[i + 1])
	res = false;
    }
    

    if (range_wid[0] > 0) res =false;

    if (range_wid[2*ny - 1] < 100) res = false;

    if(res) cout << "YES" << endl;
    else cout<< "NO" << endl;
    // next loop
    cin >> nx >> ny >> w;
  }
  
  return 0;
}
