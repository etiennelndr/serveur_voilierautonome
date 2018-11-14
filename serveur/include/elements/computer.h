#ifndef COMPUTER_H
#define COMPUTER_H


class Message;


/**
 * @brief The Computer class
 */
class Computer {
    public:
        Computer();

        int  getId();
        void setId(int id);
        int  getIndexOfSocket();
        void setIndexOfSocket(int);

        void init(Message, int);

    private:
        int id;
        int indexOfSocket;
};

inline int  Computer::getId()                 { return this->id; }
inline void Computer::setId(int id)           { this->id = id; }
inline int  Computer::getIndexOfSocket()      { return this->indexOfSocket; }
inline void Computer::setIndexOfSocket(int i) { this->indexOfSocket = i; }

#endif // COMPUTER_H
