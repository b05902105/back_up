#include<iostream>
#include<algorithm>
#include<vector>
#include<unordered_map>
#include<map>

using namespace std;

unordered_map<int, int> myMap;

int main(){
	int n;
	cin>>n;

	for(int i = 0; i < n; i++){
		int num;
		cin>>num;

		myMap.insert(make_pair(num, 0));
	}

	for(int i = 0; i < n; i++){
		int num;
		cin>>num;
		myMap[num]++;
	}

	return 0;
		
}
