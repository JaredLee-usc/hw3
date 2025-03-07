#ifndef STACK_H
#define STACK_H

#include <vector>
#include <stdexcept>

// Use inheritance from std::vector (choose public/private) as appropriate
template <typename T>
class Stack : private std::vector<T>
{
public:
    // default constructor
    Stack() : std::vector<T>() {}

    // vector deconstructor is ok
    // ~Stack();

    // check is stack is empty
    bool empty() const{
        return std::vector<T>::empty();
    }

    // get size of stack
    size_t size() const{
        return std::vector<T>::size();
    }

    // use vector push back
    void push(const T& item){
        std::vector<T>::push_back(item);
    }

    // use vector pop back and throw std::underflow_error if empty
    void pop(){
       if (std::vector<T>::empty()) {
            throw std::underflow_error("Cannot pop from an empty stack");
        }
        std::vector<T>::pop_back();
    }

    // use vector back adn throw std::underflow_error if empty
    const T& top() const{
        if (std::vector<T>::empty()) {
            throw std::underflow_error("Cannot access top of an empty stack");
        }
        return std::vector<T>::back();
    }
};


#endif