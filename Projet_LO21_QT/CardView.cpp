#include <CardView.h>
#include <Card.h>


CardView::CardView(QWidget *parent, ValuedCard card) : QPushButton(parent) {
    int value = card.getValue();
    QString color = QString::fromStdString(cardColorToString(card.getColor()));
    QString text = QString::number(value) + " " + color;

    setText(text);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    setEnabled(false);
}

CardView::CardView(QWidget *parent, TacticCard card) : QPushButton(parent) {
    QString name = QString::fromStdString(tacticTypeToString(card.getName()));
    QString text = name;

    setText(text);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    setEnabled(false);
}
