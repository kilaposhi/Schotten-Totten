//
// Created by tassili on 30/05/2023.
//
//NON EXPLOITABLE SANS VIEW CARD

#include "GameVIew.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QProgressBar>
#include <QLCDNumber>
#include <QString>
#include <QMessageBox>
#include "GameView.h"
#include "CardView.h"

VuePartie::VuePartie(QWidget *parent) : QWidget(parent), vuecartes(20,nullptr)
{
    setWindowTitle(" SchottenTotten");
    controleur.distribuer();

    deck = new QLabel("Deck");
    score = new QLabel("Score");
    // barre de progression de la pioche
    nbCartesPioche = new QProgressBar;
    nbCartesPioche->setRange(0,
                             Set::Jeu::getInstance().getNbCartes());
    nbCartesPioche->setValue(controleur.getPioche().getNbCartes());
    nbCartesPioche->setFixedHeight(30);
    nbCartesPioche->setTextVisible(false);

    scoreJoueur = new QLCDNumber;
    scoreJoueur->display(0);
    scoreJoueur->setFixedHeight(30);

    layoutInformations = new QHBoxLayout;

    layoutInformations->addWidget(pioche);
    layoutInformations->addWidget(nbCartesPioche);
    layoutInformations->addWidget(score);
    layoutInformations->addWidget(scoreJoueur);

    // création des vues des cartes
    for(size_t i = 0 ; i < 20 ; i++) vuecartes[i] = new VueCarte;
    layoutCartes = new QGridLayout;
    for(size_t i = 0 ; i < 20 ; i++) {
        layoutCartes->addWidget(vuecartes[i], i/4, i%4);
        connect(vuecartes[i], SIGNAL(carteClicked(VueCarte*)),
                this, SLOT(carteClique(VueCarte*)));
    }

    size_t i = 0;
    for(auto it = controleur.getPlateau().begin() ;
        it != controleur.getPlateau().end() ;
        ++it) {
        vuecartes[i]->setCarte(*it);
        i++;
    }

    couche = new QVBoxLayout;
    couche->addLayout(layoutInformations);
    couche->addLayout(layoutCartes);
    setLayout(couche);
}

void VuePartie::carteClique(VueCarte* vc){
    if(!vc->cartePresente()) {
        // Ajouter une carte
        if(controleur.getPioche().getNbCartes()==0) {
            QMessageBox message(QMessageBox::Icon::Warning,
                                "Attention", "La pioche est vide");
            message.exec();
        }
        controleur.distribuer(); // ajout d'une carte
        // mise à jour des vue cartes
        size_t i = 0;
        for(auto it = controleur.getPlateau().begin() ;
            it != controleur.getPlateau().end() ;
            ++it) {
            vuecartes[i]->setCarte(*it);
            i++;
        }
        nbCartesPioche->setValue(controleur.getPioche().getNbCartes());
    }
    else {
        if(vc->isChecked()) {
            // ajouter carte au set
            selectionCartes.insert(&vc->getCarte()); // insertion dans les cartes sélectionnées
            if(selectionCartes.size() == 3) {
                std::vector<const Set::Carte*> c(selectionCartes.begin(), selectionCartes.end());
                Set::Combinaison comb(*c[0], *c[1], *c[2]);
                if(comb.estUnSET()) {
                    // c'est un set -> il faut mettre à jour le plateau
                    // Retirer les cartes du plateau
                    controleur.getPlateau().retirer(*c[0]);
                    controleur.getPlateau().retirer(*c[1]);
                    controleur.getPlateau().retirer(*c[2]);
                    selectionCartes.clear();
                    if(controleur.getPlateau().getNbCartes() < 12)
                        controleur.distribuer();
                    // Mise à jour du score
                    scoreValue++;
                    scoreJoueur->display(scoreValue);
                    // Mise à jour des vues carte
                    // Nettoyage des vues carte
                    for(size_t i = 0 ; i < vuecartes.size() ; i++)
                        vuecartes[i]->setNoCarte();
                    // Réaffichage des cartes du plateau
                    size_t i = 0;
                    for(auto it = controleur.getPlateau().begin() ;
                        it != controleur.getPlateau().end() ;
                        ++it) {
                        vuecartes[i]->setCarte(*it);
                        i++;
                    }
                    nbCartesPioche->setValue(controleur.getPioche().getNbCartes());
                }
                else { // ce n'est pas un SET!
                    QMessageBox message(QMessageBox::Icon::Warning,
                                        "Attention","Ce n'est pas un SET!");
                    message.exec();
                    // déselection des cartes
                    for(size_t i = 0 ; i < vuecartes.size(); i++)
                        vuecartes[i]->setChecked(false);
                    selectionCartes.clear();
                }
            }
        }
        else {
            // la carte cliquée est déselectionnée
            selectionCartes.erase(&vc->getCarte());
        }
    }
    update();
}

