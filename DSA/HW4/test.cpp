#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int main(){
	vector<int> temp;
	for(int i = 1; i <= 20; i++)
		temp.push_back(i);

	random_shuffle(temp.begin(), temp.end());

	cout<<temp.size()<<'\n';
	for(int i = 0; i < temp.size(); i++)
		cout<<temp[i]<<'\n';

	
	return 0;
}
