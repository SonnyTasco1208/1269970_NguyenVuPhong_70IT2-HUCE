#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>

using namespace std;
using namespace std::chrono;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

TreeNode* insert(TreeNode* root, int key) {
    if (root == nullptr) return new TreeNode(key);
    if (key < root->data) root->left = insert(root->left, key);
    else if (key > root->data) root->right = insert(root->right, key);
    return root;
}

int height(TreeNode* root) {
    if (root == nullptr) return -1;
    return 1 + max(height(root->left), height(root->right));
}

TreeNode* search(TreeNode* root, int key) {
    if (root == nullptr || root->data == key) return root;
    if (key < root->data) return search(root->left, key);
    return search(root->right, key);
}

void deleteTree(TreeNode* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    mt19937 rng(42); 
    vector<int> sizes = {1000, 5000, 10000, 20000};
    
    cout << "n,loai_du_lieu,chieu_cao,thoi_gian_chen_ms,thoi_gian_tim_ms\n";

    long long dummy = 0; 

    for (int n : sizes) {

        vector<int> randomKeys(n);
        for (int i = 0; i < n; ++i) randomKeys[i] = i;
        shuffle(randomKeys.begin(), randomKeys.end(), rng);

        TreeNode* rootRandom = nullptr;
        auto start_insert_rnd = high_resolution_clock::now();
        for (int key : randomKeys) {
            rootRandom = insert(rootRandom, key);
        }
        auto end_insert_rnd = high_resolution_clock::now();
        double time_insert_rnd = duration<double, milli>(end_insert_rnd - start_insert_rnd).count();

        int h_rnd = height(rootRandom);

        vector<int> searchKeys_rnd(1000);
        for (int i = 0; i < 1000; ++i) {
            searchKeys_rnd[i] = randomKeys[rng() % n];
        }

        auto start_search_rnd = high_resolution_clock::now();
        for (int key : searchKeys_rnd) {
            TreeNode* res = search(rootRandom, key);
            if (res) dummy += res->data; 
        }
        auto end_search_rnd = high_resolution_clock::now();
        double time_search_rnd = duration<double, milli>(end_search_rnd - start_search_rnd).count();

        cout << n << ",Ngau nhien," << h_rnd << "," << time_insert_rnd << "," << time_search_rnd << "\n";

        vector<int> sortedKeys(n);
        for (int i = 0; i < n; ++i) sortedKeys[i] = i;

        TreeNode* rootSorted = nullptr;
        auto start_insert_srt = high_resolution_clock::now();
        for (int key : sortedKeys) {
            rootSorted = insert(rootSorted, key);
        }
        auto end_insert_srt = high_resolution_clock::now();
        double time_insert_srt = duration<double, milli>(end_insert_srt - start_insert_srt).count();
        int h_srt = height(rootSorted);
        vector<int> searchKeys_srt(1000);
        for (int i = 0; i < 1000; ++i) {
            searchKeys_srt[i] = sortedKeys[rng() % n];
        }
        auto start_search_srt = high_resolution_clock::now();
        for (int key : searchKeys_srt) {
            TreeNode* res = search(rootSorted, key);
            if (res) dummy += res->data;
        }
        auto end_search_srt = high_resolution_clock::now();
        double time_search_srt = duration<double, milli>(end_search_srt - start_search_srt).count();

        cout << n << ",Da sap xep," << h_srt << "," << time_insert_srt << "," << time_search_srt << "\n";
        deleteTree(rootRandom);
        deleteTree(rootSorted);
    }
    if (dummy == -1) cerr << "Dummy error"; 

    return 0;
}