//
//  main.cpp
//  VirtualTable
//
//  Created by Haochen Wang on 5/7/16.
//  Copyright © 2016 Haochen Wang. All rights reserved.
//

#include <iostream>
class Base{
public:
    virtual void func1(){
        std::cout<<"This is function 1 in Base"<<std::endl;
    }
    virtual void func2(){
        std::cout<<"This is function 2 in Base"<<std::endl;
    }
};

class C1: public Base{
public:
    virtual void func1(){
        std::cout<<"This is function 1 in C1"<<std::endl;
    }
};

class C2: public Base{
public:
    virtual void func2(){
        std::cout<<"This is function 2 in C2"<<std::endl;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    C1 c1;
    Base *b1=&c1;
    std::unique_ptr<Base> b(new Base());
    b1->func1();
    b->func1();
    //delete b;
    return 0;
    
}
