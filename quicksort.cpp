#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

typedef struct{
	int *qtdMov, *elem;
	int ind[6], qtdElem;
} Vetores; 

int cont;

int MedianaDeTres(Vetores vet, int inicio, int fim){
	int aPivo[3], auxP = 0, auxI = 0, ind[3], i, j; 
	
	aPivo[0] = vet.elem[fim/4]; 
	ind[0] = fim/4;
	aPivo[1] = vet.elem[fim/2]; 
	ind[1] = fim/2;
	aPivo[2] = vet.elem[(3*fim)/4]; 
	ind[2] = (3*fim)/4;
	
	for(i = 3; i >= 1; i--){
		for(j = 1; j < i; j++){
			if(aPivo[j-1] > aPivo[j]){
				auxP = aPivo[j];
				aPivo[j] = aPivo[j-1];
				aPivo[j-1] = auxP;
		
				auxI = ind[j];
				ind[j] = ind[j-1];
				ind[j-1] = auxI;
			}	
		}
	}
	auxP = 0;
	
	auxP = vet.elem[fim];
	vet.elem[fim] = aPivo[1];
	vet.elem[ind[1]] = auxP;
	cont++; 
	
	return vet.elem[fim];
}

int Randomico(Vetores vet, int inicio, int fim){
	int pivo, vaux, pos = inicio + (abs(vet.elem[inicio]) % fim);
	
	if(pos > fim)
		pos = fim;
	
	pivo = vet.elem[pos];
	
	vaux = vet.elem[fim]; 
	vet.elem[fim] = pivo;
	vet.elem[pos] = vaux;
	cont++; 
	
	return vet.elem[fim];
}

int ParticionarPadrao(Vetores vet, int inicio, int fim){
	int pivo = vet.elem[fim], iaux = (inicio-1), jaux, vaux; 
	
	for(jaux = inicio; jaux < fim; jaux++){
		if(vet.elem[jaux] <= pivo){
			iaux = iaux + 1;
			vaux = vet.elem[iaux];
			vet.elem[iaux] = vet.elem[jaux];
			vet.elem[jaux] = vaux;
			cont++;
		}
	}
	
	vaux = vet.elem[iaux+1];
	vet.elem[iaux+1] = vet.elem[fim];
	vet.elem[fim] = vaux;
	cont++;
	return iaux+1;
}

int ParticionarMediana(Vetores vet, int inicio, int fim){ 
	int pivo = MedianaDeTres(vet, inicio, fim), iaux = (inicio-1), jaux, vaux;
 
	for(jaux = inicio; jaux < fim; jaux++){
		if(vet.elem[jaux] <= pivo){
			iaux = iaux + 1;
			vaux = vet.elem[iaux];
			vet.elem[iaux] = vet.elem[jaux];
			vet.elem[jaux] = vaux;
			cont++;  
		}
	}
	
	vaux = vet.elem[iaux+1];
	vet.elem[iaux+1] = vet.elem[fim];
	vet.elem[fim] = vaux;
	cont++; 
	return iaux+1;
}

int ParticionarRandomico(Vetores vet, int inicio, int fim){
	int pivo = Randomico(vet, inicio, fim), iaux = (inicio-1), jaux = inicio, vaux;
	
	for(jaux = inicio; jaux < fim; jaux++){
		if(vet.elem[jaux] <= pivo){
			iaux = iaux + 1;
			vaux = vet.elem[iaux];
			vet.elem[iaux] = vet.elem[jaux];
			vet.elem[jaux] = vaux;
			cont++;
		}
	}
	
	vaux = vet.elem[iaux+1];
	vet.elem[iaux+1] = vet.elem[fim];
	vet.elem[fim] = vaux;
	cont++;
	return iaux+1;
}

int HoarePadrao(Vetores vet, int inicio, int fim){
	int pivo = vet.elem[inicio], vaux, iaux = inicio, jaux = fim;
	
	while(iaux < jaux){
		while((vet.elem[iaux] <= pivo)){	
			iaux++;
		}
		while((vet.elem[jaux] > pivo)){ 
			jaux--; 
		}
		if(iaux < jaux){
			vaux = vet.elem[iaux];
			vet.elem[iaux] = vet.elem[jaux];
			vet.elem[jaux] = vaux;
			cont++;
		}
		cont++;
	}
	return jaux;
}

int HoareMediana(Vetores vet, int inicio, int fim){
	int pivo = MedianaDeTres(vet, inicio, fim), vaux, iaux = inicio, jaux = fim;
	
	while(iaux < jaux){
		while((vet.elem[iaux] <= pivo)){
			iaux++;
		}
		while((vet.elem[jaux] > pivo)){ 
			jaux--; 
		}
		if(iaux < jaux){
			vaux = vet.elem[iaux];
			vet.elem[iaux] = vet.elem[jaux];
			vet.elem[jaux] = vaux;
			cont++;
		}
		cont++;
	}
	return jaux;
}

