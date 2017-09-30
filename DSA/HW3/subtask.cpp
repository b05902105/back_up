#include<iostream>
#include<vector>

using namespace std;

unsigned long long nextMap(unsigned long long map, int action);

typedef struct new_map{
	unsigned long long map;
	int action;
} new_map;

int mylog2(int num){
	if(num <= 1) 	return 0;
	return (1 + mylog2(num/2));
}

int mypow(int power){
	if(power == 0) 	return 1;
	return (2 * mypow(power-1));
}

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

int main(){
	int M[4][4];

	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			cin>>M[i][j];

	new_map org_map;
	org_map.map = MtoULL(M);

	int act;

	while(scanf("%d", &act) != EOF){
		org_map.map = nextMap(org_map.map, act);
		cout<<"action: "<<act<<'\n';
		printULL(org_map.map);

		printf("\n");
	}



}

