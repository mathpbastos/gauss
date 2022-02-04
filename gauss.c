#include <stdio.h>
#include <stdlib.h>

float** criaMatriz(int N){
    float** matriz;
    // MATRIZ DE VARIÁVEIS
    // Alocação das linhas.
    matriz = (float**)malloc(N * sizeof(float*));
    // Alocação das colunas.
    for(int i=0; i<N; i++){
        matriz[i] = (float*)malloc(N * sizeof(float));
    }

    return matriz;
}

float* criaVetorColuna(int N){
    float* vetorColuna;
    // VETOR DOS TERMOS INDEPENDENTES
    vetorColuna = (float*)malloc(N * sizeof(float));

    return vetorColuna;
}

void imprimeMatriz(int N, float** matrizA, float* vetorB){

    for (int i=0; i < N; i++){
        for (int j=0; j <= N; j++){
            if(j != N){
                /* IFs utilizados apenas para adequação da exibição da matriz
                para ficar o mais alinhado possível. */
                if((matrizA[i][j] < 10 && matrizA[i][j] > 0) || matrizA[i][j] == 0){
                    printf("0%.2f\t", matrizA[i][j]);
                }
                else{
                    printf("%.2f\t", matrizA[i][j]);
                }
            }
            else{
                /* IFs utilizados apenas para adequação da exibição do vetor coluna
                para ficar o mais alinhado possível. */
                if((vetorB[i] < 10 && vetorB[i] > 0) || (vetorB[i] == 0)){
                    printf("0%.2f", vetorB[i]);
                }
                else{
                    printf("%.2f", vetorB[i]);
                }    
            }
            
        }
        printf("\n");
    }
}

float* eliminacaoGauss(int N, float** matriz, float* vetorColuna){
    // ALGORITMO DE ELIMINAÇÃO DOS COMPONENTES DA MATRIZ
    for(int i=0; i<N-1; i++){
        for(int j=(i+1); j<N; j++){
            // Multiplicador
            float m;
            m = (matriz[j][i])/(matriz[i][i]);
            matriz[j][i] = 0;
            for(int k=(i+1); k<N; k++){
                matriz[j][k] = matriz[j][k] - (m * matriz[i][k]);
            }
            vetorColuna[j] = vetorColuna[j] - (m * vetorColuna[i]);
        }
    }

    printf("\nMATRIZ PÓS ELIMINAÇÃO - [%d x %d] - SENDO %d VARIÁVEIS\n\n", (N), (N+1), N);
    imprimeMatriz(N, matriz, vetorColuna);

    // ALGORITMO DE SUBSTITUIÇÃO
    float* x = criaVetorColuna(N);
    int sum = 0;
    for(int i=N-1; i>=0; i--){
        sum = 0;
        x[N-1] = (vetorColuna[N-1])/(matriz[N-1][N-1]);
        for(int j=(i+1); j<N; j++){
            sum = sum + matriz[i][j] * x[j];
        }
        x[i] = (vetorColuna[i] - sum)/matriz[i][i];
    }
    return x;
}

void preencheMatrizManual(int N, float** matriz, float* vetorColuna){
    
    for(int i=0; i<N; i++){
        for(int j=0; j<=N; j++){
            /*Abstraindo a interação fazendo parecer que tudo está numa mesma matriz (como montamos para resolver),
            porém as igualdades estarão em um vetor separado (vetor coluna) */          
            if(j != N){
                printf("Informe o elemento %d, %d da matriz: ", (i+1), (j+1));
                scanf("%f", &matriz[i][j]);
            }
            else{
                printf("Informe o elemento %d, %d do vetor coluna: ", (i+1), (i+1));
                scanf("%f", &vetorColuna[i]);
            }
            
        }
    }
    printf("\nMATRIZ GERADA - [%d x %d] - SENDO %d VARIÁVEIS\n\n", (N+1), (N+1), N);
    imprimeMatriz(N, matriz, vetorColuna);

}

void preencheMatrizArquivo(int N, float** matriz, float* vetorColuna, FILE* f){
    int value;
        
    if(f == NULL){
        printf("Arquivo não encontrado.");
    }   
    else{
        // Preenchendo a matriz quadrada que deve ser = N (Excluindo os valores do vetor coluna).
        for(int i=0; i<N; i++){
            for(int j=0; j<=N; j++){
                if(j != N){
                    if(fscanf(f, "%d", &value) != EOF){
                        matriz[i][j] = value;
                    }
                }
                /* Se J == N significa que já estamos lendo o vetor coluna no arquivo,
                então colocamos o valor no vetor coluna. */
                else if(fscanf(f, "%d", &value) != EOF){
                    vetorColuna[i] = value;
                }  
            } 
        }

    }    
    printf("\nMATRIZ GERADA - [%d x %d] - SENDO %d VARIÁVEIS\n\n", (N), (N+1), N);
    imprimeMatriz(N, matriz, vetorColuna);

}

int main(){
    // VARIÁVEIS GLOBAIS
    int opt;
    float** matrizA;
    float* vetorB;
    float* x;
    int N;
    char fname[20];
    /* CRIAR AS VARIÁVEIS NA MAIN PARA TESTAR SE AS MESMAS MODIFICAM EM FUNÇÕES VOID*/
    
    do{
        printf("######## GAUSS SOLVER - MAIN MENU ########\n");
        printf("1 - Inserir a partir de um arquivo.\n");
        printf("2 - Inserir manualmente.\n");
        printf("3 - Sair.\n\n");
        printf("Digite a Opção: "); 
        scanf("%d", &opt);

        if((opt < 1) || (opt > 3)){
            printf("ERRO > Opção inválida, tente novamente.\n");
        }
        printf("\n");
    }while ((opt < 1) || (opt > 3));
    
    switch(opt){
            case 1:
                printf("INFORME O ARQUIVO DE ENTRADA:\n");
                printf("input-file -> ");
                scanf("%s", fname);
                FILE* f = fopen(fname, "r");
                fscanf(f, "%d", &N);
                matrizA = criaMatriz(N);
                vetorB = criaVetorColuna(N);
                preencheMatrizArquivo(N, matrizA, vetorB, f);
                x = eliminacaoGauss(N, matrizA, vetorB);
                fclose(f);
                break;
            case 2:
                printf("Informe a quantidade de variáveis do sistema: ");
                scanf("%d", &N);
                matrizA = criaMatriz(N);
                vetorB = criaVetorColuna(N);
                preencheMatrizManual(N, matrizA, vetorB);
                x = eliminacaoGauss(N, matrizA, vetorB);
                break;
            case 3:
                return 1;
                printf("\nFim do programa.");
                break;
            default:
                printf("ERRO> REINICIE O PROGRAMA");
                break;
    }

    printf("\n###### SOLUÇÃO ######\n\n");
    imprimeMatriz(N, matrizA, vetorB);
    printf("\nSENDO: { ");
    for(int i=0; i<N; i++){
        printf("x%d = %.2f ", (i+1), x[i]);
    }
    printf("}");
    printf("\n\nFim do programa.");
    return 0;

}