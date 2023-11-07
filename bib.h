// Structs:

typedef struct {
    int prioridade;
    char descricao[300];
    char categoria[100];
    char estado[200];
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
int list_by_pri(tarefas tfs);
int edit_task(tarefas *tfs);
int list_by_est(tarefas tfs);
int list_by_cat(tarefas tfs);
int list_by_pri_cat(tarefas tfs);
int exp_by_pri(tarefas tfs);
int exp_by_cat(tarefas tfs);
int exp_by_pri_cat(tarefas tfs);



