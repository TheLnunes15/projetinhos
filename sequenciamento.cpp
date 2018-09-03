#include <iostream>
#include <string>
#include <fstream>
#include <math.h>

using namespace std;

typedef struct gene{
    float qtd;
    int flag; 
    string g;   
} gene;

typedef struct resposta{
  int p; 
  string c; 
} resposta;

gene *genes; 
  
float result(int tam){
 int i, count=0;
 for(i=0; i<tam; i++){
    count = count + genes[i].flag;  
 }   
 return roundf((((float)count / (float)tam )*100));  
}

void calc_tabela(int *tab, string P) {
  unsigned int i, m = P.length();
  int j = -1;
  for(i=0; i<m; i++){
    tab[i]=-1;  
  } 
  for(i = 1; i < m; i++) {
    while(j >= 0 && P[j + 1] != P[i]) j = tab[j];
    if(P[j + 1] == P[i]) j++;
   tab[i] = j;
  }
}

int subcd=3;

void busca_kmp(int *tab, string T, string P, int rol){
	unsigned int i, n = T.length();
	int j = -1;

	calc_tabela(tab, P); 

	for(i=0; i<n; i++){
    if((P[j+1]!=T[i]) && (j>=subcd-1)){
      genes[rol].qtd = genes[rol].qtd+(j+1);  
	    P = P.substr(j+1, P.length());
	    T = T.substr(i+1, T.length());
  
	    busca_kmp(tab, T, P, rol);
	    
	    break;	       
	  }  
	  
	  while(j>=0 && P[j+1] != T[i])
      j = tab[j]; 

	  if(P[j+1] == T[i]) 
      j++;    

	  if((i == n-1) && (j>=subcd-1)){
      genes[rol].qtd = genes[rol].qtd+(j+1); 		   
	  }     
	} 
} 

void ordenar(resposta a[], int tam){
  int v1, i, j;
  resposta v2;
    for(i=1; i<tam; i++){
      v1 = a[i].p;
	    v2 = a[i];
      for (j=i-1; j>=0 && a[j].p < v1; j--){
        a[j+1] = a[j];
      }
      a[j+1] = v2;
    }
}


int main(int argc, char **argv){
  int *tb, i, j, k, qtd_genes, aux_numGenes=0, num_doencas=0;
  string DNA, count_gene, codigo;
  resposta *s;
  float p;

  ifstream input(/*argv[1]"sequenciamento.input_g.txt"*/);
  ofstream output(/*argv[2]"saida.txt"*/);  
  
  input >> subcd >> DNA >> num_doencas;
  
  s = new resposta [num_doencas];
  
  for(i=0; i<num_doencas; i++){    
    input >> codigo >> aux_numGenes;

      genes = new gene [aux_numGenes];
      qtd_genes = aux_numGenes;  
    
    for(j=0; j<aux_numGenes; j++){
      input >> count_gene;

      genes[j].g = count_gene;  
      genes[j].qtd = 0; 
      tb = new int [genes[j].g.length()];  
      busca_kmp(tb, DNA, genes[j].g, j);
    }  
    
   delete [] tb;
   for(k=0; k<aux_numGenes; k++){
      p = genes[k].qtd/(float) genes[k].g.length();  
      if(p >= ((float)0.9)){
         genes[k].flag = 1;
      }
      else{          
        genes[k].flag = 0;
      }    
   }  
    s[i].c = codigo; 
    s[i].p = result(aux_numGenes);  
  }
    
  ordenar(s, num_doencas);
  
  for(i=0; i<num_doencas; i++){
    output << s[i].c << ": " << s[i].p << "%" << endl;    
  }

  delete [] s;
  input.close();
  output.close();
  return 0;
}
