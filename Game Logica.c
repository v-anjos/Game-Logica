#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_ALUNOS 1000

// ============================
// ESTRUTURA ALUNO
// ============================

struct Aluno{
    char nome[50];
    float nota;
};

// ============================
// FUNÇÕES LÓGICAS
// ============================

char VF(){
    return rand()%2 ? 'T':'F';
}

char NOT(char A){
    return A=='T'?'F':'T';
}

char AND(char A, char B){
    return (A=='T' && B=='T')?'T':'F';
}

char OR(char A, char B){
    return (A=='T' || B=='T')?'T':'F';
}

char IMPLICA(char A, char B){
    return (A=='T' && B=='F')?'F':'T';
}

char IFF(char A, char B){
    return (A==B)?'T':'F';
}

char calcula(char A, char B, int op){

    switch(op){

        case 0: return AND(A,B);
        case 1: return OR(A,B);
        case 2: return IMPLICA(A,B);
        case 3: return IFF(A,B);

    }

    return 'F';
}

char simbolo(int op){

    switch(op){

        case 0: return '^';
        case 1: return 'v';
        case 2: return '>';
        case 3: return '=';

    }

    return '?';
}

// ============================
// GERADOR EXTREMO
// ============================

char gerarFormula(char *expr, int tamanho){

    if(tamanho == 0){

        char v = VF();
        sprintf(expr,"%c",v);
        return v;

    }

    char esq[500];
    char dir[500];

    int tamEsq = rand()%tamanho;
    int tamDir = tamanho-1-tamEsq;

    char valEsq = gerarFormula(esq,tamEsq);
    char valDir = gerarFormula(dir,tamDir);

    int op = rand()%4;

    char resultado = calcula(valEsq,valDir,op);

    sprintf(expr,"(%s %c %s)",esq,simbolo(op),dir);

    return resultado;
}

// ============================
// RANKING
// ============================

void salvarResultado(char nome[], float nota){

    FILE *arquivo = fopen("resultados.txt","a");

    if(arquivo==NULL) return;

    fprintf(arquivo,"%s %.2f\n",nome,nota);

    fclose(arquivo);
}

void mostrarRanking(){

    FILE *arquivo;

    struct Aluno alunos[MAX_ALUNOS];

    int total=0,i,j;

    arquivo=fopen("resultados.txt","r");

    if(arquivo==NULL){

        printf("\nSem ranking ainda\n");
        return;
    }

    while(fscanf(arquivo,"%s %f",
    alunos[total].nome,
    &alunos[total].nota)==2){

        total++;

    }

    fclose(arquivo);

    for(i=0;i<total-1;i++)
    for(j=0;j<total-1;j++)

    if(alunos[j].nota < alunos[j+1].nota){

        struct Aluno temp=alunos[j];
        alunos[j]=alunos[j+1];
        alunos[j+1]=temp;

    }

    printf("\n====== RANKING ======\n\n");

    for(i=0;i<total;i++)
    printf("%dº %s %.1f%%\n",i+1,alunos[i].nome,alunos[i].nota);

}

// ============================
// MAIN
// ============================

int main(){

    srand(time(NULL));

    char nome[50];
    int nivel, perguntas, acertos=0;
    char resp;
    int i;

    printf("=====================================\n");
    printf(" Sistema de Avaliacao de Logica\n");
    printf("=====================================\n\n");

    printf("Digite seu nome: ");
    fgets(nome,50,stdin);
    nome[strcspn(nome,"\n")] = 0;

    printf("\nBem-vindo, %s\n\n", nome);

    printf("=========== NIVEIS ===========\n\n");

    printf("1 - INICIANTE\n");
    printf("Operacoes entre valores simples\n");
    printf("Exemplo: T ^ F\n");
    printf("Conectivos: AND(^), OR(v), IMPLICA(>), IFF(=)\n\n");

    printf("2 - INTERMEDIARIO\n");
    printf("Operacoes entre duas formulas\n");
    printf("Exemplo: (~T ^ F) > (T v F)\n");
    printf("Exige conhecimento de precedencia\n\n");

    printf("3 - AVANCADO\n");
    printf("Operacoes entre tres formulas\n");
    printf("Exemplo: ((T v F) ^ (F > T)) = (T ^ F)\n");
    printf("Alta complexidade logica\n\n");

    printf("4 - EXTREMO\n");
    printf("Formulas totalmente aleatorias\n");
    printf("O aluno escolhe o tamanho\n");
    printf("Nivel universitario\n\n");

    printf("=====================================\n");

    printf("Escolha o nivel: ");
    scanf("%d",&nivel);

    printf("Numero de perguntas: ");
    scanf("%d",&perguntas);

    for(i=1;i<=perguntas;i++){

        printf("\nPergunta %d\n",i);

        if(nivel==4){

            int tamanho;

            printf("Tamanho da formula: ");
            scanf("%d",&tamanho);

            char expr[500];

            char correta = gerarFormula(expr,tamanho);

            printf("%s = ",expr);

            scanf(" %c",&resp);

            if(resp==correta || resp==correta+32){

                printf("Correto\n");
                acertos++;

            }else{

                printf("Errado. Resposta: %c\n",correta);

            }

        }

        else{

            char A=VF();
            char B=VF();
            int op=rand()%4;

            char correta=calcula(A,B,op);

            printf("%c %c %c = ",A,simbolo(op),B);

            scanf(" %c",&resp);

            if(resp==correta || resp==correta+32){

                printf("Correto\n");
                acertos++;

            }else{

                printf("Errado. Resposta: %c\n",correta);

            }

        }

    }

    float nota=(acertos*100.0)/perguntas;

    printf("\n=====================================\n");

    printf("RELATORIO FINAL\n");

    printf("Aluno: %s\n",nome);
    printf("Acertos: %d\n",acertos);
    printf("Erros: %d\n",perguntas-acertos);
    printf("Nota: %.1f%%\n",nota);

    salvarResultado(nome,nota);

    mostrarRanking();

    return 0;
}
