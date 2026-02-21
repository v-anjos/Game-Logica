#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <string.h>

#define MAX_ALUNOS 1000

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

        case 0: return '^'; // AND
        case 1: return 'v'; // OR
        case 2: return '>'; // IMPLICA
        case 3: return '='; // IFF

    }

    return '?';
}
struct Aluno{

    char nome[50];
    float nota;

};



void salvarResultado(char nome[], float nota){

    FILE *arquivo;

    arquivo = fopen("resultados.txt","a");

    if(arquivo==NULL){

        printf("Erro ao salvar\n");
        return;

    }

    fprintf(arquivo,"%s %.2f\n",nome,nota);

    fclose(arquivo);

}



void mostrarRanking(){

    FILE *arquivo;

    struct Aluno alunos[MAX_ALUNOS];

    int total=0;

    arquivo = fopen("resultados.txt","r");

    if(arquivo==NULL){

        printf("\nNenhum resultado ainda.\n");
        return;

    }


    while(fscanf(arquivo,"%s %f",
    alunos[total].nome,
    &alunos[total].nota)==2){

        total++;

    }

    fclose(arquivo);



    // ordenar (bubble sort)

    for(int i=0;i<total-1;i++){

        for(int j=0;j<total-1;j++){

            if(alunos[j].nota < alunos[j+1].nota){

                struct Aluno temp = alunos[j];
                alunos[j] = alunos[j+1];
                alunos[j+1] = temp;

            }

        }

    }



    printf("\n====== RANKING DA TURMA ======\n\n");

    for(int i=0;i<total;i++){

        printf("%dº %s - %.2f%%\n",
        i+1,
        alunos[i].nome,
        alunos[i].nota);

    }

}


int main(){

    srand(time(NULL));

    char nome[50];
    int nivel, perguntas, acertos=0;
    char resp;

    printf("=====================================\n");
    printf(" SISTEMA DE AVALIACAO DE LOGICA\n");
    printf("=====================================\n\n");

    printf("Digite seu nome: ");
    fgets(nome,50,stdin);

    nome[strcspn(nome,"\n")] = 0;


    printf("\nBem-vindo, %s\n", nome);

    printf("\nNIVEIS DISPONIVEIS:\n\n");

    printf("1 - INICIANTE\n");
    printf("Explicacao:\n");
    printf("Operacoes entre valores simples T e F\n");
    printf("Conectivos: AND(^), OR(v), NOT(~), IMPLICA(>), IFF(=)\n\n");


    printf("2 - INTERMEDIARIO\n");
    printf("Explicacao:\n");
    printf("Operacoes entre duas formulas logicas\n");
    printf("Exemplo: (~T ^ F) > (T v F)\n\n");


    printf("3 - AVANCADO\n");
    printf("Explicacao:\n");
    printf("Operacoes entre tres formulas logicas\n");
    printf("Exemplo: ((T v F) ^ (F > T)) = (T ^ F)\n\n");


    printf("Escolha o nivel: ");
    scanf("%d",&nivel);

    printf("Quantas perguntas deseja responder? ");
    scanf("%d",&perguntas);



    for(int i=1;i<=perguntas;i++){

        printf("\nPergunta %d:\n",i);


        // INICIANTE
        if(nivel==1){

            char A=VF();
            char B=VF();

            if(rand()%2)
                A=NOT(A);

            int op=rand()%4;

            printf("%c %c %c = ",A,simbolo(op),B);

            char correta=calcula(A,B,op);

            scanf(" %c",&resp);

            if(resp==correta || resp==correta+32){

                printf("Correto\n");
                acertos++;

            }
            else
                printf("Errado. Resposta: %c\n",correta);

        }



        // INTERMEDIARIO
        else if(nivel==2){

            char A=VF();
            char B=VF();
            char C=VF();
            char D=VF();

            int op1=rand()%4;
            int op2=rand()%4;
            int opFinal=rand()%4;

            char f1=calcula(NOT(A),B,op1);
            char f2=calcula(C,D,op2);

            printf("(~%c %c %c) %c (%c %c %c) = ",
            A,simbolo(op1),B,
            simbolo(opFinal),
            C,simbolo(op2),D);

            char correta=calcula(f1,f2,opFinal);

            scanf(" %c",&resp);

            if(resp==correta || resp==correta+32){

                printf("Correto\n");
                acertos++;

            }
            else
                printf("Errado. Resposta: %c\n",correta);

        }



        // AVANCADO
        else{

            char A=VF();
            char B=VF();
            char C=VF();
            char D=VF();
            char E=VF();
            char F=VF();

            int op1=rand()%4;
            int op2=rand()%4;
            int op3=rand()%4;
            int opFinal=rand()%4;

            char f1=calcula(A,B,op1);
            char f2=calcula(C,D,op2);
            char f3=calcula(E,F,op3);

            char temp=calcula(f1,f2,opFinal);
            char correta=calcula(temp,f3,opFinal);

            printf("((%c %c %c) %c (%c %c %c)) %c (%c %c %c) = ",
            A,simbolo(op1),B,
            simbolo(opFinal),
            C,simbolo(op2),D,
            simbolo(opFinal),
            E,simbolo(op3),F);

            scanf(" %c",&resp);

            if(resp==correta || resp==correta+32){

                printf("Correto\n");
                acertos++;

            }
            else
                printf("Errado. Resposta: %c\n",correta);

        }

    }



    float aproveitamento = (acertos*100.0)/perguntas;

    printf("\n=====================================\n");

    printf("RELATORIO FINAL - %s\n", nome);

    printf("=====================================\n");

    printf("Acertos: %d\n",acertos);

    printf("Erros: %d\n", perguntas-acertos);

    printf("Aproveitamento: %.1f%%\n",aproveitamento);

	  salvarResultado(nome, aproveitamento);

	  mostrarRanking();


    if(aproveitamento>=90)
        printf("Classificacao: EXCELENTE\n");

    else if(aproveitamento>=70)
        printf("Classificacao: BOM\n");

    else if(aproveitamento>=50)
        printf("Classificacao: REGULAR\n");

    else
        printf("Classificacao: INSUFICIENTE\n");

}
