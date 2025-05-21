#include <iostream>
#include <map>

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


void inOrder(TreeNode* root) {
    if (root != nullptr) {
        inOrder(root->left);
        std::cout << "Character: " << root->data << ", Frequency: " << root->frequency << std::endl;
        inOrder(root->right);
    }
}

int main(){
    TreeNode* root = nullptr;
    std::string input;
    std::string message = "ISAM YAM SAM";
    std::map<char, int> frequency_map;


    for(int x = 0;x<message.size();x++){
        std::cout << message[x] << " ";
        frequency_map[message[x]]++;
    }
    for(auto const&pair:frequency_map){
        root = insert(root,pair.first,pair.second);
    //std::cout << pair.first << " " << pair.second << std::endl;
}
 std::cout << "In-order traversal: " << std::endl;
    inOrder(root);
return 0;
}

