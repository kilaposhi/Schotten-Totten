#ifndef CARDVIEW_H
#define CARDVIEW_H

#include <QWidget>
#include "Card.h"
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
