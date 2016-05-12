//
//  interface.h
//  Sort
//
//  Created by Haochen Wang on 5/9/16.
//  Copyright © 2016 Haochen Wang. All rights reserved.
//

#ifndef interface_h
#define interface_h
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>
#include <unistd.h>

typedef std::unique_lock<std::mutex> locker;

//Sort abstract class
class Sort{
public:
    virtual void sorting()=0;
};

#endif /* interface_h */
