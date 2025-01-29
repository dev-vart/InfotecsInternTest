#include "inputhandler.h"

InputHandler::InputHandler(SafeBuffer<std::map<char, int>> &buffer)
    : buffer(buffer) {}

void InputHandler::startInputProcess() {
    while (true) {
        std::string input;
        std::getline(std::cin, input);

        if (isValid(input)) {
            // input преобразуется в rvalue и перемещается в processedInput,
            // избегая копирования
            std::map<char, int> processedInput =
                countLettersAndSort(std::move(input));
            buffer.writeAndNotify(std::move(processedInput));
        } else {
            std::cerr
                << "Ошибка: строка содержит символы, отличные от букв или ее "
                   "длина превышает 64 символа\n";
        }
    }
}

bool InputHandler::isValid(const std::string &s) {
    return !s.empty() && s.length() <= 64 &&
           std::all_of(s.begin(), s.end(), ::isalpha);
}

std::map<char, int> InputHandler::countLettersAndSort(std::string s) {
    std::sort(s.begin(), s.end());
    std::string newString;
    std::map<char, int> charCount;

    for (char c : s) {
        if (!charCount[c]) {
            charCount[c] += std::count(s.begin(), s.end(), c);
        }
    }

    return charCount;
}
