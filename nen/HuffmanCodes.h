#ifndef HUFFMANCODES_H
#define HUFFMANCODES_H
#include<iostream>
#include<vector>
#include<fstream>
#include<bitset>
#include"NODE.h"
using namespace std;

 
// Struct này có công dụng lưu trữ bit đã mã hoá theo mã tiền tố
struct Bit
{
    char c;
    string bit;
};


class HuffmanCompression
{
private:
    string data; // Lưu trữ chuỗi đọc vào từ file
    Node* root;
    vector<Bit> bit; // Lưu trữ mã bit tương ứng với ký tự ta xét
    string bitTree; // Cây Huffman được mã hoá để lưu vào file
   
    void convertTree();
    void visit(Node* curr, string bit);
    void generateTree(Node* curr);
public:
    HuffmanCompression();
    ~HuffmanCompression();
    void compression(char*);
    void finFile(char *);
};
#endif 
