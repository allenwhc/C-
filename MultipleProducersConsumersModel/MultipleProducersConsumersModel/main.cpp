//
//  main.cpp
//  MultipleProducersConsumersModel
//
//  Created by Haochen Wang on 5/8/16.
//  Copyright © 2016 Haochen Wang. All rights reserved.
//

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>
#include <deque>
#include <atomic>
#include <vector>

//Define macroes
#define MAX_BUFFER_SIZE 10  //max buffer size
#define MAX_PRODUCTION 10   //max products a producer produces
#define MAX_CONSUMER_WAIT_TIME 30   //upper time limit for a consumer to wait
#define SYNC_TIME 50    //ms
#define NUM_CONSUMERS 10    //consumer number
#define NUM_PRODUCERS 5 //producer number

typedef std::unique_lock<std::mutex> locker;
std::atomic<int> num_working_producers(0);  //define active working producers

template <typename T>
class Buffer {
private:
    std::deque<T> buff;
    std::mutex mtx;
    std::condition_variable is_full;
    std::condition_variable is_empty;
public:
    void add(const int &producer_id, const T &item){
        locker l(mtx);
        is_full.wait(l,[this](){return buff.size()<MAX_BUFFER_SIZE;});  //Wait until queue is not full
        buff.push_back(item);
        std::cout<<"Producer: "<<producer_id<<", producing: "<<item<<std::endl;
        is_empty.notify_all();
    }
    
    void remove(const int &consumer_id){
        locker l(mtx);
        if(is_empty.wait_for(l, std::chrono::milliseconds(MAX_CONSUMER_WAIT_TIME),[this](){return !buff.empty();})){
            T item=buff.back();
            buff.pop_back();
            std::cout<<"Consumer: "<<consumer_id<<", consuming: "<<item<<std::endl;
            is_full.notify_all();
        }
    }
    
    bool is_not_empty_buffer(){return !buff.empty();}
};

template <typename T>
class Producers {
private:
    Buffer<T> *buff;
public:
    Producers(Buffer<T> *b):buff(b){}
    void run(const int &id){
        ++num_working_producers;
        for(int i=0; i<MAX_PRODUCTION; i++){
            T item=std::rand()%100;
            buff->add(id, item);
            std::this_thread::sleep_for(std::chrono::milliseconds(SYNC_TIME));
        }
        --num_working_producers;
    }
};

template <typename T>
class Consumers {
private:
    Buffer<T> *buff;
public:
    Consumers(Buffer<T> *b):buff(b){}
    void run(const int &id){
        while(num_working_producers==0) std::this_thread::yield();  //If no producer is active, then terminate the process
        while(num_working_producers!=0 || buff->is_not_empty_buffer()){
            buff->remove(id);
            std::this_thread::sleep_for(std::chrono::milliseconds(SYNC_TIME));
        }
    }

};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::vector<std::thread> threads;
    Buffer<int> b;
    for(int i=0; i<NUM_PRODUCERS; i++){
        Producers<int> p(&b);
        std::thread t_producer(&Producers<int>::run, i , &p);
        threads.push_back(t_producer);
    }
    for(int i=0; i<NUM_CONSUMERS; i++){
        Consumers<int> c(&b);
        std::thread t_consumer(&Consumers<int>::run, i, &c);
        threads.push_back(t_consumer);
    }
    for(auto &t: threads) t.join();
    return 0;
}
