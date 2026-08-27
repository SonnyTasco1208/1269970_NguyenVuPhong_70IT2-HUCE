#include <iostream>
#include <algorithm> 

using namespace std;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};


int countNodes(TreeNode* root) {
    if (root == nullptr) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}


int countLeaves(TreeNode* root) {
    if (root == nullptr) return 0;
    if (root->left == nullptr && root->right == nullptr) return 1;
    return countLeaves(root->left) + countLeaves(root->right);
}


int height(TreeNode* root) {
    if (root == nullptr) return -1;
    return 1 + max(height(root->left), height(root->right));
}


int depth(TreeNode* root, int target) {
    int currentDepth = 0;
    TreeNode* curr = root;
    
    while (curr != nullptr) {
        if (curr->data == target) {
            return currentDepth;
        }
        if (target < curr->data) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
        currentDepth++;
    }
    return -1; 
}


int maxValue(TreeNode* root) {
    if (root == nullptr) return -1;
    TreeNode* curr = root;
    while (curr->right != nullptr) {
        curr = curr->right;
    }
    return curr->data;
}


int minValue(TreeNode* root) {
    if (root == nullptr) return -1;
    TreeNode* curr = root;
    while (curr->left != nullptr) {
        curr = curr->left;
    }
    return curr->data;
}

int main() {

    TreeNode* root = new TreeNode(50);
    root->left = new TreeNode(30);
    root->right = new TreeNode(70);
    root->left->left = new TreeNode(20);
    root->left->right = new TreeNode(40);
    root->right->right = new TreeNode(80);
    root->left->left->left = new TreeNode(10);
    cout << "Tong so nut: " << countNodes(root) << endl;
    cout << "So nut la:   " << countLeaves(root) << "\t(cac nut 10, 40, 80)" << endl;
    cout << "Chieu cao:   " << height(root) << endl;
    cout << "Do sau cua nut 40: " << depth(root, 40) << endl;
    cout << "Gia tri lon nhat: " << maxValue(root) << endl;
    cout << "Gia tri nho nhat: " << minValue(root) << endl;

    return 0;
}