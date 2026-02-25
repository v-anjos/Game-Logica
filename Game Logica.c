#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_ALUNOS 1000


void sobreSoftware(){
    printf("\n=====================================\n");

    printf("LOGICCLASS - Software Educacional\n\n");

    printf("Sistema para ensino e avaliacao de Logica Proposicional\n");

    printf("\nNiveis disponiveis:\n");

    printf("Iniciante\n");
    printf("Intermediario\n");
    printf("Avancado\n");
    printf("Extremo\n");

    printf("\nDesenvolvido para uso educacional\n");

    printf("=====================================\n");

}
struct Aluno{
    char nome[50];
    float nota;
};
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


void iniciarAvaliacao(){
	

    char nome[50];
    int nivel, perguntas, acertos=0;
    char resp;
    int i;

    printf("=====================================\n");
    printf(" Sistema de Avaliacao de Logica\n");
    printf("=====================================\n\n");

    printf("Digite seu nome: ");
	scanf(" %[^\n]", nome);
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
    if(perguntas<=0){
	printf("Numero invalido\n");
	return;
}

    for(i=1;i<=perguntas;i++){

        printf("\nPergunta %d\n",i);

        if(nivel==4){

            int tamanho;

            printf("Tamanho da formula: ");
            scanf("%d",&tamanho);
                if(tamanho < 0) tamanho = 0;
    			if(tamanho > 10) tamanho = 10;

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

        else if(nivel==1){

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
else if(nivel==2){

    char A=VF();
    char B=VF();
    char C=VF();

    int op1=rand()%4;
    int op2=rand()%4;

    char parte1 = calcula(NOT(A),B,op1);

    char correta = calcula(parte1,C,op2);

    printf("(~%c %c %c) %c %c = ",
    A,simbolo(op1),B,
    simbolo(op2),
    C);

    scanf(" %c",&resp);

    if(resp==correta || resp==correta+32){
        printf("Correto\n");
        acertos++;
    }else{
        printf("Errado. Resposta: %c\n",correta);
    }

}
else if(nivel==3){

    char expr[500];

    char correta = gerarFormula(expr,2);

    printf("%s = ",expr);

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


}
int main(){

    srand(time(NULL));

    int opcao;

    do{

        printf("\n=====================================\n");
        printf("             GAME LOGICA \n");
        printf("=====================================\n");

        printf("1 - Iniciar Avaliacao\n");
        printf("2 - Ranking\n");
        printf("3 - Sobre\n");
        printf("4 - Sair\n");

        printf("\nEscolha: ");
        scanf("%d",&opcao);
        getchar(); // limpa ENTER

        switch(opcao){

            case 1:
                iniciarAvaliacao();
                break;

            case 2:
                mostrarRanking();
                break;

            case 3:
                sobreSoftware();
                break;

            case 4:
                printf("\nEncerrando...\n");
                break;

            default:
                printf("\nOpcao invalida\n");

        }

    }while(opcao!=4);

    return 0;
}
