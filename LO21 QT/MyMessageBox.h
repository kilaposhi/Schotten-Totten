#ifndef MYMESSAGEBOX_H
#define MYMESSAGEBOX_H

#include <QMessageBox>

class MyMessageBox : public QMessageBox
{
    Q_OBJECT

public:
    explicit MyMessageBox(QWidget* parent, int playerID);

signals:
    void dialogClosed(int ID);

private slots:
    void handleDialogClosed();

private :
    int playerID;
};


#endif // MYMESSAGEBOX_H
