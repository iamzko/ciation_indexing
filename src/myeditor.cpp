#include "myeditor.h"
#include <QHBoxLayout>
#include <QLineEdit>
#include <QScrollBar>
#include <QSplitter>
#include <QStandardItemModel>
#include <QTextEdit>
#include <QUuid>
#include <QVBoxLayout>
#include <QtDebug>

MyEditor::MyEditor(QWidget *parent) : QWidget(parent)
{
    m_scroll_area = new QScrollArea(this);
    m_scroll_area->setWidgetResizable(true);
    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_scroll_area);
    auto temp_widget = new QWidget(this);
    m_layout_data_area = new QGridLayout(temp_widget);
    //    auto base_string = QString::fromUtf8(u8"11012026803012026803(1)%1");
    //    for (int i = 0; i < 100; ++i) {
    //        auto label = new QLabel(base_string.arg(QString::number(i), 4, QChar('0')), this);
    //        //        label->setFixedWidth(100);
    //        m_layout_data_area->addWidget(label, i, 0);
    //        auto edit = new QPlainTextEdit(this);
    //        edit->setFixedHeight(label->height());
    //        m_layout_data_area->addWidget(edit, i, 1);
    //        //        m_layout_data_area->setRowStretch(i, 1);
    //    }
    QStringList qss;
    qss.append(QString::fromUtf8(u8"QLabel{font:normal 12px;color:#000000;border:2px solid #AAAAAA;background:white}"));
    qss.append(QString::fromUtf8(u8"QLabel:hover{font:normal bold 25px;color:#FF0000;border:3px solid #00FF00;background:green}"));
    qss.append(QString::fromUtf8(u8"QLabel:focus{font:normal bold 25px;color:#FF0000;border:3px solid #00FF00;background:green}"));
    qss.append(QString::fromUtf8(u8"QLineEdit{font:normal bold 25px;color:#000000;border:3px solid #ffffff;background:#ffffff}"));

    temp_widget->setStyleSheet(qss.join(""));

    m_scroll_area->setWidget(temp_widget);
    connect(this, SIGNAL(all_widgets_changed()), this, SLOT(update_all_widgets()));
}

bool MyEditor::add_one_line(QString& label_text, QString& content, int location)
{
    QPair<QString, QPair<QString, QString>> line;
    line.first = label_text + "_" + QUuid::createUuid().toString();
    //    qDebug() << line.first;
    QPair<QString, QString> temp;
    temp.first = label_text;
    temp.second = content;
    line.second = temp;
    if (location < 0) {
        m_edit_contents.insert(0, line);
    } else if (location < m_edit_contents.size()) {
        m_edit_contents.insert(location, line);
    } else {
        m_edit_contents.push_back(line);
    }
    emit all_widgets_changed();
    return true;
}

bool MyEditor::set_contents(QMap<QString, QMap<QString, QVariant>>& data, QString label_key, QString edit_text_key)
{
    foreach (auto& data_line, data) {
        auto temp_label_text = data_line.value(label_key).toString();
        auto temp_edit_text = data_line.value(edit_text_key).toString();
        add_one_line(temp_label_text, temp_edit_text, m_edit_contents.size());
    }
    return true;
}

void MyEditor::clear_widgets()
{
    auto widgets = findChildren<QLabel*>();
    foreach (auto w, widgets) {
        if (w) {
            delete w;
        }
    }
    auto edits = findChildren<QPlainTextEdit*>();
    foreach (auto e, edits) {
        if (e) {
            delete e;
        }
    }
}

void MyEditor::clear_lines()
{
    m_edit_contents.clear();
}

void MyEditor::resizeEvent(QResizeEvent* e)
{

    m_scroll_area->widget()->resize(m_scroll_area->width() - m_scroll_area->verticalScrollBar()->width() - 5, m_scroll_area->widget()->height());
}

void MyEditor::mousePressEvent(QMouseEvent* e)
{

    auto pt = e->pos();
    if (e->button() == Qt::LeftButton) {
        auto widget = childAt(pt);
        if (widget) {
            if (widget->inherits("QLabel")) {
                auto code = widget->objectName().split('_').at(0);
                qDebug() << code;
                emit select_edit_changed(code);
            }
        }
    }
    if (e->type() == QEvent::MouseButtonDblClick) {
        if (e->button() == Qt::LeftButton) {
            auto widget = childAt(pt);
            if (widget) {
                if (widget->inherits("QLabel")) {
                    auto parts = widget->objectName().split('_');
                    parts.removeLast();
                    parts.append("editor");
                    auto edit_name = parts.join('_');
                    qDebug() << edit_name;
                    auto edit = findChild<QPlainTextEdit*>(edit_name);
                    if (edit) {
                        edit->selectAll();
                        edit->setFocus(Qt::ActiveWindowFocusReason);
                    }
                }
            }
        }
    }
}

void MyEditor::update_edit_height()
{
    auto edit = qobject_cast<QPlainTextEdit*>(sender());
    if (edit) {
        edit->setFixedHeight((edit->document()->size().height() + 1.5) * (edit->fontMetrics().lineSpacing()));
    }
}

void MyEditor::update_all_widgets()
{
    clear_widgets();
    foreach (auto& line, m_edit_contents) {
        auto label = new QLabel(line.second.first, this);
        label->setObjectName(line.first + "_label");
        auto edit = new QPlainTextEdit(this);
        edit->setObjectName(line.first + "_editor");
        edit->setPlainText(line.second.second);
        connect(edit, SIGNAL(textChanged()), this, SLOT(update_edit_height()));
        connect(edit, SIGNAL(textChanged()), this, SLOT(update_content()));
        connect(edit, SIGNAL(selectionChanged()), this, SLOT(get_cur_edit_name()));
        edit->setFixedHeight((edit->document()->size().height() + 1.5) * (edit->fontMetrics().lineSpacing()));
        auto row = m_layout_data_area->rowCount();
        m_layout_data_area->addWidget(label, row, 0);
        m_layout_data_area->addWidget(edit, row, 1);
    }
}

void MyEditor::update_content()
{
    auto edit = qobject_cast<QPlainTextEdit*>(sender());
    if (edit) {
        for (auto it = m_edit_contents.begin(); it != m_edit_contents.end(); ++it) {
            if (it->first + "_editor" == edit->objectName()) {
                it->second.second = edit->toPlainText();
                break;
            }
        }
    }
}

void MyEditor::get_cur_edit_name()
{
    auto edit = qobject_cast<QPlainTextEdit*>(sender());
    if (edit) {
        auto code = edit->objectName().split('_').at(0);
        qDebug() << code;
        emit select_edit_changed(code);
    }
}
