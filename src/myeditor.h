#ifndef MYEDITOR_H
#define MYEDITOR_H

#include <QGridLayout>
#include <QLabel>
#include <QList>
#include <QMouseEvent>
#include <QPair>
#include <QPlainTextEdit>
#include <QScrollArea>
#include <QWidget>

class MyEditor : public QWidget {
    Q_OBJECT
public:
    explicit MyEditor(QWidget* parent = nullptr);
    bool add_one_line(QString& label_text, QString& content, int location);
    bool set_contents(QMap<QString, QMap<QString, QVariant>>& data, QString label_key, QString edit_text_key);
    void clear_widgets();
    void clear_lines();

protected:
    void resizeEvent(QResizeEvent* e) override;
    void mousePressEvent(QMouseEvent* e) override;

private:
private slots:
    void update_edit_height();
    void update_all_widgets();
    void update_content();
    void get_cur_edit_name();

signals:
    void all_widgets_changed();
    void select_edit_changed(QString edit_name);

private:
    QScrollArea* m_scroll_area;
    QGridLayout* m_layout_data_area;
    QList<QPair<QString, QPair<QString, QString>>> m_edit_contents;
};

#endif // MYEDITOR_H
