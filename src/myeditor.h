#ifndef MYEDITOR_H
#define MYEDITOR_H

#include "myciationeditor.h"
#include "myhighlighter.h"
#include <QGridLayout>
#include <QLabel>
#include <QList>
#include <QMouseEvent>
#include <QPair>
#include <QPlainTextEdit>
#include <QScrollArea>
#include <QScrollBar>
#include <QWidget>

class MyEditor : public QWidget {
    Q_OBJECT
public:
    enum LINE_STATE {
        NEW, //新增
        MODIFIED, //修改
        ORIGINAL, //原始
        DELETED, //删除
    };
    struct LineContent {
        QString line_sign; //行唯一标记
        QString ciation_code; //引文编码
        QString ciation_content; //引文内容
        LINE_STATE ciation_state; //引文状态
        QMap<QString, QVector<int>> symbol_info; //标记的位置信息，key为标记字符串，vector中为该标记在串中的位置信息，同一符号可能有多个位置
    };
    explicit MyEditor(QWidget* parent = nullptr);
    bool add_one_line(QString& label_text, QString& content, int location);
    bool set_contents(QMap<QString, QMap<QString, QVariant>>& data, QString label_key, QString edit_text_key);
    bool get_contents(QMap<QString, QString>& content);
    bool set_one_line_focus(QString& ciation_code);
    void show_one_line(int line_number);
    QList<QPair<int, QString>> check_contents(bool is_eng);
    QMap<QString, QString> get_all_contents();

    void clear_widgets();
    void clear_lines();

    void setCur_newid(int newCur_newid);

    int cur_newid() const;

    void setCur_new_ciation_id(int newCur_new_ciation_id);

    void set_label_text_style(QFont font, QColor front);
    void set_label_color(QColor back);

    void set_edit_text_style(QFont font, QColor front, QColor back);
    void set_edit_color(QColor back);

    void set_edit_indexing_symbol_text_style(QFont font, QColor front, QColor back);

protected:
    void resizeEvent(QResizeEvent* e) override;
    void mousePressEvent(QMouseEvent* e) override;
    void keyPressEvent(QKeyEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    bool eventFilter(QObject* watched, QEvent* e) override;

private:
private slots:
    void update_edit_height();
    void update_all_widgets();
    void update_content();
    void get_cur_edit_name();
    void get_cur_scroll_position(int value);

signals:
    void all_widgets_changed();
    void select_edit_changed(QString edit_name);

private:
    QScrollArea* m_scroll_area;
    QGridLayout* m_layout_data_area;
    //行标记号格式为引文编号_UUID，label的text，edit的text
    QList<QPair<QString, QPair<QString, QString>>> m_edit_contents;
    int m_have_init_index;
    int m_widget_show_line;
    QList<QPair<QLabel*, MyCiationEditor*>> m_list_widgets;
    QScrollBar* m_scroll_bar_right;
    QList<MyHighlighter*> m_highlighter;
    int m_cur_new_ciation_id;
};

#endif // MYEDITOR_H
