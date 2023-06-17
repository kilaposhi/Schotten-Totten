#include "CombinationView.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QList>

CombinationView::CombinationView(QWidget* parent, Combination* combi)
    : QWidget(parent), combination(combi)
{
    m_combiLayout = new QGridLayout(this); // Utilisez "this" comme parent pour le layout

    for (int i =0; i < combi->getNumberTacticCards(); i++) {
        CardView *card = new CardView(parent, combi->getTacticCard(i));
        if (card) {
            card->setEnabled(false);
            m_combiList.append(card);
            m_combiLayout->addWidget(card, i, 0);
        }
    }
    for (int i =0; i < combi->getNumberValuedCards(); i++) {
        CardView *card = new CardView(parent, combi->getValuedCard(i));
        if (card) {
            card->setEnabled(false);
            m_combiList.append(card);
            m_combiLayout->addWidget(card);
        }
    }

    setLayout(m_combiLayout);
}

void CombinationView::updateCoV() {
    for (CardView* card : m_combiList) {
        card->update();
    }
    m_combiLayout->update();
}
/*void CombinationView::updateCombination(Combination* combi)
{
    // Supprimer les anciennes cartes de la combinaison
    qDeleteAll(m_combiList);
    m_combiList.clear();

    // Effacer le layout existant
    QLayoutItem* item;
    while ((item = m_combiLayout->takeAt(0)) != nullptr)
        delete item;

    // Recréer l'affichage de la nouvelle combinaison
    for (int i = 0; i < combi->getNumberTacticCards(); i++) {
        CardView* card = new CardView(this, combi->getTacticCard(i));
        if (card) {
            card->setEnabled(false);
            m_combiList.append(card);
            m_combiLayout->addWidget(card, i, 0);
        }
    }
    for (int i = 0; i < combi->getNumberValuedCards(); i++) {
        CardView* card = new CardView(this, combi->getValuedCard(i));
        if (card) {
            card->setEnabled(false);
            m_combiList.append(card);
            m_combiLayout->addWidget(card, i, 1);
        }
    }

    // Mettre à jour le layout
    m_combiLayout->update();
    update();
}*/
