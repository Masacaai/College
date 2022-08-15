/*
    Course: CS 251, Spring 2022. Wed 12 PM Lab
    System: NixOS 22.05 using Visual Studio Code
    Author: Mohammed Aaqel Shaik Abdul Mazeed

    Program Overview:
    This file contains the functions used to 
    implement Huffman file compression.
*/

#include <iostream>
#include <fstream>
#include <map>
#include <queue>          // std::priority_queue
#include <vector>         // std::vector
#include <functional>     // std::greater
#include <string>
#include "bitstream.h"
#include "hashmap.h"
#include "mymap.h"
#pragma once

struct HuffmanNode {
    int character;
    int count;
    HuffmanNode* zero;
    HuffmanNode* one;
};

struct prioritize {
    bool operator()(const HuffmanNode* p1, const HuffmanNode* p2) const {
        return p1->count > p2->count;
    }
};

//
// *This function is called recursively to free the tree
//
void _free(HuffmanNode* cur) {
    if (cur) {
        _free(cur->zero);
        _free(cur->one);
        delete cur;
    }
}

//
// *This method frees the memory allocated for the Huffman tree.
//
void freeTree(HuffmanNode* node) {
    _free(node);
}

//
// *This function build the frequency map.  If isFile is true, then it reads
// from filename.  If isFile is false, then it reads from a string filename.
//
void buildFrequencyMap(string filename, bool isFile, hashmap &map) {
    if (isFile) {
        ifstream inFS(filename);
        char c;
        while (inFS.get(c)) {
            // If map contains character, increment the value.
            if (map.containsKey(c)) {
                map.put(c, map.get(c) + 1);
            } else {    // If not, add character with count = 1. 
                map.put(c, 1);
            }
        }
    } else {
        for (char c : filename) {
            if (map.containsKey(c)) {
                map.put(c, map.get(c) + 1);
            } else {    
                map.put(c, 1);
            }
        }
    }
    map.put(PSEUDO_EOF, 1);
}

//
// *This function builds an encoding tree from the frequency map.
//
HuffmanNode* buildEncodingTree(hashmap &map) {
    HuffmanNode* root;
    priority_queue<
      HuffmanNode*,
      vector<HuffmanNode*>,
      prioritize> pq;
    vector<int> vec = map.keys();

    // Create priority queue
    for (unsigned int i = 0; i < vec.size(); ++i) {
        HuffmanNode* node = new HuffmanNode();
        node->character = vec[i];
        node->count = map.get(vec[i]);
        pq.push(node);
    }

    // Build tree
    while (pq.size() > 1) {
        // Pop top two nodes
        HuffmanNode* left = pq.top();
        pq.pop();
        HuffmanNode* right = pq.top();
        pq.pop();
        // Create empty parent node
        HuffmanNode* parent = new HuffmanNode();
        parent->character = NOT_A_CHAR;
        parent->zero = left;
        parent->one = right;
        parent->count = left->count + right->count;
        // Push parent node back into queue
        pq.push(parent);
    }
    root = pq.top();
    return root;
}

//
// *This function is called recursively to build the encoding map.
//
void _encodingMap(HuffmanNode* node, string str, mymap <int, string> &map) {
    if (node->character != NOT_A_CHAR) {
        map.put(node->character, str);
    } else {
        _encodingMap(node->zero, str + "0", map);
        _encodingMap(node->one, str + "1", map);
    }
}

//
// *This function builds the encoding map from an encoding tree.
//
mymap <int, string> buildEncodingMap(HuffmanNode* tree) {
    mymap <int, string> encodingMap;
    if (tree)
        _encodingMap(tree, "", encodingMap);
    return encodingMap;
}

//
// *This function encodes the data in the input stream into the output stream
// using the encodingMap.  This function calculates the number of bits
// written to the output stream and sets result to the size parameter, which is
// passed by reference.  This function also returns a string representation of
// the output file, which is particularly useful for testing.
//
string encode(ifstream& input, mymap <int, string> &encodingMap,
              ofbitstream& output, int &size, bool makeFile) {
    string outputStr;
    size = 0;
    char c;
    // Write contents of input to output
    while (input.get(c)) {
        outputStr += encodingMap[c];
        if (makeFile) {
            for (char e : encodingMap[c]) {
                // ASCII values of 0 = 48, 1 = 49
                // 'e' is a char, while writeBit expects an int    
                output.writeBit(e - 48);
                size++;
            }
        }
    }
    // Add EOF character to output
    outputStr += encodingMap[PSEUDO_EOF];
    if (makeFile) {
        for (char f : encodingMap[PSEUDO_EOF]) {
            output.writeBit(f - 48);
            size++;
        }
    }
    return outputStr;
}


//
// *This function decodes the input stream and writes the result to the output
// stream using the encodingTree.  This function also returns a string
// representation of the output file, which is particularly useful for testing.
//
string decode(ifbitstream &input, HuffmanNode* encodingTree, ofstream &output) {
    string outputStr;
    HuffmanNode* cur = encodingTree;
    while(!input.eof() && cur->character != PSEUDO_EOF) {
        // If we reach a leaf, write character to output
        if (cur->character != NOT_A_CHAR) {
            output.put(cur->character);
            outputStr += cur->character;
            cur = encodingTree;
        }
        // Read bit and traverse tree accordingly
        int bit = input.readBit();
        if (bit) {
            cur = cur->one;
        } else {
            cur = cur->zero;
        }
    }
    return outputStr;
}

//
// *This function completes the entire compression process.  Given a file,
// filename, this function (1) builds a frequency map; (2) builds an encoding
// tree; (3) builds an encoding map; (4) encodes the file (don't forget to
// include the frequency map in the header of the output file).  This function
// should create a compressed file named (filename + ".huf") and should also
// return a string version of the bit pattern.
//
string compress(string filename) {
    ifstream input(filename);
    ofbitstream output(filename + ".huf");
    string outputStr;
    hashmap frequencyMap;
    int size;

    // Create encoding map
    buildFrequencyMap(filename, true, frequencyMap);
    HuffmanNode* tree = buildEncodingTree(frequencyMap);
    mymap <int, string> encodingMap = buildEncodingMap(tree);
    freeTree(tree);

    // Encode content
    output << frequencyMap; // Input header
    return encode(input, encodingMap, output, size, true);
}

//
// *This function completes the entire decompression process.  Given the file,
// filename (which should end with ".huf"), (1) extract the header and build
// the frequency map; (2) build an encoding tree from the frequency map; (3)
// using the encoding tree to decode the file.  This function should create a
// compressed file using the following convention.
// If filename = "example.txt.huf", then the uncompressed file should be named
// "example_unc.txt".  The function should return a string version of the
// uncompressed file.  Note: this function should reverse what the compress
// function did.
//
string decompress(string filename) {
    ifbitstream input(filename);
    ofstream output(filename.substr(0, filename.find(".")) + "_unc.txt");
    hashmap frequencyMap;
    string result;
    input >> frequencyMap; // Retrieve header

    // Create encoding tree and decode content
    HuffmanNode* tree = buildEncodingTree(frequencyMap);
    result = decode(input, tree, output);
    freeTree(tree);
    return result;
}
