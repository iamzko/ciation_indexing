#ifndef INDEXMAINWINDOW_H
#define INDEXMAINWINDOW_H

#include "mydatabasemodule.h"
#include "mydatatable.h"
#include "myeditor.h"
#include "mytaskmodule.h"
#include <QComboBox>
#include <QDockWidget>
#include <QEvent>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QScopedPointer>
#include <QSplitter>
#include <QStackedWidget>
#include <QUndoStack>

QT_BEGIN_NAMESPACE
namespace Ui { class IndexMainWindow; }
QT_END_NAMESPACE

class IndexMainWindow : public QMainWindow
{
    Q_OBJECT
    enum class CUR_WIDGET {
        WIDGET_EDITOR = 0,
        WIDGET_TABLE,
        WIDGET_ORIGIN,
    };

public:
    IndexMainWindow(QWidget *parent = nullptr);
    ~IndexMainWindow();

private slots:
    void on_action_indexing_triggered();

    void on_action_check_local_triggered();

    void on_action_check_local_with_update_triggered();

    void on_action_show_bottom_view_triggered();

    void on_action_show_original_data_triggered();

    void on_action_get_new_task_triggered();

    void on_action_finish_local_triggered();
    void update_bottom_edit_readonly(QString code);
    void update_bottom_edit_writable(QString origin_ciation);

    void on_action_auto_indexing_triggered();

private:
    bool eventFilter(QObject* target, QEvent* e) override;
    void init_user_interface();
    void init_signals_and_slots();
    void show_message(const QString& msg);
    void update_window_title(const QString& code);
    void update_task_label();
    QString get_cur_input_db_path();

private:
    Ui::IndexMainWindow *ui;
    QUndoStack* m_undo_stack;
    //引文个数
    QLabel* m_label_ciation_number;
    //任务总数
    QLabel* m_label_task_total_number;
    //引文总数
    QLabel* m_label_ciation_total_number;
    //标引总数
    QLabel* m_label_indexing_total_number;
    //岗位名称
    QLabel* m_label_job_name;
    //任务性质
    QLabel* m_label_task_characteristics;
    QLineEdit* m_lineedit_search_input;
    QComboBox* m_combobox_job_name;
    QComboBox* m_combobox_task_characteristics;
    MyEditor* m_view_ciation_editor;
    MyDataTable* m_view_data_table;
    QStackedWidget* m_stackwidget_area;
    QPlainTextEdit* m_plaintextedit_bottom;
    QPlainTextEdit* m_view_origin_ciation;
    QScopedPointer<MyTaskModule> m_task_module;
    QScopedPointer<MyDataBaseModule> m_db_module;

    QMap<QString, QMap<QString, QVariant>> m_table_job; //岗位设置表
    QMap<QString, QMap<QString, QVariant>> m_table_location; //出版地表
    QMap<QString, QMap<QString, QVariant>> m_table_publish; //出版社表
    QMap<QString, QMap<QString, QVariant>> m_table_literature; //文献索引表

    QMap<QString, QMap<QString, QVariant>> m_table_detail; //detail表
    QMap<QString, QMap<QString, QVariant>> m_table_view; //数据视图
    QMap<QString, QMap<QString, QVariant>> m_table_article; //文章信息表
    QMap<QString, QMap<QString, QVariant>> m_table_ciation; //引文信息表

    QMap<QString, QMap<QString, QVariant>> m_table_result; //引文标引结果表_RefResult

    //    QDockWidget* m_dockwidget_edit_area;
    //    QDockWidget* m_dockwidget_origin_show_area;
};
#endif // INDEXMAINWINDOW_H
