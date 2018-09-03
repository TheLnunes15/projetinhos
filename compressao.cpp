#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

using namespace std;

typedef unsigned int oxe;
int atualMax = 0, SIZE = 0, set = 0, sizeR = 0, acc = 0;

FILE *input, *output;

typedef struct no{
	struct no *dir, *esq; 
	int simb; 
	oxe freq; 
}no;

typedef struct fila{
	oxe tam, cap; 
	no **heap;
}fila;

typedef struct tabela{ 
	char *bits; 
	int simb, hex, freq, tam;
}tabela;

typedef struct tRle{ 
	int simb, len;
}tRle;

tabela* tab;
tRle* cmpRle;

oxe fEsq(int i){
	return ((2*i)+1);
}

oxe fDir(int i){
	return ((2*i)+2);
}

void heapify(no**V, oxe T, oxe i){
	no* aux;
	oxe P = i, E = fEsq(i), D = fDir(i);
	
	if(E < T && V[E]->freq < V[P]->freq) P = E;
	if(D < T && V[D]->freq < V[P]->freq) P = D;
	
	if(P != i ){
		aux = V[i];
		V[i] = V[P];
		V[P] = aux;
		heapify(V,T,P);
	} 
}

void inserirNo(fila* fMin, oxe freq, oxe simb, no* esq, no* dir){		
	no* novo = new no;
	novo->esq = esq; 
	novo->dir = dir; 
	novo->simb = simb; 
	novo->freq = freq; 

	fMin->heap[fMin->tam] = novo; 
	fMin->tam++; 	

	for(int i = fMin->tam/2; i>=0;i--){
		heapify(fMin->heap,fMin->tam,i);
	}
}

no* extraiNo(fila* fMin){	
	no* aux = fMin->heap[0];	
	fMin->heap[0] = fMin->heap[fMin->tam - 1]; 
	fMin->tam--; 
	heapify(fMin->heap,fMin->tam,0);
	return aux;
}

no* constrArvore(oxe* V, oxe* H, oxe n){
	fila* fMin = new (struct fila);  
	fMin->tam = 0; 
	fMin->cap = SIZE; 
	fMin->heap = (no**) malloc (fMin->cap*sizeof(no*)); 

	for(oxe i = 0; i < n; i++){
		inserirNo(fMin,H[i],V[i],NULL,NULL); 
	}	
	while(fMin->tam > 1){ 
		no* x = extraiNo(fMin);
		no* y = extraiNo(fMin);
		inserirNo(fMin,x->freq + y->freq,'\0',x,y); 
	}
	return extraiNo(fMin); 
}

void compacEimpr(oxe* V){
	if(set == 0){
		char bits_8[9] = {0};
		int n = 0, simb = 0, k = 0,hex;
		for(int i = 0; i < atualMax; i++){
			simb = V[i];
			n = tab[simb].tam;	
			for(int j = 0; j < n; j++){
				bits_8[k] = tab[simb].bits[j];
				k++; 
				if(k==8){
					hex = (int)strtol(bits_8,NULL,2); 
					if(i!= atualMax-1)fprintf(output,"%02X ",hex);
					else fprintf(output,"%02X ",hex); 
					k = 0;
				}
			}
		}
		if(k){
			while(k<8){
				bits_8[k] = '0';
				k++;
			}
			hex = (int)strtol(bits_8,NULL,2);
			fprintf(output,"%02X",hex);
			k = 0;
		}
		fprintf(output,"\n");
	}
	else{
		for(int i = 0; i < acc/8; i++){
			fprintf(output,"%02X ",0X00);
		}
		fprintf(output,"\n");	
	}
}

void caminhoArvore(no* raiz, char* C, int t){
	if(raiz->esq){
		C[t] = '0';
		caminhoArvore(raiz->esq,C,t+1);
	}
	if(raiz->dir){
		C[t] = '1';
		caminhoArvore(raiz->dir,C,t+1);	
	}
	if(!(raiz->esq) && !(raiz->dir)){
		tab[raiz->simb].freq = raiz->freq; 
	                    tab[raiz->simb].tam = t; 
	                    for(int i = 0; i < t; i++){
	                                    tab[raiz->simb].bits[i] = C[i]; 
	                    }
	                    tab[raiz->simb].bits[t] = '\0';
	                    acc+=t; 
	}
}

void huffman(oxe* V, oxe* H, oxe* real, oxe max){
	char* s = (char*)calloc(256,sizeof(char));
	memset(s,0,256);
	if(max>1){	
		no* raiz = constrArvore(V,H,max);
		int index = 0;
		caminhoArvore(raiz,s,index);
		set = 0;		
		free(raiz);
	}
	else{
		acc = atualMax;
		while(acc%8>0) acc++;
		set = 1;
	}
	
	free(s);	
}

