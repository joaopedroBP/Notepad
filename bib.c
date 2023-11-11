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


int quantitycheck(tarefas *tfs){ // descobre a quantidade de tasks armazenadas na lista de tarefa(acabou não sendo usada, mas mantive caso precise usar no futuro).
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

    printf("Qual a categoria da sua tarefa?: ");
    scanf("%[^\n]",tarefa.categoria);
    getchar();

    printf("Em que estado está sua tarefa? Completa,Em andamento ou Nao iniciada: ");
    scanf("%[^\n]",tarefa.estado);
    getchar();

    tfs->tarefas[tfs->qtd] = tarefa;
    tfs->qtd += 1;

    return 0;
}

void menu(){ //Apresenta o menu de opções ao usuario.
    printf("\n");
    printf("0: Sair/salvar.\n"
    "1 - Anotar uma nova tarefa.\n"
    "2 - Listar tarefas existentes.\n"
    "3 - deletar uma tarefa.\n"
    "4 - filtrar por priioridade\n"
    "5 - Editar tarefa\n"
    "6 - filtrar por estado da tarefa\n"
    "7 - filtrar por categoria\n"
    "8 - filtrar por prioridade e por categoria\n"
    "9 - exportar por prioridade\n"
    "10 - exportar por categoria\n"
    "11 - exportar por prioridade e categoria\n");
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
        printf("Estado da tarefa: %s\n",tfs.tarefas[i].estado);
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

int list_by_pri(tarefas tfs){ //lista apenas as tarefas com a prioridade que o usuario dejesar!
    if(tfs.qtd == 0 ){
        printf("\nNenhuma tarefa salva!");
        return 1;
    }

    printf("\n");
    int pri;
    printf("Qual a prioridade das tarefas que vc dejesa ver?:");
    scanf("%d",&pri);

    printf("\nSua(as) tarefa(as):\n");

    for (int i = 0; i < tfs.qtd; i++) {
        if(tfs.tarefas[i].prioridade == pri){
            printf("\n");
            printf("Numero da sua tarefa: %d\n", i + 1);
            printf("Prioridade: %d\n", tfs.tarefas[i].prioridade);
            printf("Descricao: %s\n", tfs.tarefas[i].descricao);
            printf("Categoria: %s\n", tfs.tarefas[i].categoria);
            printf("Estado: %s\n", tfs.tarefas[i].estado);
        }else{
            continue;
        }
    }
    return 0;

}

int edit_task(tarefas *tfs){ //Função que permite editar tarefas existentes 
    int tarefa;
    int indicador;
    printf("Qual o numero da tarefa que deseja editar?: ");
    scanf("%d", &tarefa);//pega o indice da tarefa no struct

    tarefa--;
    if(tarefa >= tfs->qtd || tarefa < 0){
        printf("Tarefa não existe!");
        return 1;
    }

    printf("Deseja editar a prioridade(digite 1), a descricao(digite 2), a categoria(digite 3) ou o estado da tarefa(digite 4)?: ");
    scanf("%d", &indicador);// pega qual propriedade da tarefa que o usuario dejesa alterar

    switch(indicador){
        case 1:
            printf("Qual será a nova prioridade?: ");
            scanf("%d", &tfs->tarefas[tarefa].prioridade);
            getchar();
            break;
        case 2:
            printf("Qual será a nova descricao?: ");
            scanf(" %[^\n]", tfs->tarefas[tarefa].descricao);
            getchar();
            break;
        case 3:
            printf("Qual será a nova categoria?: ");
            scanf(" %[^\n]", tfs->tarefas[tarefa].categoria);
            getchar();
            break;
        case 4:
            printf("Qual será o novo estado?: ");
            scanf(" %[^\n]", tfs->tarefas[tarefa].estado);
            getchar();
            break;
        default:
            printf("Opção inválida!\n");
            return 1;
    }

    printf("Tarefa alterada com sucesso!");
    return 0;
}

int list_by_est(tarefas tfs){//lista apenas tarefas que possuem o estado que o usuario desejar!
    if(tfs.qtd == 0 ){
        printf("\nNenhuma tarefa salva!");
        return 1;
    }

    printf("\n");
    char status[200]; 
    printf("Qual o estado das tarefas que deseja ver?: ");
    scanf(" %[^\n]", status);

    printf("\nSua(s) tarefa(s):\n");
    int t = 10;
    while(t != 0){
        for (int i = 0; i < tfs.qtd; i++) {
            if (strcmp(tfs.tarefas[i].estado, status) == 0 && tfs.tarefas[i].prioridade){
                printf("\n");
                printf("Numero da sua tarefa: %d\n", i + 1);
                printf("Prioridade: %d\n", tfs.tarefas[i].prioridade);
                printf("Descricao: %s\n", tfs.tarefas[i].descricao);
                printf("Categoria: %s\n", tfs.tarefas[i].categoria);
                printf("Estado: %s\n", tfs.tarefas[i].estado);
            }
        }
        t--;
    }
    return 0;
}

int list_by_cat(tarefas tfs){//lista apenas as tarefas que possuem a prioridade que o usuario desejar
    if(tfs.qtd == 0 ){
        printf("\nNenhuma tarefa salva!");
        return 1;
    }

    printf("\n");
    char status[200]; 
    printf("Qual a categoria das tarefas que deseja filtrar?: ");
    scanf(" %[^\n]", status);

    //Armazena as posições das tarefas na lista

    int indices[tfs.qtd];
    for(int i = 0; i < tfs.qtd;i ++){
        indices[i] = i;
    } 

    tarefa troca;
    int temp;

    for(int i = 0; i < tfs.qtd; i++){
        for(int j = 0; j < tfs.qtd; j++){
            if(tfs.tarefas[j].prioridade  < tfs.tarefas[j + 1].prioridade){
                troca = tfs.tarefas[j];
                tfs.tarefas[j] = tfs.tarefas[j + 1];
                tfs.tarefas[j + 1] = troca;

                //para manter as posições originais das structs
                
                temp = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1 ] = temp;

            }
        }
    }

    printf("\nSua(s) tarefa(s):\n");

    for (int i = 0; i < tfs.qtd; i++) {
        if (strcmp(tfs.tarefas[i].categoria, status) == 0) {
            printf("\n");
            printf("Numero da sua tarefa: %d\n", indices[i] + 1);
            printf("Prioridade: %d\n", tfs.tarefas[i].prioridade);
            printf("Descricao: %s\n", tfs.tarefas[i].descricao);
            printf("Categoria: %s\n", tfs.tarefas[i].categoria);
            printf("Estado: %s\n", tfs.tarefas[i].estado);
        }
    }
    return 0;
}

