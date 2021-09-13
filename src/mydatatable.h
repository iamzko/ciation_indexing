#ifndef MYDATATABLE_H
#define MYDATATABLE_H

#include "mydatamodel.h"
#include "myglobal.h"
#include <QTableView>
#include <QWidget>

class MyDataTable : public QWidget
{
    Q_OBJECT
public:
    explicit MyDataTable(QWidget *parent = nullptr);
    bool set_cur_data(QMap<QString, QMap<QString, QVariant>>& data);
    bool insert_one_line(const QMap<QString, QVariant>& line_data, int row_location);
    QStringList get_table_headers();

private:
    void set_one_line_data(int line, const QMap<QString, QVariant>& line_data);
    void init_signals_and_slots();
private slots:
    void on_tableview_clicked(const QModelIndex& index);
    void on_tableview_double_clicked(const QModelIndex& index);

signals:
    void current_clicked_index(QString origin_ciation);
    void current_double_clicked_index(task_part_info task_info);

private:
    QTableView* m_data_view;
    MyDataModel* m_data_model;
    QMap<QString, QMap<QString, QVariant>> m_cur_data;
};

#endif // MYDATATABLE_H
