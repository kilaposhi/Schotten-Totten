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
#include <QRadioButton>
#include <QGroupBox>


GameConfiguration::GameConfiguration(QWidget *parent) : QWidget(parent) {
    QRadioButton* radio1_ = new QRadioButton(tr("Classic mode"));
    QRadioButton* radio2_ = new QRadioButton(tr("Tactic mode"));

    radio1_->setChecked(true);

    QCheckBox* expert_ = new QCheckBox("Play in expert mode");
    QCheckBox* ai_ = new QCheckBox("Playing against AI");

    QHBoxLayout *n1 = new QHBoxLayout;
    n1->addWidget(radio1_);
    n1->addWidget(radio2_);
    n1->addWidget(expert_);
    n1->addWidget(ai_);

    QLabel *scotland = new QLabel("The one who traveled near Scotland the most recently is Player 1");

    QLabel *play1 = new QLabel("Player 1 :");
    QLineEdit *p1 = new QLineEdit(this);
    QHBoxLayout *n2 = new QHBoxLayout;
    n2->addWidget(play1);
    n2->addWidget(p1);

    QLabel *play2 = new QLabel("Player 2 :");
    QLineEdit *p2 = new QLineEdit(this);
    n2->addWidget(play2);
    n2->addWidget(p2);

    QLabel *roundLabel = new QLabel("Nombre de round", this);

    QSpinBox *round = new QSpinBox(this);
    round->setMaximum(15);
    round->setMinimum(1);
    QHBoxLayout *r = new QHBoxLayout;
    r->addWidget(roundLabel);
    r->addWidget(round);

    QPushButton *button = new QPushButton("Ok", this);

    QVBoxLayout *verti = new QVBoxLayout;
    verti->addLayout(n1);
    verti->addWidget(scotland);
    verti->addLayout(n2);
    verti->addLayout(r);
    verti->addWidget(button);


    connect(button, &QPushButton::clicked, this, [=]() {
        if (p1->text().isEmpty() || (!AI && p2->text().isEmpty()))
        {
            QMessageBox::warning(this, "Champs obligatoires", "Please fill in the name of both players.");
            return;
        }
        nbRound = round->value() ;
        player1 = p1->text();
        player2 = p2->text();

        version = !(radio1_->isChecked());
        expert = expert_->isChecked();
        AI = ai_->isChecked();
        close();});

    setLayout(verti);
}

int GameConfiguration::getNbRound(){
    return nbRound;
}

QString GameConfiguration::getPlayer1(){
    return player1;
}

QString GameConfiguration::getPlayer2(){
    return player2;
}

bool GameConfiguration::getVersion(){
    return version;
}

bool GameConfiguration::getExpert() {
    return expert;
}

bool GameConfiguration::getAI(){
    return AI;
}
