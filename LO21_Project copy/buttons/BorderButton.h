#ifndef BORDERBUTTON_H
#define BORDERBUTTON_H

#include <QPushButton>
#include <QObject>

class BorderButton : public QPushButton
{

    Q_OBJECT

public:
    BorderButton(QWidget* parent = 0);
    ~BorderButton();
};

#endif // BORDERBUTTON_H
