# projetinhos

**Projeto e Análise de Algoritmos (PAA)**


[**Porto**] - *Mergesort* 

* A empresa de automação portuária Poxim Tech está desenvolvendo um sistema para movimentação automatizada dos contêineres de carga de origem internacional no Porto de Sergipe para maximizar a eficiência da fiscalização aduaneira. 
  Todos os contêineres possuem um cadastro eletrônico contendo informações sobre o código do contêiner, o CNPJ da empresa importadora e o peso líquido em quilos da carga. 
  A inspeção dos contêineres é realizada sempre que existe alguma divergência entre as informações cadastradas, como o CNPJ informado ou a diferença percentual maior do que 10% no peso líquido. 
  Na triagem dos contêineres são fiscalizados os contêineres com a seguinte ordem de prioridade: 
  1. Divergência de CNPJ
  2. Maior diferença percentual de peso líquido

[**Quicksort**] - *Quicksort*

* A empresa de desenvolvimento de sistemas Poxim Tech está realizando um experimento para determinar qual variante do algoritmo de ordenação crescente do Quicksort apresenta o melhor resultado para um determinado conjunto de sequências numéricas.
  Neste experimento foram utilizadas as seguintes variantes: particionar padrão (PP), particionar por mediana de 3 (PM), particionar por pivô aleatório (PA), hoare padrão (HP), hoare por mediana de 3 (HM) e hoare por pivô aleatório (HA).
Técnicas de escolha do pivô:
  * Mediana de 3: V1 = V[n/4], V2 = V[n/2], V3 = [3n/4]
  * Aleatório: Va = V [ini + |V [ini]| mod n]
  
[**Sequenciamento**] - *KMP*

* A empresa de biotecnologia Poxim Tech está desenvolvendo um sistema de diagnóstico para doenças genéticas, comparando a sequência de DNA com genes conhecidos.
  A sequência de DNA é composta exclusivamente pelos símbolos A, C, G e T para codificação dos genes.
  Uma doença genética possui até 10 genes associados, cada um deles com sequências de tamanho entre 100 até 1000, denotados por letras maiúsculas e números entre 4 e 8 caracteres. 
  Para tratar os efeitos da mutação nos genes que alteram sua codificação, é feita a busca por combinações que possuam o tamanho mínimo de subcadeia, com pelo menos 90% de compatibilidade total para manifestação da doença.
  No diagnóstico será calculada a probabilidade de manifestação da doença, de acordo com a quantidade de genes detectados.
  
[**Compressão**] - *RLE e Huffman*

* A empresa de telecomunicações Poxim Tech está desenvolvendo um sistema para compressão de dados para minimizar a utilização de banda na transmissão dos dados, avaliando qual técnica apresenta a melhor taxa de compressão.
  São fornecidas sequências de bytes em formato hexadecimal que possuem valores entre 0x00 até 0xFF, com tamanho máximo de 10000 caracteres.
  As codificações de 8 bits Run-Length Encoding (RLE) e de Huffman (HUF) são utilizadas para compressão.
  A técnica que apresentar menor quantidade de bytes é selecionada para a transmissão dos dados.
  
[**Labirinto**] - *Backtracking*

* A empresa de tecnologia Poxim Tech está desenvolvendo um robô humanoide que é capaz de se deslocar de forma totalmente autônoma e sem precisar do conhecimento prévio do ambiente físico no qual está localizado.
  Durante o seu deslocamento, que é feito um passo por vez, podem ser realizadas as seguintes operações, listadas em ordem de prioridade:
    * Direita (D) 
    * Frente (F) 
    * Esquerda (E)
    * Trás (T)
    
  A medida que vai explorando o ambiente, o robô cria uma mapa interno para as rotas exploradas. 
  Caso uma rota não gere uma solução, outro caminho deve ser escolhido para ser explorado até que a solução seja obtida ou que não existam mais opções.
  Para demonstrar suas habilidades exploratórias, são criados labirintos com exatamente 1 entrada e até 1 saída, com tamanho máximo de 100 por 100 posições.
  É possível que nenhuma rota seja possível para atravessar o labirinto criado, mas quando existe uma saída, é sempre um espaço livre na borda do labirinto que não é o ponto de partida.
  
 [**Criptografia**]
 
* A empresa de tecnologia Poxim Tech está aplicando técnicas de criptografia em todos os seus sistemas de transmissão de dados, visando para proteger os dados de acessos não autorizados.
  Para verificar as características dos algoritmos rapidamente, sem necessidade de aritmética de precisão arbitrária, são utilizadas chaves privadas e públicas com tamanho máximo de 32 bits. 
  A criptografia simétrica utilizada é baseada no gerador binário G com chave privada de 32 bits, com fatores de chave M = 1103515245 e D = 12345.
  Para garantir o sigilo das chaves privadas utilizadas entre as partes A e B é utilizado o método de Diffie-Hellman para a troca de chaves.
  As mensagens de texto possuem somente símbolos com códigos ASCII entre 33 e 126, com tamanho máximo de 1000 caracteres.
