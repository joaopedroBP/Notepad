#include "bib.h" 
#include <stdio.h>
#include <string.h>


int main(){
    tarefas tfs;
    //Checa se o arquivo existe com a função lerTasks
    int cod = lerTasks(&tfs,"tarefas.bin");
    if(cod == 1){
        tfs.qtd = 0;
    }

    int escolha;
    int T = 0;

    // Visão do usuario:
    while(T == 0){

        printf("\nSua agenda: \n");

        menu();

        printf("Qual a sua escolha?: ");
        scanf("%d",&escolha);
        
        switch(escolha){ //switch baseado na escolha do usuario.
            case 0:
                T += 1;
                break;
            case 1:
                createtask(&tfs);
                break;
            case 2: 
                listtask(tfs);
                break;
            case 3:
                deleattask(&tfs);
                break;
        }
    }

    cod = saveStruckt(&tfs,"tarefas.bin");
    if(cod == 1){ //verifica se o salvamento ocorreu.
        printf("falha ao salvar!");
    }else{
        printf("Tarefas Salvas com sucesso");
    }

    
    return 0;
}
