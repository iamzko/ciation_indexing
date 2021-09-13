#include "myeditor.h"
#include "myglobal.h"
#include <QApplication>
#include <QFont>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPalette>
#include <QScrollBar>
#include <QSplitter>
#include <QStandardItemModel>
#include <QTextCharFormat>
#include <QTextEdit>
#include <QUuid>
#include <QVBoxLayout>
#include <QtDebug>

MyEditor::MyEditor(QWidget *parent) : QWidget(parent)
{
    m_scroll_bar_right = new QScrollBar(this);
    m_scroll_bar_right->setOrientation(Qt::Vertical);
    connect(m_scroll_bar_right, SIGNAL(valueChanged(int)), this, SLOT(get_cur_scroll_position(int)));
    QStringList qss;
    qss.append(QString::fromUtf8(u8"QLabel{font:normal 12px;color:#000000;border:1px solid #AAAAAA;background:white}"));
    //    qss.append(QString::fromUtf8(u8"QLabel:hover{font:normal bold 25px;color:#FF0000;border:3px solid #00FF00;background:green}"));
    //    qss.append(QString::fromUtf8(u8"QLabel:focus{font:normal bold 25px;color:#FF0000;border:3px solid #00FF00;background:green}"));
    //    qss.append(QString::fromUtf8(u8"MyCiationEditor{font:normal bold 12px;color:#000000;border:1px solid #000000;background:#ffffff}"));
    //    qss.append(QString::fromUtf8(u8"MyCiationEditor:focus{border:2px solid green;background:#ffffff}"));
    this->setStyleSheet(qss.join(""));
    for (int i = 0; i < 15; ++i) {
        auto label = new QLabel(this);
        label->installEventFilter(this);
        auto edit = new MyCiationEditor(this);

        auto highliter = new MyHighlighter(edit->document());
        QTextCharFormat article_type;
        article_type.setForeground(Qt::green);
        article_type.setFontWeight(QFont::Bold);
        highliter->set_format_rules(MyHighlighter::FORMAT_TEXT_TYPE::ARTICLE_TYPES, article_type);
        QTextCharFormat indexing_symbol;
        indexing_symbol.setForeground(Qt::green); //设置颜色
        indexing_symbol.setFontWeight(QFont::Bold); //设置加粗
        highliter->set_format_rules(MyHighlighter::FORMAT_TEXT_TYPE::INDEXING_SYMBOLS, indexing_symbol);
        QTextCharFormat normal_text;
        normal_text.setForeground(Qt::black);
        highliter->set_format_rules(MyHighlighter::FORMAT_TEXT_TYPE::NORMAL_TEXT, normal_text);
        m_highlighter.push_back(highliter);
        edit->installEventFilter(this);
        connect(edit, SIGNAL(textChanged()), this, SLOT(update_edit_height()));
        connect(edit, SIGNAL(textChanged()), this, SLOT(update_content()));
        connect(edit, SIGNAL(selectionChanged()), this, SLOT(get_cur_edit_name()));
        QPair<QLabel*, MyCiationEditor*> temp;
        temp.first = label;
        temp.second = edit;
        m_list_widgets.append(temp);
    }
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
    m_scroll_bar_right->setRange(0, m_edit_contents.size() - m_list_widgets.size());
    return true;
}

bool MyEditor::set_contents(QMap<QString, QMap<QString, QVariant>>& data, QString label_key, QString edit_text_key)
{
    m_have_init_index = 0;
    foreach (auto& data_line, data) {
        auto temp_label_text = data_line.value(label_key).toString();
        auto temp_edit_text = data_line.value(edit_text_key).toString();
        add_one_line(temp_label_text, temp_edit_text, m_edit_contents.size());
    }
    emit all_widgets_changed();
    return true;
}

bool MyEditor::get_contents(QMap<QString, QString>& content)
{
    for (auto& line : m_edit_contents) {
        content.insert(line.second.first, line.second.second);
    }
    return true;
}

bool MyEditor::set_one_line_focus(QString& ciation_code)
{
    for (auto it = m_edit_contents.begin(); it != m_edit_contents.end(); ++it) {
        if (it->second.first == ciation_code) {
            auto edit = findChild<MyCiationEditor*>(it->first + "_editor");
            if (edit) {
                edit->selectAll();
                edit->setFocus(Qt::ActiveWindowFocusReason);
            }
            break;
        }
    }
    return true;
}

void MyEditor::show_one_line(int line_number)
{
}

