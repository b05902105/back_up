#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

unsigned long long nextMap(unsigned long long map, int action);
unsigned long long ANS;
vector<int> ANS_ACT;

//my calculator

int mylog2(int num){
	if(num <= 1) 	return 0;
	return (1 + mylog2(num/2));
}

int mypow(int power){
	if(power == 0)	return 1;
	return (2 * mypow(power-1));
}

//convert matrix to unsigned long long

unsigned long long MtoULL(int map[4][4]){
	unsigned long long result = 0;
	for(int i = 3; i >= 0; i--){
		for(int j = 3; j >= 0; j--){
			result <<= 4;
			int temp = mylog2(map[i][j]);
			result ^= temp;
		}
	}

	return result;
}

void printULL(unsigned long long map){
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			int temp = 15;
			temp &= map;
			if(temp == 0)
				cout<<"0";
			else
				cout<<mypow(temp);
			if(j == 3)
				cout<<'\n';
			else
				cout<<' ';

			map >>= 4;

		}
	}
}

//main program
bool check_2048(unsigned long long map){
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++){
			int temp = 15;
			temp &= map;
			if(temp == 11)
				return true;
			map >>= 4;
		}
	return false;
}

void baosow(vector<int> act, unsigned long long current){
	if(check_2048(current)){
		ANS = current;
		ANS_ACT.assign(act.begin(), act.end());
		return;
	}

	for(int i = 0; i < 4; i++){
		unsigned long long next = nextMap(current, i);
		if(current != next)
			baosow(push(act, i), next);

		if(ANS != 0)
			return;
	}

}

int main(){
	int n;
	cin>>n;
	for(int time_count = 0; time_count < n; time_count++){
		int M[4][4];
		unsigned long long map;
		
		myStack.reserve(200);

		for(int i = 0; i < 4; i++)
			for(int j = 0; j < 4; j++)
				cin>>M[i][j];

		new_map org_map;
		org_map.map = MtoULL(M);

		vector<int> act;
		ANS = 0;
		ANS_ACT.clear();
		baosow(act, org_map.map); 
		cout<<"Action:\n";
		if(ANS == 0){
			cout<<"-1\nFinal:\n";
			for(int i = 0; i < 4; i++){
				for(int j = 0; j < 4; j++){
					if(j == 3)
						printf("-1\n");
					else
						printf("-1 ");
				}
			}
		}
		else{
			int size = ANS_ACT.size();
			for(int i = 0; i < size-1; i++)
				cout<<ANS_ACT[i]<<' ';
			cout<<ANS_ACT[size-1]<<'\n';
			cout<<"Final:\n";
			printULL(ANS);
		}

	}

	return 0;		
}
