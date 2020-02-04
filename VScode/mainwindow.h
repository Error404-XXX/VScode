#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QPaintEvent>
#include <QPainter>
#include <QPushButton>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QLabel>
#include <QStatusBar>
#include <QWidget>
#include "codeedit.h"
#include "highlighter.h"
#include "codenamedialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *);
    void init_statusBar();
    void statusBarAreaPaintEvent(QPaintEvent *event);
//    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *);
    void doProcessTriggeredByCodeName(QString);
    ~MainWindow();

public slots:
    void addNewFile();
    void openFile();
    void saveFile();
    void doCursorChanged();
    void showCodeNameDialog();
    void tabClose(int index);
    void tabHide(int index);

private:
    Ui::MainWindow *ui;
    QMenuBar *myMenuBar;
    QMenu *file;
    QMenu *edit;
    QMenu *select;
    QMenu *view;
    QMenu *go;
    QMenu *debug;
    QMenu *terminal;
    QMenu *help;
    QPushButton *btn_1;
    QPushButton *btn_2;
    QPushButton *btn_3;
    QPushButton *btn_4;
    QPushButton *btn_5;
    //QPushButton *file_1;
    QPushButton *codeName;
    QFile *qssFile;
    QTabWidget *tab;
//    CodeEdit *codeArea;
    QAction *actionNewWindow;
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionOpenDir;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionCut;
    QAction *actionPast;
    QAction *actionCopy;
    QAction *actionFind;
    QAction *actionReplace;
    QAction *actionSelectAll;
    QAction *actionSave;
    QAction *actionSaveAs;
    HighLighter *highLighter;
    QStatusBar* statusBar;
    QLabel* first_statusLabel;
    //QLabel* second_statusLabel;
    CodeNameDialog *codeNameDialog;
};

#endif // MAINWINDOW_H
