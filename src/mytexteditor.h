#ifndef MYTEXTEDITOR_H
#define MYTEXTEDITOR_H

#include <QCoreApplication>
#include <QPlainTextEdit>
#include <QScrollBar>
#include <QStringList>
#include <QWidget>
class LineNumberArea;

class MyTextEditor : public QPlainTextEdit {
    Q_OBJECT
public:
    MyTextEditor(QWidget* parent = nullptr);
    void drawLineNumberAreaEvent(QPaintEvent* e);
    void lineNumberAreaMouseEvent(QMouseEvent* e);

protected:
    virtual void keyPressEvent(QKeyEvent* e) override;
    virtual void keyReleaseEvent(QKeyEvent* e) override;
    virtual void wheelEvent(QWheelEvent* e) override;
private slots:
    void on_blockCountCHanged(int new_block_num);
    void on_update_request(const QRect& rect, int dy);
    void on_cursor_position_changed();
    void highlight_current_line();

private:
    LineNumberArea* m_line_number_area;
    QStringList m_line_number_text;
    int m_line_number_area_width;
    bool m_is_changed_over;
    int m_choose_line_number;
    int m_last_block_number;
};

class LineNumberArea : public QWidget {
    Q_OBJECT
public:
    LineNumberArea(MyTextEditor* editor = nullptr)
        : QWidget(editor)
        , m_editor(editor)
    {
    }

protected:
    void paintEvent(QPaintEvent* event) override
    {
        m_editor->drawLineNumberAreaEvent(event);
    }
    void mousePressEvent(QMouseEvent* e) override
    {
        m_editor->lineNumberAreaMouseEvent(e);
    }
    void mouseMoveEvent(QMouseEvent* e) override
    {
        m_editor->lineNumberAreaMouseEvent(e);
    }
    void mouseReleaseEvent(QMouseEvent* e) override
    {
        m_editor->lineNumberAreaMouseEvent(e);
    }
    void wheelEvent(QWheelEvent* e) override
    {
        QCoreApplication::sendEvent(m_editor->viewport(), e);
    }

private:
    MyTextEditor* m_editor;
};

#endif // MYTEXTEDITOR_H
