#include "rbtree.h"
#include <QDebug>

//template <class KEY,class VALUE>
//static typename RBTree<KEY,VALUE>::Node* root =nullptr;


template <class KEY,class VALUE>
RBTree<KEY,VALUE>::RBTree()
{

}
template <class KEY,class VALUE>
RBTree<KEY,VALUE>* RBTree<KEY,VALUE>::rootNode()
{
    return root;
}
template <class KEY,class VALUE>
void RBTree<KEY,VALUE>::rbtree_remove(KEY node){


    Node* dnode = remove(node);

    delete_fixup(dnode);


    destroyNode(dnode);
}
template <class KEY,class VALUE>
void RBTree<KEY,VALUE>::rbtree_insert(Node *&node)
{

    Node *newNode = insert(node);
    if(newNode != nullptr)
        insert_fixup(newNode);

    root->color = NODE_BLACK;
}


template <class KEY,class VALUE>
RBTree<KEY,VALUE>* RBTree<KEY,VALUE>::insert(Node *&node)
{

    qDebug()<<"insert:"<<node->key;
    Node *newNode = node;
    newNode->color = NODE_RED;
    if(root == nullptr){

        root = newNode;
        root->color = NODE_BLACK;

    }else{


        Node *curNode = root;

        int depth = 0;

        while (curNode != nullptr) {

            KEY curkey = curNode->key;
            KEY newkey = newNode->key;

            depth++;
            if(treedepth < depth)
                treedepth = depth;
            if(newkey < curkey){


                if(curNode->left == nullptr){


                    newNode->parent = curNode;
                    curNode->left = newNode;
                    return newNode;
                }else{

                    curNode = curNode->left;
                }

            }else if(newkey > curkey){


                if(curNode->right == nullptr){
                    newNode->parent = curNode;
                    curNode->right = newNode;
                    return newNode;
                }{

                    curNode = curNode->right;
                }
            }else{
                newNode = nullptr;
                return newNode;
            }
        }


    }



    return nullptr;
}

template <class KEY,class VALUE>
void RBTree< KEY, VALUE>::insert_fixup(Node* &x){

    if(x->parent == root){
        return;
    }
    while (x != root && x->parent->color == NODE_RED) {
        if (x->parent == x->parent->parent->left) {
            Node* __y = x->parent->parent->right;
            if (__y && __y->color == NODE_RED) {
                x->parent->color = NODE_BLACK;
                __y->color = NODE_BLACK;
                x->parent->parent->color = NODE_RED;
                x = x->parent->parent;
            }
            else {
                if (x == x->parent->right) {
                    x = x->parent;
                    left_rotation(x);
                }
                x->parent->color = NODE_BLACK;
                x->parent->parent->color = NODE_RED;
                right_rotation(x->parent->parent);
            }
        }
        else {
            Node* __y = x->parent->parent->left;
            if (__y && __y->color == NODE_RED) {
                x->parent->color = NODE_BLACK;
                __y->color = NODE_BLACK;
                x->parent->parent->color = NODE_RED;
                x = x->parent->parent;
            }
            else {
                if (x == x->parent->left) {
                    x = x->parent;
                    right_rotation(x);
                }
                x->parent->color = NODE_BLACK;
                x->parent->parent->color = NODE_RED;
                left_rotation(x->parent->parent);
            }
        }
    }


}

/*
 *
 * 因为删除节点时，使用的是后继节点，所以被删除的节点只可能3种情况
 * 1：子节点都为空
 * 2：只有一个子节点（左或右）
*/
template <class KEY,class VALUE>
void RBTree<KEY,VALUE>:: destroyNode(Node*dnode)
{

    Node *parentNode = dnode->parent;


    if(parentNode == nullptr){

        root = nullptr;

    }else{

        //字节点只能为空 或一个
        Node* child = nullptr;
        if(dnode->left != nullptr)
            child = dnode->left;
        else
            child = dnode->right;

        if(parentNode->left == dnode)
            parentNode->left = child;
        else
            parentNode->right = child;



        if(child != nullptr)
            child->parent = parentNode;

    }

    delete dnode;
}

