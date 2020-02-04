#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include <QToolTip>
//#include <QMouseEvent>
//#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(1000,670);
    this->setWindowTitle("Visual Studio Code");
    this->setWindowIcon(QPixmap(":/img/logo.png"));

    myMenuBar=new QMenuBar(this);
    statusBar=new QStatusBar(this);
    tab=new QTabWidget(this);
    tab->setStyleSheet("background-color:rgb(33,33,33);border:none;");
    setStyleSheet("QMenuBar::item:hover{background-color:rgb(71,71,72);}QTabBar::tab{background-color:rgb(45,45,45);color:white}QTabBar::tab:selected{background-color:rgb(33,33,33);color:white}");
//    codeArea=new CodeEdit(this);
//    highLighter=new HighLighter(codeArea->document());
    tab->setVisible(false);
    tab->setTabsClosable(true);
    tab->move(60,35);
    //状态栏
    codeName=new QPushButton;
    codeName->setStyleSheet("QPushButton{ color: white; border-radius: 30px;}"
                            "QPushButton:hover{background-color:rgb(31, 138, 210); color: white;}"
                            "QPushButton:pressed{background-color:rgb(46, 146, 213);}"
                           );
    init_statusBar();
    statusBar->move(0,640);
    statusBar->setStyleSheet("background-color:rgb(0, 122, 204);color:white;");
    //增加菜单栏
    file=myMenuBar->addMenu(tr("文件(&F)"));
    edit=myMenuBar->addMenu(tr("编辑(&E)"));
    select=myMenuBar->addMenu(tr("选择(&S)"));
    view=myMenuBar->addMenu(tr("查看(&V)"));
    go=myMenuBar->addMenu(tr("转到(&G)"));
    debug=myMenuBar->addMenu(tr("调试(&D)"));
    terminal=myMenuBar->addMenu(tr("终端(&T)"));
    help=myMenuBar->addMenu(tr("帮助(&H)"));
    //细分菜单栏
    actionNew=file->addAction(tr("新建文件"));
    actionNewWindow=file->addAction(tr("新建窗口"));
    actionNew->setShortcut(QKeySequence("Ctrl+N"));
    actionNewWindow->setShortcut(QKeySequence("Ctrl+Shift+N"));
    file->addSeparator();
    actionOpen=file->addAction(tr("打开文件"));
    actionOpenDir=file->addAction(tr("打开文件夹"));
    actionOpen->setShortcut(QKeySequence("Ctrl+O")); //快捷键
    actionOpenDir->setShortcut(QKeySequence("Ctrl+Shift+O"));
    file->addSeparator();
    actionSave=file->addAction(tr("保存"));
    actionSave->setShortcut(QKeySequence("Ctrl+S"));

    actionUndo=edit->addAction(tr("撤销"));
    actionRedo=edit->addAction(tr("恢复"));
    actionCut=edit->addAction(tr("剪切"));
    actionCopy=edit->addAction(tr("复制"));
    actionPast=edit->addAction(tr("粘贴"));
    actionUndo->setShortcut(QKeySequence("Ctrl+Z"));
    actionRedo->setShortcut(QKeySequence("Ctrl+Y"));
    actionCut->setShortcut(QKeySequence("Ctrl+X"));
    actionCopy->setShortcut(QKeySequence("Ctrl+C"));
    actionPast->setShortcut(QKeySequence("Ctrl+V"));

    connect(this->actionNew,&QAction::triggered,this,&MainWindow::addNewFile);
    connect(this->actionOpen,&QAction::triggered,this,&MainWindow::openFile);
    connect(this->actionSave,&QAction::triggered,this,&MainWindow::saveFile);
    connect(this->codeName,&QPushButton::clicked,this,&MainWindow::showCodeNameDialog);
    connect(this->tab,&QTabWidget::tabCloseRequested,this,&MainWindow::tabClose);
    connect(this->tab,&QTabWidget::tabCloseRequested,this,&MainWindow::tabHide);

    btn_1=new QPushButton(this);
    btn_1->setStyleSheet("QPushButton{border-image:url(:/img/file_1.png);}QPushButton:hover{border-image:url(:/img/file.png);}");
    btn_1->resize(33,33);
    btn_1->move(14,45);
    btn_2=new QPushButton(this);
    btn_2->setStyleSheet("QPushButton{border-image:url(:/img/search_1.png);}QPushButton:hover{border-image:url(:/img/search.png);}");
    btn_2->resize(33,33);
    btn_2->move(14,95);
    btn_3=new QPushButton(this);
    btn_3->setStyleSheet("QPushButton{border-image:url(:/img/git_1.png);}QPushButton:hover{border-image:url(:/img/git.png);}");
    btn_3->resize(33,33);
    btn_3->move(14,155);
    btn_4=new QPushButton(this);
    btn_4->setStyleSheet("QPushButton{border-image:url(:/img/bug_1.png);}QPushButton:hover{border-image:url(:/img/bug.png);}");
    btn_4->resize(33,33);
    btn_4->move(14,215);
    btn_5=new QPushButton(this);
    btn_5->setStyleSheet("QPushButton{border-image:url(:/img/app_1.png);}QPushButton:hover{border-image:url(:/img/app.png);}");
    btn_5->resize(33,33);
    btn_5->move(14,275);
