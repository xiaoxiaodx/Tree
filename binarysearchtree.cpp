#include "binarysearchtree.h"
#include <QDebug>

BinarySearchTree::BinarySearchTree():root(nullptr)
{

    treedepth = 0;
}

//默认需要保存的数据值是与key一样的字符串，
bool BinarySearchTree::insert(int key)
{

    if(root == nullptr){

        root = new Node<string>(key,"",nullptr,nullptr,nullptr);

    }else{

        Node<string> * curnode = root;
        int level = 0;
        while (curnode != nullptr) {

            int curkey = curnode->key;
            level++;
            if(curkey < key){

                if(curnode->right == nullptr){

                    Node<string> *newnode = new Node<string>(key,"",nullptr,nullptr,nullptr);
                    curnode->right = newnode;
                    newnode->parent = curnode;
                    if(treedepth < level)
                        treedepth = level;
                    qDebug()<<"插入成功，右值:"<<key<<",深度:"<<treedepth;
                    break;
                }else
                    curnode = curnode->right;

            }else if(curkey > key){

                if(curnode->left == nullptr){
                    if(treedepth < level)
                        treedepth = level;
                    Node<string> *newnode = new Node<string>(key,"",nullptr,nullptr,nullptr);

                    curnode->left = newnode;
                    newnode->parent = curnode;
                    qDebug()<<"插入成功，左值:"<<key<<",深度:"<<treedepth;
                    break;
                }else
                    curnode = curnode->left;


            }else{

                //插入相同输入
                qDebug()<<"插入失败:"<<key;
                return false;
            }

        }


    }

    return true;
}

bool BinarySearchTree::insert(Node<string>* &n)
{


}


bool BinarySearchTree::remove(int key){


    qDebug()<<"删除节点:"<<key;
    //找到要删除的节点
    Node<string> * curnode = root;

    if(root->key == key){
        qDebug()<<"不能删除根节点:";
        return false;
    }
    while (curnode != nullptr) {

        qDebug()<<"删除节点:"<<curnode->key;
        int curkey = curnode->key;
        if(curkey < key){

            curnode = curnode->right;

        }else if(curkey > key){

            curnode = curnode->left;

        }else{

            //子节点都为空，直接删除
            if(curnode->left == nullptr && curnode->right == nullptr)
            {

                qDebug()<<"左右节点都为空";
                if(curkey < curnode->parent->key){
                    curnode->parent->left = nullptr;
                    qDebug()<<"删除左节点成功:"<<key;
                }else if(curkey > curnode->parent->key){
                    curnode->parent->right = nullptr;
                    qDebug()<<"删除右节点成功:"<<key;
                }
                delete curnode;
                curnode = nullptr;
                break;
            }
            else if(curnode->left != nullptr && curnode->right == nullptr)
            {
                /*
                 * 有且只有一个子节点时，可以将子节点替换到当前节点的位置，然后删除
                 * 每一个节点都是按搜索二叉树（右子树大，左子树小）的规则插入的，所以在这种情况下子节点替换当前节点，也会满足二叉搜索树的规则
                 *
                 * 有一个左子节点，右节点空
                */


                if(curkey < curnode->parent->key){
                    curnode->parent->left = curnode->left;
                    curnode->left->parent = curnode->parent;
                    qDebug()<<"删除左节点成功:"<<key;
                }

                if(curkey > curnode->parent->key){
                    curnode->parent->right = curnode->left;
                    curnode->left->parent = curnode->parent;
                    qDebug()<<"删除右节点成功:"<<key;
                }
                delete curnode;
                curnode = nullptr;
                break;
            }else if(curnode->left == nullptr && curnode->right != nullptr)
            {//有一个右子节点，左节点空

                if(curkey < curnode->parent->key){
                    curnode->parent->left = curnode->right;
                    curnode->right->parent = curnode->parent;
                    qDebug()<<"删除左节点成功:"<<key;
                }

                if(curkey > curnode->parent->key){
                    curnode->parent->right = curnode->right;
                    curnode->right->parent = curnode->parent;
                    qDebug()<<"删除右节点成功:"<<key;
                }
                delete curnode;
                curnode = nullptr;
                break;

            }else if(curnode->left != nullptr && curnode->right != nullptr){
                /*
                 * 有2个子节点时，
                 * 1、需要先找到其后继结点（右子树中最小的子节点），找前驱节点（左子树中最大的子节点）也是可以的？
                 * 2、将后继节点与当前节点替换， 然后删除当前节点
                */
                Node<string> *successorNode  = curnode->right;


                while (successorNode->left != nullptr ) {

                    successorNode = successorNode->left;
                }


                qDebug()<<"后继节点:"<<successorNode->key;



                //只交换节点的key和值
                Node<string> tmpnode(*successorNode);

                curnode->key = successorNode->key;
                curnode->t = successorNode->t;

                successorNode->key = tmpnode.key;
                successorNode->t = tmpnode.t;




                //后继节点是当前节点的右节点
                if(curnode->right->key == successorNode->key){


                    if(successorNode->right == nullptr){
                        curnode->right = nullptr;
                        delete successorNode;
                    }else{

                        curnode->right = successorNode->right;
                        successorNode->right->parent = curnode;

                        delete successorNode;
                    }

                }else{

                    if(successorNode->right == nullptr){

                        successorNode->parent->left = nullptr;
                        delete successorNode;
                    }else{

                        successorNode->parent->left = successorNode->right;

                        successorNode->right->parent = successorNode->parent;

                        delete successorNode;
                    }

                }



                break;


            }
        }
    }
}

bool BinarySearchTree::update(int key){



}
