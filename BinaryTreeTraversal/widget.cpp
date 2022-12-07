#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{


    this->setWindowBase();
    this->setLabel();
    this->setButton();
    this->setInput();
    this->setLayout();



}

void Widget::setWindowBase() {
    this->setFixedSize(1000, 650);
    this->setWindowIcon(QIcon(":/Icon/Images/tree.png"));
    this->paintArea = new QWidget();
}

// 设置布局
void Widget::setLeftLayout() {
    this->leftLayout = new QVBoxLayout();
    this->leftLayout->addWidget(this->labelCnt);
    this->leftLayout->addWidget(this->inputCnt);

    this->leftLayout->addWidget(this->labelNode);
    this->leftLayout->addWidget(this->inputNode);

    this->leftLayout->addWidget(this->labelEdge);
    this->leftLayout->addWidget(this->inputEdges);

    this->leftLayout->setStretch(0, 1);
    this->leftLayout->setStretch(1, 1);
    this->leftLayout->setStretch(2, 1);
    this->leftLayout->setStretch(3, 10);
    this->leftLayout->setStretch(4, 1);
    this->leftLayout->setStretch(5, 10);
}
void Widget::setRightTopLayout() {
    this->rightTopLayout = new QHBoxLayout();
    this->rightTopLayout->addWidget(this->btnPreOrder);
    this->rightTopLayout->addWidget(this->btnInOrder);
    this->rightTopLayout->addWidget(this->btnPostOrder);
}
void Widget::setRightLayout() {
    this->rightLayout = new QVBoxLayout();
    this->rightLayout->addLayout(this->rightTopLayout);
    this->rightLayout->addWidget(this->paintArea);
    this->rightLayout->setStretch(0, 1);
    this->rightLayout->setStretch(1, 10);
}
void Widget::setMainLayout() {
    this->mainLayout = new QGridLayout(this);
    this->mainLayout->setSpacing(10);
    this->mainLayout->addLayout(this->leftLayout, 0, 0);
    this->mainLayout->addLayout(this->rightLayout, 0, 1);
    this->mainLayout->setColumnStretch(0, 1);
    this->mainLayout->setColumnStretch(1, 8);
}
void Widget::setLayout() {
    this->setLeftLayout();
    this->setRightTopLayout();
    this->setRightLayout();
    this->setMainLayout();
}


void Widget::setLabel() {
    this->labelCnt = new QLabel("Nodes count:");
    this->labelNode = new QLabel("node value:");
    this->labelEdge = new QLabel("edges info:");
}

// 设置信息输入的文本框
void Widget::setInputCnt() {
    this->inputCnt = new QTextEdit();
    connect(this->inputCnt, &QTextEdit::textChanged, this, [=](){
        changeTot();
        this->update();
    });
}
void Widget::setInputNode() {
    this->inputNode = new QTextEdit();
    connect(this->inputNode, &QTextEdit::textChanged, this, [=](){
        this->changeNode();
        this->update();
    });
}
void Widget::setInputEdges() {
    this->inputEdges = new QTextEdit();
    connect(this->inputEdges, &QTextEdit::textChanged, this, [=](){
        QString s = this->inputEdges->toPlainText();
        this->changeEdge();
        this->update();

    });
}
void Widget::setInput() {
    this->setInputEdges();
    this->setInputNode();
    this->setInputCnt();
}


// 信息输入框被修改后,对图做对应的修改
void Widget::changeTot() {
    QString s = this->inputCnt->toPlainText();
    this->tot = s.toInt();
}
void Widget::changeNode() {
    memset(val, 0, sizeof(val));
//    for (int i = 1; i <= N - 1; i++) edges[i].clear();
    QString s = this->inputNode->toPlainText();
    QStringList qsl = s.split("\n");
    int cnt = 0;
    for (auto& x : qsl) {
        int v = x.toInt();
        this->val[++cnt] = v;
    }
}
void Widget::changeEdge() {

    for (int i = 1; i < N - 1; i++) edges[i].clear();
    QString s = this->inputEdges->toPlainText();
    QStringList qsl = s.split("\n");
    for (auto& ss : qsl) {
        int cnt = 0;
        int u = 0, v = 0;
        ss = ss.trimmed();
        if (!ss.count(" ")) continue;
        QStringList qsl2 = ss.split(" ");
        for (auto& x : qsl2) {
            if (++cnt == 1) {
                u = x.toInt();
            } else {
                v = x.toInt();
            }
        }

        this->edges[u].push_back(v);
    }
}
void Widget::change() {
    this->changeTot();
    this->changeNode();
    this->changeEdge();
}

