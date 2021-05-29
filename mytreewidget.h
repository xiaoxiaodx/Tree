#ifndef MYTREEWIDGET_H
#define MYTREEWIDGET_H

#include <QGraphicsWidget>
#include "rbtree.h"

using namespace std;
class MyTreeWidget : public QGraphicsWidget
{
    Q_OBJECT
public:
    MyTreeWidget();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *,QWidget *) override;


    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void wheelEvent(QGraphicsSceneWheelEvent*event);

signals:
    void signal_wheelevent(int delta);

public slots:
    void slot_addnode(int key);
    void slot_deletenode(int key);


private:

     typedef RBTree<int,string> Tree;
     typedef Tree::Node TreeNode;
     Tree bstree;
     void drawTreeNode(QPainter *pt,TreeNode *node,int level,float x,float y);


    //以下定义的是以像素为单位
    //每层的垂直距离 与 左右子节点与父节点的水平距离
    float vDistance;
    float hDistance;



    float nodeRadius;



    //当前鼠标按下位置'
    bool ispress;
    float premouseposx,premouseposy;

    float m_scale;

    //根节点位置
    float rootx,rooty;
};

#endif // MYTREEWIDGET_H
