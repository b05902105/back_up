#include "game.h"

double d[5][5][151];

double max(double a, double b){
	if(a > b)
		return a;
	else
		return b;
}

double recursive(int is_cal[5][5][151], int p, int q, int s){
//	printf("p = %d, q = %d, s = %d\n", p, q, s);
	if(is_cal[p][q][s] == 1){
		return d[p][q][s];
	}
	else{
		if(p == 0 && q == 0){
			is_cal[p][q][s] = 1;
			if(s > 150)
				d[p][q][s] = 0;
			else
				d[p][q][s] = s;
			return d[p][q][s];
		}
		
		for(int i = 1; i <= 6; i++){
				
			if(p == 0){
				d[p][q][s] += recursive(is_cal, p, q-1, s + i);	
			}
			else if(q == 0){
				d[p][q][s] += recursive(is_cal, p-1, q, s + i*10);
			}
			else{
				d[p][q][s] += max(recursive(is_cal, p-1, q, s + i*10), recursive(is_cal, p, q-1, s + i));
			}
		}
		d[p][q][s] /= 6;
	//	printf("d[%d][%d][%d] = %f\n", p, q, s, d[p][q][s]);
		is_cal[p][q][s] = 1;
		return d[p][q][s];
	}
}	

// My strategy to play the dice sum game
// Returns 0 for ten's position, 1 for one's position
int myStrategy(int gameState[4][2], int diceValue){
	static int initialized;		// Static variable, default to zero
	// Add your declaration of DP structure here
	


	if (!initialized){
		initialized=1;
		// Populate your structure here		
		int is_cal[5][5][151] = {0};
		d[4][4][0] = recursive(is_cal, 4, 4, 0);
	}
	int tenAvailCount=0;	// No. of available ten's position
	for (int j=0; j<4; j++)
		if (gameState[j][0]<=0) {tenAvailCount=4-j; break;}
	int oneAvailCount=0;	// No. of available one's position
	for (int j=0; j<4; j++)
		if (gameState[j][1]<=0) {oneAvailCount=4-j; break;}
	if ((tenAvailCount!=0)&&(oneAvailCount==0)) return(0);
	if ((tenAvailCount==0)&&(oneAvailCount!=0)) return(1);
//	My strategy
	int strategy=3;
	int nextPos, total;
	switch(strategy){
		case 1:
			nextPos=rand()%2;
			break;
		case 2:
			nextPos=0;
			total=(gameState[0][0]+gameState[1][0]+gameState[2][0]+gameState[3][0])*10
					+(gameState[0][1]+gameState[1][1]+gameState[2][1]+gameState[3][1]);
			if (total+diceValue*10>SCOREMAX)
				nextPos=1;
			break;
		case 3:
			// Add your own strategy (which uses the DP structure) here
			total=(gameState[0][0]+gameState[1][0]+gameState[2][0]+gameState[3][0])*10
					+(gameState[0][1]+gameState[1][1]+gameState[2][1]+gameState[3][1]);
			if(d[tenAvailCount-1][oneAvailCount][total + 10*diceValue] > d[tenAvailCount][oneAvailCount-1][total + diceValue])
				nextPos = 0;
			else
				nextPos = 1;

			break;
		default:
			printf("Error!\n");
	}
	return(nextPos);
}
