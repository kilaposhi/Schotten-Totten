#include "BoardView.h"
#include "BorderView.h"
#include "CombinationView.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>

BoardView::BoardView(QWidget* parent, Board* board)
    : QWidget(parent), board(board)
{
    m_boardLayout = new QHBoxLayout(this); // Utilisez "this" comme parent pour le layout

    // Créer les QLabel représentant chaque case du plateau
    for (int i = 0; i < 9; ++i) {
        BorderView *border = new BorderView(this, &board->getBorderByID(i));
        connect(border, &BorderView::borderSelected, this, &BoardView::handleBorderSelected);
        /*label->setAlignment(Qt::AlignCenter);
        label->setFixedSize(80, 80);
        label->setFrameStyle(QFrame::Box);
        label->setLineWidth(2);
        gridLayout->addWidget(label,4,i);*/
        m_boardList.append(border);
        m_boardLayout->addWidget(border);
    }

    // Définir les propriétés du layout
    /*gridLayout->setSpacing(10);
    gridLayout->setHorizontalSpacing(10);*/

    setLayout(m_boardLayout);
}

QList<BorderView*> BoardView::getBordersV() const{
    return m_boardList;
}

void BoardView::handleBorderSelected(int ID) {
    for (BorderView* border : this->getBordersV()) {
        border->getBorderButton()->setEnabled(false);
    }

    emit borderChoice(ID);
}

void BoardView::handlePlayed() {
    m_boardLayout->update();
}

void BoardView::updateBV() {
    for (BorderView* border : this->getBordersV()) {
        border->updateBoV();
    }
    m_boardLayout->update();
}
