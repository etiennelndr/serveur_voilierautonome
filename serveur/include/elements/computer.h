#ifndef COMPUTER_H
#define COMPUTER_H


/**
 * @brief The Computer class
 */
class Computer {
    public:
        Computer(int id);

        int getId();
        void setId(int id);

    private:
        int id;
};

inline int Computer::getId() { return this->id; }
inline void Computer::setId(int id) { this->id = id; }

#endif // COMPUTER_H
