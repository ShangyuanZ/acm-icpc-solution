#include<iostream>
#include<list>
#include<string>
#include <algorithm>


using namespace std;

int main(){

	int n_population, n_command;

	cin >> n_population >> n_command;

	int case_number = 1;

	while(n_population != 0 || n_command != 0){

		cout << "Case " << case_number << ':'<< endl;
		case_number ++;
		
		// get the vetor queue
		list <int> queue;

		int min1 = min(n_population, n_command);

		for (int i = 1; i <= min1; i++){
			queue.push_back(i);
		} 

		//read the input E,N
		for (int i = 0; i < n_command; i++){
			char N_E;
			cin >> N_E;

			if (N_E == 'N'){

				cout << queue.front() << endl;

				queue.push_back(queue.front());

				queue.pop_front();
				

			}


			if( N_E == 'E'){
				int to_front;
				cin >> to_front;
				

				// delete the previous repetition

				queue.remove(to_front);
				queue.push_front(to_front);
			}
		}	

		cin >> n_population >> n_command;

	}

	return 0;
}