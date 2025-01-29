#include "server.h"

// Конструктор класса Server, который инициализирует сервер на указанном порте
Server::Server(int port) {
    // Создание сокета для TCP-подключений
    // AF_INET - семейство адресов IPv4
    // SOCK_STREAM - тип сокета для сетевых подключений
    // 0 - протокол по умолчанию
    // listener - сокет-слушатель
    listener = socket(AF_INET, SOCK_STREAM, 0);

    if (listener < 0) {
        perror("Ошибка: Сбой создания сокета");
        exit(1);
    }

    // Настройка адреса и порта для сокета
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;  // Семейство адресов IPv4
    // htons - Host To Network for Short int
    // Установка порта в сетевом порядке байт
    addr.sin_port = htons(port);
    // Привязка к любому доступному IP-адресу лок. машины
    // htonl - Host To Network for Long int
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // Включаем для сокета опцию REUSEADDR
    // Это позволяет использовать порт, даже если он находится в состоянии
    // TIME-WAIT
    int socket_option_value = 1;
    if (setsockopt(listener, SOL_SOCKET, SO_REUSEADDR,
                   (void *)&socket_option_value,
                   sizeof(socket_option_value)) < 0) {
        perror("Ошибка: Сбой установки опции сокета REUSEADDR");
        exit(3);
    }

    // Привязка сокета к настроенному адресу и порту
    // Функции, работающие с сокетами, используют общую структуру sockaddr
    // sockaddr_in позволяет явно указывать порт и IP-адрес, что удобнее для
    // работы с IPv4 В аргументах функции bind мы приводим указатель на
    // sockaddr_in к типу sockaddr
    if (bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("Ошибка: Сбой привязки сокета");
        exit(2);
    }

    // Перевод сокета в режим прослушивания
    startListening(listener, clientLimit);
}

// Отправка сообщений на сокет
void Server::send(std::map<char, int> data) {
    // Функция send() ожидает указатель на массив байтов, которые нужно
    // отправить
    std::string serializedData;
    for (const auto &pair : data) {
        serializedData += pair.first;
        serializedData += std::to_string(pair.second);
        serializedData += '|';
    }

    ::send(socket_, serializedData.c_str(), serializedData.size(), 0);
}

// Конфигурация и запуск сервера
void Server::run() {
    // Принимает входящее подключение на сокете
    // socket_ - cокет для общения с клиентом
    socket_ = accept(listener, NULL, NULL);
    // Поток, который будет обрабатывать переподключение
    std::thread reconnectionThread([this]() {
        char buffer[1024];
        // Функция read() читает данные из сокета клиента,
        // если возвращает <= 0, клиент закрыл соединение или произошла ошибка
        // Таким образом выполняется условие "При перезапуске программы №2
        // необходимо произвести передподключение."
        while (true) {
            if (read(socket_, buffer, 1023) <= 0) {
                close(socket_);
                socket_ = accept(listener, NULL, NULL);
            }
        }
    });
    // Поток выполняет фоновую задачу, которая не зависит от основного потока
    // Поэтому отделяем его от основного потока
    reconnectionThread.detach();
}

// Перевод сокета в режим прослушивания
void Server::startListening(int listener, const int clientLimit) {
    // Второй аргумент указывает максимальное количество ожидающих
    // подключений
    std::thread listeningThread([&]() { listen(listener, clientLimit); });
    listeningThread.detach();
}