int list_by_pri_cat(tarefas tfs){//lista apenas as tarefas com  prioridade e a categoria que o usuario desejar!
    if(tfs.qtd == 0){
        printf("Nenhuma tarefa salva!");
        return 1;
    }

    printf("\n");

    int pri;
    printf("Qual a prioridade das tarefas que vc dejesa ver?:");
    scanf("%d",&pri);

    printf("\n");
    char status[200]; 
    printf("Qual a categoria das tarefas que deseja ver?: ");
    scanf(" %[^\n]", status);

    printf("\nSuas tarefas:\n");

    for(int i = 0; i < tfs.qtd; i++){
        if(strcmp(tfs.tarefas[i].categoria, status) == 0 && tfs.tarefas[i].prioridade == pri){
            printf("\n");
            printf("Numero da sua tarefa: %d\n", i + 1);
            printf("Prioridade: %d\n", tfs.tarefas[i].prioridade);
            printf("Descricao: %s\n", tfs.tarefas[i].descricao);
            printf("Categoria: %s\n", tfs.tarefas[i].categoria);
            printf("Estado: %s\n", tfs.tarefas[i].estado);
        }
    }
    return 0;
}

int exp_by_pri(tarefas tfs){// cria um txt com as tarefas com a prioridade que o usuario desejar
    if(tfs.qtd == 0 ){
        printf("\nNenhuma tarefa salva!");
        return 1;
    }
    int pri;
    printf("Qual a prioridade das tarefas que dejesa exportar?: ");
    scanf("%d", &pri);

    FILE *f = fopen("Tarefas.txt","w");
    fprintf(f,"Suas tarefas\n");
    for(int i = 0; i < tfs.qtd ; i++){
        if(tfs.tarefas[i].prioridade == pri){
            fprintf(f,"numeros da tarefa: %d\n",i + 1);
            fprintf(f,"prioridade: %d\n",tfs.tarefas[i].prioridade);
            fprintf(f,"Categoria: %s\n",tfs.tarefas[i].categoria);
            fprintf(f,"Estado: %s\n",tfs.tarefas[i].estado);
            fprintf(f,"Descricao: %s\n",tfs.tarefas[i].descricao);
            fprintf(f,"\n\n");
        }
    }
    fclose(f);
    printf("Um arquvio Txt com as tarefas filtradas foi criado!\n");
    return 0;

}

