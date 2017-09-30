#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

typedef struct Item{
	int ID;
	int Score;
} Item;

vector<Item*> myHeap;
int real_item[1000000];
int last_place;

void change(int *a, int *b){
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

bool is_2_pow(float i){
	if((int)i % 2 != 0)		return false;
	while(i > 1.0)	i /= 2.0;
	if(i == 1.0)	return true;
	else	return false;
}

void upadjust(int pos){
	if(pos == 1) 	return;
	if(myHeap[pos/2]->Score < myHeap[pos]->Score){
		change(&(heap[pos/2]->Score), &(heap[pos]->Score));
		upadjust(pos/2);
	}
}

void downadjust(int pos, int end_pos){
	int left = pos*2;
	int right = (pos*2) + 1;
	if(right >= end_pos) 	return;
	int large_pos = (myHeap[right]->Score > myHeap[left]->Score)? right : left;
	if(myHeap[pos]->Score < myHeap[large_pos]->Score){
		change(&(heap[pos]->Score), &(heap[large_pos]->Score));
		downadjust(large_pos, end_pos);
	}
}


void print(){
	for(int i = 1; i < heap.size(); i++){
		cout<<heap[i];
		if(is_2_pow(i+1))
			cout<<'\n';
		else
			cout<<' ';
	}
	cout<<'\n';
}


void insert(Item new_item){
	myHeap.push_back(new_item);
}

void operating(int operation){
	if(operation == 1){
		int new_ID, new_score;
		cin>>new_ID>>new_score;
		Item temp;
		temp.ID = new_ID;
		temp.Score = new_score;
		insert(temp);
		 
	}
	else if(operation == 2){

	}
	else if(operation == 3){

	}
}


int main(){
	int n;
	cin>>n;
	last_place = 1;
	Item temp;
	temp.ID = -1;
	temp.Score = -1;
	real_item.push_back(temp);
	myHeap.push_back(&real_item[0]);
	for(int c = 0; c < n; c++){
		
	}
	
}
