#pragma once

#include <condition_variable>

template <typename T>
class SafeBuffer {
    std::mutex mtx;
    std::condition_variable cv;
    bool newDataWritten;
    T buffer;

   public:
    SafeBuffer() : newDataWritten(false) {}

    void writeAndNotify(T toBuffer) {
        // Блокируем мьютекс обычного типа, чтобы доступ к буферу имел только
        // один поток
        std::unique_lock<std::mutex> lock(mtx);
        // Объект toBuffer преобразуется в rvalue и перемещается в buffer,
        // избегая копирования
        buffer = std::move(toBuffer);
        newDataWritten = true;
        cv.notify_one();  // Уведомляем 1 ожидающий поток до разблокировки
    }  // Мьютекс разблокируется здесь автоматические, т.к. вызывается
       // деструктор std::unique_lock

    T readOnNotified() {
        // Блокируем мьютекс обычного типа, чтобы доступ к буферу имел только
        // один поток
        std::unique_lock<std::mutex> lock(mtx);
        // Проверка условия под блокировкой
        cv.wait(lock, [this] { return newDataWritten; });
        T bufferData = std::move(buffer);
        // После получения данных общий буфер затирается
        buffer.clear();
        newDataWritten = false;
        return bufferData;
    }  // Мьютекс разблокируется автоматически
};
