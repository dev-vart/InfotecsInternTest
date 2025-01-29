#include "bufferprocessor.h"

BufferProcessor::BufferProcessor(SafeBuffer<std::map<char, int>> &buffer)
    : buffer(buffer) {}

void BufferProcessor::processAndTransfer(Server &server) {
    while (true) {
        std::map<char, int> data = buffer.readOnNotified();

        for (const auto &[c, count] : data) {
            std::cout << c << ':' << count << '\n';
        }

        std::cout << '\n';

        server.send(std::move(data));
    }
}
