#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

typedef struct {
	char *id, *cnpj;
	int peso;
} Conteineres;

char *seqCnpj, *seqPeso;

void Transf(Conteineres *conteiner, Conteineres *temp, int inicio, int qtdConteiners, FILE *in){
	int i;
	for(i = inicio; i < qtdConteiners; i++){
		if (!feof(in)){
			temp[i].id = (char*) malloc(sizeof(char*) * 20);
			temp[i].cnpj = (char*) malloc(sizeof(char*) * 40);
			conteiner[i].id = (char*) malloc(sizeof(char*) * 20);
			conteiner[i].cnpj = (char*) malloc(sizeof(char*) * 40);
			
			if((conteiner[i].id == NULL) || (conteiner[i].cnpj == NULL))
				printf("Erro ao alocar memoria para os dados.\n");
			else{
				fscanf(in, "%s %s %d\n", conteiner[i].id, conteiner[i].cnpj, &conteiner[i].peso);
			//	cout << conteiner[i].id << " " << conteiner[i].cnpj << " " << conteiner[i].peso << endl;
			}
		}
	}
//	cout << endl;	
}

void CalcEcomp(Conteineres iconteiner, Conteineres jconteiner){
	char slinha[100];
	float diferenca = ((float)jconteiner.peso-(float)iconteiner.peso);
	float rpeso = (diferenca*100)/iconteiner.peso;
	
	if((strcmp(iconteiner.id, jconteiner.id) == 0) && (strcmp(iconteiner.cnpj, jconteiner.cnpj) != 0)){  
		snprintf(slinha, 100, "%s: %s<->%s\n", iconteiner.id, iconteiner.cnpj, jconteiner.cnpj);
		strcat(seqCnpj, slinha);
	}
	else if((strcmp(iconteiner.id, jconteiner.id) == 0) && (rpeso > 10)){
		snprintf(slinha, 100, "%s: %.0fkg (%.0f%%)\n", iconteiner.id, diferenca, rpeso);
		strcat(seqPeso, slinha);
	}	
}

void Intercalar(Conteineres *conteiner, Conteineres *temp, int inicio, int meio, int fim){
	int i = inicio, j = meio+1, k = inicio;
	//FILE *teste = fopen(/*argv[2]*/"ordenado.txt", "w");
	while(i <= meio && j <= fim){				
		if(strcmp(conteiner[i].cnpj, conteiner[j].cnpj) <= 0){  
			CalcEcomp(conteiner[i], conteiner[j]); 
			
			temp[k].id = (char*) malloc(sizeof(char*) * 20);
			temp[k].cnpj = (char*) malloc(sizeof(char*) * 40);
			
			strcpy(temp[k].id, conteiner[i].id);
			strcpy(temp[k].cnpj, conteiner[i].cnpj);
			temp[k].peso = conteiner[i].peso;
			k = k+1; 
			i = i+1;	
		}
		else{
			CalcEcomp(conteiner[i], conteiner[j]);
			
			temp[k].id = (char*) malloc(sizeof(char*) * 20);
			temp[k].cnpj = (char*) malloc(sizeof(char*) * 40);
			
			strcpy(temp[k].id, conteiner[j].id);
			strcpy(temp[k].cnpj, conteiner[j].cnpj);
			temp[k].peso = conteiner[j].peso;		
			k = k+1;
			j = j+1;
		}
	}

	while(i <= meio){
		strcpy(temp[k].id, conteiner[i].id);
		strcpy(temp[k].cnpj, conteiner[i].cnpj);
		temp[k].peso = conteiner[i].peso;
		k = k+1;
		i = i+1;
	}

	while(j <= fim){
		strcpy(temp[k].id, conteiner[j].id);
		strcpy(temp[k].cnpj, conteiner[j].cnpj);
		temp[k].peso = conteiner[j].peso;
		k = k+1; 
		j = j+1;
	}
		
	for(i = inicio; i <= fim; i++){
		strcpy(conteiner[i].id, temp[i].id);
		strcpy(conteiner[i].cnpj, temp[i].cnpj);
		conteiner[i].peso = temp[i].peso;
	//	cout << conteiner[i].id << " " << conteiner[i].cnpj << " " << conteiner[i].peso << endl;
		//fprintf(teste, "%s %s %d\n", conteiner[i].id, conteiner[i].cnpj, conteiner[i].peso);
	}
	//fclose(teste);

	/*for(i = inicio; i <= fim; i++){
		CalcEcomp(conteiner[0], conteiner[fim]);
	}*/
}

void Mergesort(Conteineres *conteiner, Conteineres *temp, int inicio, int fim){
	int meio = 0;
	if(inicio < fim){
		meio = (inicio+fim) / 2;
		Mergesort(conteiner, temp, inicio, meio);
		Mergesort(conteiner, temp, meio+1, fim);
		Intercalar(conteiner, temp, inicio, meio, fim);
	}
}

int main(int argc, char* argv[]){	
	int qtdConteineres = 0, qtdSelecionados = 0;
	char* aux = (char*) malloc(sizeof(char*) * 10); 
	
	FILE *in = fopen(/*argv[1]"porto.input_g.txt"*/, "r");
	FILE *out = fopen(/*argv[2]"saida_g.txt"*/, "w");		
	
	if(in != NULL)
	    cout << "O arquivo foi lido." << endl << endl;
	else
	   	cout << "Erro na abertura do arquivo." << endl << endl;		
	
	fgets(aux, 10, in);
	qtdConteineres = atoi(aux);
	cout << "Numero de conteineres cadastrados: " << qtdConteineres << endl;
	
	Conteineres *vconteineres = (Conteineres *) malloc(sizeof(Conteineres *) * (10*qtdConteineres)); 
	Conteineres *temp = (Conteineres *) malloc(sizeof(Conteineres *) * (10*qtdConteineres)); 
	
	seqCnpj = (char*) malloc(sizeof(char*) * (40*qtdConteineres)); 
	seqPeso = (char*) malloc(sizeof(char*) * (20*qtdConteineres));

	Transf(vconteineres, temp, 0, qtdConteineres, in);
	
	fgets(aux, 10, in);
	qtdSelecionados = atoi(aux);
	cout << "Numero de conteineres selecionados: " << qtdSelecionados << endl;
	Transf(vconteineres, temp, qtdConteineres, (qtdConteineres+qtdSelecionados), in);

	Mergesort(vconteineres, temp, 0, (qtdConteineres+qtdSelecionados)-1);	
	
	fprintf(out, "%s", seqCnpj);
	fprintf(out, "%s", seqPeso);

	cout << endl << "Fim do processo." << endl;
	
	free(aux);
	free(seqCnpj);
	free(seqPeso);
	free(vconteineres);
	free(temp);
	fclose(in);
	fclose(out);
	
	return 0;
}
