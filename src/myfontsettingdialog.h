#ifndef MYFONTSETTINGDIALOG_H
#define MYFONTSETTINGDIALOG_H

#include <QColor>
#include <QDialog>
#include <QFont>
#include <QListWidgetItem>
#include <QMap>

namespace Ui {
class MyFontSettingDialog;
}
struct SettingContent {
    QColor front;
    QColor back;
    QFont font;
};

class MyFontSettingDialog : public QDialog
{
    Q_OBJECT

public:
    enum SETTING_TYPE {
        CIATION_CODE_TEXT = 0,
        CIATION_TEXT,
        INDEXING_SYMBOL,
        CIATION_BOX,
        CIATION_CODE_BOX,
        CIATION_PREVIEW_TEXT,
        CIATION_PREVIEW_BOX,
    };
    static MyFontSettingDialog* get_dialog(QWidget* parent = nullptr);
    MyFontSettingDialog(MyFontSettingDialog&) = delete;
    MyFontSettingDialog& operator=(const MyFontSettingDialog&) = delete;

    ~MyFontSettingDialog();
    QMap<SETTING_TYPE, SettingContent> current_setting() const;

private:
    explicit MyFontSettingDialog(QWidget* parent = nullptr);
    void init_setting_contents();

private slots:
    void on_pushButton_front_color_clicked();

    void on_pushButton_back_color_clicked();

    void on_pushButton_font_set_clicked();

    void on_listwidget_itemClicked(QListWidgetItem* item);

private:
    static MyFontSettingDialog* m_dialog;
    Ui::MyFontSettingDialog* ui;
    QMap<SETTING_TYPE, SettingContent> m_setting_contents;
};

#endif // MYFONTSETTINGDIALOG_H
