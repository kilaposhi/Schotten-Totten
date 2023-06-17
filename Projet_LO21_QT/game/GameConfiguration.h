#ifndef GAMECONFIGURATION_H
#define GAMECONFIGURATION_H

#include <QWidget>
#include <QGridLayout>
#include <QString>

class GameConfiguration : public QWidget
{
    Q_OBJECT

public:
    GameConfiguration(QWidget *parent = nullptr);
    int getNbRound();
    bool getVersion();
    bool getExpert();
    bool getAI();
    QString getPlayer1();
    QString getPlayer2();

protected:
           //void showEvent(QShowEvent *event);

private:
    int nbRound;
    bool version;
    bool expert;
    bool AI;
    QString player1;
    QString player2;
    void HandleOk();

    /*void paintEvent(QPaintEvent *event);
    void CenterOnScreen();
    QGridLayout MainLayout;*/
};


#endif // GAMECONFIGURATION_H
