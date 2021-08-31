#include "indexmainwindow.h"
#include "ui_indexmainwindow.h"
#include <QDebug>
#include <QKeyEvent>
#include <QScopedPointer>
#include <QStandardItemModel>
#include <QTextBrowser>
static const QString WINDOWS_TITLE = QString::fromUtf8(u8"引文人工加标记");

IndexMainWindow::IndexMainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::IndexMainWindow)
    , m_task_module(new MyTaskModule())
    , m_db_module(new MyDataBaseModule())
{
    ui->setupUi(this);
    init_user_interface();
    init_signals_and_slots();
    if (!m_db_module->system_info_db_open(QGuiApplication::applicationDirPath() + "/" + "system_info.db")) {
        show_message(m_db_module->error());
    }
    m_table_job.clear();
    if (!m_db_module->system_info_db_job_table_read(m_table_job)) {
        show_message(m_db_module->error());
    }
    if (!m_db_module->system_info_db_literature_table_read(m_table_literature)) {
        show_message(m_db_module->error());
    }
    if (!m_db_module->system_info_db_location_table_read(m_table_location)) {
        show_message(m_db_module->error());
    }
    if (!m_db_module->system_info_db_publish_table_read(m_table_publish)) {
        show_message(m_db_module->error());
    }
    setWindowTitle(WINDOWS_TITLE);
    on_action_get_new_task_triggered();
}

IndexMainWindow::~IndexMainWindow()
{
    delete ui;
}

bool IndexMainWindow::eventFilter(QObject* target, QEvent* e)
{
    if (e->type() == QEvent::KeyPress) {
        auto key_event = static_cast<QKeyEvent*>(e);
        switch (key_event->key() + key_event->modifiers()) {
        case Qt::Key_V + Qt::ControlModifier:
            return true;
            break;
        case Qt::Key_K + Qt::ControlModifier:
            return true;
            break;
        case Qt::Key_Z + Qt::ControlModifier:
            return true;
            break;
        case Qt::Key_Y + Qt::ControlModifier:
            return true;
            break;
        }
        switch (key_event->key()) {
        case Qt::Key_Enter:
        case Qt::Key_Return:
            break;
        }
        return false;
    }
    return false;
}