void rle(oxe* V){
	int len, i=0, j=0;	
	cmpRle = (tRle*)calloc(atualMax,sizeof(tRle));
	
	for(i=0, j=0; i < (int)atualMax; i++,j++){
		len = 1;
		while(i+1 < (int)atualMax && V[i] == V[i+1]){
			len++;
			i++;
		}
		cmpRle[j].len = len; 
		cmpRle[j].simb = V[i]; 
		sizeR = j+1;
	}
}

int calcHist(oxe* simb, oxe* freq, oxe* H){ 
	int j = 0;
	for(int i = 0; i < 256; i++){
		if(H[i]>0){
			simb[j] = i;
			freq[j] = H[i];
			j++;
		}		
	}	
	return j;	
}

int main(int argc, char* argv[]){	
	input = fopen(/*"compressao.input_g.txt"/*argv[1]*/, "r");
	output = fopen(/*"saida.txt"/*argv[2]*/, "w");

	int qtdSeq = 0, t = 0, hex = 0, n = 0; 
	float porHuff, porRle;
	char* cmpHuff = (char*)calloc(100000, sizeof(char)); 
	tab = (tabela*)malloc(sizeof(tabela)*256);
	
	oxe* V = (oxe*)calloc(10001,sizeof(oxe)); 
	oxe* H = (oxe*)calloc(256,sizeof(oxe)); 
	oxe* freq = (oxe*)calloc(256,sizeof(oxe)); 
	oxe* simb = (oxe*)calloc(256,sizeof(oxe)); 

	memset(cmpHuff,0,100000);
	
	for(int i = 0; i < 256; i++){		
		H[i] = 0;
		tab[i].simb = 0;
		tab[i].bits = (char*)calloc(256,sizeof(char));
		memset(tab[i].bits,0,256);		
	}		
		
	fscanf(input,"%d", &qtdSeq); 
	for(int i = 0; i < qtdSeq; i++){		
		fscanf(input,"%d",&t);
		atualMax = t;
		for(int j = 0; j < t; j++){		
			fscanf(input,"%X",&V[j]);
			hex = V[j];
			H[hex]++; 		
		}
		n = calcHist(simb,freq,H);		
		SIZE = n;
		huffman(simb,freq,V,n); 	
		rle(V); 

		if(set == 0){
			int compressao = 0;
		                    for(int i = 0; i < atualMax;i++){
		                    	for(int j = 0; j < tab[V[i]].tam; j++){
		                    		compressao++;
			                    }	
		                    }
		                    while(compressao%8>0) compressao++; 
		                    float bits = (float)compressao;
		                    float n_bits = atualMax * 8.0;
		                    porHuff = (bits/n_bits)*100.0; 
	                    }
	                    else{
	                    	float bits = (float)acc;
		                    float n_bits = atualMax * 8.0;
		                    porHuff = (bits/n_bits)*100.0; 
		}

		float bits = (2*8)*sizeR; 
	                    float n_bits = atualMax*8;
	                    porRle = (bits/n_bits)*100.0;	

		if(porHuff < porRle){ 
		       fprintf(output,"%d: [HUF %.2f%%] ",i,porHuff);
		      compacEimpr(V);
	                    }
	                    else if (porRle < porHuff){ 
		        fprintf(output,"%d: [RLE %.2f%%] ",i,porRle);
		        for(int i = 0; i < (int)sizeR; i++){
		        	if(i != sizeR-1)
		        	          fprintf(output,"%02X %02X ",cmpRle[i].len,cmpRle[i].simb);
		                    else
		                              fprintf(output,"%02X %02X",cmpRle[i].len,cmpRle[i].simb);		
	                            }
	                            fprintf(output,"\n");
	                    }
	                    else{ 
		       fprintf(output,"%d: [HUF %.2f%%] ",i,porHuff);
		       compacEimpr(V);
		       fprintf(output,"%d: [RLE %.2f%%] ",i,porRle);
		        for(int i = 0; i < (int)sizeR; i++){
		        	if(i != sizeR-1)
		        	          fprintf(output,"%02X %02X ",cmpRle[i].len,cmpRle[i].simb);
		                    else
		                              fprintf(output,"%02X %02X",cmpRle[i].len,cmpRle[i].simb);		
	                            }
	                            fprintf(output,"\n");
	                    }
		
		for(int r = 0; r < 256; r++){ 
			freq[r] = simb[r] = H[r] = 0;
			
		}
		memset(cmpHuff,0,100000);
		acc = 0;
	}

	free(cmpHuff);

	free(V);
	free(H);
	free(freq);
	free(simb);
	
	fclose(input);
	fclose(output);
	
	return 0;	
}
