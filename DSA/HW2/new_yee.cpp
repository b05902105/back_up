#include<cstdio>
#include<string>
#include<vector>
#include<unordered_map>
#include<cassert>
#include<iostream>
#include<cstdbool>

using namespace std;

FILE *org_file_2gm;


unordered_map<string, vector<int>> dict_2gm;
unordered_map<streamoff, vector<string>> file_2gm;

bool is_num(string s){
	string::iterator it = s.begin();
	while(it != s.end() && isdigit(*it))	it++;
	return (!s.empty() && it == s.end());
}

int main(int argc, char **argv){
	string name = "2gm.small.txt";
	string path = argv[1] + name;
	org_file_2gm = fopen(path.c_str(), "r");
	assert(org_file_2gm != NULL);
	char word[128];
	int index = 0;
	while(fscanf(org_file_2gm, "%s", word) != EOF){
		if(is_num(word)){
			index = ftell(org_file_2gm) + 2;
		}
		else{
			unordered_map<string, vector<int>>::iterator it = dict_2gm.find(word);
			if(it != dict_2gm.end())
				it->second.push_back(index);
			else{
				vector<int> temp = {index};
				dict_2gm.insert(make_pair(word, temp));
			}
		}
	}
	cout<<"dict_2gm builded\n";
	
	unordered_map<string, vector<int>>::iterator it;
	for(it = dict_2gm.begin(); it != dict_2gm.end(); it++){
		cout<<it->first<<'\n';
		for(int i = 0; i < it->second.size(); i++)
			cout<<it->second[i]<<' ';
		cout<<'\n';
	}

	fclose(org_file_2gm);
	
	return 0;

}