void IndexMainWindow::init_user_interface()
{
    //初始化工具栏
    ui->action_indexing->setVisible(false);
    ui->toolBar_combobox_area->hide();
    m_undo_stack = new QUndoStack(this);
    //初始化显示引文个数，任务总数区域
    auto temp_widget = new QWidget(this);
    auto temp_h_layout = new QHBoxLayout(temp_widget);
    temp_h_layout->addWidget(new QLabel(QString::fromUtf8(u8"引文个数："), this));
    temp_h_layout->addSpacing(10);
    m_label_ciation_number = new QLabel(QString::fromUtf8(u8"0"), this);
    temp_h_layout->addWidget(m_label_ciation_number);
    temp_h_layout->addSpacing(20);
    temp_h_layout->addWidget(new QLabel(QString::fromUtf8(u8"待提交/任务总数："), this));
    temp_h_layout->addSpacing(10);
    m_label_task_total_number = new QLabel(QString::fromUtf8(u8"0/0"));
    temp_h_layout->addWidget(m_label_task_total_number);
    temp_h_layout->addStretch();
    temp_h_layout->addWidget(new QLabel(QString::fromUtf8(u8"岗位名称："), this));
    temp_h_layout->addSpacing(10);
    m_label_job_name = new QLabel(QString::fromUtf8(u8"无"), this);
    temp_h_layout->addWidget(m_label_job_name);
    temp_h_layout->addSpacing(20);
    temp_h_layout->addWidget(new QLabel(QString::fromUtf8(u8"任务性质："), this));
    temp_h_layout->addSpacing(10);
    m_label_task_characteristics = new QLabel(QString::fromUtf8(u8"无"), this);
    temp_h_layout->addWidget(m_label_task_characteristics);
    ui->toolBar_label_area->addWidget(temp_widget);
    //初始化查找区域
    m_lineedit_search_input = new QLineEdit(this);
    m_lineedit_search_input->setFixedWidth(100);
    ui->toolBar_search_area->insertWidget(ui->action_search, m_lineedit_search_input);
    //初始化表格视图时的label区域
    temp_widget = new QWidget(this);
    temp_h_layout = new QHBoxLayout(temp_widget);
    temp_h_layout->addWidget(new QLabel(QString::fromUtf8(u8"岗位名称：")));
    temp_h_layout->addSpacing(10);
    m_combobox_job_name = new QComboBox(this);
    m_combobox_job_name->setFixedWidth(100);
    temp_h_layout->addWidget(m_combobox_job_name);
    temp_h_layout->addSpacing(20);
    temp_h_layout->addWidget(new QLabel(QString::fromUtf8(u8"任务性质：")));
    temp_h_layout->addSpacing(10);
    m_combobox_task_characteristics = new QComboBox(this);
    m_combobox_task_characteristics->setFixedWidth(100);
    temp_h_layout->addWidget(m_combobox_task_characteristics);
    ui->toolBar_combobox_area->addWidget(temp_widget);
    //初始化状态栏区域
    ui->statusbar->addPermanentWidget(new QLabel(QString::fromUtf8(u8"引文总数："), this));
    m_label_ciation_total_number = new QLabel(QString::fromUtf8(u8"0"), this);
    ui->statusbar->addPermanentWidget(m_label_ciation_total_number);
    ui->statusbar->addPermanentWidget(new QLabel(QString::fromUtf8(u8"标记总数："), this));
    m_label_indexing_total_number = new QLabel(QString::fromUtf8(u8"0"), this);
    ui->statusbar->addPermanentWidget(m_label_indexing_total_number);
    //主界面区域使用分裂布局，上下分割
    auto spliter = new QSplitter(centralWidget());
    m_stackwidget_area = new QStackedWidget(this);
    m_view_ciation_editor = new MyEditor(this);
    m_stackwidget_area->addWidget(m_view_ciation_editor); //入栈顺序很重要，CUR_WIDGET枚举值与此对应
    m_view_data_table = new MyDataTable(this);
    m_stackwidget_area->addWidget(m_view_data_table);
    m_view_origin_ciation = new QPlainTextEdit(this);
    m_view_origin_ciation->setReadOnly(true);
    m_stackwidget_area->addWidget(m_view_origin_ciation);
    m_stackwidget_area->setCurrentIndex(int(CUR_WIDGET::WIDGET_EDITOR));
    spliter->setOrientation(Qt::Vertical);
    //初始化引文编辑区域
    spliter->addWidget(m_stackwidget_area);
    //初始化原始引文展示区域
    m_plaintextedit_bottom = new QPlainTextEdit(this);
    m_plaintextedit_bottom->setReadOnly(true);
    spliter->addWidget(m_plaintextedit_bottom);
    setCentralWidget(spliter);
}

void IndexMainWindow::init_signals_and_slots()
{
    switch (m_stackwidget_area->currentIndex()) {
    case int(CUR_WIDGET::WIDGET_EDITOR):
        disconnect(m_view_data_table, SIGNAL(current_clicked_index(QString)), this, SLOT(update_bottom_edit_writable(QString)));
        connect(m_view_ciation_editor, SIGNAL(select_edit_changed(QString)), this, SLOT(update_bottom_edit_readonly(QString)));
        break;
    case int(CUR_WIDGET::WIDGET_TABLE):
        qDebug() << "connect writable";
        disconnect(m_view_ciation_editor, SIGNAL(select_edit_changed(QString)), this, SLOT(update_bottom_edit_readonly(QString)));
        connect(m_view_data_table, SIGNAL(current_clicked_index(QString)), this, SLOT(update_bottom_edit_writable(QString)));
        break;
    }
}

void IndexMainWindow::show_message(const QString& msg)
{
    QMessageBox::critical(this, QString::fromUtf8(u8"错误"), msg);
}

void IndexMainWindow::update_window_title(const QString& code)
{
    if (code.isEmpty()) {
        setWindowTitle(WINDOWS_TITLE);
    } else {
        setWindowTitle(QString::fromUtf8(u8"%1 [%2]").arg(WINDOWS_TITLE).arg(code));
    }
}

void IndexMainWindow::update_task_label()
{
    auto temp_data = m_task_module->get_all_task_info();
    auto total_num = temp_data.size();
    qDebug() << total_num;
    int task_finished = 0;
    foreach (auto& task, temp_data) {
        if (task["TaskStatus"].toUInt() == 8) {
            task_finished += 1;
        }
    }
    m_label_task_total_number->setText(QString::fromUtf8(u8"%1/%2").arg(task_finished).arg(total_num));
}

