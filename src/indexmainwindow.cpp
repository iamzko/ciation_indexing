#include "indexmainwindow.h"
#include "myfontsettingdialog.h"
#include "myglobal.h"
#include "ui_indexmainwindow.h"
#include <QDebug>
#include <QFontDialog>
#include <QKeyEvent>
#include <QRegExp>
#include <QScopedPointer>
#include <QStandardItemModel>
#include <QTextBrowser>
#include <QTime>
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
    switch_signals_and_slots();
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
    showMaximized();
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
        default:
            break;
        }
        switch (key_event->key()) {
        default:
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
    spliter->setStretchFactor(0, 8);
    spliter->setStretchFactor(1, 2);
    setCentralWidget(spliter);
}

void IndexMainWindow::init_signals_and_slots()
{
    connect(m_view_data_table, SIGNAL(current_double_clicked_index(task_part_info)), this, SLOT(updata_ciation_editor_content(task_part_info)));
    connect(this, SIGNAL(choose_one_line(QString)), this, SLOT(on_choose_one_line(QString)));
}

void IndexMainWindow::switch_signals_and_slots()
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
    m_task_module->refresh_all_task_info();
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

QString IndexMainWindow::get_cur_output_db_path()
{
    return QString::fromUtf8(u8"%1\\%2.db").arg(m_task_module->get_upload_path()).arg(m_task_module->get_article_code());
}

QMap<QString, QVariant> IndexMainWindow::get_one_ciation_split_result(QString ciation_code, QString ciation_content)
{
    QMap<QString, QVariant> one_line_ciation_info;
    foreach (auto& it, m_table_ciation) {
        if (it.value(MyGlobal::CIATION_CODE).toString() == ciation_code) {
            one_line_ciation_info = it;
            break;
        }
    }
    QMap<QString, QVariant> one_line_view_info;
    foreach (auto& it, m_table_view) {
        if (it.value(MyGlobal::CIATION_CODE).toString() == ciation_code) {
            one_line_view_info = it;
            break;
        }
    }

    QMap<QString, QVariant> one_line;
    if (!m_db_module->out_db_is_open()) {
        show_message(m_db_module->error());
        return one_line;
    }
    one_line = m_db_module->out_db_one_empty_line_create();
    one_line[MyGlobal::TASK_CODE] = QVariant(m_task_module->get_code());
    one_line[MyGlobal::ARTICLE_CODE] = QVariant(m_task_module->get_article_code());
    one_line[MyGlobal::CIATION_CODE] = QVariant(ciation_code);
    one_line[MyGlobal::MARK_ARRIVE_TIME] = QVariant(m_task_module->get_task_come_time());
    //整本编号从引文信息表或文章信息表中获取
    one_line[MyGlobal::TOTAL_BOOK_CODE] = one_line_ciation_info[MyGlobal::TOTAL_BOOK_CODE];
    one_line[MyGlobal::TASK_CHARACTERISTICS] = QVariant(m_task_module->get_task_kind());
    one_line[MyGlobal::CHECK_BATCH] = one_line_view_info[MyGlobal::CHECK_BATCH];

    one_line[MyGlobal::CIATION_INDEXICAL] = ciation_content;
    //拆分标记引文，获取标记项
    //获取文献类型
    QRegularExpression pattern(QString::fromUtf8(u8"%1(.*)%1").arg(MyGlobal::DOUBLE_STAR));
    auto it = pattern.globalMatch(ciation_content);
    while (it.hasNext()) {
        auto match = it.next();
        one_line[MyGlobal::ARTICLE_TYPE] = QVariant(match.captured());
    }
    //想个算法一次遍历把所有标记内容拆出来

    //TODO:继续构造写库的行数据
    //    one_line[]
    //    one_line[MyGlobal::] = QVariant(ciation_code);
}

void IndexMainWindow::on_action_indexing_triggered()
{
    m_stackwidget_area->setCurrentIndex(int(CUR_WIDGET::WIDGET_EDITOR));
    ui->action_indexing->setVisible(false);
    ui->action_check_local->setVisible(true);
    ui->toolBar_combobox_area->hide();
    m_plaintextedit_bottom->setReadOnly(true);
    switch_signals_and_slots();
}

void IndexMainWindow::on_action_check_local_triggered()
{
    m_stackwidget_area->setCurrentIndex(int(CUR_WIDGET::WIDGET_TABLE));
    ui->action_indexing->setVisible(true);
    ui->action_check_local->setVisible(false);
    ui->toolBar_combobox_area->show();
    m_plaintextedit_bottom->setReadOnly(false);
    switch_signals_and_slots();
}

void IndexMainWindow::on_action_check_local_with_update_triggered()
{
    m_stackwidget_area->setCurrentIndex(int(CUR_WIDGET::WIDGET_TABLE));
    ui->action_indexing->setVisible(true);
    ui->action_check_local->setVisible(false);
    ui->toolBar_combobox_area->show();
    m_plaintextedit_bottom->setReadOnly(false);
    switch_signals_and_slots();
    //刷新数据库流程
}

