//
// Created by tassili on 30/05/2023.
//

#ifndef SCHOTTEN_TOTTEN_GAMEVIEW_H
#define SCHOTTEN_TOTTEN_GAMEVIEW_H
#include <QWidget>
#include <vector>

class QLabel;
class QLineEdit;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class QGridLayout;
class QProgressBar;
class QLCDNumber;
class CardView;
class GameView : public QWidget
{
    Q_OBJECT
public:
    explicit GameView(QWidget *parent = nullptr);
private:
    Set::Controleur controleur; // controleur de la partie
    QLabel* score; // texte "Score"
    QLCDNumber* scoreJoueur; // affichage du score
    QLabel* pioche; // texte "Pioche"
    QProgressBar* nbCartesPioche; // progression de la pioche
    QHBoxLayout* layoutInformations;
    QGridLayout* layoutCartes; // grille des cartes
    QVBoxLayout* couche;
    vector<VueCarte*> vuecartes; // adresses des objets VueCarte
    std::<const Card*> selectionCartes; // ensemble des cartes sélectionnées
    int scoreValue=0; // score courant (nb de sets trouvés)
private slots:
// slots qui gère les clics sur les cartes
            void carteClique(ViewCard* vc);
};

#endif //SCHOTTEN_TOTTEN_GAMEVIEW_H
