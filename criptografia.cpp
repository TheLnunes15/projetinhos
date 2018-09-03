#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <math.h>
#include <string.h>  

using namespace std;

long long int M = 1103515245, D = 12345, k, a, b, raiz, p;

long long int dom(long long int a, long long int b, long long m){
  long long int ns = 1ll;
  while(b){
    if(b&1) ns = (ns*a) % m;
        
    a = (a*a) % m;
    b = b/2;
  }
  return ns;
}

unsigned long int diffieHellman(unsigned long int c){
  long long int ax = dom(raiz, c, p);  
  unsigned long int key = (unsigned long int) ax;  
  return key;
} 

unsigned char G(unsigned long int k){
  static unsigned char j = 0;
  static unsigned long long int key = k;
  
  if(j == 0){
    key = M * key + D;
  }
  
  unsigned char z = (key >> j);
  j = (j + 8) % 32;
  return z;
}

int main(int argc, char **argv){
  ifstream entrada(argv[1]/*"entrada.txt"*/);
  ofstream saida(argv[2]/*"s.txt"*/);

  unsigned char r, A, B, dh;
  entrada >> A >> a >> B >> b >> dh >> dh >> p >> raiz;

  int n = 0;
  entrada >> n; 
  
  saida << "A->B: " << diffieHellman(a) << "\n";
  saida << "B->A: " << diffieHellman(b) << "\n";   
      
  long long int s = (long unsigned int) diffieHellman(b);
  long long int ax = dom(s,a,p);  
  unsigned long int S = (unsigned long int) ax;  

  string v;   
  getline(entrada, v);
   
  for(int i=0; i<n; i++){
    getline(entrada,v);
    int vtam = v.size();
    if(i % 2 == 0){
      saida << "A->B: ";
      int k=0;
      while(k < vtam){
        char ch = G(S);
        r = (unsigned char) v[k] ^ ch;
        saida << (int)r << " ";
        k++;
      }
      saida << "\n";
    }
    else{
      saida << "B->A: ";
      int k=0;
      while(k < vtam){
        char ch = G(S);
        r = (unsigned char) v[k] ^ ch;
        saida << (int)r << " ";
        k++;
      }
      saida << "\n";
    }     
  }  
  
  entrada.close();
  saida.close();

  return 0;
}
