#include<string>
#include<iostream>
#include<ctype.h>
#define ll long long
using namespace std;

int main(){
	string s;

	while(cin >> s){
		ll number = 0;

		ll re0 = 0;
		ll re1 = 0; 
		ll re2 = 0;

		for(int i = 0; i < s.size(); i++){
			if (isdigit(s[i])){

				ll now0, now1, now2;

				if((s[i] - '0') % 3 == 0){
					now0 = re0 + 1;
					now1 = re1;
					now2 = re2;
				}

				if((s[i] - '0') % 3 == 1){
					now0 = re2;
					now1 = re0 + 1;
					now2 = re1;
				}

				if((s[i] - '0') % 3 == 2){
					now0 = re1;
					now1 = re2;
					now2 = re0 + 1;
				}

				number += now0;

				re0 = now0;
				re1 = now1;
				re2 = now2;

			}
			else{
				re0 = 0;
				re1 = 0;
				re2 = 0;
			}
		}

		cout << number << endl;

	}

	return 0;
}