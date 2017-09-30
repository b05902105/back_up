#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

unsigned long long nextMap(unsigned long long map, int action);

vector<int> myOrder = {13, 9, 14, 5, 15, 1, 16, 10, 6, 11, 2, 12, 7, 3, 8, 4};

typedef struct new_map{
	unsigned long long map;
	int action;
} new_map;

vector<new_map> myStack;

//my calculator

int mylog2(int num){
	if(num <= 1) 	return 0;
	return (1 + mylog2(num/2));
}

int mypow(int power){
	if(power == 0)	return 1;
	return (2 * mypow(power-1));
}

//convert matrix to unsigned long long

unsigned long long MtoULL(int map[4][4]){
	unsigned long long result = 0;
	for(int i = 3; i >= 0; i--){
		for(int j = 3; j >= 0; j--){
			result <<= 4;
			int temp = mylog2(map[i][j]);
			result ^= temp;
		}
	}

	return result;
}

void printULL(unsigned long long map){
	for(int i = 0, c = 0; i < 4; i++){
		for(int j = 0; j < 4; j++, c++){
			int temp = 15;
			temp &= map;
			if(temp == 0)
				cout<<"0";
			else
				cout<<mypow(temp);
			if(j == 3)
				cout<<'\n';
			else
				cout<<' ';

			map >>= 4;

		}
	}
}

//stack function

new_map pop(){
	new_map result = *(myStack.rbegin());
	myStack.erase(myStack.end() - 1);
	return result;
}

void push(new_map a){
	myStack.push_back(a);
}

//main program

bool can_move(unsigned long long org, int action){
	if(org == nextMap(org, action))
		return false;
	else
		return true;
}

int take_value(unsigned long long org, int order){
	int temp = 15;
	org >>= (order-1) * 4;
	temp &= org;
}

int which_is_better(unsigned long long a, unsigned long long b){
	for(int i = 0; i < 16; i++){
		int left = take_value(a, myOrder[i]);
		int right = take_value(b, myOrder[i]);
		if(left > right)
			return 1;
		else if(left < right)
			return -1;
	}

	return 0;
}


vector<new_map> determine_order(new_map org){
	vector<new_map> result;
		
	new_map right, down, left, up;

	right.map = nextMap(org.map, 0);
	down.map = nextMap(org.map, 1);
	left.map = nextMap(org.map, 2);
	up.map = nextMap(org.map, 3);
	right.action = 0;
	down.action = 1;
	left.action = 2;
	up.action = 3;

	if(left.map != org.map && down.map != org.map){
		if(org.action == 3){
			result.push_back(left);
			result.push_back(down);
		}
		else if(org.action == 1){
			result.push_back(left);
			result.push_back(down);
		}
		else{
			result.push_back(down);
			result.push_back(left);
		}
	}
	else if(left.map != org.map && down.map == org.map)
		result.push_back(left);
	else if(left.map == org.map && down.map != org.map)
		result.push_back(down);

	if(up.map != org.map)
		result.push_back(up);

	if(right.map != org.map)
		result.push_back(right);

	return result;
	
}


bool check_2048(unsigned long long map){
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++){
			int temp = 15;
			temp &= map;
			if(temp == 11)
				return true;
			map >>= 4;
		}
	return false;
}

vector<int> error(){
	vector<int> errormess;
	errormess.push_back(-1);
	return errormess;
}

int main(){
	int n;
	cin>>n;
	for(int k = 0; k < n; k++){
	int M[4][4];
	unsigned long long map;

	myStack.reserve(200);

	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			cin>>M[i][j];
	new_map org_map;
	org_map.map = MtoULL(M);
	org_map.action = -1;

//	myStack.push_back(org_map);
	
	vector<int> act;

	vector<new_map> result = determine_order(org_map);

	for(auto i = result.rbegin(); i != result.rend(); i++)
		myStack.push_back(*i);

	new_map current = org_map;
	bool err = false;
//	for(int i = 0; i < 10; i++){
	while(true){
	//	cout<<"action = "<<current.action<<'\n';
	//	printULL(current.map);
		if(check_2048(current.map)){
			//printULL(current.map);
			break;
		}

		if(myStack.empty()){
			act = error();
			err = true;
			break;
		}
			
		current = pop();
		result = determine_order(current);
		if(result.size() != 0){
			for(auto i = result.rbegin(); i != result.rend(); i++)
				myStack.push_back(*i);
			act.push_back(current.action);
		}

	}

	cout<<"Action:\n";
	for(int i = 0; i < act.size(); i++){
		if(i == act.size() - 1)
			cout<<act[i]<<'\n';
		else
			cout<<act[i]<<' ';
	}
	cout<<"Final:\n";

	if(!err)
		printULL(current.map);
	else{
		for(int i = 0; i < 4; i++){
			for(int j = 0; j < 4; j++){
				if(j == 3)
					printf("-1\n");
				else
					printf("-1 ");
			}
		}
	}
	
	myStack.clear();
	}
	return 0;
	

				
}