QList<QPair<int, QString>> MyEditor::check_contents(bool is_eng)
{
    QSet<QString> symbols_set;
    for (auto it = MyGlobal::INDEXING_SYMBOLS_MAP.begin(); it != MyGlobal::INDEXING_SYMBOLS_MAP.end(); ++it) {
        symbols_set.insert(it.value());
    }
    QSet<QString> article_typse_set;
    for (auto it = MyGlobal::ARTICLE_TYPES_MAP.begin(); it != MyGlobal::ARTICLE_TYPES_MAP.end(); ++it) {
        article_typse_set.insert(it.value());
    }
    QList<QPair<int, QString>> result;
    for (int i = 0; i < m_edit_contents.size(); ++i) {
        auto line_ptr = m_edit_contents.at(i);
        auto line_content = line_ptr.second.second;
        if (line_content.contains(MyGlobal::INDEXING_SYMBOLS_MAP.value(MyGlobal::LANGUAGE_TRANS)) && is_eng) {
            result.append(qMakePair(i, QString::fromUtf8(u8"英文加标记中出现[%1]标记").arg(MyGlobal::LANGUAGE_TRANS)));
        }
        //检查文献类型标记
        //不会不做的无需检查
        if (!line_content.contains(MyGlobal::INDEXING_SYMBOLS_MAP.value(MyGlobal::DO_NOT))
            && !line_content.contains(MyGlobal::INDEXING_SYMBOLS_MAP.value(MyGlobal::CAN_NOT))
            && !line_content.contains(MyGlobal::INDEXING_SYMBOLS_MAP.value(MyGlobal::LANGUAGE_TRANS))) {
            auto double_star_count = line_content.count(MyGlobal::DOUBLE_STAR);
            if (double_star_count > 2) {
                result.append(qMakePair(i, QString::fromUtf8(u8"本行中有多个[文献类型]标记")));
                continue;
            } else if (double_star_count == 0) {
                result.append(qMakePair(i, QString::fromUtf8(u8"本行中没有[文献类型]标记")));
                continue;
            }
        }
        //检查引文加了多少标记
        //没有标记要标记出来
        //标记相连也要标记出来
        //末尾不允许有标记
        //两个<<之间没有其他标记
        //先去掉文献类型标记
        for (auto it = article_typse_set.begin(); it != article_typse_set.end(); ++it) {
            line_content.replace(*it, "");
        }
        auto can_not_do_symbol_nums = line_content.contains(MyGlobal::INDEXING_SYMBOLS_MAP.value(MyGlobal::CAN_NOT))
            + line_content.contains(MyGlobal::INDEXING_SYMBOLS_MAP.value(MyGlobal::DO_NOT))
            + line_content.contains(MyGlobal::INDEXING_SYMBOLS_MAP.value(MyGlobal::LANGUAGE_TRANS));
        if (can_not_do_symbol_nums > 1) {
            result.append(qMakePair(i, QString::fromUtf8(u8"含有多个[不做/不会/语言转换]标记")));
            continue;
        } else if (can_not_do_symbol_nums == 1) {
            continue;
        }
        for (auto it = symbols_set.begin(); it != symbols_set.end(); ++it) {
            if (line_content.endsWith(*it)) {
                result.append(qMakePair(i, QString::fromUtf8(u8"引文末尾不该有任何标记")));
            }
        }
    }
    return result;
}

QMap<QString, QString> MyEditor::get_all_contents()
{
    QMap<QString, QString> result;
    for (auto it = m_edit_contents.begin(); it != m_edit_contents.end(); ++it) {
        result.insert(it->second.first, it->second.second);
    }
    return result;
}

void MyEditor::clear_widgets()
{
    auto widgets = findChildren<QLabel*>();
    foreach (auto w, widgets) {
        if (w) {
            delete w;
        }
    }
    auto edits = findChildren<MyCiationEditor*>();
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
                    auto edit = findChild<MyCiationEditor*>(edit_name);
                    if (edit) {
                        edit->selectAll();
                        edit->setFocus(Qt::ActiveWindowFocusReason);
                    }
                }
            }
        }
    }
}

void MyEditor::keyPressEvent(QKeyEvent* event)
{
    switch (event->key() + event->modifiers()) {
    default:
        break;
    }
    switch (event->key()) {
    default:
        break;
    }
}

void MyEditor::update_edit_height()
{
    auto edit = qobject_cast<MyCiationEditor*>(sender());
    if (edit) {
        edit->setFixedHeight((edit->document()->size().height() + 1.5) * (edit->fontMetrics().lineSpacing()));
    }
}

