//
//  main.cpp
//  ProducerCustomerProblem
//
//  Created by Haochen Wang on 5/8/16.
//  Copyright © 2016 Haochen Wang. All rights reserved.
//

#include <iostream>
#include <mutex>
#include <thread>
#include <deque>
#include <chrono>
#include <condition_variable>

#define MAX_BUFFER_SIZE 10
#define NUM_PRODUCER 5
#define NUM_CONSUMER 10
#define MAX_CONSUMER_WAIT_TIME 30 //ms
#define SYCNCHONIZE_TIME 50 //ms

typedef std::unique_lock<std::mutex> unlocker;   //set lock/unlock
typedef std::lock_guard<std::mutex> locker;


/***Single producer-consumer problem ***/
//Buffer class
template <typename T>
class Buffer {
private:
    std::deque<T> buffer;
    std::condition_variable cond;
    std::mutex mtx;
public:
    void push(const T &val){
        locker l(mtx);
        bool isFull=buffer.empty();
        buffer.push_back(val);
        if(isFull) cond.notify_one();
    }
    
    T pop(){
        unlocker u_l(mtx);
        while(buffer.empty()){cond.wait(u_l);}
        T ret_val=buffer.back();
        buffer.pop_back();
        return ret_val;
    }
};


//Consumer class
template <typename T>
class Consumer{
private:
    Buffer<T> *buffer_;
    std::mutex mtx;
public:
    Consumer(Buffer<T> *b):buffer_(b){}
    void run(){
        while (true) {
            T item=buffer_->pop();
            mtx.lock();
            std::cout<<"Consuming: "<<item<<std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            mtx.unlock();
        }
    }
};

//Producer class
template <typename T>
class Producer {
private:
    Buffer<T> *buffer_;
    std::mutex mtx;
public:
    Producer(Buffer<T> *b):buffer_(b){}
    void run(){
        while(true){
            T item=std::rand()%20;
            buffer_->push(item);
            mtx.lock();
            std::cout<<"Producing: "<<item<<std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));    //Synchronize threads
            mtx.unlock();
        }
    }
};

int main(int argc, const char * argv[]) {
    Buffer<int> b;
    Consumer<int> c(&b);
    Producer<int> p(&b);
    std::cout<<"Start all threads"<<std::endl;
    std::thread thread_consumer(&Consumer<int>::run, &c);
    std::thread thread_producer(&Producer<int>::run, &p);
    thread_consumer.join();
    thread_producer.join();
    std::cout<<"Complete all threads"<<std::endl;
    return 0;
}
