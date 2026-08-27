#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

void preorderHelper(TreeNode* root, vector<int>& result) {
    if (root == nullptr) return;
    result.push_back(root->data);
    preorderHelper(root->left, result);
    preorderHelper(root->right, result);
}

vector<int> preorder(TreeNode* root) {
    vector<int> result;
    preorderHelper(root, result);
    return result;
}

void inorderHelper(TreeNode* root, vector<int>& result) {
    if (root == nullptr) return;
    inorderHelper(root->left, result);
    result.push_back(root->data);
    inorderHelper(root->right, result);
}

vector<int> inorder(TreeNode* root) {
    vector<int> result;
    inorderHelper(root, result);
    return result;
}

void postorderHelper(TreeNode* root, vector<int>& result) {
    if (root == nullptr) return;
    postorderHelper(root->left, result);
    postorderHelper(root->right, result);
    result.push_back(root->data);
}

vector<int> postorder(TreeNode* root) {
    vector<int> result;
    postorderHelper(root, result);
    return result;
}

vector<int> levelOrder(TreeNode* root) {
    vector<int> result;
    if (root == nullptr) return result;
    
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();
        
        result.push_back(current->data);
        
        if (current->left != nullptr) q.push(current->left);
        if (current->right != nullptr) q.push(current->right);
    }
    
    return result;
}

vector<int> inorderIterative(TreeNode* root) {
    vector<int> result;
    stack<TreeNode*> s;
    TreeNode* curr = root;

    while (curr != nullptr || !s.empty()) {
        while (curr != nullptr) {
            s.push(curr);
            curr = curr->left;
        }
        curr = s.top();
        s.pop();
        result.push_back(curr->data);
        curr = curr->right;
    }
    return result;
}


void printVector(vector<int>& v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << (i == v.size() - 1 ? "" : " ");
    }
    cout << endl;
}

int main() {
    TreeNode* root = new TreeNode(50);
    root->left = new TreeNode(30);
    root->right = new TreeNode(70);
    root->left->left = new TreeNode(20);
    root->left->right = new TreeNode(40);
    root->right->right = new TreeNode(80);
    root->left->left->left = new TreeNode(10);
    vector<int> pre = preorder(root);
    cout << "Preorder:    ";
    printVector(pre);

    vector<int> in = inorder(root);
    cout << "Inorder:     ";
    printVector(in);

    vector<int> post = postorder(root);
    cout << "Postorder:   ";
    printVector(post);

    vector<int> level = levelOrder(root);
    cout << "Level-order: ";
    printVector(level);
    vector<int> in_iter = inorderIterative(root);

    return 0;
}