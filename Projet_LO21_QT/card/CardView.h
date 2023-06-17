#ifndef CARDVIEW_H
#define CARDVIEW_H

#include "Card.h"

#include <QWidget>
#include <QPushButton>
#include <memory>


class CardView : public QPushButton
{
    Q_OBJECT

signals:
    void cardSelected();

private slots:

private:
    bool tactic {false};
    int value;
    QString color;
    QString name;

public:
    CardView(QWidget* parent, Card* card); // Utiliser std::unique_ptr<Card>

};





#endif // CARDVIEW_H
