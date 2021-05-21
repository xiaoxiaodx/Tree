#include "mainwindow.h"
#include <QPainter>
#include <QPushButton>
#include <QtGlobal>
#include <QTime>
#include <QRandomGenerator>
#include <QFontMetrics>
#include <QTextEdit>
#include <QtMath>
#include <QDebug>

MainWindow::MainWindow(QMainWindow *parent)
    : QMainWindow(parent)
{

    ispress = false;
    nodeRadius = 40;
    vDistance = 120;
    hDistance = 40;

    rootx = 0;
    rooty = 0;







    m_scene=new QGraphicsScene;


    m_window = new QGraphicsView(this);
    m_window->setFrameStyle(0);
    m_window->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    m_window->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_window->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    treewidget = new MyTreeWidget;
    treewidget->setGeometry(0,0,800,600);

    m_scene->addItem(treewidget);
    this->setCentralWidget(m_window);

    m_window->setScene(m_scene);

    connect(treewidget,&MyTreeWidget::signal_wheelevent,this,&MainWindow::slot_wheelevent);
    btnProcess();
}

void MainWindow::btnProcess(){


    int btn_w = 80;
    int btn_h = 30;
    int w = this->width();
    int h = this->height();

    int btnindex = 0;

    QTextEdit *editkey = new QTextEdit(this);
    editkey->setGeometry((10+btn_w)*(btnindex++),10,btn_w,btn_h);

    QPushButton *btn_addnode = new QPushButton("添加节点",this);
    btn_addnode->setGeometry((10+btn_w)*(btnindex++),10,btn_w,btn_h);
    connect(btn_addnode,&QPushButton::clicked,this,[=] ()  {




        unsigned int a = QRandomGenerator::global()->bounded(10242);

        bool isok = false;
        int n = editkey->toPlainText().toInt(&isok);
        if(isok){
             emit signal_inset(n);
        }else
            emit signal_inset(a);

        m_window->viewport()->update();


    });


    int index11 = 0;
    QTextEdit *editkey1 = new QTextEdit(this);
    editkey1->setGeometry((10+btn_w)*(index11++),40,btn_w,btn_h);
    //删除节点
    QPushButton *btn_deletenode = new QPushButton("删除节点",this);
    btn_deletenode->setGeometry((10+btn_w)*(index11++),40,btn_w,btn_h);
    connect(btn_deletenode,&QPushButton::clicked,this,[=] ()  {


        int key = editkey1->toPlainText().toInt();


        emit signal_remove(key);
        m_window->viewport()->update();
    });


    connect(this,&MainWindow::signal_inset,treewidget,&MyTreeWidget::slot_addnode);
    connect(this,&MainWindow::signal_remove,treewidget,&MyTreeWidget::slot_deletenode);
}


void MainWindow::resizeEvent(QResizeEvent *event)
{


   // qDebug()<<"resizeEvent:"<<event->size();

    //qDebug()<<"m_window size:"<<m_window->size();

    treewidget->resize(event->size());

    m_scene->setSceneRect(0,0,event->size().width(),event->size().height());
    //qDebug()<<"treewidget resize:"<<treewidget->size();
}
void MainWindow::slot_wheelevent(int delta)
{



    //    qDebug()<<"delta:"<<delta;
    //    if(delta > 0){
    //        m_scale = 1.2;
    //    }else{
    //        m_scale = 0.833333;
    //    }


    //    qDebug()<<"scale:"<<m_scale;
    //    m_window->scale(m_scale,m_scale);
    //    m_window->viewport()->update();

}
MainWindow::~MainWindow()
{
}
