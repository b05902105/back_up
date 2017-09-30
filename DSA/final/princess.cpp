#include<iostream>
#include<vector>

using namespace std;

int max(int a, int b)	{return (a > b)? a : b;}
int min(int a, int b)	{return (a < b)? a : b;}

int trivago(vector<int> box, int n){
	int table[n][n], gap, i, j, x, y, z;

	for(gap = 0; gap < n; gap++){
		for(i = 0, j = gap; j < n; i++, j++){
			x = ((i+2) <= j)? table[i+2][j] : 0;
			y = ((i+1) <= (j-1))? table[i+1][j-1] : 0;
			z = (i <= (j-2))? table[i][j-2]: 0;

			table[i][j] = max(box[i] + min(x, y), box[j] + min(y, z));
		}
	}

	return table[0][n-1];
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;

	cin>>n;
	vector<int> box;

	int sum = 0;
	for(int z = 0; z < n; z++){
		int num;
		cin>>num;
		box.push_back(num);
		sum += num;
	}

	int me = trivago(box, n);
	int he = sum-me;

	int ans = me-he;

	if(ans >= 0)
		printf("Y\n");
	else
		printf("N\n");
	printf("%d\n", (ans>0)? ans : -ans);

	return 0;	
}
