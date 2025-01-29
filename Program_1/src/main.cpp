#include <iostream>
#include <thread>

#include "bufferprocessor.h"
#include "inputhandler.h"
#include "safebuffer.h"
#include "server.h"

int main() {
    SafeBuffer<std::map<char, int>> buffer;

    Server server(52000);
    server.run();

    InputHandler handler(buffer);
    BufferProcessor bp(buffer);

    std::thread inputThread(&InputHandler::startInputProcess, handler);
    std::thread processingThread(&BufferProcessor::processAndTransfer, bp,
                                 std::ref(server));

    // join() блокирует выполнение вызывающего потока до тех пор, пока поток,
    // для которого он был вызван, не завершит свою работу
    inputThread.join();
    processingThread.join();

    return 0;
}
