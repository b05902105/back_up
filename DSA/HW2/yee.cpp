#include<iostream>
#include<sstream>
#include<fstream>

#include<algorithm>
#include<string>
#include<vector>
#include<unordered_map>
#include<map>

#include<cassert>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<cstddef>
#include<cstring>

using namespace std;

#define ALPHABET_SIZE 26
#define CtoI(c) ((int)c - (int)'a')

typedef struct Node{
	struct Node *child[ALPHABET_SIZE];
	bool is_end;
	vector<long> posting;
} Node;

typedef struct Ans{
	long f;
	string ans_str;
}Ans;

FILE *org_file_2gm, *org_file_3gm, *org_file_4gm, *org_file_5gm;
Node *Dict_2gm, *Dict_3gm, *Dict_4gm, *Dict_5gm;

vector<Ans> a;
long min_freq;
int ans_count;

map<long, long> two;

Node *init(){
	Node *root = new Node();
	for(int i = 0; i < ALPHABET_SIZE; i++)
		root->child[i] = NULL;
	root->is_end = false;
	root->posting.reserve(50);
	return root;
}

void insert(Node *root, string key, long index){
	Node *current = root;
	int len = key.length();
	for(int i = 0; i < len; i++){
		int letter = CtoI(key[i]);
		if(current->child[letter] == NULL)
			current->child[letter] = init();
		current = current->child[letter];
	}
	current->is_end = true;
	current->posting.push_back(index);
}

vector<long> search(Node *root, string word){
	Node *current = root;
	vector<long> error;
	int len = word.length();
	for(int i = 0; i < len; i++){
		int letter = CtoI(word[i]);
		if(current->child[letter] == NULL)
			return error;
		current = current->child[letter];
	}

	if(current->is_end)
		return current->posting;
	else
		return error;
}

void compare_ans(Ans temp, long freq, string str){
	vector<Ans>::iterator it;
	for(it = a.begin(); it != a.end() && freq > (*it).f; it++);
	if((*it).f == freq){
		if(str < (*it).ans_str)
			a.insert(it, temp);
		else if(str > (*it).ans_str)
			a.insert(it+1, temp);
	}
	else
		a.insert(it, temp);
}

void insert_ans(long freq, string str){
	Ans temp;
	temp.f = freq;
	temp.ans_str = str;
	bool is_exist = false;

	for(int i = 0; i < ans_count; i++)
		if(a[i].f == freq && a[i].ans_str == str)
			is_exist = true;

	if(ans_count == 0){
		a.push_back(temp);
		ans_count++;
	}
	else if(ans_count != 0 && ans_count < 5){
		if(!is_exist){
			compare_ans(temp, freq, str);
			ans_count++;
		}
	}
	else
		if((freq > min_freq) || (freq == min_freq && str < (*a.begin()).ans_str)){
			if(!is_exist){	
				a.erase(a.begin());
				compare_ans(temp, freq, str);
			}
		}

	min_freq = (*a.begin()).f;
}

bool is_num(string s){		//to confirm if the string s is a number
	string::iterator it = s.begin();
	while(it != s.end() && isdigit(*it))	it++;
	return (!s.empty() && it == s.end());
}

vector<string> split_space(string str){		//split space and tab in a string
	vector<string> result;
	char s[200];
	strcpy(s, str.c_str());
	char c[] = " 	";
	char *p;
	p = strtok(s, c);
	while(p){
		result.push_back(p);
		p = strtok(NULL, c);
	}
	return result;
}

vector<string> split(string str, char pattern){		//split "/" in a string
	stringstream ss(str);
	string sub_str;
	vector<string> result;
	while(getline(ss, sub_str, pattern))
		result.push_back(sub_str);

	return result;
}


vector<long> compare(vector<long> org_vec, vector<long> vec){	//used to find the same factor in two vector, and store in a new vector
	int size1 = org_vec.size();
	int size2 = vec.size();
	int spin1 = 0, spin2 = 0;
	vector<long> ans;
	while(spin1 < size1 && spin2 < size2){
		if(org_vec[spin1] < vec[spin2])
			spin1++;
		else if(org_vec[spin1] == vec[spin2]){
			ans.push_back(org_vec[spin1]);
			spin1++;
			spin2++;
		}
		else
			spin2++;
	}
	return ans;
}

bool compare_word_order(int type, int is_word[], vector<string> query_str, string org_str){
	bool ans = true;
	vector<string> split_org_str = split_space(org_str);
	for(int i = 0; i < type && ans; i++){
		if(is_word[i] != 1)
			continue;
		else{
			if(query_str[i] != split_org_str[i])
				ans = false;
		}
	}
	return ans;
}

long find_frequency(string s){
	long ans;
	size_t found = s.find_last_of(" 	");
	string num = s.substr(found+1);
	ans = stol(num);
	return ans;
}

