#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent, int numberCardsPlayer1, int numberCardsPlayer2, int numberBorders, bool cardPlayer1Enable, bool cardPlayer2Enable, bool borderEnable)
    : QMainWindow(parent)
{
    setWindowTitle("Schotten-Totten");

    // Créer le widget principal
    mainWidget = new QWidget(this);

    // Créer les layouts horizontaux
    hCardPlayer1Layout = new QHBoxLayout;
    hCardPlayer2Layout = new QHBoxLayout;
    hBorderLayout = new QHBoxLayout;

    // Ajouter les layouts au layout vertical principal
    vBoxLayout = new QVBoxLayout(mainWidget);
    vBoxLayout->addLayout(hCardPlayer1Layout);
    vBoxLayout->addLayout(hBorderLayout);
    vBoxLayout->addLayout(hCardPlayer2Layout);

    // Configurer le widget principal avec le layout vertical
    mainWidget->setLayout(vBoxLayout);

    createBorderButtons(mainWidget, numberBorders, hBorderLayout, borderEnable);

    createCardButtons(mainWidget, numberCardsPlayer1, hCardPlayer1Layout, cardPlayer1Enable);

    createCardButtons(mainWidget, numberCardsPlayer2, hCardPlayer2Layout, cardPlayer2Enable);

    // Définir la taille de la fenêtre
    int windowWidth = 800;
    int windowHeight = 600;
    resize(windowWidth, windowHeight);

    // Définir le widget principal comme widget central
    setCentralWidget(mainWidget);
}


void MainWindow::createCardButtons(QWidget* parent, int numCards, QHBoxLayout* layout, bool enable)
{
    for (int i = 0; i < numCards; i++) {
        CardButton* cardBtn = new CardButton(parent, "bleu");
        cardBtn->setEnabled(enable);
        listCardButton.append(cardBtn);
        layout->addWidget(cardBtn);
    }
}

void MainWindow::createBorderButtons(QWidget* parent, int numBorders, QHBoxLayout* layout, bool enable)
{
    for (int i = 0; i < numBorders; i++) {
        BorderButton* borderBtn = new BorderButton(mainWidget);
        borderBtn->setEnabled(enable);
        listBorderButton.append(borderBtn);
        hBorderLayout->addWidget(borderBtn);
    }
}

