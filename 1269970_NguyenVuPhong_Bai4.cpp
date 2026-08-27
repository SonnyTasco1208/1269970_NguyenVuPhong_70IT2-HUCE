#include <iostream>
#include <algorithm>

using namespace std;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};


int height(TreeNode* root) {
    if (root == nullptr) return -1;
    return 1 + max(height(root->left), height(root->right));
}

void inorder(TreeNode* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

TreeNode* insert(TreeNode* root, int key) {
    if (root == nullptr) {
        return new TreeNode(key);
    }
    
    if (key < root->data) {
        root->left = insert(root->left, key);
    } else if (key > root->data) {
        root->right = insert(root->right, key);
    }
    return root; 
}

TreeNode* search(TreeNode* root, int key) {
    if (root == nullptr || root->data == key) {
        return root;
    }
    if (key < root->data) {
        return search(root->left, key);
    }
    return search(root->right, key);
}

TreeNode* findMin(TreeNode* root) {
    TreeNode* current = root;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

TreeNode* deleteNode(TreeNode* root, int key) {
    if (root == nullptr) return root;

    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left == nullptr) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }
        TreeNode* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}


void printMenu() {
    cout << "\n----- MENU QUAN LY BST -----\n";
    cout << "1. Chen khoa\n";
    cout << "2. Tim kiem khoa\n";
    cout << "3. Xoa khoa\n";
    cout << "4. In cay theo Inorder\n";
    cout << "5. In chieu cao cay\n";
    cout << "0. Thoat\n";
    cout << "Lua chon cua ban: ";
}

int main() {
    TreeNode* root = nullptr;
    int choice, key;
    TreeNode* result = nullptr;

    do {
        printMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Nhap khoa can chen: ";
                cin >> key;
                root = insert(root, key);
                cout << "Da chen " << key << " vao cay.\n";
                break;
            case 2:
                cout << "Nhap khoa can tim: ";
                cin >> key;
                result = search(root, key);
                if (result != nullptr) cout << "-> Tim thay " << key << " trong cay.\n";
                else cout << "-> Khong tim thay " << key << ".\n";
                break;
            case 3:
                cout << "Nhap khoa can xoa: ";
                cin >> key;
                if (search(root, key) != nullptr) {
                    root = deleteNode(root, key);
                    cout << "-> Da xoa " << key << " khoi cay.\n";
                } else {
                    cout << "-> Khoa " << key << " khong ton tai!\n";
                }
                break;
            case 4:
                cout << "-> Inorder: ";
                if (root == nullptr) cout << "Cay rong!";
                else inorder(root);
                cout << endl;
                break;
            case 5:
                cout << "-> Chieu cao cay: " << height(root) << endl;
                break;
            case 0:
                cout << "Thoat chuong trinh...\n";
                break;
            default:
                cout << "Lua chon khong hop le!\n";
        }
    } while (choice != 0);

    return 0;
}