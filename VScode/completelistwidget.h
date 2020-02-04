#ifndef COMPLETELISTWIDGET_H
#define COMPLETELISTWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QPlainTextEdit>
#include <QApplication>

class CompleteListWidget : public QListWidget
{
public:
    CompleteListWidget(QWidget *parent=0);
    static int ldistance(const QString source, const QString target);

protected:
  void keyPressEvent(QKeyEvent *event) override;

private:
  QPlainTextEdit* p;
  QColor backgroundColor;
  QColor highlightColor;
};

#endif // COMPLETELISTWIDGET_H
