#include <stdio.h> 
#include <stdlib.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 

int main(int argc, char *argv[]) {
    int clien_fd, bind_result, read_result;
    struct sockaddr_in serve_addr;

    char buffer[1024];

    if (argc < 3) {
        printf("Error! Pass IP addr and port number as an argument\n");
        return 1;
    }

    clien_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (clien_fd < 0) {
        printf("Error! Could not create socket!\n");
        return 1;
    }

    serve_addr.sin_family = AF_INET;
    serve_addr.sin_port = htons(atoi(argv[2]));
    if (inet_pton(AF_INET, argv[1], &serve_addr.sin_addr) < 0) {
        printf("Error! Invalid address\n");
        return 1;
    }

    if (connect(clien_fd, (struct sockaddr *) &serve_addr, sizeof(serve_addr))) {
            printf("Error! Connection failed\n");
            return 1;
    }

    printf("Enter a query in the form <operand> <operator> <operand>:\n");

    fgets(buffer, 1023, stdin);

    send(clien_fd, buffer, 1024, 0);

    read_result = read(clien_fd, buffer, 1024);
    buffer[read_result] = '\0';
    printf("Result: %s\n", buffer);

    return 0;
}
