#include<iostream>
#include<vector>

using namespace std;

void trivago(vector<int> tree, int count, int N){
	if(tree[count] == -1)
		return;

	if(2*count > N){
		cout<<tree[count]<<' ';
		return;
	}

	trivago(tree, 2*count, N);

	cout<<tree[count]<<' ';

	if(2*count+1 <= N)
		trivago(tree, 2*count + 1, N);

	return;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int count;
	cin>>count;

	for(int z = 0; z < count; z++){
		int N;
		cin>>N;

		vector<int> tree;
		tree.push_back(2147483647);

		for(int i = 0; i < N; i++){
			int num;
			cin>>num;
			tree.push_back(num);
		}
		
		if(tree[1] != -1)
			trivago(tree, 1, N);
		cout<<'\n';
	}
}