QString IndexMainWindow::get_cur_input_db_path()
{
    return QString::fromUtf8(u8"%1\\%2.db").arg(m_task_module->get_work_path()).arg(m_task_module->get_article_code());
}

void IndexMainWindow::on_action_indexing_triggered()
{
    m_stackwidget_area->setCurrentIndex(int(CUR_WIDGET::WIDGET_EDITOR));
    ui->action_indexing->setVisible(false);
    ui->action_check_local->setVisible(true);
    ui->toolBar_combobox_area->hide();
    m_plaintextedit_bottom->setReadOnly(true);
    init_signals_and_slots();
}

void IndexMainWindow::on_action_check_local_triggered()
{
    m_stackwidget_area->setCurrentIndex(int(CUR_WIDGET::WIDGET_TABLE));
    ui->action_indexing->setVisible(true);
    ui->action_check_local->setVisible(false);
    ui->toolBar_combobox_area->show();
    m_plaintextedit_bottom->setReadOnly(false);
    init_signals_and_slots();
}

void IndexMainWindow::on_action_check_local_with_update_triggered()
{
    m_stackwidget_area->setCurrentIndex(int(CUR_WIDGET::WIDGET_TABLE));
    ui->action_indexing->setVisible(true);
    ui->action_check_local->setVisible(false);
    ui->toolBar_combobox_area->show();
    m_plaintextedit_bottom->setReadOnly(false);
    init_signals_and_slots();
    //刷新数据库流程
}

void IndexMainWindow::on_action_show_bottom_view_triggered()
{
    if (!m_db_module->out_db_open(QString::fromUtf8(u8"D:\\work\\613304\\20210812\\132732200025725789\\13\\3370\\20232\\upload\\20232.db"))) {
        show_message(m_db_module->error());
        return;
    }
    QMap<QString, QMap<QString, QVariant>> temp_map;
    if (!m_db_module->out_db_table_result_read(m_table_result)) {
        show_message(m_db_module->error());
        return;
    }
    m_view_data_table->set_cur_data(m_table_result);
    m_db_module->out_db_close();
}

void IndexMainWindow::on_action_show_original_data_triggered()
{
    m_stackwidget_area->setCurrentIndex(int(CUR_WIDGET::WIDGET_ORIGIN));
}

void IndexMainWindow::on_action_get_new_task_triggered()
{
    if (!m_task_module->load_new_task()) {
        show_message(m_task_module->get_error_string());
        return;
    }
    update_window_title(m_task_module->get_code());
    m_label_job_name->setText(m_task_module->get_post_name());
    m_label_task_characteristics->setText(m_task_module->get_task_kind());
    m_task_module->refresh_all_task_info();
    update_task_label();

    qDebug() << get_cur_input_db_path();
    if (!m_db_module->input_db_open(get_cur_input_db_path())) {
        show_message(m_db_module->error());
        return;
    }
    //TODO 往出拿数据
    if (!m_db_module->input_db_table_view_cn_read(m_table_view)) {
        show_message(m_db_module->error());
        return;
    }
    m_view_ciation_editor->set_contents(m_table_view, QString::fromUtf8(u8"引文编号"), QString::fromUtf8(u8"标记引文"));
}

void IndexMainWindow::on_action_finish_local_triggered()
{
    QMap<QString, QVariant> temp;
    m_view_data_table->insert_one_line(temp, 25);
}

void IndexMainWindow::update_bottom_edit_readonly(QString code)
{
    qDebug() << "update bottom edit!";
    foreach (auto& line, m_table_view) {
        if (line.value(QString::fromUtf8(u8"引文编号")) == code) {
            m_plaintextedit_bottom->setPlainText(line.value(QString::fromUtf8(u8"原始引文")).toString());
            break;
        }
    }
}

void IndexMainWindow::update_bottom_edit_writable(QString origin_ciation)
{
    qDebug() << "origin:" << origin_ciation;
    m_plaintextedit_bottom->setPlainText(origin_ciation);
}

void IndexMainWindow::on_action_auto_indexing_triggered()
{
    QMap<QString, QVariant> temp;
    m_view_data_table->insert_one_line(temp, 2);
}
