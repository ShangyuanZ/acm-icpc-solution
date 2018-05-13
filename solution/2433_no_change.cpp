#include <iostream>

using namespace std;

int main(){

	int n_data;

	cin >> n_data;

	while (n_data--){

		// get the data
		int x,k;
		
		cin >> x >> k;

		int v[k];

		int array[100000] = {0};

		for(int i = 0; i < k; i++){
			cin >> v[i];
		}

		array[v[0] - 1] = 1;

		for (int i = 1; i < k; i++){
			v[i] += v[i - 1];

			array[v[i] - 1] = 1;
		}

		// //test
		// for (int i = 0; i < 100000; i++){
		// 	if (array[i] == 1) cout << i + 1 << endl; 
		// }

		for (int i = v[0]; i < x; i ++){
			for (int j = 0; j < k; j ++ )
				if (i + 1 > v[j])
					array[i] = array[i] || array[i - v[j]];
		}

		// //test
		// for (int i = 0; i < 100000; i++){
		// 	if (array[i] == 1) cout << i + 1 << endl; 
		// }

		if (array[x - 1]) cout<< "YES" << endl;
		
		else cout << "NO" << endl;

		if (n_data) cout << endl;


	}

	return 0;
}