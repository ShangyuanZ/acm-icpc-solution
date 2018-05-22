#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

int main(){
    int case_number = 0;
    scanf("%d", &case_number);
    
    while(case_number--){
        int m,k;
        long long max_pages = 0;
        long long sum = 0;
        scanf("%d %d", &m, &k);
        
        long long pages[m];
        for(int i = 0; i < m; i++){
            scanf("%lld", &pages[i]);
            sum += pages[i];
            max_pages = max(max_pages, pages[i]);
        }
        
        // find this min_max
        long long left = max_pages;
        long long right = sum;
        
        
        while(left != right){
            long long mid = (left + right)/2;
            
            int num_scriber = 1;
            long long sum_books = 0;
            
            
            for (int i = 0; i < m; i++){
                sum_books += pages[i];
                
                if(sum_books > mid){
                    num_scriber++;
                    sum_books = pages[i];
                }
            }
            
            if(num_scriber > k){
                left = mid + 1;
                continue;
            }
            else{
                right = mid;
                continue;
            }
        }
        
        //slash position
        long long min_max = left;
        
        int exist_slash[m];
        memset(exist_slash, 0, sizeof(exist_slash));
        
        long long sum_books2 = 0;
        int slash_rest = k - 1;
        
        if (k == m){
            for(int j = 0; j < m - 1; j++){
                exist_slash[j] = 1;
            }
        }
        else{
            for (int i = m - 1; i >= 0; i--){
                if(i + 1 == slash_rest ){
                    for(int j = 0; j <= i; j++){
                        exist_slash[j] = 1;
                    }
                    break;
                }
                
                sum_books2 += pages[i];
                
                if(sum_books2 > min_max){
                    exist_slash[i] = 1;
                    sum_books2 = pages[i];
                    slash_rest--;
                }
            }
        }
        
        for (int i = 0; i < m - 1; i++){
            printf("%lld ", pages[i]);
            if(exist_slash[i]) printf("/ ");
        }
        printf("%lld\n", pages[m - 1]);
    }
    
    return 0;
}