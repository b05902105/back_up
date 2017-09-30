#include<iostream>

using namespace std;

int N;
int M[1000][1000];

int min(int a, int b, int c){
	int m = a;
	if(m > b)
		m = b;
	if(m > c)
		m = c;
	return m;
}

int trivago(){
	int ans = 0;
	for(int i = 1; i < N; i++){
		for(int j = 1; j < N; j++){
			if(M[i][j] > 0)
				M[i][j] = min(M[i][j-1], M[i-1][j], M[i-1][j-1]) + 1;
		}
	}

	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++)
			ans	+= M[i][j];
	}
	return ans;
}

int main(){
	int count;
	cin>>count;
	for(int z = 0; z < count; z++){
		cin>>N;

		for(int i = 0; i < N; i++){
			string input;
			cin>>input;
			for(int j = 0; j < N; j++)
				M[i][j] = input[j] - '0';
		}

		int ans = trivago();

		cout<<ans<<'\n';
	}

	return 0;
}
