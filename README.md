# GAUSS SOLVER - MANUAL

Gauss Solver é um programa escrito em C que soluciona sistemas lineares através da notação de matrizes sem a utilização da técnica de pivoteamento.

## Início

Ao iniciar o programa, a tela abaixo será apresentada:

~~~
######## GAUSS SOLVER - MAIN MENU ########
1 - Inserir a partir de um arquivo.
2 - Inserir manualmente.
3 - Sair.

Digite a Opção: 
~~~

> Nos exemplos abaixo, usaremos o seguinte sistema de exemplo:
> x1 + x2 + x3 = 13
> -3x1 - x2 + 4x3 = 8
> 2x1 + 14x2 + 5x3 = 50

### 1 - Inserir a partir de um arquivo
Ao selecionar a opção `1`, você poderá utilizar um arquivo para preenchimento da matriz. Nesse exemplo utilizamos o `input.in` para inserção dos dados, na seguinte forma:
~~~
Digite a Opção: 1

INFORME O ARQUIVO DE ENTRADA:
input-file -> input.in

Sendo:
input.in

3
1 2 4 13
-3 -1 4 8
2 14 5 50
~~~

As linhas do arquivo são, respecitvamente:
1. Quantidade de variáveis do sistema;
2.  As demais linhas são os multiplicadores seguidos de seus termos independentes.

### 2 - Inserir Manualmente
Ao selecionar a opção `2`, o programa irá solicitar a quantidade de variáveis seguida dos termos do sistema, na seguinte forma:
Utilizaremos o mesmo sistema do exemplo acima `input.in`.
~~~
Digite a Opção: 2

Informe a quantidade de variáveis do sistema: 3
Informe o elemento 1, 1 da matriz: 1
Informe o elemento 1, 2 da matriz: 2
Informe o elemento 1, 3 da matriz: 4
Informe o elemento 1, 1 do vetor coluna: 13
Informe o elemento 2, 1 da matriz: -3
Informe o elemento 2, 2 da matriz: -1
Informe o elemento 2, 3 da matriz: 4
Informe o elemento 2, 2 do vetor coluna: 8
Informe o elemento 3, 1 da matriz: 2
Informe o elemento 3, 2 da matriz: 14
Informe o elemento 3, 3 da matriz: 5
Informe o elemento 3, 3 do vetor coluna: 50
~~~

### 3 - Sair
Encerra a  aplicação.

### Etapas Da Resolução
Após a inserção dos dados, manualmente ou através de um arquivo, o processo é análogo.

Passando pelos seguintes passos:

##### Impressão da matriz gerada
~~~
MATRIZ GERADA - [3 x 4] - SENDO 3 VARIÁVEIS

01.00   02.00   04.00   13.00
-3.00   -1.00   04.00   08.00
02.00   14.00   05.00   50.00
~~~

##### Impressão da matriz escalonada
Após a aplicação do algoritmo de eliminação, a matriz modificada é apresentada na tela:
~~~
MATRIZ PÓS ELIMINAÇÃO - [3 x 4] - SENDO 3 VARIÁVEIS

01.00   02.00   04.00   13.00
00.00   05.00   16.00   47.00
00.00   00.00   -35.00  -70.00
~~~

##### Impressão da solução

A saída da solução será a matriz escalonada bem como o vetor das variáveis com seus respectivos valores.
~~~
###### SOLUÇÃO ######

01.00   02.00   04.00   13.00
00.00   05.00   16.00   47.00
00.00   00.00   -35.00  -70.00

SENDO: { x1 = -1.00 x2 = 3.00 x3 = 2.00 }

Fim do programa.
~~~