void IndexMainWindow::on_action_show_bottom_view_triggered()
{
    if (m_plaintextedit_bottom->isHidden()) {
        m_plaintextedit_bottom->show();
    } else {
        m_plaintextedit_bottom->hide();
    }
}

void IndexMainWindow::on_action_show_original_data_triggered()
{
    m_stackwidget_area->setCurrentIndex(int(CUR_WIDGET::WIDGET_ORIGIN));
}

void IndexMainWindow::on_action_get_new_task_triggered()
{
#if 0
    if (!m_db_module->out_db_open(QString::fromUtf8(u8"D:\\work\\65651\\20210819\\132738317783906250\\13\\3163\\4309896\\upload\\4309896.db"))) {
        show_message(m_db_module->error());
        return;
    }
    QMap<QString, QMap<QString, QVariant>> temp_map;
    if (!m_db_module->out_db_table_result_read(m_table_result)) {
        show_message(m_db_module->error());
        return;
    }
    for (auto it = m_table_result.begin(); it != m_table_result.end(); ++it) {
        it.value().insert(QString::fromUtf8(u8"岗位名称"), m_task_module->get_post_name());
        it.value().insert(QString::fromUtf8(u8"工作路径"), m_task_module->get_work_path());
        //        it->value(QString::fromUtf8("岗位名称")) = m_task_module->get_post_name();
    }
    qDebug() << *m_table_result.begin();
    m_view_data_table->set_cur_data(m_table_result);
    m_db_module->out_db_close();
#else
    if (!m_task_module->load_new_task()) {
        show_message(m_task_module->get_error_string());
        return;
    }
    update_window_title(m_task_module->get_code());
    m_label_job_name->setText(m_task_module->get_post_name());
    m_label_task_characteristics->setText(m_task_module->get_task_kind());
    update_task_label();

    qDebug() << get_cur_input_db_path();
    if (!m_db_module->input_db_open(get_cur_input_db_path())) {
        show_message(m_db_module->error());
        return;
    }
    //TODO 往出拿数据
    if (m_task_module->get_post_name().contains(u8"中文标记")) {
        if (!m_db_module->input_db_table_view_cn_read(m_table_view)) {
            show_message(m_db_module->error());
            return;
        }
    } else {
        if (!m_db_module->input_db_table_view_en_read(m_table_view)) {
            show_message(m_db_module->error());
            return;
        }
    }
    if (!m_db_module->input_db_table_article_read(m_table_article)) {
        show_message(m_db_module->error());
        return;
    }

    if (!m_db_module->input_db_table_ciation_read(m_table_ciation)) {
        show_message(m_db_module->error());
        return;
    }
    for (int i = 0; i < 0; ++i) {
        m_table_view.remove(QString::number(i));
    }
    QElapsedTimer timer;
    timer.start();

    m_view_ciation_editor->set_contents(m_table_view, QString::fromUtf8(u8"引文编号"), QString::fromUtf8(u8"替换引文"));
    m_view_ciation_editor->setCur_new_ciation_id(9999);
    qDebug() << "time:" << timer.elapsed() / 1000.0 << "s";

    qDebug() << "height:" << m_view_ciation_editor->height();
    qDebug() << "size:" << m_table_view.size();
#endif
}


void IndexMainWindow::update_bottom_edit_readonly(QString code)
{
    //    qDebug() << "update bottom edit!";
    m_plaintextedit_bottom->show();
    foreach (auto& line, m_table_view) {
        if (line.value(QString::fromUtf8(u8"引文编号")) == code) {
            m_plaintextedit_bottom->setPlainText(line.value(QString::fromUtf8(u8"原始引文")).toString());
            break;
        }
    }
}

void IndexMainWindow::update_bottom_edit_writable(QString origin_ciation)
{
    //    qDebug() << "origin:" << origin_ciation;
    m_plaintextedit_bottom->show();
    m_plaintextedit_bottom->setPlainText(origin_ciation);
}

void IndexMainWindow::updata_ciation_editor_content(task_part_info task_info)
{
    m_task_module->refresh_all_task_info();
    auto all_task = m_task_module->get_all_task_info();
    QMap<QString, QString> cur_task;
    foreach (auto& task, all_task) {
        //        qDebug() << task;
        if (task["Code"] == task_info.task_code) {
            cur_task = task;
            break;
        }
    }
    auto db_path = cur_task["WorkPath"] + "\\" + task_info.task_code + ".db";
    //    qDebug() << db_path;
    m_db_module->input_db_open(db_path);
    m_table_view.clear();
    m_db_module->input_db_table_view_cn_read(m_table_view);
    QMap<QString, QMap<QString, QVariant>> temp;
    for (auto it = m_table_view.begin(); it != m_table_view.end(); ++it) {
        if (it.value().value(QString::fromUtf8(u8"文章编号")) == task_info.article_code)
            temp.insert(it.key(), it.value());
    }
    m_view_ciation_editor->clear_lines();

    m_view_ciation_editor->set_contents(temp, QString::fromUtf8(u8"引文编号"), QString::fromUtf8(u8"标记引文"));
    on_action_indexing_triggered();
    emit choose_one_line(task_info.ciation_code);
}

