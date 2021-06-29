#ifndef MINHEAP_H
#define MINHEAP_H

#include <vector>
#include <QDebug>
#include <map>
using namespace std;

template <class T>
class Node{

public:
    int key;
    int idx;
    T t;
};

template <class T>
class MinHeap
{
public:
    MinHeap(){
        heap.clear();
    };

    void addNode(int key,T v)
    {
        Node<T> *node = new Node<T>();
        node->key = key;
        node->t = v;
        node->idx = heap.size();
        heap.push_back(node);



        shiftUp(heap.size()-1);
        maps.insert(make_pair(key,node));

        levelCount++;

        if(levelCount >= levelSumCount){

            levelSumCount *= 2;
            levelCount = 0;
            treeh++;
        }

    }
    void removeNode(int key){

        if(maps.find(key) == maps.end())
            return;

        Node<T> *node = maps.at(key);
        int index = node->idx;
        int lastone = heap.size()-1;

        if(index != lastone){
            swap(heap[index],heap[lastone]);
            heap[index]->idx = index;
            if(!shiftDown(index))
                shiftUp(index);
        }

        heap.pop_back();
        maps.erase(key);



        levelCount--;

        if(levelCount <= 0){

            levelSumCount /= 2;
            levelCount = levelSumCount;
            treeh--;
        }

    }

    bool shiftDown(int index)
    {
        int lengh = heap.size();
        int curindex = index;
        while (true) {
            //如果是最后一个，不进行下沉操作，因为要删除
            if(curindex == lengh-1)
                break;

            int childleft_index = curindex*2+1;
            int childright_index = curindex*2+2;
            int childmin_index = 0;


            if(childleft_index >= lengh)
                break;
            if(childright_index >= lengh)
                childmin_index = childleft_index;
            else{

                if(heap.at(childleft_index)->key < heap.at(childright_index)->key)
                    childmin_index = childleft_index;
                else
                    childmin_index = childright_index;

            }

            //最后一个节点需要删除
            if(childmin_index == lengh - 1)
                break;

            swap(heap.at(curindex),heap.at(childmin_index));
            heap.at(curindex)->idx = curindex;
            heap.at(childmin_index)->idx = childmin_index;
            curindex = childmin_index;
        }

        return curindex>index;
    }

    void shiftUp(int index){

        int curindex = index;
        while (true) {

            int parentindex = (curindex-1)/2;
            Node<T> *node = heap.at(curindex);
            Node<T> *pnode = heap.at(parentindex);

            if(node->key < pnode->key){

                swap(heap[parentindex],heap[curindex]);

                heap[curindex]->idx = curindex;
                heap[parentindex]->idx = parentindex;
                curindex = parentindex;

            }else
                break;


        }

    }
    Node<T> *getMinNode(){
        if(heap.size() > 0)
            return heap.at(0);
        return nullptr;
    }

    vector<Node<T> *> heap;
    map<int,Node<T>*> maps;
    int treeh =1;
    int levelCount = 0;
    int levelSumCount = 1;
private:

};

#endif // MINHEAP_H