// 设置按钮,路径信号槽
void Widget::setButton() {
    this->btnPreOrder = new QPushButton("Preorder Traversal");
    connect(this->btnPreOrder, &QPushButton::clicked, this, [=](){
        this->preOrder();
    });


    this->btnInOrder = new QPushButton("Inorder Traversal");
    connect(this->btnInOrder, &QPushButton::clicked, this, [=](){
        this->inOrder();
    });


    this->btnPostOrder = new QPushButton("Postorder Traversal");
    connect(this->btnPostOrder, &QPushButton::clicked, this, [=](){
        this->postOrder();
    });

}


// 绘图
void Widget::drawCircle(QPainter& p, int x, int y, int r) {
//    qDebug() << "x=" << x << ", cx=" << cx <<", y=" << y << ", cy="<<cy;
    if (x == cx && y == cy) p.setBrush(Qt::green);
    else p.setBrush(Qt::transparent);
    p.drawEllipse(x, y, r, r);
}
void Widget::drawNum(QPainter& p, int x ,int y, int num) {
    p.drawText(x + 15, y + 25, QString::number(num));
}
void Widget::drawNode(QPainter& p, int x, int y, int num, int r) {
    this->drawCircle(p, x ,y, r);
    this->drawNum(p, x, y, num);
}
void Widget::drawTree(QPainter& p, int x ,int y, int u, int r, int depth) {
//    qDebug() <<"*********depth***********" << depth;
//    qDebug() << "u = " << u;
    this->drawNode(p, x, y, val[u], r);
    map[u] = {x, y};
    int left = 0, right = 0;
    if (edges[u].size() >= 1) left = edges[u][0];
    if (edges[u].size() >= 2) right = edges[u][1];
//    qDebug() << "left = " << left << ", right = " << right;

    int deltaX = 140, deltaY = 80;
    deltaX -= depth  * 30;
    deltaY += depth * 8;
    int x1 = x - deltaX, y1 = y + deltaY;
    int x2 = x + deltaX, y2 = y + deltaY;
    if (x1 <= 50 || x2 >= 950) return ;
    if (y1 >= 600) return ;

//    qDebug() << "666";
    if (left != 0) {
        p.drawLine(x + 5, y + r - 5, x1 + r - 5, y1 + 5);
        drawTree(p, x1, y1, left, r, depth + 1);

    }
    if (right != 0) {
        p.drawLine(x + r - 5, y + r - 5, x2 + 5, y2 + 5);
        drawTree(p, x2, y2, right, r, depth + 1);
    }


}


// 遍历
void Widget::preOrder() {
    this->preOrder(root);
    cx = -1, cy = -1;
    this->repaint();
}
void Widget::preOrder(int u) {
    int x = map[u].first, y = map[u].second;
    cx = x, cy = y;
//    qDebug() << cx <<" "<< cy;
    // ❗❗❗❗❗❗❗❗❗❗❗❗❗❗❗❗❗❗❗❗❗❗❗❗❗❗❗❗❗❗
    this->repaint();
    Sleep(1000);

    int left = 0, right = 0;
    if (edges[u].size() >= 1) left = edges[u][0];
    if (edges[u].size() >= 2) right = edges[u][1];
    if (left != 0) preOrder(left);
    if (right != 0) preOrder(right);
}

void Widget::inOrder() {
    this->inOrder(root);
    cx = -1, cy = -1;
    this->repaint();
}
void Widget::inOrder(int u) {
    if (u == 0) return;
    int left = 0, right = 0;
    if (edges[u].size() >= 1) left = edges[u][0];
    if (edges[u].size() >= 2) right = edges[u][1];
    inOrder(left);


    int x = map[u].first, y = map[u].second;
    cx = x, cy = y;
    this->repaint();
    Sleep(1000);




    inOrder(right);
}

void Widget::postOrder() {
    this->postOrder(root);
    cx = -1, cy = -1;
    this->repaint();
}
void Widget::postOrder(int u) {
    if (u == 0) return;
    int left = 0, right = 0;
    if (edges[u].size() >= 1) left = edges[u][0];
    if (edges[u].size() >= 2) right = edges[u][1];



    postOrder(left);

    postOrder(right);

    int x = map[u].first, y = map[u].second;
    cx = x, cy = y;
    this->repaint();
    Sleep(1000);
}

void Widget::getRoot() {
    QString s = this->inputEdges->toPlainText();
    QStringList qsl = s.split("\n");
    QString ss = qsl.first();
    qsl = ss.split(" ");
    s = qsl.first();
    this->root = s.toInt();
}

void Widget::paintEvent(QPaintEvent*) {
    QPen pen;
    pen.setWidth(3);
    pen.setStyle(Qt::SolidLine);

    QPainter p(this);
    p.setPen(pen);

    int x0 = 520, y0 = 50;
    int r = 40;


    this->getRoot();
    if (this->edges[root].size() >= 1) drawTree(p, x0, y0, root, r, 0);
}
Widget::~Widget()
{
}

