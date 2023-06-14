#ifndef CARDVIEW_H
#define CARDVIEW_H
#include <QPushButton>
#include <QWidget>
#include "Card.h"

class CardView : public QPushButton
{
    Q_OBJECT

public :
    CardView(QWidget *parent, ValuedCard card);
    CardView(QWidget *parent, TacticCard card);
};

#endif // CARDVIEW_H
