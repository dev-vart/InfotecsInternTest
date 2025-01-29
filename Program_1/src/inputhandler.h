#pragma once

#include <algorithm>
#include <iostream>
#include <map>
#include <string>

#include "safebuffer.h"

class InputHandler {
    SafeBuffer<std::map<char, int>>& buffer;

   public:
    InputHandler(SafeBuffer<std::map<char, int>>& buffer);

    void startInputProcess();

   private:
    bool isValid(const std::string& s);

    std::map<char, int> countLettersAndSort(std::string s);
};
