#include <iostream>
#include <climits>

using namespace std;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};
bool isValidBSTHelper(TreeNode* node, long long minVal, long long maxVal) {
    if (node == nullptr) {
        return true;
    }
    if (node->data <= minVal || node->data >= maxVal) {
        return false;
    }
    return isValidBSTHelper(node->left, minVal, node->data) && 
           isValidBSTHelper(node->right, node->data, maxVal);
}
bool isValidBST(TreeNode* root) {
    return isValidBSTHelper(root, LLONG_MIN, LLONG_MAX);
}

int main() {
    TreeNode* validRoot = new TreeNode(50);
    validRoot->left = new TreeNode(30);
    validRoot->right = new TreeNode(70);
    validRoot->left->left = new TreeNode(20);
    validRoot->left->right = new TreeNode(40);
    validRoot->right->right = new TreeNode(80);
    validRoot->left->left->left = new TreeNode(10);
    
    cout << "Kiem tra Cay 1 (Giong Bai 1 - Hop le): " 
         << (isValidBST(validRoot) ? "TRUE (La BST)" : "FALSE (Khong la BST)") << endl;
    TreeNode* invalidRoot = new TreeNode(10);
    invalidRoot->left = new TreeNode(5);
    invalidRoot->right = new TreeNode(15);
    invalidRoot->right->left = new TreeNode(6);
    invalidRoot->right->right = new TreeNode(20);

    cout << "Kiem tra Cay 2 (Phan vi du - Khong hop le): " 
         << (isValidBST(invalidRoot) ? "TRUE (La BST)" : "FALSE (Khong la BST)") << endl;

    return 0;
}