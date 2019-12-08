#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    int serve_fd, port, bind_result, pid;
    struct sockaddr_in address;
    int address_size = sizeof(address);
    
    char buffer[1024];
    int new_socket, read_result;
    double a, b;
    double result;
    char op, *tok;

    if (argc < 2) {
        printf("Error! Pass port number as an argument\n");
        return 1;
    }

    serve_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (serve_fd == 0) {
        printf("Error! Failed to create socket!\n");
        return 1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(atoi(argv[1]));
    
    bind_result = bind(serve_fd, (struct sockaddr *) &address, sizeof(address));
    if (bind_result < 0) {
        printf("Error! Failed to bind socket!\n");
        return 1;
    }

    listen(serve_fd, 5);
    printf("Listening for connections on port %s\n", argv[1]);
    while(1) {
        new_socket = accept(serve_fd, (struct sockaddr *) &address, &address_size);
        if (new_socket < 0) {
            printf("Error! Failed to accept connection\n");
            return 1;
        }

        pid = fork();
        if (pid < 0) {
            perror("Error in creating child process!\n");
        } else if (pid == 0) {
            printf("Listening to %s:%d on pid %d\n", inet_ntoa(address.sin_addr), ntohs(address.sin_port), (int) getpid());
            close(serve_fd);

            // handle the client
            read_result = read(new_socket, buffer, 1024);
    
            tok = strtok(buffer, " ");
            a = atof(tok);
            tok = strtok(NULL, " ");
            op = tok[0];
            tok = strtok(NULL, " ");
            b = atof(tok);

            switch(op) {
                case '+':
                    result = a + b;
                    break;
                case '-':
                    result = a - b;
                    break;
                case '*':
                    result = a * b;
                    break;
                case '/':
                    result = a / b;
                    break;
            }

            sprintf(buffer, "%lf", result);

            printf("GOT: %lf %c %lf, SENDING: %lf\n", a, op, b, result);
            send(new_socket, buffer, strlen(buffer), 0);

            exit(0);
        } else {
            close(new_socket);
        }

    }

    return 0;
}
