#include "receivehandler.h"

void ReceiveHandler::handle(std::string serializedData) {
    std::map<char, int> data;
    std::string key;
    std::string value;

    size_t start = 0;
    while (start < serializedData.length()) {
        size_t end = serializedData.find('|', start);
        if (end == std::string::npos) {
            end = serializedData.length();
        }

        std::string pair = serializedData.substr(start, end - start);

        if (!pair.empty()) {
            char key = pair[0];
            int value = std::stoi(pair.substr(1));

            data[key] = value;
        }

        start = end + 1;
    }

    std::vector<std::pair<char, int>> sortedData(data.begin(), data.end());

    std::sort(
        sortedData.begin(), sortedData.end(),
        [](const auto& p1, const auto& p2) { return p1.second < p2.second; });

    for (const auto& [key, value] : sortedData) {
        std::cout << key << ":" << value << "\n";
    }
    std::cout << "\n";
}
