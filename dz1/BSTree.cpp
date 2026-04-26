#include "BSTree.hpp"

using namespace bst;


BSTree::BSTree() : root(nullptr) {}

BSTree::BSTree(const BSTree& other) {
    root = copy(other.root);
}

BSTree::BSTree(BSTree&& other) {
    root = other.root;
    other.root = nullptr;
}

BSTree::~BSTree() {
    clear();
}


BSTree::Node* BSTree::insert(Node* node, int value) {
    if (!node) return new Node(value);

    if (value < node->data)
        node->left = insert(node->left, value);
    else
        node->right = insert(node->right, value);

    return node;
}

void BSTree::insert(int value) {
    root = insert(root, value);
}

// Поиск
BSTree::Node* BSTree::search(Node* node, int value) {
    if (!node || node->data == value) return node;

    if (value < node->data)
        return search(node->left, value);
    else
        return search(node->right, value);
}

bool BSTree::search(int value) {
    return search(root, value) != nullptr;
}

// Минимум
BSTree::Node* BSTree::findMin(Node* node) {
    while (node->left) node = node->left;
    return node;
}

// Удаление
BSTree::Node* BSTree::remove(Node* node, int value) {
    if (!node) return nullptr;

    if (value < node->data)
        node->left = remove(node->left, value);
    else if (value > node->data)
        node->right = remove(node->right, value);
    else {
        if (!node->left) return node->right;
        if (!node->right) return node->left;

        Node* minNode = findMin(node->right);
        node->data = minNode->data;
        node->right = remove(node->right, minNode->data);
    }

    return node;
}

void BSTree::remove(int value) {
    root = remove(root, value);
}

// Обходы
void BSTree::inorder(Node* node) {
    if (!node) return;
    inorder(node->left);
    std::cout << node->data << " ";
    inorder(node->right);
}

void BSTree::preorder(Node* node) {
    if (!node) return;
    std::cout << node->data << " ";
    preorder(node->left);
    preorder(node->right);
}

void BSTree::postorder(Node* node) {
    if (!node) return;
    postorder(node->left);
    postorder(node->right);
    std::cout << node->data << " ";
}

void BSTree::inorder() { inorder(root); }
void BSTree::preorder() { preorder(root); }
void BSTree::postorder() { postorder(root); }

// Очистка
void BSTree::clear(Node* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

void BSTree::clear() {
    clear(root);
    root = nullptr;
}

// Копирование
BSTree::Node* BSTree::copy(Node* node) {
    if (!node) return nullptr;

    Node* newNode = new Node(node->data);
    newNode->left = copy(node->left);
    newNode->right = copy(node->right);

    return newNode;
}

// Файл
void BSTree::save(Node* node, std::ofstream& out) {
    if (!node) return;
    out << node->data << " ";
    save(node->left, out);
    save(node->right, out);
}

void BSTree::saveToFile(const std::string& filename) {
    std::ofstream out(filename);
    save(root, out);
}

BSTree::Node* BSTree::load(std::ifstream& in) {
    int value;
    Node* node = nullptr;

    while (in >> value) {
        insert(value);
    }

    return node;
}

void BSTree::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    load(in);
}


std::ostream& bst::operator<<(std::ostream& os, BSTree& tree) {
    tree.inorder();
    return os;
}