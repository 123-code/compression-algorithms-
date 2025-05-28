#include <iostream>
#include <map>
#include <queue>

struct TreeNode{
    char data; 
    int frequency;
    TreeNode* left;
    TreeNode* right;

    TreeNode(char value,int freq):data(value),frequency(freq),left(nullptr),right(nullptr){}

};



TreeNode* insert(TreeNode* root,char value,int freq){
    if (root == nullptr){
        return new TreeNode(value,freq);
    }
    if(value < root->data){
        root->left = insert(root->left,value,freq);

    } else{
        root -> right = insert(root->right,value,freq);
    }
    return root;
}

struct Compare {
    bool operator()(TreeNode* a,TreeNode* b){
        return a->frequency > b->frequency;

    }
};

void printTree(TreeNode* root, int depth = 0) {
    if (root == nullptr) return;

    // Print the right child first (to visualize the tree structure)
    printTree(root->right, depth + 1);

    // Print the current node with indentation based on depth
    for (int i = 0; i < depth; i++) {
        std::cout << "    "; // Indentation for depth
    }
    if (root->data != '\0') {
        std::cout << root->data << " (" << root->frequency << ")\n"; // Print character and frequency
    } else {
        std::cout << "* (" << root->frequency << ")\n"; // Print internal node
    }

    // Print the left child
    printTree(root->left, depth + 1);
};

//add codes, 0 when going to the left, 1 when going to the right
void TraverseTree(TreeNode*root,std::string code,std::map<char,std::string>&huffmancodes){
    if (root == nullptr) return; 
    if(root->data != '\0'){
        huffmancodes[root->data] = code;
        return;
    }
    TraverseTree(root->left,code + "0",huffmancodes);
    TraverseTree(root->right,code + "1",huffmancodes);
}

std::string compress(const std::string& message,const std::map<char,std::string>&codes){
std::string compressed = "";
for(char ch:message){
    compressed += codes.at(ch);
}
return compressed;
}

std::string decompress(const std::string& compressed,TreeNode* root){
std::string result  = "";
TreeNode* current = root;

for(char bit:compressed){
    if(bit == '0'){
        current = current->left;

    } else {
        current = current->right;
    }

    if(current->data != '\0'){
        result += current->data;
        current = root;
    }
}
return result;
}



int main(){
    TreeNode* root = nullptr;
    std::string input;
    std::string message = "ISAM YAM SAM";
    std::map<char, int> frequency_map;
    for(char ch:message){
        frequency_map[ch] ++;
    }

    std::priority_queue<TreeNode*,std::vector<TreeNode*>,Compare> pq;

    for(auto const&pair:frequency_map){
        pq.push(new TreeNode(pair.first,pair.second));
}

while(pq.size() > 1){
    TreeNode* left  = pq.top(); pq.pop();
    TreeNode* right = pq.top(); pq.pop();

    TreeNode* newNode = new TreeNode('\0',left->frequency + right->frequency);
    newNode->left = left;
    newNode->right = right;
    pq.push(newNode);

    root = pq.top();
  

}
  std::cout << "Huffman Tree Visualization:\n";
    printTree(root);

std::map<char, std::string> huffmanCodes;
TraverseTree(root, "", huffmanCodes);

std::cout << "\nHuffman Codes:\n";
for (const auto& pair : huffmanCodes) {
    std::cout << "'" << pair.first << "' : " << pair.second << std::endl;
}


std::string compressed = compress(message, huffmanCodes);
std::cout << "\nOriginal: " << message << std::endl;
std::cout << "Compressed: " << compressed << std::endl;


std::string decompressed = decompress(compressed, root);
std::cout << "Decompressed: " << decompressed << std::endl;


std::cout << "\nCompression Stats:" << std::endl;
std::cout << "Original bits: " << message.length() * 8 << std::endl;
std::cout << "Compressed bits: " << compressed.length() << std::endl;
std::cout << "Compression ratio: " << (float)compressed.length() / (message.length() * 8) << std::endl;
}
