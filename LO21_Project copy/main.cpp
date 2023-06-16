#include "MainWindow/MainWindow.h"
#include <QApplication>
#include <iostream>
#include <string>
#include <QDebug>
#include "gameconfiguration/GameConfiguration.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Crée une instance de GameConfiguration
    GameConfiguration gameConfig;

    // Affiche la fenêtre modale
    gameConfig.show();

    // Exécute la boucle d'événements de l'application
    app.exec();

    // Récupère les valeurs depuis GameConfiguration
    int nbRound = gameConfig.getNbRound();
    qDebug() << nbRound << Qt::endl;

    QString player1 = gameConfig.getPlayer1();
    qDebug() << player1 << Qt::endl;

    QString player2 = gameConfig.getPlayer2();
    qDebug() << player2 << Qt::endl;

    int version = gameConfig.getVersion();
    qDebug() << "version : " << version << Qt::endl;

    bool ai = gameConfig.getAI();
    qDebug() << "AI : " << ai << Qt::endl;

    int numberCardsPlayer1 = 6;
    int numberCardsPlayer2 = 6;
    int numberBorders = 9;

    MainWindow mainWindow(nullptr, numberCardsPlayer1, numberCardsPlayer2, numberBorders, false, true, true);
    mainWindow.show();

    // Exécute la boucle d'événements de l'application
    return app.exec();
}




/*{
    QApplication app(argc, argv);

    int numberCardsPlayer1 = 6;
    int numberCardsPlayer2 = 6;
    int numberBorders = 9;

    MainWindow mainWindow(nullptr, numberCardsPlayer1, numberCardsPlayer2, numberBorders, false, true, true);
    mainWindow.show();
    return app.exec();
}*/
