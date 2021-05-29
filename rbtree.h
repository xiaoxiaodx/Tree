#ifndef RBTREE_H
#define RBTREE_H



typedef bool NODE_COLOR;
enum{
    NODE_RED = 0,
    NODE_BLACK
};

template <class KEY,class VALUE>
class RBTree
{


public:
    explicit RBTree();

    typedef RBTree<KEY,VALUE> Node;

    void rbtree_insert(Node *&node);
    void rbtree_remove(KEY node);
    Node* insert(Node *&node);
    Node* remove(KEY node);
    Node *rootNode();



    int treedepth;

    Node *left = nullptr;
    Node *right = nullptr;
    Node *parent = nullptr;
    NODE_COLOR color;
    KEY key;

private:

    Node *findPrecursorNode(Node *node);
    Node *findSuccessorNode(Node *node);
    void insert_fixup(Node *&node);
    void delete_fixup(Node *node);

    void destroyNode(Node*);


    void left_rotation(Node *node);
    void right_rotation(Node *node);


     Node* root =nullptr;
    VALUE value;
};

#endif // RBTREE_H
