#include<iostream>
#include<vector>

using namespace std;

int max(int a, int b)	{return (a > b)? a : b;}
int min(int a, int b)	{return (a < b)? a : b;}

int trivago(vector<int> song_time, int M, int T){
	int table[n][n], gap, i, j, a, b;

	for(gap = 0; gap < n; gap++){
		for(i = 0, j = gap; j < n; i++, j++){
			
			a = (i-
		}
	}

	return table[0][n-1];
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int X;
	cin>>X;

	for(int z = 0; z < X; z++){
		int N, M, T;
		cin>>N>>M>>T;
		vector<int> song_time;
		for(int i = 0; i < N; i++){
			int t;
			cin>>t;
			song_time.push_back(t);
		}

		trivago(song_time, M, T);
	}
}