void query_2gm(vector<string> query_str){
	vector<long> cpr;
	cpr.reserve(20);
	int count = 0;
	int is_word[5] = {0};
	bool no_word = true;
		
	for(int i = 0; i < 2; i++){
		if(query_str[i] != "_"){
			no_word = false;
			is_word[i] = 1;
			if(count == 0)
				cpr = search(Dict_2gm, query_str[i]);
			else
				cpr = compare(cpr, search(Dict_2gm, query_str[i]));
			count++;
		}
	}
	char ans_line[200];

	if(no_word){
		ans_count = 5;
		Ans temp;
		for(auto i = two.rbegin(); i != two.rend(); i++){
			temp.f = i->first;
			fseek(org_file_2gm, i->second, SEEK_SET);
			fgets(ans_line, 200, org_file_2gm);
			temp.ans_str = ans_line;
			a.push_back(temp);
		}
	}
	
	
	for(int i = 0; i < cpr.size() && !no_word; i++){

		fseek(org_file_2gm, cpr[i], SEEK_SET);
		fgets(ans_line, 200, org_file_2gm);
		long freq;
		if(compare_word_order(2, is_word, query_str, ans_line)){
			freq = find_frequency(ans_line);
		//	cout<<"freq = "<<freq<<", min_freq = "<<min_freq<<", ans is "<<ans_line;
			
			insert_ans(freq, ans_line);

		/*	if(ans_count < 5){
				if(ans.find(freq) == ans.end())
					ans_count++;
				ans[freq] = ans_line;
				min_freq = ans.begin()->first;
			}
			else
				if(freq > min_freq){
					if(ans.find(freq) == ans.end())
						ans.erase(min_freq);
					ans[freq] = ans_line;
					min_freq = ans.begin()->first;
				}

		*/
		}
	}
	
}

void query_3gm(vector<string> query_str){
	vector<long> cpr;
	cpr.reserve(20);
	int count = 0;
	int is_word[5] = {0};
	bool no_word = true;
	
	for(int i = 0; i < 3; i++){
		if(query_str[i] != "_"){
			no_word = false;
			is_word[i] = 1;
			if(count == 0)
				cpr = search(Dict_3gm, query_str[i]);
			else
				cpr = compare(cpr, search(Dict_3gm, query_str[i]));
			count++;
		}
	}


	for(int i = 0; i < cpr.size() && !no_word; i++){
		char ans_line[128];
		fseek(org_file_3gm, cpr[i], SEEK_SET);
		fgets(ans_line, 128, org_file_3gm);
		long freq;
		if(compare_word_order(3, is_word, query_str, ans_line)){
			freq = find_frequency(ans_line);
		//	cout<<"freq = "<<freq<<", min_freq = "<<min_freq<<", ans is "<<ans_line;
			insert_ans(freq, ans_line);

		}
	}
	
}

void query_4gm(vector<string> query_str){
	vector<long> cpr;
	cpr.reserve(20);
	int count = 0;
	int is_word[5] = {0};
	bool no_word = true;
	
	for(int i = 0; i < 4; i++){
		if(query_str[i] != "_"){
			no_word = false;
			is_word[i] = 1;
			if(count == 0)
				cpr = search(Dict_4gm, query_str[i]);
			else
				cpr = compare(cpr, search(Dict_4gm, query_str[i]));
			count++;
		}
	}
	for(int i = 0; i < cpr.size() && !no_word; i++){
		char ans_line[128];
		fseek(org_file_4gm, cpr[i], SEEK_SET);
		fgets(ans_line, 128, org_file_4gm);
		long freq;
		if(compare_word_order(4, is_word, query_str, ans_line)){
			freq = find_frequency(ans_line);
		//	cout<<"freq = "<<freq<<", min_freq = "<<min_freq<<", ans is "<<ans_line;
			insert_ans(freq, ans_line);
		}
	}
	
}

void query_5gm(vector<string> query_str){
	vector<long> cpr;
	cpr.reserve(20);
	int count = 0;
	int is_word[5] = {0};
	bool no_word = true;

	for(int i = 0; i < 5; i++){
		if(query_str[i] != "_"){
			no_word = false;
			is_word[i] = 1;
			if(count == 0)
				cpr = search(Dict_5gm, query_str[i]);
			else
				cpr = compare(cpr, search(Dict_5gm, query_str[i]));
			count++;
		}
	}
	for(int i = 0; i < cpr.size() && !no_word; i++){
		char ans_line[128];
		fseek(org_file_5gm, cpr[i], SEEK_SET);
		fgets(ans_line, 128, org_file_5gm);
		long freq;
		if(compare_word_order(5, is_word, query_str, ans_line)){
			freq = find_frequency(ans_line);
		//	cout<<"freq = "<<freq<<", min_freq = "<<min_freq<<", ans is "<<ans_line;
			insert_ans(freq, ans_line);

		}
	}
	
}

void query(vector<string> query_str){
	int size = query_str.size();

	if(size == 2)
		query_2gm(query_str);
	else if(size == 3)
		query_3gm(query_str);
	else if(size == 4)
		query_4gm(query_str);
	else if(size == 5)
		query_5gm(query_str);

}


