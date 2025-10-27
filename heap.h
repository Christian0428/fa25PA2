//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    void push(int idx, int weightArr[]) {
        // TODO: insert index at end of heap, restore order using upheap()
        data[size] = idx; //adds the int idx to teh array
        upheap(size, weightArr); //calls upheap to check if any reorganizing needs to be done
        size++; //incriments the size for proper position use
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()
        return -1; // placeholder
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent

        while (pos > 0) { //continously runs until explicitly broken
            int parent = (pos - 1) /2; //initializes parent position
            if (data[parent] < data[pos]) { //data instead of weightArr because we need the index of the dataArr instead of the weightArr
                swap(data[pos], data[parent]); //ofc swaps the values of pos and parent
                pos = parent; //shifts the values
            }
            else break; //breaks whenever the parent is greater than the position
        }
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
    }
};

#endif