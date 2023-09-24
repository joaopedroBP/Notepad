#include "bib.h"
#include <stdio.h>
#include <string.h>

tarefas tfs;

int lerTasks(tarefas *tfs, char nome[]){ //ler tarefas já armazenadas no arquivo.
    FILE *f = fopen(nome,"rb");
    if(f == NULL){ // verifica se o arquivo não existe.
        return 1;
    }
    fread(tfs,sizeof(tarefas),1,f); 
    fclose(f);

    return 0 ;

}


int quantitycheck(tarefas *tfs){ // descobre a quantidade de tasks armazenadas na lista de tarefa.
    int count = 0;
    FILE *f = fopen("tarefas.bin", "rb");
    fread(&tfs->qtd, sizeof(int), 1, f);
    fclose(f);
    return count;
}

int createtask(tarefas *tfs){ // cira uma nova tarefa. 
    tarefa tarefa;

    printf("\n");

    if(tfs->qtd == 100){
        printf("\nlimite de tarefas exedido!\n");
        return 0; 
    }

    while(tarefa.prioridade > 10 || tarefa.prioridade <= 0){
        printf("Qual a prioridade(1/10) da sua tarefa?: ");
        scanf("%d",&tarefa.prioridade);
        getchar();
        if(tarefa.prioridade > 10 || tarefa.prioridade <= 0){
            printf("Entrada invalada, entre com uma prioridade apropriada!\n");
        }
    }
 
    printf("Descreva a sua tarefa: ");
    scanf("%[^\n]",tarefa.descricao);
    getchar();

    printf("Qual a categoria da sua tarefa?:");
    scanf("%[^\n]",tarefa.categoria);
    getchar();

    tfs->tarefas[tfs->qtd] = tarefa;
    tfs->qtd += 1;

    return 0;
}

void menu(){ //Apresenta o menu de opções ao usuario.
    printf("\n");
    printf("0: Sair/salvar.\n"
    "1: Anotar uma nova tarefa.\n"
    "2: Listar tarefas existentes.\n"
    "3: deletar uma tarefa.\n");
}

int saveStruckt(tarefas *tfs , char nome[]){ //salva novas tarefas ao arquivo binario.

    FILE *f = fopen(nome, "wb");

    if(f == NULL){
        return 1;
    }    

    fwrite(tfs,sizeof(tarefas), 1, f);
    fclose(f);
    
}

int listtask(tarefas tfs){ // lista todas as tarefas.
    if(tfs.qtd == 0 ){
        printf("\nNenhuma tarefa salva!");
        return 1;
    }

    printf("\nSua(as) tarefa(as):\n");

    for (int i = 0; i < tfs.qtd; i++) {
        printf("\n");
        printf("Numero da sua tarefa: %d\n", i + 1);
        printf("Prioridade: %d\n", tfs.tarefas[i].prioridade);
        printf("Descricao: %s\n", tfs.tarefas[i].descricao);
        printf("Categoria: %s\n", tfs.tarefas[i].categoria);
    }
    return 0;
}

int deleattask(tarefas *tfs){ // deleta uma tarefa escolhida pelo usuario.    
    printf("\n");
    int indice;
    printf("Qual o numero da tarefa que dejesa deletar?: ");
    scanf("%d", &indice);
    
    indice --;
    for(;indice < tfs->qtd; indice++){
        tfs->tarefas[indice].prioridade = tfs->tarefas[indice + 1].prioridade;
        strcpy(tfs->tarefas[indice].descricao,tfs->tarefas[indice + 1].descricao);
        strcpy(tfs->tarefas[indice].categoria,tfs->tarefas[indice + 1].categoria);
    }
    
    printf("\ntarefa deletada! \n");
    tfs->qtd --;
    return 0;

}



