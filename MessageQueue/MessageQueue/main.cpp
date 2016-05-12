//
//  main.cpp
//  MessageQueue
//
//  Created by Haochen Wang on 5/10/16.
//  Copyright © 2016 Haochen Wang. All rights reserved.
//

#include <iostream>
#include "queue.h"
class A{
public:
    void print(){
        std::cout<<"hi";
    }
};

class B:public A{
public:
    void print(){
        std::cout<<"hello";
    }
};

int main(int argc, const char * argv[]) {
    A x;
    std::unique_ptr<A> a(new B());
    x.print();
    a->print();
    return 0;
}
