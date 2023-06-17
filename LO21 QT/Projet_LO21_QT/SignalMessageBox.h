#ifndef SIGNALMESSAGEBOX_H
#define SIGNALMESSAGEBOX_H



#include <QMessageBox>

class SignalMessageBox : public QMessageBox
{
    Q_OBJECT

public:
    explicit SignalMessageBox(QWidget* parent, int playerID);

signals:
    void dialogClosed(int ID);

private slots:
    void handleDialogClosed();

private :
    int playerID;
};


#endif // SIGNALMESSAGEBOX_H
