#include "mygraphicseditor.h"
#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QHBoxLayout>

MyGraphicsEditor::MyGraphicsEditor(QWidget *parent) : QWidget(parent)
{
    m_view = new QGraphicsView(this);
    auto layout = new QHBoxLayout(this);
    layout->addWidget(m_view);
    auto scene = new QGraphicsScene(m_view);
    scene->setSceneRect(-500, -500, 1000, 1000);
    for (int i = 0; i < 1000; ++i) {
        auto item = new QGraphicsSimpleTextItem(QString::number(i));
        item->setPos(-500, -500 + i * 10);
        item->setFlag(QGraphicsItem::ItemIsMovable);
        scene->addItem(item);
    }
    m_view->setScene(scene);
    m_view->centerOn(0, 0);
    m_view->show();
}
