#include<iostream>
#include<vector>

using namespace std;


void push(vector<int> *stack, int n){
	(*stack).push_back(n);
}

int stack_pop(vector<int> *stack){
	int a = *((*stack).rbegin());
	(*stack).erase((*stack).end()-1);
	return a;
}

int queue_pop(vector<int> *queue){
	int a = *((*queue).begin());
	(*queue).erase((*queue).begin());
	return a;
}

void trivago(vector<int> q, vector<int> s, vector<int> a){
	if(q.empty() && s.empty()){
		for(auto i = a.begin(); i != a.end(); i++)
			cout<<*i<<' ';
		cout<<'\n';
		return;
	}

	if(!q.empty()){
		vector<int> tmp_q = q;
		vector<int> tmp_s = s;
		push(&tmp_s, queue_pop(&tmp_q));
		trivago(tmp_q, tmp_s, a);
	}

	if(!s.empty()){
		vector<int> tmp_s = s;
		vector<int> tmp_a = a;
		push(&tmp_a, stack_pop(&tmp_s));
		trivago(q, tmp_s, tmp_a);
	}

}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	vector<int> queue, stack, ans;
	int N;
	cin>>N;

	for(int i = 1; i <= N; i++){
		queue.push_back(i);
	}
	trivago(queue, stack, ans);

	return 0;
}
