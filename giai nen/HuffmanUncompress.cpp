#include"HuffmanUncompress.h"

HuffmanExtraction::HuffmanExtraction() {
	root = new Node();
}

HuffmanExtraction::~HuffmanExtraction(){}


char convertBitToChar(string input)
{
    char c = 0;
    for (int i = 0; i < input.length(); i++)
    {
        c = (c << 1) | (input[i] - 48);
    }
    return c;
}
// Constructor của class trên
void HuffmanExtraction::compressedFileLoad(char *filePath)
//void HuffmanExtraction::compressedFileLoad()
{
    root = new Node();
    string bitSequence = "";
    ifstream fi(filePath, ios::binary);
    char c;
    // Ta không thể đọc 1 lần toàn bộ kí tự trong file
    // Vì có thể đâu đó trong file có chứa kí tự '\0'
    // Nếu ta cố tình đọc thì chuỗi bitSequence sẽ không thể lưu hết được
    // Vì vậy ta cần phải đọc từng ký tự trong file
    while (fi >> noskipws >> c)
    {
        bitset<8> bit(c);
        bitSequence += bit.to_string();
    }
     
    // Lấy ra số ký tự có trong chuỗi mã hoá
    char numChar = convertBitToChar(bitSequence.substr(0, 8));
    bitSequence.erase(0, 8);
 
    // Lấy ra số bit '0' được thêm vào như phía trên mình đề cập
    char addBit = convertBitToChar(bitSequence.substr(0, 8));
    bitSequence.erase(0, 8);
 
    // Bỏ đi các bit '0' thừa
    bitSequence.erase(0, addBit);
 
    // Số bit cần lấy tuân theo công thức dưới đây
    int sizeBit = 10 * numChar - 1;
    bitTree = bitSequence.substr(0, sizeBit);
    bitSequence.erase(0, sizeBit);
    data = bitSequence;
    fi.close();
}


void HuffmanExtraction::generateTree(Node* curr)
{
    while (bitTree.length() > 0)
    {
        // Nếu là node lá
        if (curr->left != NULL && curr->right != NULL) return;
 
        Node* node = new Node();
        if (bitTree[0] == '0')
        {
            bitTree.erase(0, 1);
            // Ta cần phải xác định xem mình nên gọi đệ quy đến node trái hay phải
            if (curr->left == NULL)
            {
                curr->left = node;
                generateTree(curr->left);
            }
            else
            {
                curr->right = node;
                generateTree(curr->right);
            }
        }
         
        // Nếu gặp bit '1', ta get 8 bit kế tiếp
        else
        {
            string temp = bitTree.substr(1, 8);
            bitTree.erase(0, 9);
             
            // Hàm char convertBitToChar(string temp) dùng để xuất ra ký tự tương ứng với chuỗi bit
            node->c = convertBitToChar(temp);
            if (curr->left == NULL) curr->left = node;
            else curr->right = node;
        }
    }
}

char HuffmanExtraction::visit(Node* curr)
{
    if (curr->left == NULL && curr->right == NULL)
    {
        return curr->c;
    }
    if (data[0] == '0')
    {
        data.erase(0, 1);
        visit(curr->left);
    }
    else
    {
        data.erase(0, 1);
        visit(curr->right);
    }
}

void HuffmanExtraction::extraction(char *outputPath)
//void HuffmanExtraction::extraction()
{
    this->generateTree(root);
	// HuffmanTree algorithm: Merge two lowest weight leaf nodes until
    // only one node is left (root).
    root = root->left;
    string result = "";
	ofstream fo(outputPath);
    while (data.length() > 0)
	{
		char text = this->visit(root);
    	fo << text;
		//cout << i++ << ": " << text << endl;
	}
    fo.close();
}
