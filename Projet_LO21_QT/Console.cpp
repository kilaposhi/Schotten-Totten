#include "console.h"
#include <string>

#include <iostream>
#include <QApplication>
#include <QInputDialog>
#include <QWidget>
#include <QMessageBox>
#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

int askPlayerValue(Player* player, std::array<int,2> rangeValue){
    cout << *player << " ";
    return askValue(rangeValue);
}


bool askYesNo(const string& question)
{
    bool result = false;
    QMessageBox::StandardButton reply = QMessageBox::question(nullptr, "Confirmation", "Do you want to claim a border?", QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        result = true;
    }

    return result;
}

/*int chooseGameMode() {
    int selectedMode = 0;

    QDialog dialog;
    dialog.setWindowTitle("Choix du mode de jeu");

    QLabel *label = new QLabel("Choisissez le mode de jeu :");

    QPushButton *buttonClassic = new QPushButton("Partie Classique");
    QPushButton *buttonTactical = new QPushButton("Partie Tactique");

    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    layout->addWidget(label);
    layout->addWidget(buttonClassic);
    layout->addWidget(buttonTactical);

    QObject::connect(buttonClassic, &QPushButton::clicked, [&]() {
        selectedMode = 1;
        dialog.close();
    });

    QObject::connect(buttonTactical, &QPushButton::clicked, [&]() {
        selectedMode = 2;
        dialog.close();
    });

    dialog.setLayout(layout);
    dialog.exec();

    return selectedMode;
}*/

int chooseNumberRound(){
    int result;
    bool isValid = false;
    do {

        bool ok;
        QString input = QInputDialog::getText(nullptr, "Choix du nombre de round", QString("Choisissez le nombre de round (entre 1 et 15) :"), QLineEdit::Normal, "", &ok);
        if (ok && !input.isEmpty()) {
            bool conversionOk;
            result = input.toInt(&conversionOk);
            if (conversionOk && result >= 1 && result <= 15) {
                isValid = true;
            } else {
                QApplication::beep();
                QMessageBox::warning(nullptr, "Erreur", "Entrée incorrecte, veuillez réessayer !");
            }
        } else {
            // L'utilisateur a annulé la saisie ou fermé la boîte de dialogue
            throw std::runtime_error("Saisie annulée");
        }
    } while (!isValid);

    return result;
}

int askValue(const std::array<int, 2>& rangeValue)
{
    int result;
    bool isValid = false;
    if (rangeValue[0] > rangeValue[1])
        throw std::out_of_range("rangeValue is impossible");
    do {
        bool ok;
        QString input = QInputDialog::getText(nullptr, "Entrée utilisateur", QString("Choisissez une valeur entre %1 et %2 :").arg(rangeValue[0]).arg(rangeValue[1]), QLineEdit::Normal, "", &ok);

        if (ok && !input.isEmpty()) {
            bool conversionOk;
            result = input.toInt(&conversionOk);
            if (conversionOk && result >= rangeValue[0] && result <= rangeValue[1]) {
                isValid = true;
            } else {
                QApplication::beep();
                QMessageBox::warning(nullptr, "Erreur", "Entrée incorrecte, veuillez réessayer !");
            }
        } else {
            // L'utilisateur a annulé la saisie ou fermé la boîte de dialogue
            throw std::runtime_error("Saisie annulée");
        }
    } while (!isValid);
    return result;
}



CardColor askPlayerColor(Player* player, int numberColors){
    cout << "Here are the colors : \n";
    auto color_iterator = cardColors.begin();
    for (size_t i = 0; i < numberColors; i++){
        CardColor color = *color_iterator++;
        cout << i << " : " << cardColorToString(color) << "\t";
    }
    int color_index = askPlayerValue(player, {0, numberColors});
    CardColor result = *(cardColors.begin() + color_index);
    return result;
}
