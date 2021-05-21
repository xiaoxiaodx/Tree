#include "mytreewidget.h"
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
MyTreeWidget::MyTreeWidget()
{
    nodeRadius = 40;
    vDistance = 120;
    hDistance = 40;

    rootx = 0;
    rooty = 0;

    this->setAcceptedMouseButtons(Qt::LeftButton);
    setFlag(QGraphicsItem::ItemIsSelectable);
}


void MyTreeWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *,QWidget *){


    painter->setRenderHint(QPainter::Antialiasing,true);


    //painter->fillRect(0,0,size().rwidth(),size().rheight(),QBrush(Qt::red));
    if(rootx == 0 && rooty == 0){

        rootx = 150+nodeRadius;
        rooty = nodeRadius;
    }

    drawTreeNode(painter,bstree.root,bstree.treedepth,rootx,rooty);

}


void MyTreeWidget::slot_addnode(int key)
{
    bstree.insert(key);

}
void MyTreeWidget::slot_deletenode(int key)
{
    bstree.remove(key);

}


void MyTreeWidget::drawTreeNode(QPainter *pt,Node<string> *node,int level,float x,float y)
{

    if(node == nullptr)
        return;
    Node<string> *childleft = node->left;
    Node<string> *childright = node->right;

    QRect drawrect(x,y,nodeRadius*2,nodeRadius*2);


    //绘制节点圆形
    pt->save();
    pt->setPen(Qt::NoPen);
    pt->setBrush(QBrush(QColor(200,200,200)));
    pt->drawEllipse(drawrect);
    pt->restore();

    //绘制文字
    pt->save();
    pt->setPen(QColor(0,0,0));
    QFont font = pt->font();
    font.setPixelSize(20);
    QFontMetrics fm(font);
    QString showstr = QString::number(node->key);
    QRect stringRect = fm.boundingRect(showstr);
    int strx = drawrect.x() + drawrect.width()/2 - stringRect.width()/2;
    int stry = drawrect.y() + drawrect.height()/2 - stringRect.height()/2;
    pt->setFont(font);
    pt->drawText(QRect(strx,stry,stringRect.width(),stringRect.height()),0,QString::number(node->key));
    pt->restore();



    int levelv = 1;
    for(int i=0;i<level;i++){
        levelv *=2;
    }

    float childleftX = x - hDistance*levelv;
    float childerightX = x+ hDistance*levelv;
    float childerY = y + vDistance;


    int tmplevel = level - 1;

    if(childleft != nullptr){
        //绘制直线
        pt->drawLine(x+nodeRadius,y+nodeRadius*2,childleftX+nodeRadius,childerY);
        drawTreeNode(pt,childleft,tmplevel,childleftX,childerY);

    }

    if(childright != nullptr){
        //绘制直线
        pt->drawLine(x+nodeRadius,y+nodeRadius*2,childerightX+nodeRadius,childerY);
        drawTreeNode(pt,childright,tmplevel,childerightX,childerY);

    }
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

    //qDebug()<<"mouseMoveEvent   111111111111";

    if(ispress){


        float dx = event->pos().rx() - premouseposx;
        float dy = event->pos().ry() - premouseposy;


       // qDebug()<<"mouseMoveEvent dx:"<<dx<<"   dy:"<<dy;

        premouseposx = event->pos().rx();
        premouseposy = event->pos().ry();

       // qDebug()<<"mouseMoveEvent rootx:"<<rootx<<"   rooty:"<<rooty;

        rootx = (rootx + dx);
        rooty = (rooty + dy);


       // qDebug()<<"mouseMoveEvent rootx:"<<rootx<<"   rooty:"<<rooty;




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

