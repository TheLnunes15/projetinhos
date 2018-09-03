#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <math.h>

using namespace std;

typedef struct desloca{
   char D, F, E, T;
   int a, b;
} desloca; 

int main(int argc, char **argv){
	ifstream entrada(argv[1]/*"entrada.txt"*/);
    ofstream saida(argv[2]/*"s.txt"*/);

	int labNum;
	entrada >> labNum;
	
	for(int contLab = 0; contLab < labNum; contLab++){		
		int lg, alt;

		saida << "L" << contLab << ":" << endl;		
		entrada >> lg >> alt;
		
		char lab[alt][lg];
		int ini[2], fim[2] = {-1,-1};
		
		for(int altCont = 0; altCont < alt; altCont++){
			for(int lgCont = 0; lgCont < lg; lgCont++){				
				entrada >> lab[altCont][lgCont];			
				if(lab[altCont][lgCont] == 'X'){
					ini[0] = altCont;
					ini[1] = lgCont;
				}			
			}		
		}

		saida << "INICIO [" << ini[0] << "," << ini[1] << "]" << endl;
		
		int	roboIndica[2] = {ini[0], ini[1]}, idVia = 0;
		int viaTam = (alt-2)*(lg-2)+1, ant[2] = {ini[0], ini[1]};
		desloca via[viaTam];
		
		while(fim[0] == -1){			
			int D[2] = {roboIndica[0], roboIndica[1]+1}, F[2] = {roboIndica[0]-1, roboIndica[1]};
			int	E[2] = {roboIndica[0], roboIndica[1]-1}, T[2] = {roboIndica[0]+1, roboIndica[1]};			
		
			if(0 <= D[0] && D[0] < alt && 0 <= D[1] && D[1] < lg && lab[D[0]][D[1]] == '0' && (ant[0] != D[0] || ant[1] != D[1])){
				via[idVia].a = roboIndica[0];
				via[idVia].b = roboIndica[1];
				
				via[idVia].D = 'L';				
				idVia++;

				saida << "D [" << roboIndica[0] << "," << roboIndica[1] << "]->[" << D[0] << "," << D[1] << "]" << endl;
				
				ant[0] = roboIndica[0];
				ant[1] = roboIndica[1];
				
				lab[roboIndica[0]][roboIndica[1]] = '1';
				roboIndica[0] = D[0];
				roboIndica[1] = D[1];				
			}
			else if(0 <= F[0] && F[0] < alt && 0 <= F[1] && F[1] < lg && lab[F[0]][F[1]] == '0' && (ant[0] != F[0] || ant[1] != F[1])){
				via[idVia].a = roboIndica[0];
				via[idVia].b = roboIndica[1];
				
				via[idVia].D = 'L';
				via[idVia].F = 'L';
				idVia++;
				
				saida << "F [" << roboIndica[0] << "," << roboIndica[1] << "]->[" << F[0] << "," << F[1] << "]" << endl;
				
				ant[0] = roboIndica[0];
				ant[1] = roboIndica[1];
				
				lab[roboIndica[0]][roboIndica[1]] = '1';
				roboIndica[0] = F[0];
				roboIndica[1] = F[1];
			}
			else if(0 <= E[0] && E[0] < alt && 0 <= E[1] && E[1] < lg && lab[E[0]][E[1]] == '0' && (ant[0] != E[0] || ant[1] != E[1])){
				via[idVia].a = roboIndica[0];
				via[idVia].b = roboIndica[1];
				
				via[idVia].D = 'L';
				via[idVia].F = 'L';
				via[idVia].E = 'L';				
				idVia++;

				saida << "E [" << roboIndica[0] << "," << roboIndica[1] << "]->[" << E[0] << "," << E[1] << "]" << endl;
				
				ant[0] = roboIndica[0];
				ant[1] = roboIndica[1];
				
				lab[roboIndica[0]][roboIndica[1]] = '1';
				roboIndica[0] = E[0];
				roboIndica[1] = E[1];
			}
			else if(0 <= T[0] && T[0] < alt && 0 <= T[1] && T[1] < lg && lab[T[0]][T[1]] == '0' && (ant[0] != T[0] || ant[1] != T[1])){
				via[idVia].a = roboIndica[0];
				via[idVia].b = roboIndica[1];
				
				via[idVia].D = 'L';
				via[idVia].F = 'L';
				via[idVia].E = 'L';
				via[idVia].T = 'L';				
				idVia++;
				
	            saida << "T [" << roboIndica[0] << "," << roboIndica[1] << "]->[" << T[0] << "," << T[1] << "]" << endl;
				
				ant[0] = roboIndica[0];
				ant[1] = roboIndica[1];
				
				lab[roboIndica[0]][roboIndica[1]] = '1';
				roboIndica[0] = T[0];
				roboIndica[1] = T[1];				
			}
			else{
				if(roboIndica[0] == ini[0] && roboIndica[1] == ini[1]){
					break;
				} 
				else{
					saida << "BT [" << ant[0] << "," << ant[1] << "]<-[" << roboIndica[0] << "," << roboIndica[1] << "]" << endl;
				}				
				
				lab[roboIndica[0]][roboIndica[1]] = '1';

				via[idVia].D = 'Z';
				via[idVia].F = 'Z';
				via[idVia].E = 'Z';
				via[idVia].T = 'Z';				
								
				lab[roboIndica[0]][roboIndica[1]] = '1';
				roboIndica[0] = ant[0];
				roboIndica[1] = ant[1];
				
				idVia--;
				
				ant[0] = via[idVia-1].a;
				ant[1] = via[idVia-1].b;				
			}
			if((roboIndica[0] == 0 || roboIndica[0]== alt-1) || (roboIndica[1] == 0 || roboIndica[1] == lg-1)){				
				fim[0] = roboIndica[0];
				fim[1] = roboIndica[1];
			}				
		}
		
		if(fim[0] == -1 || fim[1] == -1){
			saida << "SEM SAIDA" << endl;
		} 
		else{
			saida << "SAIDA [" << fim[0] << "," << fim[1] << "]" << endl;
		}
	}	
	
    entrada.close();
    saida.close();
	
	return 0;
}
