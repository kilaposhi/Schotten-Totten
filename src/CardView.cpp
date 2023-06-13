#include "CardView.h"

#include <QPainter>
#include <QString>
#include <QStaticText>


CardView::CardView(const Card& c, QWidget* parent) : QPushButton(parent), card(&c){
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    setFixedSize(120,200);
    connect(this,SIGNAL(clicked()), this, SLOT(clickedEvent()));
    setCheckable(true);
}


CardView::CardView(QWidget* parent) : QPushButton(parent){
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    setFixedSize(120,200);
    connect(this,SIGNAL(clicked()), this, SLOT(clickedEvent()));
    setCheckable(true);
}


void CardView::setCard(const Card& c){
    setCheckable(true);
    setChecked(false);
    card = &c;
    update();
}


void CardView::setNoCard(){
    setCheckable(false);
    update();
}


const Card& CardView::getCard() const{
    return *card;
}


bool CardView::presentCard() const{
    return card!=nullptr;
}


void CardView::clickedEvent(){
    emit cardClicked(this);
}


void VueCarte::paintEvent(QPaintEvent * /* event */)
{
    const QPoint pointsTriangle[3] = {
        QPoint(50, 0),
        QPoint(100, 50),
        QPoint(0, 50),
    };
    const QPoint pointsCercle[22] = {
        QPoint(10, 0),
        QPoint(30, 0),
        QPoint(40, 10),
        QPoint(40, 30),
        QPoint(30, 40),
        QPoint(10, 40),
        QPoint(0, 30),
        QPoint(0, 10),
        QPoint(10, 0),
        QPoint(30, 0),
        QPoint(40, 10),
        QPoint(40, 30),
        QPoint(30, 40),
        QPoint(10, 40),
        QPoint(0, 30),
        QPoint(0, 10),
        QPoint(5, 5),
        QPoint(5, 35),
        QPoint(35, 35),
        QPoint(35, 5),
        QPoint(5, 5),
    };

    QRect rect(0, 0, 100, 40);
    QPainter painter(this);

    // Rectangle autour de la carte
    pen.setColor(QColor("gray"));
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(3);
    painter.setPen(pen);
    painter.drawRect(QRect(2, 2, width() - 2, height() - 2));

    if (carte == nullptr) {
        painter.drawText(QRect(15, 50, 100, 60), Qt::AlignCenter, tr("Cliquez\npour ajouter\nune carte"));
        return;
    }

    // Couleurs des formes
    switch (carte->getCouleur()) {
    case Set::Couleur::rouge:
        pen.setColor(QColor("red"));
        brush.setColor(QColor("red"));
        break;
    case Set::Couleur::bleu:
        pen.setColor(QColor("blue"));
        brush.setColor(QColor("blue"));
        break;
    case Set::Couleur::vert:
        pen.setColor(QColor("green"));
        brush.setColor(QColor("green"));
        break;
    }

    // Remplissage
    switch (carte->getRemplissage()) {
    case Set::Remplissage::vide:
        brush.setStyle(Qt::NoBrush);
        break;
    case Set::Remplissage::plein:
        brush.setStyle(Qt::SolidPattern);
        break;
    case Set::Remplissage::hachure:
        brush.setStyle(Qt::Dense2Pattern);
        break;
    }

    pen.setWidth(2);
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.setRenderHint(QPainter::Antialiasing, true);

    int coeffTranslation;
    int debutY;
    switch (carte->getNombre()) {
    case Set::Nombre::un:
        debutY = 75;
        coeffTranslation = 100;
        break;
    case Set::Nombre::deux:
        debutY = 35;
        coeffTranslation = 90;
        break;
    case Set::Nombre::trois:
        debutY = 20;
        coeffTranslation = 60;
        break;
    }
    for (size_t i = 0; i < static_cast<size_t>(carte->getNombre()); i++) {
        painter.save();
        painter.translate(10, coeffTranslation * i + debutY);
        switch (carte->getForme()) {
        case Set::Forme::triangle:
            painter.drawPolygon(pointsTriangle, 3);
            break;
        case Set::Forme::cercle:
            painter.drawPolygon(pointsCercle, 22);
            break;
        case Set::Forme::rectangle:
            painter.drawRect(rect);
            break;
        }
        painter.restore();
    }

    if (isChecked()) {
        // Si la carte est sélectionnée, on ajoute une bordure noire
        pen.setColor(QColor("black"));
        pen.setStyle(Qt::SolidLine);
        pen.setWidth(3);
        painter.setPen(pen);
        painter.drawRect(QRect(2, 2, width() - 2, height() - 2));
    }
}


