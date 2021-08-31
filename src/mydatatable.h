#ifndef MYDATATABLE_H
#define MYDATATABLE_H

#include "mydatamodel.h"
#include <QTableView>
#include <QWidget>

class MyDataTable : public QWidget
{
    Q_OBJECT
public:
    explicit MyDataTable(QWidget *parent = nullptr);

signals:
private:
    QTableView* m_data_view;
    MyDataModel* m_data_model;
};

#endif // MYDATATABLE_H
