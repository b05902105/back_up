#include<iostream>
#include<vector>

using namespace std;

long long ID[1000010];
long long insert_ID[1000010];
long long insert_count;
long long decrease_value;
long long max_v;
long long max_ID;

void operate(int operation){
	if(operation == 1){
		long long new_ID, new_score;

		cin>>new_ID>>new_score;

		new_score += insert_count * decrease_value;

		ID[new_ID] = new_score;
		
		insert_ID[insert_count] = new_ID;
	
		insert_count++;	

		if(new_score >= max_v){
			max_ID = new_ID;
			max_v = new_score;
		}
	}
	else if(operation == 2){
		long long increase_value;
		int update_c, update_ID;
		cin>>increase_value>>update_c;
		for(int i = 0; i < update_c; i++){
			cin>>update_ID;

			ID[update_ID] += increase_value;

			if(ID[update_ID] >= max_v){
				max_ID = update_ID;
				max_v = ID[update_ID];
			}
		}
	}
	else if(operation == 3){
		long long ans = max_v - (insert_count-1) * decrease_value;
		printf("id: %lld, value: %lld\n", max_ID, ans);
	}

}

int main(){
	int n;

	ios::sync_with_stdio(false);
	cin.tie(0);

	insert_count = 0;

	cin>>n>>decrease_value;

	int max_v = 0;

	for(int c = 0; c < n; c++){
		int operation;

		cin>>operation;

		operate(operation);

	}
}
