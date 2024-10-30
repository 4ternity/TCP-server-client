/*sum
*/
#include <stdio.h>      // Для ввода-вывода
#include <stdlib.h>     // Для стандартных функций
#include <string.h>     // Для работы со строками
#include <unistd.h>     // Для close()
#include <arpa/inet.h>  // Для sockaddr_in и других сетевых функций
#include <sys/socket.h> // Для работы с сокетами
int main() {

    char server_message[256] = "You have reached the server!";

    // create the server socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;
    printf("Сервер запущен.\n");

    // bind the socket to our specified IP and port
    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

    // second agrument is a backlog - how many connections
    // can be waiting for this socket simultaneously
    listen(server_socket, 5);

    while (1)
    {
        int client_socket = accept(server_socket, NULL, NULL);
        
        while (1) {
            // Получение байта от клиента
            char received_byte;
            int bytes_received = recv(client_socket, &received_byte, sizeof(received_byte), 0);
            
            if (bytes_received <= 0) {
                printf("Соединение закрыто клиентом.\n");
                break; // Выход из внутреннего цикла, если клиент закрыл соединение
            }
            
            // Печать полученного байта
            printf("Получен байт: %c\n", received_byte);
        }
         close(client_socket);
    }
    printf("Сервер выключен.\n");
    // close the socket
    close(server_socket);
	return 0;
}
