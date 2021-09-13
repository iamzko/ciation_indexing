#ifndef MYCIATIONEDITOR_H
#define MYCIATIONEDITOR_H

#include <QPlainTextEdit>

class MyCiationEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    MyCiationEditor(QWidget* parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent* e) override;
    void mousePressEvent(QMouseEvent* e) override;
    //    bool nativeEvent(const QByteArray& event_type, void* message, long* result);
};

#endif // MYCIATIONEDITOR_H
