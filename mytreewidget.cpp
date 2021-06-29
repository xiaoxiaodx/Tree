#include "mytreewidget.h"
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include "math.h"

#include "worker.h"

#include <QDateTime>
MyTreeWidget::MyTreeWidget()
{
    nodeRadius = 30;
    vDistance = 60;
    hDistance = 40;

    rootx = 0;
    rooty = 0;

    this->setAcceptedMouseButtons(Qt::LeftButton);
    setFlag(QGraphicsItem::ItemIsSelectable);


    Worker *work = new Worker;

    work->moveToThread(&workerThread);

    connect(this,&MyTreeWidget::signal_dowork,work,&Worker::slot_dowork);
    connect(&workerThread,&QThread::finished,work,&Worker::deleteLater);
    connect(work,&Worker::signal_timeout,this,&MyTreeWidget::slot_timeout,Qt::QueuedConnection);

    workerThread.start();
    emit signal_dowork();
}

void MyTreeWidget::slot_timeout(){



    Node<TimerNode*>* node = minheap.getMinNode();
    if(node != nullptr){

        TimerNode *tn = node->t;

        if(tn != nullptr){

            qint64 time = QDateTime::currentMSecsSinceEpoch();
            if(time >= tn->expire){
                qDebug()<<"time:"<<time<<",tn->expire:"<<tn->expire;
                tn->debug();
                minheap.removeNode(tn->expire);
                update();
            }

        }
    }
}

void MyTreeWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *,QWidget *){

    painter->setRenderHint(QPainter::Antialiasing,true);

    //painter->fillRect(0,0,size().rwidth(),size().rheight(),QBrush(Qt::red));
    if(rootx == 0 && rooty == 0){
        rootx = 150+nodeRadius;
        rooty = nodeRadius;
    }

    float drawx = rootx;
    float drawy = rooty;
    for(int i=0;i<minheap.heap.size();i++){

        Node<TimerNode*> *node = minheap.heap.at(i);

        if(i == 0){

            node->t->x = rootx;
            node->t->y = rooty;
            node->t->offset = hDistance*pow(2,minheap.treeh-1);

        }else{

            int pindex = (i-1)/2;
            int parentx = minheap.heap.at(pindex)->t->x;
            int parenty = minheap.heap.at(pindex)->t->y;
            node->t->offset = minheap.heap.at(pindex)->t->offset/2;
            if(i%2 != 0)
                node->t->x = parentx -node->t->offset;
            else
                node->t->x = parentx +node->t->offset;

            node->t->y = parenty +vDistance;

        }


       drawTreeNode(painter,*node,drawx,drawy);
       // qDebug()<<i<<","<<sum<<","<<ncount<<","<<remain<<","<<drawx<<","<<drawy;

    }



}


void MyTreeWidget::slot_addnode(int key)
{


    qint64 time = QDateTime::currentMSecsSinceEpoch();




    TimerNode *tn = new TimerNode;
    tn->expire = (qint64)key+time;

    qDebug()<<"slot_addnode:"<<tn->expire;
    minheap.addNode(key+time,tn);
}

void MyTreeWidget::slot_deletenode(int key)
{
    minheap.removeNode(key);
}


void MyTreeWidget::drawTreeNode(QPainter *pt,Node<TimerNode*> node,int x,int y)
{

    QRect drawrect(node.t->x,node.t->y,nodeRadius*2,nodeRadius*2);

    //绘制节点圆形
    pt->save();
    pt->setPen(Qt::NoPen);
    pt->setBrush(QBrush(Qt::gray));
    pt->drawEllipse(drawrect);
    pt->restore();

    //绘制文字
    pt->save();
    pt->setPen(QColor(255,0,0));
    QFont font = pt->font();
    font.setPixelSize(20);
    QFontMetrics fm(font);

    QString showstr = QString::number(node.key);

    //QString showstr = QString::number(node.t->expire);


    QRect stringRect = fm.boundingRect(showstr);
    int strx = drawrect.x() + drawrect.width()/2 - stringRect.width()/2;
    int stry = drawrect.y() + drawrect.height()/2 - stringRect.height()/2;
    pt->setFont(font);
    pt->drawText(QRect(strx,stry,stringRect.width(),stringRect.height()),0,QString::number(node.key));
    pt->restore();






}


void MyTreeWidget::mousePressEvent(QGraphicsSceneMouseEvent *event){

    //qDebug()<<"mousePressEvent  1111111111";
    ispress = true;
    premouseposx = event->pos().rx();
    premouseposy = event->pos().ry();

}


void MyTreeWidget::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    ispress = false;
}
void MyTreeWidget::mouseMoveEvent(QGraphicsSceneMouseEvent *event){


    if(ispress){


        float dx = event->pos().rx() - premouseposx;
        float dy = event->pos().ry() - premouseposy;



        premouseposx = event->pos().rx();
        premouseposy = event->pos().ry();


        rootx = (rootx + dx);
        rooty = (rooty + dy);



        update();
    }

}

void MyTreeWidget::wheelEvent(QGraphicsSceneWheelEvent*event)
{



    setScale(1/m_scale);
    if(event->delta() > 0){
        if(m_scale < 10){
            m_scale += 0.2;
        }else{
            m_scale = 10;
        }
    }else{
        if(m_scale > 0.2){
            m_scale -= 0.2;
        }else{
            m_scale = 0.2;
        }
    }
    setScale(m_scale);

    qDebug()<<" m_scale 1111:"<<m_scale;
}

