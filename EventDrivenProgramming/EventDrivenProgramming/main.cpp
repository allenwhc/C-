//
//  main.cpp
//  EventDrivenProgramming
//
//  Created by Haochen Wang on 5/9/16.
//  Copyright © 2016 Haochen Wang. All rights reserved.
//

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>

class Task{
public:
    virtual void operation()=0; //Define operation as pure virtual function
};

class TaskRunner{
    static std::vector<Task*> tasks;
    static TaskRunner tr;
public:
    TaskRunner(){}  //Default constructor
    TaskRunner(const TaskRunner&){} //Copy constructor
    TaskRunner& operator=(TaskRunner&);
    void add(Task &t){tasks.push_back(&t);}
    void run(){
        std::vector<Task*>::iterator it=tasks.begin();
        while(it!=tasks.end()) (*it++)->operation();
    }
};

TaskRunner tr;
std::vector<Task*> TaskRunner::tasks;

class EventSimulator{
    clock_t creation;
    clock_t delay;
public:
    EventSimulator():creation(std::clock()){
        delay=CLOCKS_PER_SEC/4*(std::rand()%20+1);
        std::cout<<"Delay is: "<<delay<<std::endl;
    }
    bool fired(){return std::clock()>creation+delay;}
};

class Button{
    bool pressed;
    std::string id;
    EventSimulator e;
public:
    Button(std::string name):pressed(false),id(name){}
    void press(){pressed=true;}
    bool isPressed(){
        if(e.fired()) press();  //Simulate event
        return pressed;
    }
    friend std::ostream& operator<<(std::ostream &os, const Button &b){return os<<b.id;}
};

class CheckButton: public Task{
    Button &b;
    bool handled;
public:
    CheckButton(Button &b):b(b),handled(false){}
    void operation(){
        if(b.isPressed() && !handled){
            std::cout<<b<<" pressed."<<std::endl;
        }
        handled=true;
    }
};

void procedure1(){
    tr.run();
}

void procedure2(){
    tr.run();
}

void procedure3(){
    //...
    tr.run();
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::srand(std::time(0));
    Button b1("Button 1"), b2("Button 2"), b3("Button 3");
    CheckButton cb1(b1), cb2(b2), cb3(b3);
    tr.add(cb1);
    tr.add(cb2);
    tr.add(cb3);
    while (true) {
        procedure1();
        procedure2();
        procedure3();
    }
    
    return 0;
}
