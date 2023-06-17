#include "HandView.h"

#include <QGridLayout>
#include <QList>
#include <QDebug>

HandView::HandView(QWidget* parent, Player* player)
    : QWidget(parent), player(player)
{
    m_handLayout = new QGridLayout(this);

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
    for (CardView* cardV : m_handList) {
        cardV->setEnabled(false);
    }
    emit cardSelected(index);
}

void HandView::handlePlayed() {
    m_handLayout->update();
}

void HandView::updateHV() {
    qDeleteAll(m_handLayout->children());
    m_handList.clear();
    for (int i = 0; i < player->getNumber_of_cards(); i++) {
        CardView* cardButton = new CardView(this, player->getCardAtIndex(i).get());
        cardButton->setEnabled(false);
        connect(cardButton, &CardView::clicked, [this, i]() {
            cardClicked(i);
        });
        m_handList.append(cardButton);
        m_handLayout->addWidget(cardButton, 0, i);
    }
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    for (CardView* cardV : m_handList) {
        cardV->update();
    }
}

void HandView::clearSelectedCards() {
    for (CardView* cardV : m_handList) {
        cardV->setChecked(false);
    }
}

