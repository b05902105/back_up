#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

vector<int> heap;
int now_pos;


void change(int *a, int *b){
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void downadjust(int pos, int end_pos){
	int left = pos*2;
	int right = (pos*2) + 1;
	if(right >= end_pos)	return;
	int large_pos = (heap[right] > heap[left])? right : left;

	if(heap[pos] < heap[large_pos]){
		change(&heap[pos], &heap[large_pos]);
		downadjust(large_pos, end_pos);
	}
}

void sort(int sort_pos){
	int temp = heap[1];
	heap[1] = heap[sort_pos];
	heap[sort_pos] = 0;
	downadjust(1, sort_pos);
	heap[sort_pos] = temp;
}


void upadjust(int pos){
	if(pos == 1)	return;
	if(heap[pos/2] < heap[pos]){
		change(&heap[pos/2], &heap[pos]);
		upadjust(pos/2);
	}
}

void insert(int num){
	heap.push_back(num);
	if(now_pos != 1)
		upadjust(now_pos);
	now_pos++;
}

void print(){
	for(int i = 1; i < heap.size(); i++)
		cout<<heap[i]<<' ';
	cout<<'\n';
}

int main(){
	int n;
	cin>>n;
	
	heap.push_back(-1);
	
	now_pos = 1;
	for(int i = 0; i < n; i++){
		int num;
		cin>>num;
		insert(num);

	}

	for(int i = now_pos -1 ; i >= 1; i--)
		sort(i);

	print();
}
