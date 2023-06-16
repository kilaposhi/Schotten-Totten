#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "buttons/CardButton.h"
#include "buttons/BorderButton.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent, int numberCardsPlayer1, int numberCardsPlayer2, int numberBorders, bool cardPlayer1Enable, bool cardPlayer2Enable, bool borderEnable);
    ~MainWindow() = default;
    void createCardButtons(QWidget* parent, int numCards, QHBoxLayout* layout, bool enable);
    void createBorderButtons(QWidget* parent, int numBorder, QHBoxLayout* layout, bool enable);

private:

    QList<BorderButton*> listBorderButton;
    QList<CardButton*> listCardButton;


    QHBoxLayout* hCardPlayer1Layout;
    QHBoxLayout* hCardPlayer2Layout;
    QHBoxLayout* hBorderLayout;
    QVBoxLayout* vBoxLayout;


    QWidget* mainWidget;

};


#endif // MAINWINDOW_H
