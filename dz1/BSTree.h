#pragma once
#include <iostream>
#include <fstream>

namespace bst {

    class BSTree {
    private:
        struct Node {
            int data;
            Node* left;
            Node* right;

            Node(int value) : data(value), left(nullptr), right(nullptr) {}
        };

        Node* root;

        Node* insert(Node* node, int value);
        Node* remove(Node* node, int value);
        Node* findMin(Node* node);
        Node* search(Node* node, int value);

        void inorder(Node* node);
        void preorder(Node* node);
        void postorder(Node* node);

        void clear(Node* node);
        Node* copy(Node* node);

        void save(Node* node, std::ofstream& out);
        Node* load(std::ifstream& in);

    public:
        BSTree();
        BSTree(const BSTree& other);
        BSTree(BSTree&& other);
        ~BSTree();

        void insert(int value);
        void remove(int value);
        bool search(int value);

        void inorder();
        void preorder();
        void postorder();

        void clear();

        void saveToFile(const std::string& filename);
        void loadFromFile(const std::string& filename);

        friend std::ostream& operator<<(std::ostream& os, BSTree& tree);
    };

}