void MyEditor::update_all_widgets()
{
    auto temp_index = m_scroll_bar_right->value();
    for (int i = 0; i < m_list_widgets.size(); ++i) {
        auto label_ptr = m_list_widgets.at(i).first;
        auto edit_ptr = m_list_widgets.at(i).second;
        if (temp_index < m_edit_contents.size()) {
            label_ptr->setObjectName(m_edit_contents.at(temp_index).first + "_label");
            label_ptr->setText(m_edit_contents.at(temp_index).second.first);
            edit_ptr->setObjectName(m_edit_contents.at(temp_index).first + "_editor");
            edit_ptr->setPlainText(m_edit_contents.at(temp_index).second.second);
            edit_ptr->setFixedHeight((edit_ptr->document()->size().height() + 1.5) * (edit_ptr->fontMetrics().lineSpacing()));
        } else {
            label_ptr->setObjectName("");
            label_ptr->setText("");
            edit_ptr->setObjectName("");
            edit_ptr->setPlainText("");
        }
        temp_index++;
    }
}

void MyEditor::update_content()
{
    auto edit = qobject_cast<MyCiationEditor*>(sender());
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
    auto edit = qobject_cast<MyCiationEditor*>(sender());
    if (edit) {
        auto code = edit->objectName().split('_').at(0);
        qDebug() << code;

        emit select_edit_changed(code);
    }
}

void MyEditor::get_cur_scroll_position(int value)
{
    emit all_widgets_changed();
}

void MyEditor::setCur_new_ciation_id(int newCur_new_ciation_id)
{
    m_cur_new_ciation_id = newCur_new_ciation_id;
}

void MyEditor::set_label_text_style(QFont font, QColor front)
{
    for(auto widget:m_list_widgets)
    {
        widget.first->setFont(font);
        widget.first->setStyleSheet(QString::fromUtf8(u8"color:rgb(%1,%2,%3);").arg(front.red()).arg(front.green()).arg(front.blue()));
    }
}

void MyEditor::set_label_color(QColor back)
{
       this->setStyleSheet(QString::fromUtf8(u8"QLabel{background: rgb(%1,%2,%3);}").arg(back.red()).arg(back.green()).arg(back.blue()));
//    for(auto widget:m_list_widgets)
//    {
//        qDebug() << "label_backcolor" << back;
////        widget.first->setStyleSheet(QString::fromUtf8(u8"{background: rgb(%1,%2,%3);}").arg(back.red()).arg(back.green()).arg(back.blue()));
////        QPalette p;
////        p.setColor(QPalette::Base,back);
////        widget.first->setAutoFillBackground(true);
////        widget.first->setPalette(p);
//    }
}

void MyEditor::set_edit_text_style(QFont font, QColor front,QColor back)
{
    for(auto highliter:m_highlighter)
    {
        QTextCharFormat normal_text;
        normal_text.setBackground(back);
        normal_text.setForeground(front);
        normal_text.setFont(font);
        highliter->set_format_rules(MyHighlighter::FORMAT_TEXT_TYPE::NORMAL_TEXT, normal_text);
    }
}

void MyEditor::set_edit_color(QColor back)
{
    for(auto widget:m_list_widgets)
    {
        widget.second->setStyleSheet(QString::fromUtf8(u8"background-color:rgb(%1,%2,%3);").arg(back.red()).arg(back.green()).arg(back.blue()));
    }
    
}

void MyEditor::set_edit_indexing_symbol_text_style(QFont font, QColor front, QColor back)
{
    for(auto highliter:m_highlighter)
    {
        QTextCharFormat indexing_symbol;
        indexing_symbol.setForeground(front); //设置颜色
        indexing_symbol.setBackground(back);
        indexing_symbol.setFont(font);
        highliter->set_format_rules(MyHighlighter::FORMAT_TEXT_TYPE::INDEXING_SYMBOLS, indexing_symbol);
        QTextCharFormat article_type;
        article_type.setForeground(front);
        article_type.setBackground(back);
        article_type.setFont(font);
        highliter->set_format_rules(MyHighlighter::FORMAT_TEXT_TYPE::ARTICLE_TYPES, article_type);
    }
    
}


void MyEditor::wheelEvent(QWheelEvent *event)
{
    if(event->angleDelta().y()>0)
    {
        m_scroll_bar_right->setValue(m_scroll_bar_right->value()-m_list_widgets.size());
    }
    else
    {
        m_scroll_bar_right->setValue(m_scroll_bar_right->value()+m_list_widgets.size());
    }
        qDebug() << m_list_widgets.size();
    
    event->accept();
}

