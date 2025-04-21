// Baseado em https://gist.github.com/apfohl/de1915e4d6502ae4c4d7
// Para compilar: gcc process_to_process_message_queue.c -o process_to_process_message_queue 

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <string.h>

/* Estrutura da mensagem */
struct message {
    long mtype;
    char mtext[8192];
};

int main(void)
{
    /* Cria a fila de mensagens */
    int msqid = msgget(IPC_PRIVATE, IPC_CREAT | 0600); // IPC_PRIVATE cria uma fila privada
    if (msqid == -1) {
        perror("msgget"); // Imprime mensagem de erro se msgget falhar
        return EXIT_FAILURE; // Retorna código de erro se falhar
    }

    /* Cria um processo filho */
    pid_t pid = fork();
    if (pid == 0) {
        // Processo filho
        struct message message;
        message.mtype = 1; // Tipo da mensagem
        memset(&(message.mtext), 0, 8192 * sizeof(char)); // Limpa o buffer de texto
        (void)strcpy(message.mtext, "Um olá do processo filho!"); // Copia a string para o buffer

        /* Envia a mensagem para a fila */
        if (msgsnd(msqid, &message, sizeof(long) + (strlen(message.mtext) * sizeof(char)) + 1, 0) == -1) {
            perror("msgsnd"); // Imprime mensagem de erro se msgsnd falhar
            return EXIT_FAILURE; // Retorna código de erro se falhar
        }
    } else {
        // Processo pai
        /* Aguarda o processo filho terminar */
        (void)waitpid(pid, NULL, 0); // Espera o processo filho finalizar

        /* Recebe a mensagem da fila */
        struct message message;
        if (msgrcv(msqid, &message, 8192, 0, 0) == -1) {
            perror("msgrcv"); // Imprime mensagem de erro se msgrcv falhar
            return EXIT_FAILURE; // Retorna código de erro se falhar
        }

        printf("%s\n", message.mtext); // Imprime a mensagem recebida

        /* Destrói a fila de mensagens */
        if (msgctl(msqid, IPC_RMID, NULL) == -1) {
            perror("msgctl"); // Imprime mensagem de erro se msgctl falhar
            return EXIT_FAILURE; // Retorna código de erro se falhar
        }
    }

    return EXIT_SUCCESS; // Retorna código de sucesso
}
