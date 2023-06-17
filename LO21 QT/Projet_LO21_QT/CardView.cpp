#include <CardView.h>
#include <Card.h>
#include <QPushButton>

CardView::CardView(QWidget* parent, Card* card)
    : QPushButton(parent)
{
    // Vérifier si la carte est une TacticCard
    TacticCard* tacticCard = dynamic_cast<TacticCard*>(card);
    if (tacticCard) {

        name = QString::fromStdString(tacticTypeToString(tacticCard->getName()));

        setText(name);
    }

    // Vérifier si la carte est une ValuedCard
    ValuedCard* valuedCard = dynamic_cast<ValuedCard*>(card);
    if (valuedCard) {
        value = valuedCard->getValue();
        color = QString::fromStdString(cardColorToString(valuedCard->getColor()));
        QString text = QString::number(value) + " " + color;

        setText(text);
    }

    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    setEnabled(false);
}


/*CardView& CardView::operator=(CardView&& other)
{
    if (this != &other) {
        QPushButton::operator=(std::move(other));
        tactic = other.tactic;
        name = std::move(other.name);
        // Copiez les autres membres de données de l'objet source dans l'objet cible
    }
    return *this;
}

CardView::CardView(CardView&& other)
    : QPushButton(std::move(other)), tactic(other.tactic), name(std::move(other.name))
{*/

