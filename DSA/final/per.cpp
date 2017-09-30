#include<iostream>
#include<vector>
#include<string>

using namespace std;

int pop(vector<int> *container, int order){
	int a = *((*container).begin() + order);
	*((*container).erase((*container).begin() + order));
	return a;
}

int queue_pop(vector<int> *queue){
	int a = *((*queue).begin());
	(*queue).erase((*queue).begin());
	return a;
}

int stack_pop(vector<int> *stack){
	int a = *((*stack).rbegin());
	(*stack).erase((*stack).end()-1);
	return a;
}

void trivago(vector<int> org, vector<int> con, vector<int> ans, int Di, int N){
	
	int count = 0;
	while(true){
	int n = org.size();
	int pre;
	for(int i = n-1; i >= 0; i--){
		int tmp = stack_pop(&org);
		
		if(con.size() != 0 && tmp < pre){
			con.push_back(tmp);
			break;
		}
	
		con.push_back(tmp);
		pre = tmp;
	}

	ans = org;


	int c;

	for(c = 0; c < con.size(); c++){
		if(*(con.begin()+c) > *(con.rbegin()))
			break;
	}


	if(c == N-1 || c == N){
		cout<<"NOPE!!\n";
		break;
	}



	ans.push_back(pop(&con, c));

	for(int i = 0; i < c; i++)
		ans.push_back(queue_pop(&con));

	ans.push_back(stack_pop(&con));

	int tmp = con.size();
	for(int i = 0; i < tmp; i++)
		ans.push_back(queue_pop(&con));
	
	count++;
	if(Di == count){
		for(auto i = ans.begin(); i != ans.end(); i++)
			cout<<*i;
		cout<<'\n';
		break;
	}

	org = ans;
	ans.clear();
	}
/*
	for(auto i = org.begin(); i != org.end(); i++)
		cout<<*i<<' ';
	cout<<'\n';
	
	
	for(auto i = con.begin(); i != con.end(); i++)
		cout<<*i<<' ';
	cout<<'\n';
	
*/
}

int main(){
	int N;

	cin>>N;
	
	for(int i = 0; i < N; i++){
		int Di;
		string Pi;
		vector<int> org;

		cin>>Di>>Pi;

		int c = Pi.length();
		for(int j = 0; j < c; j++)
			org.push_back(Pi[j] - '0');
		vector<int> ans, con;
		trivago(org, con, ans, Di, c); 
	}

	return 0;
}