void MyEditor::paintEvent(QPaintEvent *event)
{
    if(rect().contains(event->rect())  )
    {
    int label_left_space = 5;
    int label_len = 120;
    int space = 5;
    int line_space = 5;
    int edit_right_space = 5;
    int start_left = 0;
    int start_top = 0;
    int scroll_bar_width = 20;
    for (int i = 0; i < m_list_widgets.size(); ++i) {
        m_list_widgets.at(i).second->setGeometry(start_left + label_left_space + label_len + space, start_top + line_space, width() - label_left_space - label_len - space - edit_right_space - scroll_bar_width, 10);
        m_list_widgets.at(i).second->setFixedHeight((m_list_widgets.at(i).second->document()->size().height() + 1.5) * (m_list_widgets.at(i).second->fontMetrics().lineSpacing()));
        m_list_widgets.at(i).first->setGeometry(start_left + label_left_space, start_top + line_space, label_len, m_list_widgets.at(i).second->height());
        start_top = line_space + m_list_widgets.at(i).first->y() + m_list_widgets.at(i).first->height();
    }
    m_scroll_bar_right->setGeometry(m_list_widgets.at(0).second->x() + m_list_widgets.at(0).second->width() + edit_right_space, 0, scroll_bar_width, height());
    }
}

bool MyEditor::eventFilter(QObject *watched, QEvent *e)
{
    if (e->type() == QEvent::KeyPress) {
        auto key_event = static_cast<QKeyEvent*>(e);
        switch (key_event->key() + key_event->modifiers()) {
        }
        switch (key_event->key()) {
        case Qt::Key_Down:
            for(int i = 0; i < m_list_widgets.size(); ++i)
            {
                if(m_list_widgets.at(i).second->hasFocus())
                {
                    if(i+1 < m_list_widgets.size())
                    {
                        m_list_widgets.at(i+1).second->setFocus(Qt::ActiveWindowFocusReason);
                        emit select_edit_changed(m_list_widgets.at(i+1).first->objectName().split('_').at(0));
                    }
                    else
                    {
                        m_scroll_bar_right->setValue(m_scroll_bar_right->value() + 1);
                        emit select_edit_changed(m_list_widgets.at(i).first->objectName().split('_').at(0));
                    }
                    break;
                }
            }
            return true;
            break;
        case Qt::Key_Up:
            for(int i = m_list_widgets.size()-1; i >=0; --i)
            {
                if(m_list_widgets.at(i).second->hasFocus())
                {
                    if(i-1>=0 )
                    {
                        m_list_widgets.at(i-1).second->setFocus(Qt::ActiveWindowFocusReason);
                        emit select_edit_changed(m_list_widgets.at(i-1).first->objectName().split('_').at(0));
                    }
                    else
                    {
                        m_scroll_bar_right->setValue(m_scroll_bar_right->value() - 1);
                        emit select_edit_changed(m_list_widgets.at(i).first->objectName().split('_').at(0));
                    }
                    break;
                }
            }
            return true;
            break;
        case Qt::Key_PageDown:
            m_scroll_bar_right->setValue(m_scroll_bar_right->value() + m_list_widgets.size());
            return true;
            break;
        case Qt::Key_PageUp:
            m_scroll_bar_right->setValue(m_scroll_bar_right->value() - m_list_widgets.size());
            return true;
            break;
        case Qt::Key_Home:
            m_scroll_bar_right->setValue(0);
            return true;
            break;
        case Qt::Key_End:
            m_scroll_bar_right->setValue(m_scroll_bar_right->maximum());
            return true;
            break;
        case Qt::Key_Enter:
        case Qt::Key_Return:
            for(int i = m_list_widgets.size()-1; i >=0; --i)
            {
                if(m_list_widgets.at(i).second->hasFocus())
                {
                    auto ciation_code = m_list_widgets.at(i).first->text();
                    for(auto it = m_edit_contents.begin();it != m_edit_contents.end();++it)
                    {
                        if(it->second.first == ciation_code)
                        {
                            auto new_id = ciation_code.left(ciation_code.size()-4) ;
                            new_id.append( QString::fromUtf8(u8"%1").arg(QString::number(m_cur_new_ciation_id--),4,QChar('0')));
                            
                            auto cursor = m_list_widgets.at(i).second->textCursor();
                            cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor); //keepanchor移动的时候选中文本
                            auto new_content = cursor.selectedText();
                            cursor.removeSelectedText();
                            add_one_line(new_id,new_content, it-m_edit_contents.begin()+1);
                            break;
                        }
                    }
                    break;
                }
            }
        emit all_widgets_changed();
        return true;
        break;
            
        }
        return false;
    }
    return false;

} 
