#include "mydatatable.h"
#include <QHeaderView>
#include <QVBoxLayout>
#include <QtDebug>

MyDataTable::MyDataTable(QWidget *parent) : QWidget(parent)
{
    m_data_view = new QTableView(this);
    m_data_model = new MyDataModel(this);
    m_data_view->setModel(m_data_model);
    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_data_view);
    for (int i = 0; i < 2; ++i) {
        m_data_model->insertRow(i);
        m_data_model->setData(m_data_model->index(i, 0), QString("%1").arg(i), Qt::DisplayRole);
    }
    auto header_view = m_data_view->horizontalHeader();
    header_view->setSectionsMovable(true);
    header_view->setSectionsClickable(true);
    header_view->setStretchLastSection(true);
    m_data_view->setSortingEnabled(true);
}
