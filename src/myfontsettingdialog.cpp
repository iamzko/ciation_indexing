#include "myfontsettingdialog.h"
#include "ui_myfontsettingdialog.h"
#include <QColorDialog>
#include <QFontDialog>
#include <QtDebug>

MyFontSettingDialog* MyFontSettingDialog::m_dialog = nullptr;

MyFontSettingDialog::MyFontSettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyFontSettingDialog)
{
    setWindowTitle(QString::fromUtf8(u8"字体颜色设置"));
    ui->setupUi(this);
    auto list = ui->listWidget_set_item;
    list->addItem(QString::fromUtf8(u8"引文编号文本"));
    list->addItem(QString::fromUtf8(u8"引文文本"));
    list->addItem(QString::fromUtf8(u8"标记符号文本"));
    list->addItem(QString::fromUtf8(u8"引文编辑框"));
    list->addItem(QString::fromUtf8(u8"引文编号框"));
    list->addItem(QString::fromUtf8(u8"引文预览文本"));
    list->addItem(QString::fromUtf8(u8"引文预览框"));
    list->setMaximumWidth(200);
    connect(list, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(on_listwidget_itemClicked(QListWidgetItem*)));
    init_setting_contents();
}

MyFontSettingDialog* MyFontSettingDialog::get_dialog(QWidget* parent)
{
    if (m_dialog == nullptr) {
        m_dialog = new MyFontSettingDialog(parent);
    } else {
        m_dialog->setParent(parent);
    }
    return m_dialog;
}

MyFontSettingDialog::~MyFontSettingDialog()
{
    delete ui;
}

QMap<MyFontSettingDialog::SETTING_TYPE, SettingContent> MyFontSettingDialog::current_setting() const
{
    return m_setting_contents;
}

void MyFontSettingDialog::init_setting_contents()
{
    //TODO : 从DB中读取配置项，DB文件不存在则使用默认配置，
    for (int i = 0; i < ui->listWidget_set_item->count(); ++i) {
        SettingContent temp;
        switch (static_cast<SETTING_TYPE>(i)) {
        case int(CIATION_CODE_TEXT):
            temp.back = QColor(255, 255, 255);
            temp.front = QColor(0, 0, 0);
            temp.font = font();
            break;
        case int(CIATION_CODE_BOX):
            temp.back = QColor(255, 255, 255);
            break;
        case int(INDEXING_SYMBOL):
            temp.back = QColor(255, 255, 255);
            temp.front = QColor(0, 0, 0);
            temp.font = font();
            break;
        case int(CIATION_BOX):
            temp.back = QColor(255, 255, 255);
            break;
        case int(CIATION_TEXT):
            temp.back = QColor(255, 255, 255);
            temp.front = QColor(0, 0, 0);
            temp.font = font();
            break;
        case int(CIATION_PREVIEW_TEXT):
            temp.back = QColor(255, 255, 255);
            temp.front = QColor(0, 0, 0);
            temp.font = font();
            break;
        case int(CIATION_PREVIEW_BOX):
            temp.back = QColor(255, 255, 255);
            break;
        }
        m_setting_contents.insert(static_cast<SETTING_TYPE>(i), temp);
    }
    ui->listWidget_set_item->setCurrentRow(0);
    on_listwidget_itemClicked(nullptr);
}

void MyFontSettingDialog::on_pushButton_front_color_clicked()
{
    QColorDialog dialog(this);
    auto ret = dialog.exec();
    if (ret == QDialog::Accepted) {
        qDebug() << dialog.currentColor();
        auto color = dialog.currentColor();
        ui->pushButton_front_color->setStyleSheet(QString::fromUtf8(u8"background-color: rgb(%1,%2,%3);").arg(color.red()).arg(color.green()).arg(color.blue()));
        switch (ui->listWidget_set_item->currentIndex().row()) {
        case int(CIATION_CODE_TEXT):
            m_setting_contents[CIATION_CODE_TEXT].front = color;
            break;
        case int(CIATION_CODE_BOX):
            break;
        case int(INDEXING_SYMBOL):
            m_setting_contents[INDEXING_SYMBOL].front = color;
            break;
        case int(CIATION_BOX):
            break;
        case int(CIATION_TEXT):
            m_setting_contents[CIATION_TEXT].front = color;
            break;
        case int(CIATION_PREVIEW_TEXT):
            m_setting_contents[CIATION_PREVIEW_TEXT].front = color;
            break;
        case int(CIATION_PREVIEW_BOX):
            break;
        }
    }
}

