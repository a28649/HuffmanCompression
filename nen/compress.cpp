#include<iostream>
#include"HuffmanCodes.h"
using namespace std;
int main(int argc, char *argv[])
{
    HuffmanCompression a;   
	a.finFile(argv[1]);
	a.compression(argv[2]);
	return 0;
}
