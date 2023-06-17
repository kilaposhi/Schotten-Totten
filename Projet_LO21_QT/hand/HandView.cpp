#include "HandView.h"

#include <QGridLayout>
#include <QList>
#include <QDebug>
#include <QPushButton>

/*
HandView::HandView(QWidget *parent, Player* player) : QWidget(parent) {
    m_handLayout = new QHBoxLayout(parent);
    vector<unique_ptr<Card>> hand = player->getHand();
    for (int i = 0; i< player->getNumber_of_cards(); i++) {
        string card = player->displayCard(i);
        QPushButton *cardButton = new QPushButton(QString::fromStdString(card),parent);
        cardButton->setEnabled(false);
        m_handList.append(*cardButton);
        m_handLayout->addWidget(cardButton);
    }
    setLayout(m_handLayout);
}*/

HandView::HandView(QWidget* parent, Player* player)
    : QWidget(parent), player(player)
{
    m_handLayout = new QGridLayout(this); // Utilisez "this" comme parent pour le layout

    //std::vector<Card> playerHand = player->getHand();

    for (int i = 0; i < player->getNumber_of_cards(); i++) {
        CardView* cardButton = new CardView(parent, player->getCardAtIndex(i).get());
        cardButton->setEnabled(false);
        connect(cardButton, &CardView::clicked, [this, i]() {
            cardClicked(i);
        });
        m_handList.append(cardButton);
        m_handLayout->addWidget(cardButton, 0, i);
    }
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    setLayout(m_handLayout);

}

QList<CardView*> HandView::getHandList() const {
    return m_handList;
}

void HandView::cardClicked(int index) {
    for (CardView* cardV : this->getHandList()) {
        cardV->setEnabled(false);
    }
    qDebug() << "Dans cardClicked HandView";
    //m_handLayout->update();
    emit cardSelected(index);
}

void HandView::handlePlayed() {
    m_handLayout->update();
}

void HandView::updateHV() {
    delete(m_handLayout);
    m_handList.clear();
    for (int i = 0; i < player->getNumber_of_cards(); i++) {
        CardView* cardButton = new CardView(this, player->getCardAtIndex(i).get());
        cardButton->setEnabled(false);
        connect(cardButton, &CardView::clicked, [this, i]() {
            cardClicked(i);
        });
        m_handList.append(cardButton);

    }
    int i = 0;
    for (CardView* card : m_handList) {
        m_handLayout->addWidget(card, 0, i);
        i++;
    }
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    for (CardView* cardV : this->getHandList()) {
        cardV->update();
    }
    m_handLayout->update();
}
