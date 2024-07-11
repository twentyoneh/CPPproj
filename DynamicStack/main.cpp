#include <iostream>
#include"Stack.h"

int main()
{
    Stack st1(15);
    st1.Push(5);
    st1.Push(10);
    st1.Push(20);
    st1.Pop();
    st1.Push(50);
    std::cout << st1.Peek().GetValue();
}

