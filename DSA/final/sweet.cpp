#include<iostream>
#include<vector>

using namespace std;

vector<int> satis;
vector<int> price;

int trivago(int n, int p){
	if(w < 0)
		return -1e9;
	if(n == 0)
		return 0;

	return max(trivago(n-1,  
}

int main(){
	int N, M;
	cin>>N>>M;

	for(int z = 0; z < N; z++){
		int a, b, c;
		cin>>a>>b>>c;
		for(int i = 0; i < a; i++){
			price.push_back(b);
			satis.push_back(c);
		}
	}


}
