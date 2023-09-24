// Structs:

typedef struct {
    int prioridade;
    char descricao[300];
    char categoria[100];
}tarefa;

typedef struct{
    tarefa tarefas[100];
    int qtd;
}tarefas;


// funções:
void menu();
int quantitycheck(tarefas *tfs);
int createtask(tarefas *tfs);
int deleattask(tarefas *tfs);
int listtask(tarefas tfs );
int lerTasks(tarefas *tfs,char nome[]);
int saveStruckt(tarefas *tfs , char nome[]);   



