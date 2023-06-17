#include "BorderView.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>


BorderView::BorderView(QWidget* parent, Border* border)
    : QWidget(parent), border(border)
{
    m_borderLayout = new QVBoxLayout(this); // Utilisez "this" comme parent pour le layout

    ID = border->getBorderId();

    combiJ1 = new CombinationView(this, border->getPlayer1Combination());
    combiJ2 = new CombinationView(this, border->getPlayer2Combination());
    m_borderLayout->addWidget(combiJ1);

    m_borderButton = new QPushButton(QString::number(ID));
    m_borderButton->setEnabled(false);
    connect(m_borderButton, &QPushButton::clicked, this, &BorderView::borderClicked);
    /*borderButton->setAlignment(Qt::AlignCenter);
    label->setFixedSize(80, 80);
    label->setFrameStyle(QFrame::Box);
    label->setLineWidth(2);*/
    //connect(m_borderButton, &QPushButton::clicked, this, &BorderView::borderClicked());

    m_borderLayout->addWidget(m_borderButton);
    m_borderLayout->addWidget(combiJ2);

    setLayout(m_borderLayout);
}

//void BorderView::borderClicked() {}

QPushButton* BorderView::getBorderButton() const {
    return m_borderButton;
}

void BorderView::borderClicked() {
    m_borderLayout->update();

    emit borderSelected(ID);

}

void BorderView::updateBoV(){
    combiJ1->updateCoV();
    combiJ2->updateCoV();
    m_borderLayout->update();
}
