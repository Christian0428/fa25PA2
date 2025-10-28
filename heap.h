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
        if (size == 0) //checks if the heap is empty
            return -1;
        int min = data[0]; //stores the root in the int min
        data[0] = data[size - 1]; //replcaes the root with the most recent implement
        size--; //decrements the size bc we removed a leaf
        downheap(0, weightArr); //reorders after replacing root with leaf
        return min; //returns the val that was in the root
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
        while (pos < size) {
            int left = (2 * pos) + 1; //position  of the left child
            int right = (2 * pos) + 2; //position of the right child

            if (left >= size) break; //condition if the left child still exists

            bool leftSmallest = false; // condtion to check which child holds the smallest value

            //checks if right child exists, then checks if the value of the left child is less than the value of the right child
            if ((right < size) && (weightArr[data[left]] < weightArr[data[right]]))
                //checks if left child is smaller
                leftSmallest = true;
            else
                leftSmallest = false; //if false right child holds the smallest value

            //if left is the smallest also checks if the index of the position is greater than the index of the left child
            if ((leftSmallest) && (weightArr[data[pos]] > weightArr[data[left]])) {
                swap(data[left], data[pos]); //swaps the index's of the left and the position
                pos = left; //reinitiaizes the position with the child
            }
            else if ((!leftSmallest) && (right < size && weightArr[data[right]] > weightArr[data[pos]])) { //checks if right child is the smalles
                //also checks if the right child still exists and checks if the index of the right is greater than the original position
                swap(data[right], data[pos]); //swaps index's
                pos = right; //changes the position with the right child
            }
            else break; //condition that breaks if the value belongs where it is
        }
    }
};

#endif