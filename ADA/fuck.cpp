#include<iostream>
#include<cstdio>
#define LIM 1000000007

using namespace std;

unsigned long long fuck(unsigned long long a, unsigned long long b, int n){
	unsigned long long ans[4] = {1, 0, 0, 1}, base[4] = {1, 1, 1, 0}, temp_ans[4], temp_base[4];

	while(n != 0){
		for(int i = 0; i < 4; i++)
			temp_base[i] = base[i];
		
		if(n & 1){
			for(int i = 0; i < 4; i++)
				temp_ans[i] = ans[i];

			ans[0] = (temp_ans[0] * temp_base[0] + temp_ans[1] * temp_base[2]) % LIM;
			ans[1] = (temp_ans[0] * temp_base[1] + temp_ans[1] * temp_base[3]) % LIM;
			ans[2] = (temp_ans[2] * temp_base[0] + temp_ans[3] * temp_base[2]) % LIM;
			ans[3] = (temp_ans[2] * temp_base[1] + temp_ans[3] * temp_base[3]) % LIM;
			
		
		}
		base[0] = (temp_base[0] * temp_base[0] + temp_base[1] * temp_base[2]) % LIM;
		base[1] = (temp_base[0] * temp_base[1] + temp_base[1] * temp_base[3]) % LIM;
		base[2] = (temp_base[2] * temp_base[0] + temp_base[3] * temp_base[2]) % LIM;
		base[3] = (temp_base[2] * temp_base[1] + temp_base[3] * temp_base[3]) % LIM;

		#ifdef DEBUG
			printf("ans: %llu %llu\n     %llu %llu\n", ans[0], ans[1], ans[2], ans[3]);
			printf("base: %llu %llu\n      %llu %llu\n", base[0], base[1], base[2], base[3]);
		#endif
		n >>= 1;
	}


	return (ans[0] * b + ans[1] * a) % LIM;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t;

	cin>>t;

	for(int i = 0; i < t; i++){
		unsigned long long a, b;
		int n;

		cin>>a>>b>>n;

		if(n == 1)	cout<<a<<"\n";
		else if(n == 2)	cout<<b<<"\n";
		else
			cout<<fuck(a, b, n-2)<<"\n";
	}

	return 0;
}
