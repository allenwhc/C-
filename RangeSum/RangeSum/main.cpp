//
//  main.cpp
//  RangeSum
//
//  Created by Haochen Wang on 5/23/16.
//  Copyright © 2016 Haochen Wang. All rights reserved.
//
#include "segment.cpp"
#include "partial.cpp"
#include "binaryindex.cpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    static vector<int> array={3,2,-1,6,5,4,-3,3,7,2,3};
//    static vector<int> array={200,99,98,97,96,95,94,93,92,91,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,90,89,88,87,86,85,84,83,82,81,71,72,73,74,75,76,77,78,79,80,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70};
    vector<pair<int,int>> queries={make_pair(0, 99),make_pair(0, 49), make_pair(0, 99),make_pair(0, 59),make_pair(0, 39),make_pair(0, 59)};
    
    
    vector<int> test_array1(array);
    vector<int> test_array2(array);
    vector<int> test_array3(array);
    int start=0;
    int end=10;
    int update_index=1;
    int update_value=0;
    
    //Instantiate class instances
    /**** Partial Sum Solution ****/
    /*
     *  Time complexity:
     *              1. Construct partial sum array: O(N)
     *              2. Search range sum: O(1)
     *              3. Update value: O(N)
     *  Space complexity: O(N)
     */
    cout<<"Partial sum solution: "<<endl;
    Partial par(test_array1);
    cout<<par.rangeSum(start, end)<<endl;
    par.update(update_index, update_value);
    cout<<par.rangeSum(start, end)<<endl;
    cout<<endl;
    
    /**** Segment Tree Solution ****/
    /*
     *  Time complexity: 
     *              1. Construct segment tree: O(N)
     *              2. Search range sum: O(logN)
     *              3. Update value: O(logN)
     *  Space complexity: O(4N-1) --> (worst case) 
     *                    O(N)    --> (average)
     */
    cout<<"Segment tree solution: "<<endl;
    SegmentTree seg(test_array2);
    cout<<seg.rangeSum(start, end)<<endl;
    seg.update(update_index, update_value);
    cout<<seg.rangeSum(start, end)<<endl;
    cout<<endl;
    
    /**** Binary Index Tree Solution ****/
    /*
     *  Time complexity:
     *              1. Construct segment tree: O(NlogN)
     *              2. Search range sum: O(logN)
     *              3. Update value: O(logN)
     *  Space complexity: O(N)
     */
    cout<<"Binary Index Tree solution:"<<endl;
    BinaryIndexTree ft(test_array3);
    ft.printFenwickTree();
    return 0;
}
