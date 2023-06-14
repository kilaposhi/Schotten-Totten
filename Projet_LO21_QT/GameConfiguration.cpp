#include "GameConfiguration.h"
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QApplication>
#include <QMessageBox>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>


GameConfiguration::GameConfiguration(QWidget *parent) : QWidget(parent) {
    QCheckBox *mode = new QCheckBox("Tactic mode");

    QLabel *scotland = new QLabel("The one who traveled near Scotland the most recently is Player 1");

    QLabel *play1 = new QLabel("Player 1 :");
    QLineEdit *p1 = new QLineEdit(this);
    QHBoxLayout *n1 = new QHBoxLayout;
    n1->addWidget(play1);
    n1->addWidget(p1);

    QLabel *play2 = new QLabel("Player 2 :");
    QLineEdit *p2 = new QLineEdit(this);
    QHBoxLayout *n2 = new QHBoxLayout;
    n1->addWidget(play2);
    n1->addWidget(p2);

    QLabel *roundLabel = new QLabel("Nombre de round", this);

    QSpinBox *round = new QSpinBox(this);
    round->setMaximum(15);
    round->setMinimum(1);
    QHBoxLayout *r = new QHBoxLayout;
    r->addWidget(roundLabel);
    r->addWidget(round);

    QPushButton *button = new QPushButton("Ok", this);

    QVBoxLayout *verti = new QVBoxLayout;
    verti->addWidget(mode);
    verti->addWidget(scotland);
    verti->addLayout(n1);
    verti->addLayout(n2);
    verti->addLayout(r);
    verti->addWidget(button);


    connect(button, &QPushButton::clicked, this, [=]() {
        if (p1->text().isEmpty() || p2->text().isEmpty())
        {
            QMessageBox::warning(this, "Champs obligatoires", "Please fill in the name of both players.");
            return;
        }
        nbRound = round->value() ;
        player1 = p1->text();
        player2 = p2->text();
        tactic = mode->isChecked();
        close();});

    setLayout(verti);
}

int GameConfiguration::getNbRoud(){
    return nbRound;
}

QString GameConfiguration::getPlayer1(){
    return player1;
}

QString GameConfiguration::getPlayer2(){
    return player2;
}

bool GameConfiguration::getTactic() {
    return tactic;
}

/*void GameConfiguration::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);

    CenterOnScreen();
}
*/
/*void GameConfiguration::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QBrush background(QColor(23, 23, 34));

    painter.setBrush(background);
    painter.setPen  (Qt::NoPen ); // No stroke

    painter.drawRect(0, 0, width(), height());
}

bool GameConfiguration::chooseGameMode(){
    bool tactic = false;


    QLabel *label = new QLabel("Choisissez le mode de jeu :");

    QPushButton *buttonClassic = new QPushButton("Partie Classique");
    QPushButton *buttonTactical = new QPushButton("Partie Tactique");

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(label);
    layout->addWidget(buttonClassic);
    layout->addWidget(buttonTactical);

    QObject::connect(buttonClassic, &QPushButton::clicked, [&]() {
        tactic = false;
    });

    QObject::connect(buttonTactical, &QPushButton::clicked, [&]() {
        tactic = true;
    });

    return tactic;
}
int GameConfiguration::chooseNumberRound(){

    return nbRound->value();
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
}*/
