#include<iostream>
#include<vector>

using namespace std;

int N, M;
vector<int> tree;

int pow(int n){
	if(n == 0)	return 1;
	else	return 2*pow(n-1);
}

vector<int> insert(vector<int> fuck, int n){
	fuck.push_back(n);
	return fuck;
}

void DFS(int order, int sum, vector<int> ans){
	if(order >= pow(N+1))
		return;

	if(sum == M){
		int i = 0;
		for(; i < ans.size()-1; i++)
			cout<<ans[i]<<' ';
		cout<<ans[i]<<'\n';
	}

	for(int i = 0; i < 2; i++){
		int a = order*2 + i;
		DFS(a, sum + tree[a], insert(ans, tree[a]));
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	tree.reserve(pow(21));

	int num;

	cin>>N;
	
	tree.push_back(2147483647);

	vector<int> a;

	for(int i = 0; i <= N; i++){
		int k = pow(i);
		for(int j = 0; j < k; j++){
			cin>>num;
			tree.push_back(num);
		}
	}
	cin>>M;
	
	a.push_back(tree[1]);
	DFS(1, tree[1], a);

	return 0;
}