int HoareRandomico(Vetores vet, int inicio, int fim){
	int pivo = Randomico(vet, inicio, fim), vaux, iaux = inicio, jaux = fim;
	
	while(iaux < jaux){
		while((vet.elem[iaux] <= pivo)){
			iaux++;
		}
		while((vet.elem[jaux] > pivo)){ 
			jaux--; 
		}
		if(iaux < jaux){
			vaux = vet.elem[iaux];
			vet.elem[iaux] = vet.elem[jaux];
			vet.elem[jaux] = vaux;
			cont++;
		}
		cont++;
	}
	return jaux;
}

void quicksort(Vetores vet, int var, int inicio, int fim){
    int pivo = -1;
	if(inicio < fim){	
		switch(var){
			case 0: pivo = ParticionarPadrao(vet, inicio, fim); break;
			case 1: pivo = ParticionarMediana(vet, inicio, fim); break;
			case 2: pivo = ParticionarRandomico(vet, inicio, fim); break;			
			case 3: pivo = HoarePadrao(vet, inicio, fim); break;
			case 4: pivo = HoareMediana(vet, inicio, fim); break;
			case 5: pivo = HoareRandomico(vet, inicio, fim); break;
			default: cout << "Erro. Opcao incorreta das funcoes." << endl; break;			
		}
		quicksort(vet, var, inicio, pivo-1);
		quicksort(vet, var, pivo+1, fim);
	}	
	cont++;
}

int main(int argc, char* argv[]){
	int i = 0, j = 0, k = 0, l = 0, z = 0, auxInd, auxPassos, qtdVet = 0;
	char *tempElem, *tempArq = (char*) malloc (sizeof(char*) * (2800)); 
	Vetores* vet;
	
	FILE *in = fopen(/*"quicksort.input.txt"argv[1]*/, "r");
	FILE *out = fopen(/*"saida.txt"argv[2]*/, "w");
	
	if(in != NULL)
	    cout << "O arquivo foi lido." << endl << endl;
	else
	   	cout << "Erro na abertura do arquivo." << endl << endl;	

	fgets(tempArq, 100, in);
	qtdVet = atoi(tempArq);		
	cout << "Quantidade total de vetores: " << qtdVet << endl;
	vet = (Vetores*) malloc(sizeof(Vetores*) * (20*qtdVet)); 
	
	while(!feof(in)){
		if(fgets(tempArq, 100, in))
			vet[i].qtdElem = atoi(tempArq);
		
		vet[i].elem = (int*) malloc(sizeof(int*) * (20*vet[i].qtdElem));
		tempElem = (char*) malloc(sizeof(char*) * (vet[i].qtdElem*6));

		if(fgets(tempArq, (vet[i].qtdElem*(vet[i].qtdElem + 3)), in)){ 
			tempElem = strtok(tempArq, " ");
			for(j = 0; j < vet[i].qtdElem; j++){
				vet[i].elem[j] = atoi(tempElem);
				tempElem = strtok(NULL, " ");
			}
		}
		i++;
	}
	
	cout << "Ordenando com o Quicksort..." << endl;
	for(i = 0; i < qtdVet; i++){
		vet[i].qtdMov = (int*) malloc(sizeof(int*) * 36);
		for(j = 0; j < 6; j++){
			cont = 0;
			quicksort(vet[i], j, 0, (vet[i].qtdElem-1)); 
			vet[i].qtdMov[j] = cont; 
			vet[i].ind[j] = j;
		}

		for(k = 6; k >= 1; k--){
			for(l = 1; l < k; l++){
				if(vet[i].qtdMov[l-1] > vet[i].qtdMov[l]){
					auxPassos = vet[i].qtdMov[l];
					vet[i].qtdMov[l] = vet[i].qtdMov[l-1];
					vet[i].qtdMov[l-1] = auxPassos;
					
					auxInd = vet[i].ind[l];
					vet[i].ind[l] = vet[i].ind[l-1];
					vet[i].ind[l-1] = auxInd;
				}
			}
		}

		fprintf(out, "%d: N(%d) ", i, vet[i].qtdElem);
		for(z = 0; z < 6; z++){
			switch(vet[i].ind[z]){
				case 0: fprintf(out, "PP"); break;
				case 1: fprintf(out, "PM"); break;
				case 2: fprintf(out, "PA"); break;
				case 3: fprintf(out, "HP"); break;
				case 4: fprintf(out, "HM"); break;
				case 5: fprintf(out, "HA"); break;
				default: cout << "Valor incorreto" << endl; break;
			}
			fprintf(out, "(%d) ", vet[i].qtdMov[z]);
		}
		fprintf(out, "\n");
	}

	cout << endl << "Fim do processo." << endl;	
	
	fclose(in);
	fclose(out);
	free(tempArq);
	free(tempElem);
	free(vet);	
	
	return 0;
}
