#include "signalmessagebox.h"


SignalMessageBox::SignalMessageBox(QWidget* parent, int player) : QMessageBox(parent)
{   playerID = player;
    connect(this, &QMessageBox::finished, this, &SignalMessageBox::handleDialogClosed);


}


void SignalMessageBox::handleDialogClosed(){
    //qDebug() << playerID;
    emit dialogClosed(playerID);
}
