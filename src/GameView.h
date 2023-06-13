#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QWidget>
#include <vector>
#include <set>

#include "deck/Card.h"

class QLabel;
class QLineEdit;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class QGridLayout;
class QProgressBar;
class QLCDNumber;

class CardView;

class GameView : public QWidget{
    Q_OBJECT

public:
    explicit GameView(QWidget* parent = nullptr);

private:
    QLabel* scoreLabel; // texte "Score"
    QLCDNumber* scoreDisplayer; // affichage du score

    QLabel* deckLabel; // texte "Pioche"
    QProgressBar* numberCardsDeckProgressBar; // progression de la pioche

    QHBoxLayout* informationsHeaderLayout;
    QGridLayout* cardsGridLayout; // grille des cartes
    QVBoxLayout* layer;

    std::vector<CardView*> cardsView; // adresses des objets VueCarte
    std::set<const Card*> selectedCards; // ensemble des cartes sélectionnées
    int userScore=0; // score courant (nb de sets trouvés)

    void updateVueCards();
    void showWarning(const char* message);

private slots:
    // slots qui gère les clics sur les cartes
    void onCardClicked(CardView* vc);

};

#endif // GAMEVIEW_H
