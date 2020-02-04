#include "codenamedialog.h"

CodeNameDialog::CodeNameDialog(QWidget *parent)
{
    codeNameList=new QListWidget(this);
    p=(QMainWindow *)parent;
    backgroundColor=QColor(37,37,38);
    highlightColor.setRgb(22,165,248);
    QPalette palette=codeNameList->palette();
    palette.setColor(QPalette::Active,QPalette::Highlight,highlightColor);
    palette.setColor(QPalette::Inactive,QPalette::Highlight,highlightColor);
    palette.setColor(QPalette::Active, QPalette::Base,backgroundColor);
    palette.setColor(QPalette::Inactive, QPalette::Base, backgroundColor);
    palette.setColor(QPalette::Text,Qt::white);
    codeNameList->setPalette(palette);

    codeNameItems<<"UTF-8"<<"GB18030";
    foreach(const QString& item,codeNameItems){
        QListWidgetItem *pItem=new QListWidgetItem(item);
        pItem->setFont(QFont(tr("Consolas"), 14));
        codeNameList->addItem(pItem);
    }
    setFixedSize(250,100);
    codeNameList->setCurrentRow(0,QItemSelectionModel::Select);
    setModal(true);
}

void CodeNameDialog::keyPressEvent(QKeyEvent *event)
{
    QApplication::sendEvent(p,event);
}



