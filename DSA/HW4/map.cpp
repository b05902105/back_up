#include<iostream>
#include<algorithm>
#include<vector>
#include<unordered_map>
#include<map>

using namespace std;

map<int, int> sort_map;

int main(){
	int n;
	cin>>n;

	for(int i = 0; i < n; i++){
		int num;
		cin>>num;
		sort_map.insert(make_pair(num, 0));
	}
	return 0;
}
