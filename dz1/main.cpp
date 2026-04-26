#include "BSTree.hpp"

using namespace std;
using namespace bst;

int main() {
    BSTree tree;

    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);

    cout << "Дерево: " << tree << endl;

    cout << "Поиск 4: " << tree.search(4) << endl;

    tree.remove(3);
    cout << "После удаления 3: " << tree << endl;

    tree.saveToFile("tree.txt");

    BSTree tree2;
    tree2.loadFromFile("tree.txt");

    cout << "Загруженное дерево: " << tree2 << endl;

    return 0;
}