vector<string> process_quest(vector<string> str, int pos, int type){
	if(type == 0){
		str.erase(str.begin() + pos);
		return str;
	}
	else{
		str[pos].erase(str[pos].begin());
		return str;
	}
}

vector<string> process_splash(vector<string> str, string s, int pos){
	str[pos] = s;
	return str;
}

vector<string> process_star(vector<string> str, int underscore, int pos){
	str.erase(str.begin() + pos);
	for(int i = 0; i < underscore; i++)
		str.insert(str.begin() + pos, "_");

	return str;
}

void expand_star(vector<string> query_str){
	int size = query_str.size();
	int limit = 5;
	for(int i = 0; i < size; i++)
		if(query_str[i] == "*")
			limit++;

	if(size > limit)
		return;

	if(limit == 5){
		query(query_str);

		return;
	}

	for(int i = 0; i < size; i++){
		if(query_str[i] == "*"){
			for(int j = 0; j < 9-size; j++)	
				expand_star(process_star(query_str, j, i));

			return;
		}
	}

}

void expand(vector<string> query_str){
	int size = query_str.size();

	if(size > 5)
		return;

	int flag = 0;
	for(int i = 0; i < size && flag == 0; i++){
		size_t found = query_str[i].find_first_of("/?");
		if(found != string::npos)
			flag = 1;
	}

	if(flag == 0){
		expand_star(query_str);
		return;
	}
	else{
		for(int i = 0; i < size; i++){
			size_t found = query_str[i].find_first_of('?');
			if(found != string::npos){
				expand(process_quest(query_str, i, 0));

				expand(process_quest(query_str, i, 1));

				return;
			}	

		}
		
		for(int i = 0; i < size; i++){
			size_t found = query_str[i].find_first_of('/');
			if(found != string::npos){
				vector<string> temp = split(query_str[i], '/');
		
				for(int j = 0; j < temp.size(); j++)
					expand(process_splash(query_str, temp[j], i));
				
				return;
			}
		}
	}

}

int main(int argc, char *argv[]){


	org_file_2gm = fopen((string(argv[1]) + "2gm.small.txt").c_str(), "r");
	org_file_3gm = fopen((string(argv[1]) + "3gm.small.txt").c_str(), "r");
	org_file_4gm = fopen((string(argv[1]) + "4gm.small.txt").c_str(), "r");
	org_file_5gm = fopen((string(argv[1]) + "5gm.small.txt").c_str(), "r");
	
	assert(org_file_2gm != NULL);
	assert(org_file_3gm != NULL);
	assert(org_file_4gm != NULL);
	assert(org_file_5gm != NULL);
	char word[200];
	long index = 0;

	Dict_2gm = init();
	Dict_3gm = init();
	Dict_4gm = init();
	Dict_5gm = init();

	long min_t;
	int ex_count = 0;
	
	while(fscanf(org_file_2gm, "%s", word) != EOF){
		if(is_num(word)){
			long t = find_frequency(word);
			
			if(ex_count == 0 || (ex_count != 0 && ex_count < 5)){
				two[t] = index;
				ex_count++;
				min_t = (two.begin())->first;
			}
			else if(ex_count > 5)
				if(t > min_t){
					two.erase(two.begin());
					two[t] = index;
				}

			index = ftell(org_file_2gm) + 1;
		}
		else
			insert(Dict_2gm, word, index);
		
	}

	index = 0;

	while(fscanf(org_file_3gm, "%s", word) != EOF){
		if(is_num(word))
			index = ftell(org_file_3gm) + 1;
		else
			insert(Dict_3gm, word, index);
	}

	index = 0;
	while(fscanf(org_file_4gm, "%s", word) != EOF){
		if(is_num(word))
			index = ftell(org_file_4gm) + 1;
		else
			insert(Dict_4gm, word, index);
	}

	index = 0;
	while(fscanf(org_file_5gm, "%s", word) != EOF){
		if(is_num(word))
			index = ftell(org_file_5gm) + 1;
		else
			insert(Dict_5gm, word, index);
	}
	//now start query
	
	string str;
	//printf("start\n");
	while(getline(cin, str)){
		cout<<"query: "<<str<<'\n';
		a.clear();
		ans_count = 0;
		min_freq = 0;
		expand(split_space(str));
		
		cout<<"output: "<<ans_count<<'\n';
		
		for(int i = a.size()-1; i >= 0; i--)
			cout<<a[i].ans_str;
		/*
		map<long, string>::iterator it = ans.end();
		map<long, string>::iterator it2 = ans.begin();
		if(!ans.empty()){
			for(it--; true; it--){
				cout<<it->second;
				if(it == it2)
					break;
			}
		}
		*/
	
	}

	fclose(org_file_2gm);
	fclose(org_file_3gm);
	fclose(org_file_4gm);
	fclose(org_file_5gm);
	
	return 0;
	
}

//bug 1 : input two same word will print two times
//bug 2 : can't identify "abc */?ab" type query 
//bug 3 : should modify the int to streamoff or long
//bug 4 : same frequency yet not same n-gram will be erased cause map can store only one-by-one key
