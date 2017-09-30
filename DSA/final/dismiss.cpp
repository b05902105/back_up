#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>

using namespace std;

unordered_map<int, vector<int>> parents; 
vector<int> ans;

void trivago(int num){
	unordered_map<int, vector<int>>::iterator it = parents.find(num);

	if(it == parents.end())
		return;

	for(int i = 0; i < it->second.size(); i++){
		ans.push_back(it->second[i]);
		trivago(it->second[i]);
	}

}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	vector<int> id;
	vector<int> p;

	cin>>n;
	for(int i = 0; i < n; i++){
		int num;
		cin>>num;
		id.push_back(num);
	}

	for(int i = 0; i < n; i++){
		int num;
		cin>>num;
		p.push_back(num);
	}


	for(int i = 0; i < n; i++){	
		unordered_map<int, vector<int>>::iterator it = parents.find(p[i]);
		if(it == parents.end()){
			vector<int> tmp;
			tmp.push_back(id[i]);
			parents.insert(make_pair(p[i], tmp));
		}
		else
			it->second.push_back(id[i]);
	}
	
	int k;
	cin>>k;

	ans.push_back(k);

	trivago(k);

	sort(ans.begin(), ans.end());
	int i;
	for(i = 0; i < ans.size()-1; i++)
		cout<<ans[i]<<' ';
	cout<<ans[i]<<'\n';

	return 0;
}