//    file_1=new QPushButton(this);
//    file_1->setStyleSheet(tr("QPushButton{border:0px;border-color:rgb(33,33,33);border-bottom:2px solid blue;background-color:rgb(33,33,33);color:white;font:bold;}"));
//    file_1->setText("Untitled");
//    file_1->setFont(QFont("等线",10));
//    file_1->resize(140,30);
//    file_1->move(60,35);

    qssFile = new QFile(":/stylesheet.qss", this);
    // 只读方式打开该文件
    qssFile->open(QFile::ReadOnly);
    // 读取文件全部内容，使用tr()函数将其转换为QString类型
    QString styleSheet = tr(qssFile->readAll());
    // 为QApplication设置样式表
    qApp->setStyleSheet(styleSheet);
    qssFile->close();
    myMenuBar->setGeometry(QRect(0,0,1920,35));

    addNewFile();

//    this->centralWidget()->setMouseTracking(true);
//    setMouseTracking(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addNewFile()
{
    CodeEdit *codeArea;
    HighLighter *highLighter;
    codeArea=new CodeEdit(tab);
    highLighter=new HighLighter(codeArea->document());
    codeArea->setAttribute(Qt::WA_DeleteOnClose);
    connect(codeArea,SIGNAL(cursorPositionChanged()),this,SLOT(doCursorChanged()));
    int cur=tab->addTab(codeArea,QString::asprintf("Untitle-%d",tab->count()+1));
    tab->setCurrentIndex(cur);
    tab->setVisible(true);
}

void MainWindow::openFile()
{
    CodeEdit *codeArea;
    HighLighter *highLighter;
    codeArea=new CodeEdit(tab);
    highLighter=new HighLighter(codeArea->document());
    QString filename=QFileDialog::getOpenFileName(this,"打开文件",".","Text(*.cpp *.h *.txt)");
    codeArea->fileName=filename;
    if(filename.isEmpty())
        return;
    QStringList list=filename.split("/");
    QString title=list.at(list.length()-1);
//    this->file_1->setText(title);
// QFileInfo info(filename);
// QString title=info.fileName();
    codeArea->myFile->setFileName(filename);
    bool ret=codeArea->myFile->open(QIODevice::ReadOnly);
    if(!ret)
    {
        QMessageBox::warning(this,"文件失败","打开失败");
    }
    QTextStream stream(codeArea->myFile);
    codeArea->codeName="UTF-8";
    stream.setCodec(codeArea->codeName.toLocal8Bit().data());
    codeArea->setPlainText(stream.readAll());
    codeArea->myFile->close();
    codeArea->setAttribute(Qt::WA_DeleteOnClose);
    connect(codeArea,SIGNAL(cursorPositionChanged()),this,SLOT(doCursorChanged()));
    int cur=tab->addTab(codeArea,QString::asprintf(title.toStdString().c_str()));
    tab->setCurrentIndex(cur);
    tab->setVisible(true);
}

