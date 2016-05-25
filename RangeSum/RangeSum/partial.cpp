//
//  partial.cpp
//  RangeSum
//
//  Created by Haochen Wang on 5/23/16.
//  Copyright © 2016 Haochen Wang. All rights reserved.
//

#include <stdio.h>
#include "interface.h"

class Partial: public RangeSum{
    vector<int> arr, origin;
    void getParitialSum(){
        partial_sum(origin.begin(), origin.end(), arr.begin());
        
    }
public:
    Partial(vector<int> &array):origin(array){
        arr.reserve(array.size());
        fill(arr.begin(), arr.end(), 0);
    }
    //Override
    int rangeSum(int start, int end);
    
    void update(int i, int value);
};

int Partial::rangeSum(int start, int end){
    getParitialSum();
    return start==0?arr[end]:arr[end]-arr[start]+origin[start];
}

void Partial::update(int i, int value){
    origin[i]=value;
}


