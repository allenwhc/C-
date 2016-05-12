//
//  main.cpp
//  Sort
//
//  Created by Haochen Wang on 5/8/16.
//  Copyright © 2016 Haochen Wang. All rights reserved.
//

#include <iostream>
#include <vector>
#include <thread>

class Sort{
public:
    virtual void sorting()=0;
};

class Bubble: public Sort{
private:
    std::vector<int> array;
public:
    Bubble(std::vector<int> a):array(a){}
    void sorting(){
        for (int i=0; i<array.size(); i++) {
            for(int j=i+1; j<array.size(); j++){
                if (array[j]<array[i]) {
                    int temp=array[i];
                    array[i]=array[j];
                    array[j]=temp;
                }
            }
        }
        std::cout<<"Bubble sort: ";
        for(std::vector<int>::iterator it=array.begin(); it!=array.end(); it++)
            std::cout<<*it<<" ";
        std::cout<<std::endl;
    }
};

class Selection: public Sort{
private:
    std::vector<int> array;
public:
    Selection(std::vector<int> a):array(a){}
    void sorting(){
        for (int i=0; i<array.size(); i++) {
            int min=i;
            for(int j=i+1; j<array.size(); j++){
                if(array[j]<array[min])
                    min=j;
            }
            if (min!=i) std::swap(array[min], array[i]);
        }
        std::cout<<"Selection sort: ";
        for(std::vector<int>::iterator it=array.begin(); it!=array.end(); it++)
            std::cout<<*it<<" ";
        std::cout<<std::endl;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::vector<int> array={4,-1,2,7,10,6};
    std::vector<std::thread> threads;
    Bubble bub(array);
    Selection sel(array);
    std::thread t_bub(&Bubble::sorting, &bub);
    std::thread t_sel(&Selection::sorting, &sel);
    
    threads.push_back(t_bub);
    threads.push_back(t_sel);
    
    for(auto &t: threads) t.join();
    return 0;
}
