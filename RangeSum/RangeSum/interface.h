//
//  interface.h
//  RangeSum
//
//  Created by Haochen Wang on 5/23/16.
//  Copyright © 2016 Haochen Wang. All rights reserved.
//

#ifndef interface_h
#define interface_h

#include <iostream>
#include <numeric>
#include <algorithm>
#include <vector>
using namespace std;

class RangeSum{
public:
    virtual int rangeSum(int start, int end)=0;
    virtual void update(int i, int value)=0;
};



#endif /* interface_h */
