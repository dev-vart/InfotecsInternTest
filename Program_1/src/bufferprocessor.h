#pragma once

#include <iostream>
#include <map>
#include <numeric>

#include "safebuffer.h"
#include "server.h"

class BufferProcessor {
    SafeBuffer<std::map<char, int>>& buffer;

   public:
    BufferProcessor(SafeBuffer<std::map<char, int>>& buffer);

    void processAndTransfer(Server& server);
};
