#ifndef HUFFMAN_UNCOMPRESS_H
#define HUFFMAN_UNCOMPRESS_H
#include<iostream>
#include<vector>
#include<fstream>
#include<bitset>
#include"NODE.h"
using namespace std;


class HuffmanExtraction
{
private:
    string bitTree;
    string data;
    Node* root;
    void generateTree(Node* curr);
    char visit(Node* curr);
public:
    HuffmanExtraction();
	~HuffmanExtraction();
    void compressedFileLoad(char *);
    void extraction(char *);
	//void compressedFileLoad();
    //void extraction();
};



#endif
