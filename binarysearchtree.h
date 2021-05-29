#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <QObject>

template <typename T>
class Node{

public:

    Node(int key,T t,Node* left,Node *right,Node *parent){
        this->t = t;
        this->key = key;
        this->left = left;
        this->right = right;
        this->parent = parent;
    };
    Node(){};

    Node(Node &node){
        this->t = node.t;
        this->key = node.key;
        this->left = node.left;
        this->right = node.right;
        this->parent = node.parent;
    };

    Node *left;
    Node *right;
    Node *parent;

    int key;
    //定义自己的数据结构
    T t;
};
using namespace std;
//template <typename T>
class BinarySearchTree
{

public:
    BinarySearchTree();

    bool insert(int key);
    bool remove(int key);


//private:
    Node<string> *root;
    int treedepth;
};

#endif // BINARYSEARCHTREE_H
