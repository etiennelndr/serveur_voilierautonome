#include "computer.h"

#include "message.h"

/**
 * CONSTRUCTOR
 *
 * @brief Computer::Computer
 */
Computer::Computer() {
    // Nothing to do
}

/**
 * METHOD
 *
 * @brief Computer::init : init parameters with a Message object
 * @param m
 * @param indexOfSocket
 */
void Computer::init(Message m, int indexOfSocket) {
    if (m.getIdSender())
        this->id = *m.getIdSender();

    this->indexOfSocket = indexOfSocket;
}
