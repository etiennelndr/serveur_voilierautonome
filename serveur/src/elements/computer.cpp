#include "computer.h"

#include "message.h"

/**
 * CONSTRUCTOR
 *
 * @brief Computer::Computer
 */
Computer::Computer(int _id, int indexOfSocket) {
    if (_id)
        this->id = _id;

    this->indexOfSocket = indexOfSocket;
}
Computer::Computer() {
    this->id = -1;
    this->indexOfSocket = -1;
}
