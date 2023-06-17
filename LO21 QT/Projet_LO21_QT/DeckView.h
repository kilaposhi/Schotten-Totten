#ifndef DECKVIEW_H
#define DECKVIEW_H

#include <QPushButton>
#include <QWidget>
#include "Card.h"
#include "Deck.h"
#include "Player.h"

class TacticDeckView : public QPushButton
{
    Q_OBJECT

signals :


private slots :
               //void TacticDeckClicked(Deck* deck);


private :
    QPushButton* button;


public :
    TacticDeckView(QWidget *parent, Deck* deck);
};



class ClanDeckView : public QPushButton
{
    Q_OBJECT

signals :


private slots :
               //void ClanDeckClicked(Deck* deck, Player* player);

private :
    QPushButton* button;


public :
    ClanDeckView(QWidget *parent, Deck* deck);
};

#endif // DECKVIEW_H
