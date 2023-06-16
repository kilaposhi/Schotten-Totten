#ifndef HANDVIEW_H
#define HANDVIEW_H

#include <QWidget>
#include "Player.h"
#include <QGridLayout>
#include <QList>
#include "CardView.h"

class HandView : public QWidget
{
    Q_OBJECT

public :
    HandView(QWidget *parent, Player* player);
    QList<CardView*> getHandList() const;
    void updateHV();

signals :
    void cardSelected(int cardIndex);

private slots :
    void cardClicked(int index);
    void handlePlayed();

private :
    Player* player;
    QList<CardView*> m_handList;
    QGridLayout *m_handLayout;
};

#endif // HANDVIEW_H