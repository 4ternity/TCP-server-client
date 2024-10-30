#include <stdio.h>      // Для ввода-вывода
#include <stdlib.h>     // Для стандартных функций
#include <string.h>     // Для работы со строками
#include <unistd.h>     // Для close()
#include <arpa/inet.h>  // Для sockaddr_in и других сетевых функций
#include <sys/socket.h> // Для работы с сокетами
#include <netdb.h>
int main() {
	// create a socket
	int network_socket;
	network_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	// specify an address for the socket
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	struct hostent *host = gethostbyname("serveo.net");
    if (host == NULL) {
        fprintf(stderr, "Ошибка: не удалось найти хост.\n");
        return 1;
    }

	memcpy(&server_address.sin_addr.s_addr, host->h_addr, host->h_length);

	int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
	// check for error with the connection
	if (connection_status == -1){
		printf("There was an error making a connection to the remote socket \n\n");
	}
	
	while (1) {
        // Ввод байта пользователем
        char byte_to_send;
        printf("Введите байт для отправки (1 символ): ");
        scanf(" %c", &byte_to_send); // Считываем один символ

        // Отправка данных на сервер
        send(network_socket, &byte_to_send, sizeof(byte_to_send), 0);

        // Проверка условия выхода
        if (byte_to_send == 'q') {
            printf("Выход из клиента.\n");
            break; // Выход из цикла при вводе 'q'
        }
    }
    
    close(network_socket);
	return 0;
}