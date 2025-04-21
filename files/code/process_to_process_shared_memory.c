// Para compilar: gcc producer_consumer.c -o producer_consumer

#include <stdio.h>         // Biblioteca padrão de entrada/saída (printf, etc.)
#include <stdlib.h>        // Biblioteca padrão para funções utilitárias (exit, malloc, etc.)
#include <sys/types.h>      // Tipos de dados do sistema operacional (pid_t)
#include <unistd.h>         // Funções relacionadas ao sistema Unix (fork, wait, sleep)
#include <sys/shm.h>        // Funções para trabalhar com memória compartilhada
#include <string.h>        // Biblioteca padrão para manipulação de strings (strcpy)

#define SHM_KEY 1234      // Chave única que identifica a seção de memória compartilhada.  Deve ser consistente entre o pai e o filho.
#define SHARED_SIZE 1024   // Tamanho da seção de memória compartilhada em bytes.

int main() {
    int shmid;             // ID (identificador) da seção de memória compartilhada
    char *shared_memory;  // Ponteiro para a região de memória compartilhada
    pid_t pid;            // Processo ID (ID do processo) do processo filho

    // 1. Criar ou Anexar uma Seção de Memória Compartilhada
    shmid = shmget(SHM_KEY, SHARED_SIZE, IPC_CREAT | 0666); // Cria a seção se não existir (IPC_CREAT) e define as permissões (0666 - leitura/escrita para todos).  Se a seção já existir, ela é anexada.
    if (shmid < 0) {
        perror("shmget");   // Imprime uma mensagem de erro se shmget falhar
        exit(1);           // Sai do programa com código de erro 1 (indica falha)
    }

    // 2. Anexar a Seção de Memória Compartilhada ao Espaço de Endereçamento do Processo
    shared_memory = (char *) shmat(shmid, NULL, 0); // Mapeia a seção de memória compartilhada para o espaço de endereço do processo atual.  NULL significa usar o endereço padrão da seção; 0 indica que não há flags adicionais.
    if (shared_memory == (char *)-1) {
        perror("shmat");   // Imprime uma mensagem de erro se shmat falhar
        exit(1);           // Sai do programa com código de erro 1
    }

    // 3. Criar um Processo Filho
    pid = fork();

    if (pid < 0) {
        perror("fork");   // Imprime uma mensagem de erro se fork falhar
        exit(1);           // Sai do programa com código de erro 1
    }

    if (pid == 0) { // Processo Filho
        // 4. Escrever na Memória Compartilhada
        strcpy(shared_memory, "Olá do filho!");  // Copia uma string para a memória compartilhada.  É importante usar strcpy e não apenas assignment para evitar problemas de buffer overflow.
        printf("Filho: Escreveu '%s' na memória compartilhada.\n", shared_memory);

        // 5. Desanexar a Memória Compartilhada (Importante!)
        shmdt(shared_memory); // Remove o mapeamento da seção de memória compartilhada do espaço de endereço do processo.  Isso é crucial para evitar problemas de acesso à memória.
        exit(0);           // Sai do processo filho com código de erro 0 (indica sucesso)
    } else { // Processo Pai
        // 6. Esperar pelo Processo Filho Terminar
        wait(NULL);   // Aguarda o término do processo filho.  Se o processo filho não terminar, o pai continuará a execução.

        // 7. Ler da Memória Compartilhada
        printf("Pai: Recebeu '%s' do filho.\n", shared_memory);

        // 8. Desanexar a Memória Compartilhada (Importante!)
        shmdt(shared_memory);
    }

    return 0;
}
