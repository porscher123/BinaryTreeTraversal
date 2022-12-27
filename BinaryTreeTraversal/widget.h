#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QPainter>
#include <synchapi.h>
#include <QTimerEvent>
#include <QMap>
#include <QPair>
#include <QIcon>
#include <QQueue>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    static const int N = 128;
    int tot = 0;
    void changeTot();
    void changeNode();
    void changeEdge();
    void change();

    // 存图
    QVector<int> edges[N];
    int val[N];
    // 布局
    QGridLayout *mainLayout;
    QVBoxLayout *leftLayout;
    QVBoxLayout *rightLayout;
    QHBoxLayout *rightTopLayout;
    void setWindowBase();
    void setMainLayout();
    void setLeftLayout();
    void setRightTopLayout();
    void setRightLayout();
    void setLayout();

    QString data;
    // 信息输入框
    QTextEdit *inputNode;
    QTextEdit *inputEdges;
    QTextEdit *inputCnt;
    void setInputCnt();
    void setInputEdges();
    void setInputNode();
    void setInput();


    QLabel *labelCnt;
    QLabel *labelEdge;
    QLabel *labelNode;
    void setLabel();

    // 按钮
    QPushButton *btnPreOrder;
    QPushButton *btnInOrder;
    QPushButton *btnPostOrder;
    QPushButton *btnLevelOrder;
    void setButton();


    // 画图
    QWidget *paintArea;
    void paintEvent(QPaintEvent*);
    void drawCircle(QPainter&, int x, int y, int r);
    void drawNum(QPainter&, int x, int y, int num);
    void drawNode(QPainter&, int x, int y, int num, int r);
    void drawTree(QPainter& p, int x ,int y, int num, int r, int depth);


    // 存每个结点应该画在哪里
    QMap<int, QPair<int, int>> map;

    // 读取遍历到的结点的坐标, 应该被染色的结点
    int cx = -1, cy = -1;

    // 遍历
    void preOrder();
    void preOrder(int u);

    void inOrder();
    void inOrder(int u);

    void postOrder();
    void postOrder(int u);

    void levelOrder();

    // 默认第一条边的左端点为根
    int root = 0;
    void getRoot();

    // 遍历序列
    QLabel *labelSeqName;
    QVector<int> seq;
    void drawSeq(QPainter& p);

};
#endif // WIDGET_H
