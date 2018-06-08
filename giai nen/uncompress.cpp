#include<iostream>
#include"HuffmanUncompress.h"
using namespace std;

int main(int argc, char *argv[])
{
    HuffmanExtraction a;
	a.compressedFileLoad(argv[1]);
	a.extraction(argv[2]);
	return 0;
}
