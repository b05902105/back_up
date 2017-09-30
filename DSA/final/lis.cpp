#include<iostream>
#include<cstdlib>

using namespace std;

int trivago(string str, int n){
	int lis[n];
	int i, j, max = 0;

	for(i = 0; i < n; i++)
		lis[i] = 1;

	for(i = 1; i < n; i++)
		for(j = 0; j < i; j++)
			if(str[i] > str[j] && lis[i] < lis[j]+1)
				lis[i] = lis[j] + 1;

	for(i = 0; i < n; i++)
		if(max < lis[i])
			max = lis[i];

	return max;
}

int main(){
	int zz;
	cin>>zz;
	for(int z = 0; z < zz; z++){
		string str;
		cin>>str;
		cout<<trivago(str, str.length())<<'\n';
	}
	return 0;
}
