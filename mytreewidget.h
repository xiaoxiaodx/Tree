#ifndef MYTREEWIDGET_H
#define MYTREEWIDGET_H

#include <QGraphicsWidget>

#include "minheap.h"
#include <QThread>

class TimerNode{

public:
    int x,y,offset;
    qint64 expire;
    void debug(){

        qDebug()<<"expire:"<<expire;
    }
};
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

    void signal_dowork();
public slots:
    void slot_addnode(int key);
    void slot_deletenode(int key);
    void slot_timeout();

private:

     MinHeap<TimerNode*> minheap;


     void drawTreeNode(QPainter *pt,Node<TimerNode*> node,int x,int y);


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

    QThread workerThread;
};

#endif // MYTREEWIDGET_H