void IndexMainWindow::on_action_auto_indexing_triggered()
{
    QMap<QString, QVariant> temp;
    m_view_data_table->insert_one_line(temp, 2);
    qDebug() << m_view_ciation_editor->height();
}

void IndexMainWindow::on_choose_one_line(QString ciation_code)
{
    qDebug() << "on_choose_one_line";
    m_view_ciation_editor->set_one_line_focus(ciation_code);
}

void IndexMainWindow::on_action_submit_triggered()
{
    qDebug() << "开始提交任务！";
    QMap<QString, QString> processed_content;
    m_view_ciation_editor->get_contents(processed_content);
    auto out_db_pat = get_cur_output_db_path();

    if (!m_db_module->out_db_open(out_db_pat)) {
        show_message(m_db_module->error());
        return;
    }
    QMap<QString, QMap<QString, QVariant>> all_result;
    int i = 0;
    for (auto it_line = processed_content.begin(); it_line != processed_content.end(); ++it_line) {
        //不会/不做/语言转换删除除前面三种的所有标记
        if (it_line->contains(MyGlobal::INDEXING_SYMBOLS_MAP.value(MyGlobal::CAN_NOT))
            || it_line->contains(MyGlobal::INDEXING_SYMBOLS_MAP.value(MyGlobal::DO_NOT))
            || it_line->contains(MyGlobal::INDEXING_SYMBOLS_MAP.value(MyGlobal::LANGUAGE_TRANS))) {
            foreach (auto& symbol, MyGlobal::INDEXING_SYMBOLS_MAP) {
                if (symbol == MyGlobal::INDEXING_SYMBOLS_MAP.value(MyGlobal::CAN_NOT)
                    || symbol == MyGlobal::INDEXING_SYMBOLS_MAP.value(MyGlobal::DO_NOT)
                    || symbol == MyGlobal::INDEXING_SYMBOLS_MAP.value(MyGlobal::LANGUAGE_TRANS)) {
                    continue;
                }
                it_line->replace(symbol, "");
            }
            foreach (auto& type, MyGlobal::ARTICLE_TYPES_MAP) {
                it_line->replace(type, "");
            }
        }
        //小语种清除所有标记，在引文开始加入<<标记，我也不知道为啥
        if (it_line->contains(MyGlobal::ARTICLE_TYPES_MAP.value(MyGlobal::MINOR_LANG))) {
            foreach (auto& symbol, MyGlobal::INDEXING_SYMBOLS_MAP) {
                it_line->replace(symbol, "");
            }
            it_line->insert(0, MyGlobal::INDEXING_SYMBOLS_MAP.value(MyGlobal::OTHER));
        }
        auto one_line_result = get_one_ciation_split_result(processed_content.key(*it_line), *it_line);
        all_result.insert(QString::number(i++), one_line_result);
    }
    m_db_module->out_db_table_result_write(all_result);
    m_db_module->out_db_close();
}

void IndexMainWindow::on_action_set_font_triggered()
{
#if 0
    bool ok;
    QFont temp = QFontDialog::getFont(&ok, this);
    if (ok)
        qDebug() << "push OK";
    else
        qDebug() << "push cancel";
#endif
    auto temp = MyFontSettingDialog::get_dialog(this);
    auto ret = temp->exec();
    if (ret == QDialog::Accepted) {
        qDebug() << "BGEING SETTING!";
        auto settings = temp->current_setting();
        m_view_ciation_editor->set_edit_color(settings.value(MyFontSettingDialog::CIATION_BOX).back);
        m_view_ciation_editor->set_edit_text_style(settings.value(MyFontSettingDialog::CIATION_TEXT).font, settings.value(MyFontSettingDialog::CIATION_TEXT).front, settings.value(MyFontSettingDialog::CIATION_TEXT).back);
        m_view_ciation_editor->set_edit_indexing_symbol_text_style(settings.value(MyFontSettingDialog::INDEXING_SYMBOL).font, settings.value(MyFontSettingDialog::INDEXING_SYMBOL).front, settings.value(MyFontSettingDialog::INDEXING_SYMBOL).back);
        m_view_ciation_editor->set_label_color(settings.value(MyFontSettingDialog::CIATION_CODE_BOX).back);
        m_view_ciation_editor->set_label_text_style(settings.value(MyFontSettingDialog::CIATION_CODE_TEXT).font, settings.value(MyFontSettingDialog::CIATION_CODE_TEXT).front);
        auto color = settings.value(MyFontSettingDialog::CIATION_PREVIEW_TEXT).front;
        //TODO： 下方文字颜色设置还有问题
        m_plaintextedit_bottom->setFont(settings.value(MyFontSettingDialog::CIATION_PREVIEW_TEXT).font);
        m_plaintextedit_bottom->setStyleSheet(QString::fromUtf8(u8"color:rgb(%1,%2,%3);").arg(color.red()).arg(color.green()).arg(color.blue()));
        color = settings.value(MyFontSettingDialog::CIATION_PREVIEW_BOX).back;
        m_plaintextedit_bottom->setStyleSheet(QString::fromUtf8(u8"background:rgb(%1,%2,%3);").arg(color.red()).arg(color.green()).arg(color.blue()));
    }
}
