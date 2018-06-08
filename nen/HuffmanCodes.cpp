#include "HuffmanCodes.h"


HuffmanCompression::HuffmanCompression(){
	bitTree = ""; 
}

HuffmanCompression::~HuffmanCompression(){}


void HuffmanCompression::finFile(char *fileName)
{
    fstream f;
	f.open(fileName);
    for( string line; getline(f,line);)
    {
        data+=line;
        data+="\n";
    }
    
	f.close();
 
	
}



void HuffmanCompression::convertTree()
{
    
    vector<Node*> tree;
    // Lập bảng tần số
    // Duyệt hết chuỗi để kiểm tra
    for (int i = 0; i < data.length(); i++)
    {
        bool existed = false;
        // Duyệt trong bảng, nếu ký tự ta xét đã có trong bảng thì ++freq
        for (int j = 0; j < tree.size(); j++) 
                {
            if (tree[j]->c == data[i])
            {
                tree[j]->freq++;
                existed = true;
                break;
            }
        }
        // Ngược lại thì thêm ký tự đó vào bảng
        if (!existed)
        {
            Node* node = new Node();
            node->c = data[i];
            node->freq = 1;
            tree.push_back(node);
        }
    }
 
    // Tiếp theo là sắp xếp lại bảng tần số
    for (int i = 0; i < tree.size() - 1; i++)
    {
        for (int j = i + 1; j < tree.size(); j++)
                {
                        if (tree[i]->freq > tree[j]->freq)
            {
                Node* temp = tree[i];
                tree[i] = tree[j];
                tree[j] = temp;
            }
        }
    }
     
    while (true)
    {
        // Tạo node z có con là 2 phần tử đầu trong bảng tần số
        Node* tmp = new Node();
        tmp->left = tree[0];
        tmp->right = tree[1];
        tmp->freq = tmp->left->freq + tmp->right->freq;
 
        // Xoá 2 phần tử đầu trong bảng tần số
        tree.erase(tree.begin(), tree.begin() + 2);
        tree.resize(tree.size() + 1);
 
        // Nếu chỉ còn đúng 1 phần tử
        if (tree.size() == 1)
        {
            tree[0] = tmp;
            break;
        }
        else
        {
            // Chèn vị trí node z vào bảng tần số sao cho phù hợp
            // Ở đây mình sắp xếp giảm dần
            for (int j = 0; j < tree.size() - 1; j++)
                        {
                                bool isMax = true;
                                if (tree[j]->freq > tmp->freq)
                {
                    for (int k = tree.size() - 1; k > j; k--)
                    {
                        tree[k] = tree[k - 1];
                    }
                    tree[j] = tmp;
                    isMax = false;
                    break;
                }
                if (isMax) tree[tree.size() - 1] = tmp;
            }
        }
    }
 
    // Cuối cùng ta thu được cây Huffman là phần tử duy nhất còn lại trong bảng tần số
    root = tree[0];
}



void HuffmanCompression::generateTree(Node* curr)
{
    if (curr != NULL)
    {
        // Nếu node là lá
        if (curr->left == NULL && curr->right == NULL)
        {
            bitTree += '1';
            bitset<8> charToBit(curr->c);
            bitTree += charToBit.to_string();
        }
        // Ngược lại
        else
        {
            bitTree += '0';
            generateTree(curr->left);
            generateTree(curr->right);
        }
    }
}



void HuffmanCompression::visit(Node* curr, string bit)
{
    if (curr != NULL)
    {
        if (curr->left == NULL || curr->right == NULL)
        {
            Bit cBit;
            cBit.c = curr->c;
            cBit.bit = bit;
            this->bit.push_back(cBit);
        }
        else
        {
            visit(curr->left, bit + "0");
            visit(curr->right, bit + "1");
        }
    }
}


char convertBitToChar(string input)
{
    char c = 0;
    for (int i = 0; i < input.length(); i++)
    {
        c = (c << 1) | (input[i] - 48);
    }
    return c;
}

string convertBitStringToCharString(string input)
{
    string result = "";
    while (input.length() > 0)
    {
        string temp;
        if (input.length() > 8)
        {
            temp = input.substr(input.length() - 8, 8);
            input = input.erase(input.length() - 8, 8);
        }
        else
        {
            temp = input;
            if (temp.length() > 8) temp = "0" + temp;
            input = "";
        }
        result = convertBitToChar(temp) + result;
    }
    return result;
}


void HuffmanCompression::compression(char *fileName)
{
    this->convertTree();
    this->visit(root, "");
    this->generateTree(root);
 
    // Thay thế các kí tự trong chuỗi data thành mã bit tương ứng trong bảng tần số
    string allWordToBit = "";
    for (int i = 0; i < data.length(); i++)
    {
        for (int j = 0; j < bit.size(); j++)
        {
            // kiểm tra xem tại kí tự data[i] có bằng bằng kí tự trong bit[j].
            if (data[i] == bit[j].c)
            {
                // lấy tất cả bit trong vector cho vào allwordToBit.
                allWordToBit += bit[j].bit;
                break;
            }
        }
    }
 
    // Mã hoá bit cây Huffman và bit data thành ký tự để lưu vào file
    string afterConverBitToString = convertBitStringToCharString(bitTree + allWordToBit);
    int realBit = 0, sizeBit = (bitTree + allWordToBit).length();
 
    // Do độ dài bit của bitTree và allwordToBit không là bội của 8
    // Ta cần xác định phải thêm  bao nhiêu bit '0'  vào chuỗi bit bitTree và allwordToBit
    // sao cho độ dài của bitTrê và allwordToBit là bội của 8 
    while (realBit < sizeBit) realBit += 8;
    char addBit = realBit - sizeBit; 
    // số lượng kiểu ký tự có trong chuỗi 
    char bitNum = this->bit.size();
 
    ofstream fo(fileName);
    fo << (char)bitNum << (char)addBit << afterConverBitToString;
    fo.close();
}

