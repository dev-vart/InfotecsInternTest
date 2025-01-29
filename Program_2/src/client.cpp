#include "client.h"

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

// Конструктор клиента
Client::Client(const std::string &serverIP, int serverPort)
    : serverIP_(serverIP), serverPort_(serverPort) {}

// Запуск клиента
void Client::run(void (*handler)(std::string)) {
    while (true) {
        if (!connectToServer()) {
            sleep(1);
            continue;
        }

        receiveData(handler);

        close(clientSocket);
    }
}

// Подключение к серверу
bool Client::connectToServer() {
    // Создание сокета для TCP-подключения
    // AF_INET - семейство адресов IPv4
    // SOCK_STREAM - тип сокета для сетевых подключений
    // 0 - протокол по умолчанию
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (clientSocket < 0) {
        perror("Ошибка: Сбой создания сокета");
        return false;
    }

    // Настройка адреса сервера
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;           // Семейство адресов (IPv4)
    serverAddress.sin_port = htons(serverPort_);  // Порт сервера

    // Преобразование строки IP-адреса в двоичный формат
    if (inet_pton(AF_INET, serverIP_.c_str(), &(serverAddress.sin_addr)) <= 0) {
        perror("Ошибка: Ошибка в адресе сервера");
        close(clientSocket);
        return false;
    }

    // Установка соединения с сервером
    if (connect(clientSocket,
                reinterpret_cast<const sockaddr *>(&serverAddress),
                sizeof(serverAddress)) < 0) {
        close(clientSocket);
        std::cout << "Ожидание подключения...\n";
        return false;
    }

    return true;
}

// Функция-обработчик полученных данных.
void Client::receiveData(void (*handler)(std::string)) {
    // Буфер для хранения полученных данных
    char buffer[BUFFER_SIZE];

    while (true) {
        // Очистка буфера перед чтением
        memset(buffer, 0, BUFFER_SIZE);

        if (read(clientSocket, buffer, BUFFER_SIZE - 1) <= 0) {
            break;
        }

        std::string data(buffer);

        handler(std::move(data));
    }
}
