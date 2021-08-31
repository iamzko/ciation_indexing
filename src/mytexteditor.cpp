#include "mytexteditor.h"
#include <QPainter>
#include <QTextBlock>
#include <QtDebug>

MyTextEditor::MyTextEditor(QWidget* parent)
    : QPlainTextEdit(parent)
    , m_line_number_area_width(0)
    , m_is_changed_over(true)
    , m_last_block_number(0)
{
    m_line_number_area = new LineNumberArea(this);
    auto new_v_scroll_bar = new QScrollBar(this);
    setVerticalScrollBar(new_v_scroll_bar);
    connect(this, SIGNAL(updateRequest(const QRect&, int)), this, SLOT(on_update_request(const QRect&, int)));
    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(on_blockCountCHanged(int)));
    connect(new_v_scroll_bar, SIGNAL(sliderMoved(int)), m_line_number_area, SLOT(update()));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(on_cursor_position_changed()));
    viewport()->installEventFilter(this);
    m_line_number_text << "1020134774";
    m_last_block_number = blockCount();
}

void MyTextEditor::drawLineNumberAreaEvent(QPaintEvent* e)
{
    if (m_is_changed_over) {
        auto viewport_left = fontMetrics().horizontalAdvance(m_line_number_text.last());
        m_line_number_area_width = viewport_left + viewport_left / 5;
        QPainter p(m_line_number_area);
        p.fillRect(m_line_number_area->rect(), QColor(Qt::green).lighter(160));
        m_line_number_area->setGeometry(0, 0, m_line_number_area_width, this->height());

        QTextBlock text_block = firstVisibleBlock();
        int line_num_top = qRound(blockBoundingGeometry(text_block).translated(contentOffset()).top());
        int line_num_bottom = line_num_top + qRound(blockBoundingGeometry(text_block).height());
        int text_index = text_block.blockNumber();

        //遍历textblock获取
        while (text_block.isValid() && line_num_top <= m_line_number_area->rect().bottom()) {
            if (text_block.isVisible() && line_num_bottom >= m_line_number_area->rect().top()) {
                if (m_choose_line_number == text_index) {
                    p.drawRect(0, line_num_top, m_line_number_area_width, qRound(blockBoundingGeometry(text_block).height()));
                }
                p.drawText(0, line_num_top + (qRound(blockBoundingGeometry(text_block).height()) - fontMetrics().height()) / 2, m_line_number_area_width, fontMetrics().height(), Qt::AlignRight, m_line_number_text.at(text_index));
            }
            text_block = text_block.next();
            line_num_top = line_num_bottom;
            line_num_bottom = line_num_top + qRound(blockBoundingGeometry(text_block).height());
            text_index++;
        }
    }
    setViewportMargins(m_line_number_area_width, 0, 0, 0);
}

void MyTextEditor::lineNumberAreaMouseEvent(QMouseEvent* e)
{
    auto cursor = cursorForPosition(QPoint(0, e->pos().y()));
    if (e->type() == QEvent::MouseButtonPress || e->type() == QEvent::MouseButtonDblClick) {
        if (e->button() == Qt::LeftButton) {
            auto sel = cursor;
            sel.setVisualNavigation(true);
            sel.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor); //moveanchor移动的时候不选中文本
            sel.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor); //keepanchor移动的时候选中文本
            setTextCursor(sel);
            m_choose_line_number = cursor.blockNumber();
            m_line_number_area->update();
        }
    }
}

void MyTextEditor::keyPressEvent(QKeyEvent* e)
{
    switch (e->key() + e->modifiers()) {
    case Qt::Key_V + Qt::ControlModifier:
        break;
    case Qt::Key_K + Qt::ControlModifier:
        break;
    case Qt::Key_Z + Qt::ControlModifier:
        break;
    }
    switch (e->key()) {
    case Qt::Key_Enter:
    case Qt::Key_Return: {
        m_is_changed_over = false;

        auto last_line = m_line_number_text.last().toInt();
        //        m_line_number_text << QString::number(last_line + 1);
        m_line_number_text.insert(textCursor().blockNumber() + 1, QString::number(last_line + 1));
        m_last_block_number = blockCount();
        m_is_changed_over = true;
    } break;
    case Qt::Key_Delete:
    case Qt::Key_Backspace: {
        if (m_last_block_number != blockCount()) {
            m_line_number_text.removeAt(textCursor().blockNumber());
            m_last_block_number = blockCount();
        }

    } break;
    }

    QPlainTextEdit::keyPressEvent(e);
}

void MyTextEditor::keyReleaseEvent(QKeyEvent* e)
{
    if (e->key() == Qt::Key_Enter) {
        qDebug() << textCursor().blockNumber();
    }
    QPlainTextEdit::keyReleaseEvent(e);
}

void MyTextEditor::wheelEvent(QWheelEvent* e)
{
    auto old = verticalScrollBar()->value();
    if (e->angleDelta().y() > 0) {
        verticalScrollBar()->setValue(old - 1);
    } else {
        verticalScrollBar()->setValue(old + 1);
    }
    m_line_number_area->update();
}

void MyTextEditor::on_blockCountCHanged(int new_block_num)
{
}

void MyTextEditor::on_update_request(const QRect& rect, int dy)
{
    if (dy)
        m_line_number_area->scroll(0, dy);
    else
        m_line_number_area->update(0, rect.y(), m_line_number_area_width, rect.height());

    if (rect.contains(viewport()->rect()))
        setViewportMargins(m_line_number_area_width, 0, 0, 0);
}

void MyTextEditor::on_cursor_position_changed()
{
    if (textCursor().blockNumber() != m_choose_line_number) {
        m_choose_line_number = textCursor().blockNumber();
    }
    highlight_current_line();
}

void MyTextEditor::highlight_current_line()
{
    QList<QTextEdit::ExtraSelection> extra_selections;
    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;
        QColor line_color = QColor(Qt::yellow).lighter(160);
        selection.format.setBackground(line_color);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extra_selections.append(selection);
    }
    setExtraSelections(extra_selections);
}
