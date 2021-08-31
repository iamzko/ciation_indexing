#ifndef MYGRAPHICSEDITOR_H
#define MYGRAPHICSEDITOR_H

#include <QGraphicsView>
#include <QWidget>

class MyGraphicsEditor : public QWidget
{
    Q_OBJECT
public:
    explicit MyGraphicsEditor(QWidget *parent = nullptr);

signals:
private:
    QGraphicsView* m_view;
};

#endif // MYGRAPHICSEDITOR_H
