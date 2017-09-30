#include<iostream>
#include<vector>

using namespace std;

int trivago(vector<int> boo, vector<int> oper, int n){
	int F[n][n], T[n][n];

	for(int i = 0; i < n; i++){
		F[i][i] = (boo[i] == 0)? 1 : 0;
		T[i][i] = (boo[i] == 1)? 1 : 0;
	}

	for(int m = 1; m < n; m++){
		for(int i = 0, j = m; j < n; i++, j++){
			T[i][j] = F[i][j] = 0;
			for(int g = 0; g < m; g++){
				int k = i + g;
				int tik = T[i][k] + F[i][k];
				int tkj = T[k+1][j] + F[k+1][j];
				
				if(oper[k] == 1){
					T[i][j] += T[i][k] * T[k+1][j];
					F[i][j] += (tik * tkj - T[i][k] * T[k+1][j]);
				}
				if(oper[k] == 2){
					F[i][j] += F[i][k] * F[k+1][j];
					T[i][j] += (tik*tkj - F[i][k]*F[k+1][j]);
				}
				if(oper[k] == 3){
					T[i][j] += F[i][k]*T[k+1][j] + T[i][k]*F[k+1][j];
					F[i][j] += T[i][k]*T[k+1][j] + F[i][k]*F[k+1][j];
				}
			}
		}
	}

	return T[0][n-1];
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int zz;

	cin>>zz;
	for(int z = 0; z < zz; z++){
		vector<int> boo, oper;

		int n;
		cin>>n;
		
		for(int i = 0; i < n; i++){
			string a;
			cin>>a;
			if(a == "true")
				boo.push_back(1);
			else if(a == "false")
				boo.push_back(0);
			else if(a == "and")
				oper.push_back(1);
			else if(a == "or")
				oper.push_back(2);
			else if(a == "xor")
				oper.push_back(3);
		}

		cout<<trivago(boo, oper, n/2 + 1)<<'\n';
	}
	
}