void MainWindow::saveFile()
{
    CodeEdit *codeArea=(CodeEdit*)tab->currentWidget();
    if(codeArea->fileName.isEmpty())
    {
        QString filename=QFileDialog::getSaveFileName(this,"保存",".","*.txt*.cpp *.h");
        codeArea->fileName=filename;
    }
    codeArea->myFile->setFileName(codeArea->fileName);
    codeArea->myFile->open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream stream(codeArea->myFile);
    stream.setCodec(codeArea->codeName.toLocal8Bit().data());
    stream<<codeArea->toPlainText();
    stream.flush();
    codeArea->myFile->close();
    if(!codeArea->fileName.isEmpty())
        QMessageBox::information(this,"成功","保存成功！");
}

void MainWindow::doCursorChanged()
{
    CodeEdit *codeArea=(CodeEdit*)tab->currentWidget();
    int rowNum = codeArea->document()->blockCount();
    const QTextCursor cursor = codeArea->textCursor();
    int colNum = cursor.columnNumber();
    first_statusLabel->setText(tr("%1行 %2列").arg(rowNum).arg(colNum));
}

//void MainWindow::mouseMoveEvent(QMouseEvent *event)
//{
//    QString pos=QString("%1, %2").arg(event->pos().x()).arg(event->pos().y());
//    QToolTip::showText(event->globalPos(),pos,this);
//}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Return)
    {
        QString text=codeNameDialog->codeNameList->currentItem()->text();
        doProcessTriggeredByCodeName(text);
    }
    else{
        MainWindow::keyPressEvent(event);
    }
    codeNameDialog->close();
}

void MainWindow::showCodeNameDialog()
{
    codeNameDialog=new CodeNameDialog(this);
    codeNameDialog->setWindowTitle(tr("选择编码"));
    codeNameDialog->show();
}

void MainWindow::tabClose(int index)
{
    if(index<0)
        return;
    QWidget *aTab=tab->widget(index);
    aTab->close();
}

void MainWindow::tabHide(int index)
{
    bool en=tab->count()>0;
    tab->setVisible(en);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QBrush brush(QColor(33,33,33));
    painter.setBrush(brush);
    painter.fillRect(QRect(60,35,this->geometry().width()-60,this->geometry().height()-30),QBrush(QColor(33,33,33)));
    painter.fillRect(QRect(0,35,60,this->geometry().height()-30),QBrush(QColor(51,51,51)));
}

void MainWindow::resizeEvent(QResizeEvent *){
    tab->resize(this->geometry().width()-60,this->geometry().height()-65);
    statusBar->setGeometry(QRect(0,this->rect().bottom()-30,this->geometry().width(),30));
}

void MainWindow::init_statusBar()
{
    first_statusLabel = new QLabel; //新建标签
    first_statusLabel->setMinimumSize(75,20); //设置标签最小尺寸

//    second_statusLabel = new QLabel;
//    second_statusLabel->setMinimumSize(150,20);
//    second_statusLabel->setFrameShadow(QFrame::Plain);

    statusBar->addPermanentWidget(first_statusLabel);
    //statusBar->addPermanentWidget(second_statusLabel);
    statusBar->addPermanentWidget(codeName);
    first_statusLabel->setText(tr("欢迎使用VS code")); //初始化内容
    //second_statusLabel->setText(tr("yafeilinux制作!"));
    codeName->setText("UTF-8");
}

void MainWindow::doProcessTriggeredByCodeName(QString text)
{
    CodeEdit *codeArea=(CodeEdit*)tab->currentWidget();
    if(codeArea!=0){
        this->codeName->setText(text);
        QTextStream stream(codeArea->myFile);
        stream.setCodec(this->codeName->text().toLocal8Bit().data());
    }
    else
        QMessageBox::information(this,"Error","请先添加文件！");
}