int exp_by_cat(tarefas tfs){// cria um txt com as tarefas com a categoria que o usuarii dejesar
    if(tfs.qtd == 0 ){
        printf("\nNenhuma tarefa salva!");
        return 1;
    }

    printf("\n");
    char status[200]; 
    printf("Qual a categoria das tarefas que deseja ver?: ");
    scanf(" %[^\n]", status);

    //Armazena as posições das tarefas na lista

    int indices[tfs.qtd];
    for(int i = 0; i < tfs.qtd;i ++){
        indices[i] = i;
    } 

    tarefa troca;
    int temp;

    for(int i = 0; i < tfs.qtd; i++){
        for(int j = 0; j < tfs.qtd; j++){
            if(tfs.tarefas[j].prioridade  < tfs.tarefas[j + 1].prioridade){
                troca = tfs.tarefas[j];
                tfs.tarefas[j] = tfs.tarefas[j + 1];
                tfs.tarefas[j + 1] = troca;

                //para manter as posições originais das structs
                
                temp = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1 ] = temp;

            }
        }
    }

    FILE *f = fopen("Tarefas.txt","w");
    fprintf(f,"Suas tarefas\n");
    for(int i = 0; i < tfs.qtd ; i++){
        if(strcmp(tfs.tarefas[i].categoria, status) == 0){
            fprintf(f,"Numero da tarefa: %d\n", indices[i] + 1);
            fprintf(f,"prioridade: %d\n",tfs.tarefas[i].prioridade);
            fprintf(f,"Categoria: %s\n",tfs.tarefas[i].categoria);
            fprintf(f,"Estado: %s\n",tfs.tarefas[i].estado);
            fprintf(f,"Descricao: %s\n",tfs.tarefas[i].descricao);
            fprintf(f,"\n\n");
        }
    }
    fclose(f);
    printf("Um arquvio Txt com as tarefas filtradas foi criado!\n");
    return 0;
}

int exp_by_pri_cat(tarefas tfs){//cria um txt com tarefas com a prioridade e categoria que o usuario desejar
    if(tfs.qtd == 0 ){
        printf("\nNenhuma tarefa salva!");
        return 1;
    }
    int pri;
    printf("Qual a prioridade das tarefas que dejesa exportar?: ");
    scanf("%d", &pri);

    printf("\n");
    char status[200]; 
    printf("Qual a categoria das tarefas que deseja ver?: ");
    scanf(" %[^\n]", status);

    FILE *f = fopen("Tarefas.txt","w");
    fprintf(f,"Suas tarefas\n");
    for(int i = 0; i < tfs.qtd ; i++){
        if(tfs.tarefas[i].prioridade == pri && strcmp(tfs.tarefas[i].categoria, status) == 0){
            fprintf(f,"Numero da tarefa: %d\n",i + 1);
            fprintf(f,"prioridade: %d\n",tfs.tarefas[i].prioridade);
            fprintf(f,"Categoria: %s\n",tfs.tarefas[i].categoria);
            fprintf(f,"Estado: %s\n",tfs.tarefas[i].estado);
            fprintf(f,"Descricao: %s\n",tfs.tarefas[i].descricao);
            fprintf(f,"\n\n");
        }
    }
    fclose(f);
    printf("Um arquvio Txt com as tarefas filtradas foi criado!\n");
    return 0;
}