void MyFontSettingDialog::on_pushButton_back_color_clicked()
{
    QColorDialog dialog(this);
    auto ret = dialog.exec();
    if (ret == QDialog::Accepted) {
        qDebug() << dialog.currentColor();
        auto color = dialog.currentColor();
        ui->pushButton_back_color->setStyleSheet(QString::fromUtf8(u8"background-color: rgb(%1,%2,%3);").arg(color.red()).arg(color.green()).arg(color.blue()));
        switch (ui->listWidget_set_item->currentIndex().row()) {
        case int(CIATION_CODE_TEXT):
            m_setting_contents[CIATION_CODE_TEXT].back = color;
            break;
        case int(CIATION_CODE_BOX):
            m_setting_contents[CIATION_CODE_BOX].back = color;
            break;
        case int(INDEXING_SYMBOL):
            m_setting_contents[INDEXING_SYMBOL].back = color;
            break;
        case int(CIATION_BOX):
            m_setting_contents[CIATION_BOX].back = color;
            break;
        case int(CIATION_TEXT):
            m_setting_contents[CIATION_TEXT].back = color;
            break;
        case int(CIATION_PREVIEW_TEXT):
            m_setting_contents[CIATION_PREVIEW_TEXT].back = color;
            break;
        case int(CIATION_PREVIEW_BOX):
            m_setting_contents[CIATION_PREVIEW_BOX].back = color;
            break;
        }
    }
}

void MyFontSettingDialog::on_pushButton_font_set_clicked()
{
    bool ok;
    auto font = QFontDialog::getFont(&ok, this);
    if (ok) {
        qDebug() << font;
        switch (ui->listWidget_set_item->currentIndex().row()) {
        case int(CIATION_CODE_TEXT):
            m_setting_contents[CIATION_CODE_TEXT].font = font;
            break;
        case int(CIATION_CODE_BOX):
            break;
        case int(INDEXING_SYMBOL):
            m_setting_contents[INDEXING_SYMBOL].font = font;
            break;
        case int(CIATION_BOX):
            break;
        case int(CIATION_TEXT):
            m_setting_contents[CIATION_TEXT].font = font;
            break;
        case int(CIATION_PREVIEW_TEXT):
            m_setting_contents[CIATION_PREVIEW_TEXT].font = font;
            break;
        case int(CIATION_PREVIEW_BOX):
            break;
        }
    }
}

