//Luana Miho Yasuda 42148677
#define _GNU_SOURCE 
#include <stdlib.h> 
#include <malloc.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <signal.h> 
#include <sched.h> 
#include <stdio.h> 
#include <pthread.h>

// 64kB stack 
#define FIBER_STACK 1024*64 
#define MAX_TRANSFERENCIAS 100

struct c { 
    int saldo; 
}; 

typedef struct c conta; 
conta from, to; 
int valor; 

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

struct transferencia_args {
    conta* from;
    conta* to;
    int valor;
};

int transferencia( struct transferencia_args *arg) { 
    pthread_mutex_lock(&mutex);
    if (arg->from->saldo >= arg->valor){
        arg->from->saldo -= arg->valor; 
        arg->to->saldo += arg->valor; 
    } else {
        printf("Transferência não foi concluída pois saldo de c1 é 0!\n"); 
        printf("Saldo de c1: %d\n", arg->from->saldo); 
        printf("Saldo de c2: %d\n", arg->to->saldo);
        pthread_mutex_unlock(&mutex);
        return 0; 
    }
    printf("Transferência concluída com sucesso!\n"); 
    printf("Saldo de c1: %d\n", arg->from->saldo); 
    printf("Saldo de c2: %d\n", arg->to->saldo); 
    pthread_mutex_unlock(&mutex);
    return 0; 
} 

int main() { 
    void* stack; 
    pid_t pid; 
    int i; 
    stack = malloc( FIBER_STACK ); 
    if ( stack == 0 ) { 
        perror("malloc: could not allocate stack"); 
        exit(1); 
    } 
    from.saldo = 100; 
    to.saldo = 100; 
    printf( "Transferindo 10 para a conta c2\n" ); 
    valor = 10; 
    for (i = 0; i < MAX_TRANSFERENCIAS; i++) { 
        struct transferencia_args args = { &from, &to, valor };
        pid = clone( (int ()(void *))transferencia, (char) stack + FIBER_STACK, SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, &args );
        if ( pid == -1 ) { 
            perror( "clone" ); 
            exit(2); 
        } 
        // Adiciona waitpid aqui para esperar a transação atual ser concluída antes de começar a próxima
        waitpid(pid, NULL, 0);
    } 
    free( stack ); 
    printf("Transferências concluídas e memória liberada.\n"); 
    return 0; 
}