#include<iostream>
#include<algorithm>
#include<vector>
#include<cstdio>

using namespace std;

struct Max_heap{
	private:
		vector<int> A;
		int PARENT(int i)	{return (i-1)/2;}
		int LEFT(int i)		{return (2*i + 1);}
		int RIGHT(int i)	{return (2*i + 2);}

		void heapify_down(int i){
			int left = LEFT(i);
			int right = RIGHT(i);
			int largest = i;

			if(left < size() && A[left] > A[i])
				largest = left;
			
			if(right < size() && A[right] > A[largest])
				largest = right;

			if(largest != i){
				swap(A[i], A[largest]);
				heapify_down(largest);
			}
		}

		void heapify_up(int i){
			if(i > 0 && A[PARENT(i)] < A[i]){
				swap(A[i], A[PARENT(i)]);
				heapify_up(PARENT(i));
			}
		}

	public:
		unsigned int size(){	return A.size();}
		bool empty(){	return (size() == 0);}
		void push(int key){
			A.push_back(key);
			int index = size()-1;
			heapify_up(index);
		}
		void pop(){
			A[0] = A.back();
			A.pop_back();
			heapify_down(0);
		}

		int top(){
			if(size() == 0)
				return 0;
			return A[0];
		}
};

struct Min_heap{
	private:
		vector<int> A;
		int PARENT(int i)	{return (i-1)/2;}
		int LEFT(int i)		{return (2*i + 1);}
		int RIGHT(int i)	{return (2*i + 2);}

		void heapify_down(int i){
			int left = LEFT(i);
			int right = RIGHT(i);
			int smallest = i;

			if(left < size() && A[left] < A[i])
				smallest = left;
			
			if(right < size() && A[right] < A[smallest])
				smallest = right;

			if(smallest != i){
				swap(A[i], A[smallest]);
				heapify_down(smallest);
			}
		}

		void heapify_up(int i){
			if(i && A[PARENT(i)] > A[i]){
				swap(A[i], A[PARENT(i)]);
				heapify_up(PARENT(i));
			}
		}

	public:
		unsigned int size(){	return A.size();}
		bool empty(){	return size() == 0;}
		void push(int key){
			A.push_back(key);
			int index = size()-1;
			heapify_up(index);
		}
		void pop(){	
			A[0] = A.back();
			A.pop_back();
			heapify_down(0);
		}

		int top(){
			if(size() == 0)
				return 0;
			return A[0];
		}

};

Max_heap max_h;
Min_heap min_h;

void insert(int num){
	int val;
	if(max_h.empty()){
		max_h.push(num);
	}
	else if(min_h.empty()){
		if(num < max_h.top()){
			val = max_h.top();
			max_h.pop();
			max_h.push(num);
			min_h.push(val);
		}
		else
			min_h.push(num);
	}
	else{
		if(num < max_h.top())
			max_h.push(num);
		else if(num > min_h.top()){
			val = min_h.top();
			min_h.pop();
			min_h.push(num);
			max_h.push(val);
		}
		else
			max_h.push(num);

		while(max_h.size() > min_h.size()+1){
			val = max_h.top();
			max_h.pop();
			min_h.push(val);
		}
	}
}

int find_median(){
	if(max_h.size() == min_h.size())
		return (max_h.top() + min_h.top())/2;
	else
		return max_h.top();
}

int extract_median(){
	int ans = max_h.top();
	max_h.pop();

	if(min_h.size() > max_h.size()){
		int val = min_h.top();
		min_h.pop();
		max_h.push(val);
	}

	return ans;
}

int main(){
	
	int N;

	cin>>N;

	for(int i = 0; i < N; i++){
		int oper;
		cin>>oper;

		if(oper == 1){
			int ID;
			cin>>ID;
			insert(ID);

	//		cout<<"max_h:"<<max_h.top()<<'\n';
	//		cout<<"min_h:"<<min_h.top()<<'\n';
		}
		else if(oper == 2){
			if(i != N-1)
				printf("Current median ID:%d\n", find_median());
			else if(i == N-1)
				printf("The winner ID: %d!!!\n", max_h.top());
		}
		else if(oper == 3){
			printf("Player ID:%d is out!\n", extract_median());
		}
	}

	return 0;
}

