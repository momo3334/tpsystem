#include "../gestionListeChaineeVMS.h"
#include "./gestionVMS_CLIENT.h"
#define ls ACS_VLINE
#define bs ACS_HLINE

int main(int argc, char *argv[])
{
    WINDOW *fen1, *transmetteur1;
    int server_fifo_fd, client_fifo_fd;
    char input_command[200];
    int input_char;

    // Creating the window
    initscr();
    cbreak();
    noecho();
    int ligne = 15, colonne = 55;
    fen1 = newwin(ligne, colonne, 0, 0); // Cree une fenetre de 15 lignes,
    box(fen1, ls, bs);                   /* creation de la bordure */

    mvwaddstr(fen1, 0, colonne / 4, " USER 1 - Transmission ");

    // Getting user input
    int c = wgetch(fen1);
    int i = 1;
    while (strcmp(input_command, "exit"))
    {

        mvwprintw(fen1, 7, 1, "%d", c);
        if (c != 10 && c != '\n' && c != 127)
        {
            append(input_command, (char)c);
        }
        else if (c == 127)
        {
            pop(input_command);
        }
        else
        {
            memset(input_command, 0, sizeof input_command);
        }

        mvwaddstr(fen1, 3, 1, input_command);

        // Getting the next character
        c = wgetch(fen1);
        i++;
    }

    mvwaddstr(fen1, 3, 1, input_command);
    wrefresh(fen1);

    // creer_fenetreTxD1(fen1, transmetteur1);
    //  sleep(10);
    //   server_fifo_fd = open(SERVER_FIFO_NAME, O_WRONLY);
    //  printf("opened FIFO");

    // if (server_fifo_fd == -1)
    // {
    //     fprintf(stderr, "Sorry, no server\n");
    //     exit(EXIT_FAILURE);
    // }

    // get command
    // get_input(&input_char, fen1);
    // printw("%d %c", input_char, input_char);
    // mvwaddstr(fen1, 1, 1, " USER 1 - Transmission ");
    // wrefresh(fen1);

    // send command
    // send_command(input_command, server_fifo_fd);

    // printf("Closing fifo");
    close(server_fifo_fd);
    unlink(CLIENT_FIFO_NAME);
    exit(EXIT_SUCCESS);
}

void creer_fenetreTxD1(WINDOW *fen1, WINDOW *transmetteur1)
{

    // wmove(fen1, 1, 1);

    // transmetteur1 = newwin(ligne - 2, colonne - 2, 1, 1); /*Cree une fenetre de 13 lignes,52 colonnes placée à la ligne 1 et colonne 1*/
    // wrefresh(transmetteur1);
    // scrollok(transmetteur1, 1); /* définition du défilement vertical de la fenêtre */
    // wrefresh(transmetteur1);    /* rafraîchissement de la fenêtre de transmission */
}

void get_input(int *inputk, WINDOW *window)
{

    // printw("%d %c", *input, *input);
    // refresh();
}

void send_command(char *to_send, int server_fifo_fd)
{
    struct Info_FIFO_Transaction info_Transaction;

    info_Transaction.pid_client = getpid();
    strcpy(info_Transaction.transaction, to_send);
    //  sprintf(CLIENT_FIFO_NAME, info_Transaction.pid_client);
    //  if (mkfifo(CLIENT_FIFO_NAME, 0777) == -1)
    //  {
    //      fprintf(stderr, "Sorry, can't make %s\n", CLIENT_FIFO_NAME);
    //  }

    // For each of the five loops, the client data is sent to the server.
    // Then the client FIFO is opened (read-only, blocking mode) and the data read back.
    // Finally, the server FIFO is closed and the client FIFO removed from memory.
    // fprintf(stderr, "beforelloop %s\n", CLIENT_FIFO_NAME);

    // for (times_to_send = 0; times_to_send < 5; times_to_send++)
    // {
    // fprintf(stderr, "lloop %s\n", CLIENT_FIFO_NAME);

    // sprintf(info_Transaction.transaction, "Transaction data: \n pid: %d \n command: %s", info_Transaction.pid_client, info_Transaction.transaction);
    printf("%d sent %s, ", info_Transaction.pid_client, info_Transaction.transaction);
    write(server_fifo_fd, &info_Transaction, sizeof(info_Transaction));
    // client_fifo_fd = open(CLIENT_FIFO_NAME, O_RDONLY);
    // if (client_fifo_fd != -1)
    //  //{
    //      if (read(client_fifo_fd, &info_Transaction, sizeof(info_Transaction)) > 0)
    //      {
    //          printf("received: %s\n", info_Transaction.transaction);
    //      }
    //      close(client_fifo_fd);
    //  }
    // }
}

void append(char *s, char c)
{
    int len = strlen(s);
    s[len] = c;
    s[len + 1] = '\0';
}

void pop(char *s)
{
    int len = strlen(s);
    s[len] = '\0';
    // s[len + 1] = '\0';
}