template <class KEY,class VALUE>
void RBTree<KEY,VALUE>::delete_fixup(Node* node)
{

    Node *curNode = node;
    while (curNode->parent != nullptr && curNode->color == NODE_BLACK) {
        if(curNode == curNode->parent->left){

            //左子节点
            Node * siblingNode = curNode->parent->right;
            Node * parentNode = curNode->parent;

            if(siblingNode == nullptr){
                curNode = parentNode;
                continue;
            }
            //被删除的节点为黑，根据红黑树性质，兄弟节点不可能为空
            Node * siblingLeftChildeNode = siblingNode->left;
            Node * siblingRightChildeNode = siblingNode->right;

            //兄弟节点为黑
            if(siblingNode->color == NODE_BLACK){


                if(siblingRightChildeNode != nullptr && siblingRightChildeNode->color == NODE_RED){
                    //兄弟节点有右子节点且为红

                    left_rotation(parentNode);

                    siblingNode->color = parentNode->color;
                    parentNode->color = NODE_BLACK;
                    siblingRightChildeNode->color = NODE_BLACK;
                    break;

                }else if(siblingLeftChildeNode != nullptr  && siblingLeftChildeNode->color == NODE_RED){
                    //兄弟节点的左子节点为红，右子节点只能为黑或者nullptr
                    right_rotation(siblingNode);
                    siblingLeftChildeNode->color = NODE_BLACK;
                    siblingNode->color = NODE_RED;

                }else{

                    //兄弟节点的子节点为黑或者nullptr

                    if(parentNode->color == NODE_RED){

                        parentNode->color = NODE_BLACK;
                        siblingNode->color = NODE_RED;
                        break;
                    }else{

                        siblingNode->color = NODE_RED;
                        curNode = parentNode;//新的起点
                        continue;
                    }

                }



            }else if(siblingNode->color == NODE_RED ){

                left_rotation(parentNode);
                siblingNode->color = NODE_BLACK;
                parentNode->color = NODE_RED;

            }




        }else{//与左子节点对称




            Node * siblingNode = curNode->parent->left;
            Node * parentNode = curNode->parent;

            if(siblingNode == nullptr){
                curNode = parentNode;
                continue;
            }
            //被删除的节点为黑
            Node * siblingLeftChildeNode = siblingNode->left;
            Node * siblingRightChildeNode = siblingNode->right;

            //兄弟节点为黑
            if(siblingNode->color == NODE_BLACK){


                if(siblingLeftChildeNode != nullptr && siblingLeftChildeNode->color == NODE_RED){
                    //左子节点为红

                    right_rotation(parentNode);

                    siblingNode->color = parentNode->color;
                    parentNode->color = NODE_BLACK;
                    siblingRightChildeNode->color = NODE_BLACK;
                    break;

                }else if(siblingRightChildeNode != nullptr  && siblingRightChildeNode->color == NODE_RED){
                    //右子节点为红，左子节点为黑
                    left_rotation(siblingNode);
                    siblingLeftChildeNode->color = NODE_BLACK;
                    siblingNode->color = NODE_RED;

                }else{

                    if(parentNode->color == NODE_RED){

                        parentNode->color = NODE_BLACK;
                        siblingNode->color = NODE_RED;
                        break;
                    }else{

                        siblingNode->color = NODE_RED;
                        curNode = parentNode;//新的起点
                        break;
                    }
                }



            }else if(siblingNode->color == NODE_RED ){

                right_rotation(parentNode);
                siblingNode->color = NODE_BLACK;
                parentNode->color = NODE_RED;

            }

        }


    }


}


//来自stl
template <class KEY,class VALUE>
void RBTree<KEY,VALUE>::left_rotation(Node *x){

    Node* y = x->right;

    x->right = y->left;
    if(y->left  != nullptr)
        y->left->parent = x;

    y->parent = x->parent;
    if(x == root)
        root = y;
    else if(x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}


//来自stl
template <class KEY,class VALUE>
void RBTree<KEY,VALUE>::right_rotation(Node *x){

    Node *y = x->left;
    x->left = y->right;
    if(y->right != nullptr)
        y->right->parent = x;
    y->parent = x->parent;

    if(x == root)
        root = y;
    else if(x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;

    y->right = x;
    x->parent = y;

}



template <class KEY,class VALUE>
RBTree<KEY,VALUE>* RBTree<KEY,VALUE>::remove(KEY key){


    qDebug()<<"删除节点:"<<key;
    //找到要删除的节点
    Node * curnode = root;

    while (curnode != nullptr) {

        int curkey = curnode->key;
        if(curkey < key){

            curnode = curnode->right;

        }else if(curkey > key){

            curnode = curnode->left;

        }else{

            //子节点都为空，直接删除
            if(curnode->left == nullptr && curnode->right == nullptr)
            {


                return curnode;
            }
            else if(curnode->left != nullptr && curnode->right == nullptr)
            {
                /*
                     * 有个子节点时，
                     * 1、需要先找到其后继结点（右子树中最小的子节点），找前驱节点（左子树中最大的子节点）也是可以的
                     * 2、将后继节点与当前节点替换， 然后删除当前节点
                    */

                //只有一个左子节点

                return curnode;


            }else if(curnode->right != nullptr)
            {
                //有一个右子节点
                Node *successorNode  = findSuccessorNode(curnode);
                //交换值不交换颜色 和指针
                KEY key = curnode->key;
                VALUE value = curnode->value;

                curnode->key = successorNode->key;
                curnode->value = successorNode->value;

                successorNode->key = key;
                successorNode->value = value;






                return successorNode;

            }
        }
    }


    qDebug()<<"最终删除节点:"<<curnode->key;

    return curnode;
}


template <class KEY,class VALUE>
RBTree<KEY,VALUE>* RBTree<KEY,VALUE>::findPrecursorNode(Node *node)
{

    Node *findNode = node->left;


    while (findNode != nullptr && findNode->right != nullptr) {

        findNode = findNode->right;

    }

    qDebug()<<"findPrecursorNode:"<<findNode->key;
    return findNode;

}
template <class KEY,class VALUE>
RBTree<KEY,VALUE>* RBTree<KEY,VALUE>::findSuccessorNode(Node *node)
{
    Node *findNode = node->right;

    while (findNode != nullptr && findNode->left != nullptr) {
        findNode = findNode->left;
    }
    qDebug()<<"findSuccessorNode:"<<findNode->key;
    return findNode;

}

