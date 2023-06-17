#include"DeckView.h"
#include <QWidget>
#include "Game.h"
#include <QMessageBox>

TacticDeckView::TacticDeckView(QWidget* parent, Deck* deck) : QPushButton(parent) {
    setEnabled(false);
    setText("Tactic deck");
    //connect(this, SIGNAL(clicked()), this, SLOT(TacticDeckClicked(deck, player)));
}

ClanDeckView::ClanDeckView(QWidget* parent, Deck* deck) : QPushButton(parent) {
    setText("Clan deck");
    setEnabled(false);
    //connect(this, SIGNAL(clicked()), this, SLOT(ClanDeckClicked(deck, player)));
}

/*void TacticDeckView::TacticDeckClicked(Deck* deck){
    if (deck->isEmpty()){
        QMessageBox::warning(nullptr, "Tactic Deck", "The tactic deck is empty.");
    }
    else {
        player->draw_card(*deck);
    }
    setEnabled(false);
}

void ClanDeckView::ClanDeckClicked(Deck* deck){
    if (deck->isEmpty()){
        QMessageBox::warning(nullptr, "Clan Deck", "The clan deck is empty.");
    }
    else {
        player->draw_card(*deck);
    }
    setEnabled(false);
}*/
