#ifndef CARDBUTTON_H
#define CARDBUTTON_H

#include <QPushButton>
#include <QObject>
#include <QString>

class CardButton : public QPushButton
{

    Q_OBJECT

public:
    CardButton(QWidget* parent = 0, const QString& text = "");
    ~CardButton();
};

#endif // CARDBUTTON_H
