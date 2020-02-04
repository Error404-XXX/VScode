#ifndef CODEEDIT_H
#define CODEEDIT_H
#include <QPlainTextEdit>
#include <QTextBlock>
#include <QPainter>
#include "completelistwidget.h"

class LineNumberArea;
class CodeEdit : public QPlainTextEdit
{
    Q_OBJECT
public:
    CodeEdit(QWidget *parent=0);
    QString fileName;
    QString codeName;
    QFile *myFile;
    void lineNumberAreaPaintEvent(QPaintEvent *event);
    void setUpCompleteList();

public slots:
    void updateLineNumberArea(QRect rect, int dy);
    void highLightCurrentLine();
    void showCompleteWidget();

protected:
    void resizeEvent(QResizeEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    LineNumberArea *lineNumberArea;
    QStringList completeList;
    CompleteListWidget *completeWidget;
    int completeState;
    QString getWordOfCursor();
    int getCompleteWidgetX();
};

class LineNumberArea : public QWidget
{
    Q_OBJECT
public:
    LineNumberArea(CodeEdit *editor):QWidget(editor)
    {
        this->resize(40,1500);
        this->move(0,0);
        codeEdit=editor;
        this->setFont(QFont(tr("Consolas"), 14));
    }
    void paintEvent(QPaintEvent *event){
        codeEdit->lineNumberAreaPaintEvent(event);
    }

private:
    CodeEdit *codeEdit;
};

enum CompleteState{
  Ignore=0,
  Showing=1,
  Hide=2
};
#endif // CODEEDIT_H
