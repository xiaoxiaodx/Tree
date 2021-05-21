#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "binarysearchtree.h"
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "mytreewidget.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QMainWindow *parent = nullptr);
    ~MainWindow();


protected:

    void resizeEvent(QResizeEvent *event);


public slots:
       void slot_wheelevent(int delta);

signals:
    void signal_inset(int key);
    void signal_remove(int key);
protected:




private:

    void btnProcess();



    //以下定义的是以像素为单位
    //每层的垂直距离 与 左右子节点与父节点的水平距离
    float vDistance;
    float hDistance;



    float nodeRadius;



    //当前鼠标按下位置'
    bool ispress;
    float premouseposx,premouseposy;


    //根节点位置
    float rootx,rooty;
    //所有绘制的尺寸比例
    float m_scale;



    QGraphicsScene *m_scene;

    QGraphicsView *m_window;
    MyTreeWidget *treewidget;

};
#endif // MAINWINDOW_H