void MyFontSettingDialog::on_listwidget_itemClicked(QListWidgetItem* item)
{
    qDebug() << ui->listWidget_set_item->currentIndex().row();
    switch (ui->listWidget_set_item->currentIndex().row()) {
    case int(CIATION_CODE_TEXT): {
        auto front_color = m_setting_contents.value(CIATION_CODE_TEXT).front;
        auto back_color = m_setting_contents.value(CIATION_CODE_TEXT).back;
        ui->label_front_color->show();
        ui->pushButton_front_color->show();
        ui->pushButton_front_color->setStyleSheet(QString::fromUtf8(u8"background-color: rgb(%1,%2,%3);").arg(front_color.red()).arg(front_color.green()).arg(front_color.blue()));
        ui->label_back_color->show();
        ui->pushButton_back_color->show();
        ui->pushButton_back_color->setStyleSheet(QString::fromUtf8(u8"background-color: rgb(%1,%2,%3);").arg(back_color.red()).arg(back_color.green()).arg(back_color.blue()));
        ui->pushButton_font_set->show();
    } break;
    case int(CIATION_CODE_BOX): {
        auto back_color = m_setting_contents.value(CIATION_CODE_BOX).back;
        ui->label_front_color->hide();
        ui->pushButton_front_color->hide();
        ui->label_back_color->show();
        ui->pushButton_back_color->show();
        ui->pushButton_back_color->setStyleSheet(QString::fromUtf8(u8"background-color: rgb(%1,%2,%3);").arg(back_color.red()).arg(back_color.green()).arg(back_color.blue()));
        ui->pushButton_font_set->hide();
    } break;
    case int(INDEXING_SYMBOL): {
        auto front_color = m_setting_contents.value(INDEXING_SYMBOL).front;
        auto back_color = m_setting_contents.value(INDEXING_SYMBOL).back;
        ui->label_front_color->show();
        ui->pushButton_front_color->show();
        ui->pushButton_front_color->setStyleSheet(QString::fromUtf8(u8"background-color: rgb(%1,%2,%3);").arg(front_color.red()).arg(front_color.green()).arg(front_color.blue()));
        ui->label_back_color->show();
        ui->pushButton_back_color->show();
        ui->pushButton_back_color->setStyleSheet(QString::fromUtf8(u8"background-color: rgb(%1,%2,%3);").arg(back_color.red()).arg(back_color.green()).arg(back_color.blue()));
        ui->pushButton_font_set->show();
    } break;
    case int(CIATION_BOX): {
        auto back_color = m_setting_contents.value(CIATION_BOX).back;
        ui->label_front_color->hide();
        ui->pushButton_front_color->hide();
        ui->label_back_color->show();
        ui->pushButton_back_color->show();
        ui->pushButton_back_color->setStyleSheet(QString::fromUtf8(u8"background-color: rgb(%1,%2,%3);").arg(back_color.red()).arg(back_color.green()).arg(back_color.blue()));
        ui->pushButton_font_set->hide();
    } break;
    case int(CIATION_TEXT): {
        auto front_color = m_setting_contents.value(CIATION_TEXT).front;
        auto back_color = m_setting_contents.value(CIATION_TEXT).back;
        ui->label_front_color->show();
        ui->pushButton_front_color->show();
        ui->pushButton_front_color->setStyleSheet(QString::fromUtf8(u8"background-color: rgb(%1,%2,%3);").arg(front_color.red()).arg(front_color.green()).arg(front_color.blue()));
        ui->label_back_color->show();
        ui->pushButton_back_color->show();
        ui->pushButton_back_color->setStyleSheet(QString::fromUtf8(u8"background-color: rgb(%1,%2,%3);").arg(back_color.red()).arg(back_color.green()).arg(back_color.blue()));
        ui->pushButton_font_set->show();
    } break;
    case int(CIATION_PREVIEW_TEXT): {
        auto front_color = m_setting_contents.value(CIATION_PREVIEW_TEXT).front;
        auto back_color = m_setting_contents.value(CIATION_PREVIEW_TEXT).back;
        ui->label_front_color->show();
        ui->pushButton_front_color->show();
        ui->pushButton_front_color->setStyleSheet(QString::fromUtf8(u8"background-color: rgb(%1,%2,%3);").arg(front_color.red()).arg(front_color.green()).arg(front_color.blue()));
        ui->label_back_color->show();
        ui->pushButton_back_color->show();
        ui->pushButton_back_color->setStyleSheet(QString::fromUtf8(u8"background-color: rgb(%1,%2,%3);").arg(back_color.red()).arg(back_color.green()).arg(back_color.blue()));
        ui->pushButton_font_set->show();
    } break;
    case int(CIATION_PREVIEW_BOX): {
        auto back_color = m_setting_contents.value(CIATION_PREVIEW_BOX).back;
        ui->label_front_color->hide();
        ui->pushButton_front_color->hide();
        ui->label_back_color->show();
        ui->pushButton_back_color->show();
        ui->pushButton_back_color->setStyleSheet(QString::fromUtf8(u8"background-color: rgb(%1,%2,%3);").arg(back_color.red()).arg(back_color.green()).arg(back_color.blue()));
        ui->pushButton_font_set->hide();
    } break;
    }
}
