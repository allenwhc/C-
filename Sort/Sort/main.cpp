//
//  main.cpp
//  Sort
//
//  Created by Haochen Wang on 5/8/16.
//  Copyright © 2016 Haochen Wang. All rights reserved.
//
#include "interface.h"
#include "bubble.cpp"
#include "quick.cpp"
#include "selection.cpp"
#include "merge.cpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::vector<int> array={4,-1,2,7,10,6};
    std::vector<std::thread> threads;
    Bubble bub(array);
    Selection sel(array);
    Merge mer(array);
    Quick qui(array);
    //Define threads
//    threads.push_back(std::thread(&Bubble::sorting,&bub));
//    usleep(100);
//    threads.push_back(std::thread(&Selection::sorting,&sel));
//    usleep(100);
//    threads.push_back(std::thread(&Merge::sorting,&mer));
//    usleep(100);
//    threads.push_back(std::thread(&Quick::sorting,&qui));
//    usleep(100);
    
    std::thread t_bub (std::bind(&Bubble::sorting, &bub));
    usleep(100);
    std::thread t_sel (std::bind(&Selection::sorting, &sel));
    usleep(100);
    std::thread t_mer (std::bind(&Merge::sorting, &mer));
    usleep(100);
    std::thread t_qui (std::bind(&Quick::sorting, &qui));
    usleep(100);
    
//    threads.push_back(t_bub);
//    threads.push_back(t_sel);
//    threads.push_back(t_mer);
//    threads.push_back(t_qui);
//    for(auto &t: threads) t.join();
    t_bub.join();
    t_sel.join();
    t_mer.join();
    t_qui.join();
    return 0;
}
