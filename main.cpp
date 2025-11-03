//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }
    //testing lines
//    cout << "Text: " << file.rdbuf() << "\n";
//    file.clear();
//    file.seekg(0);

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// Step 3: Build the encoding tree using heap operations
int buildEncodingTree(int nextFree) {
    // TODO:
    // 1. Create a MinHeap object.
    // 2. Push all leaf node indices into the heap.
    // 3. While the heap size is greater than 1:
    //    - Pop two smallest nodes
    //    - Create a new parent node with combined weight
    //    - Set left/right pointers
    //    - Push new parent index back into the heap
    // 4. Return the index of the last remaining node (root)

    MinHeap minHeap;
    for (int i = 0; i < nextFree; ++i) {
        minHeap.push(i, weightArr);
    }

    while (minHeap.size > 1) {
        int firstPop = minHeap.pop(weightArr); //pops the first smallest node
        int secondPop = minHeap.pop(weightArr); //pops the second smallest node

        int parentTotalWeight = weightArr[firstPop] + weightArr[secondPop]; //new parent node with total weight
        int parentIndex = nextFree++; //changes the index

        leftArr[parentIndex] = firstPop; //left array holds the first popped val
        rightArr[parentIndex] = secondPop; //right array holds the second popped val
        weightArr[parentIndex] = parentTotalWeight;//changes the weight of the parent node

        minHeap.push(parentIndex, weightArr); //pushes the heap and reorders

    }
    int root = minHeap.pop(weightArr); //int for the root
    return root; //returns the index of the root
}

// Step 4: Use an STL stack to generate codes
void generateCodes(int root, string codes[]) {
    // TODO:
    // Use stack<pair<int, string>> to simulate DFS traversal.
    // Left edge adds '0', right edge adds '1'.
    // Record code when a leaf node is reached.

    stack<pair<int, string>> stack; //intialized the stack
    stack.push({root, ""}); //pushes the root along with the space
    while (!stack.empty()) { //traverses until the stack is empty
        pair<int, string> p = stack.top();//grabs the top element, the node and the code
        stack.pop(); //pops top element

        int cur = p.first; //cur index
        string curCode = p.second; //current code

        int leftChild = leftArr[cur]; //left child
        int rightChild = rightArr[cur]; //right child

        if (leftChild == -1 && rightChild == -1) { //condition which checks if it is a leaf node
            codes[cur] = curCode; //records the current code in the codes array
        }
        else { //if node does have children continue
            if (rightChild != -1) { //checks right first for DFS
                stack.push({rightChild, curCode + "1"}); //adds 1 if right
            }

            if (leftChild != -1) { //proceeds to check left
                stack.push({leftChild, curCode + "0"}); //adds 0 if left
            }
        }
    }
}

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}