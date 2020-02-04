#ifndef CODENAMEDIALOG_H
#define CODENAMEDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QListWidget>
#include <QApplication>
#include <QKeyEvent>
#include <QMainWindow>

class codeNameListWidget;
class CodeNameDialog :public QDialog
{
    Q_OBJECT
public:
    CodeNameDialog(QWidget *parent=0);
    QListWidget *codeNameList;

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    QStringList codeNameItems;

    QMainWindow *p;
    QColor backgroundColor;
    QColor highlightColor;
};


#endif // CODENAMEDIALOG_H
