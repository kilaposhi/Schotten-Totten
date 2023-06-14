#include "boardview.h"
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


BoardView::BoardView(QWidget *parent=nullptr) : QWidget(parent){
    // Création des boutons et ajout au layout
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 9; ++col) {
            QPushButton *button = new QPushButton(QString("Bouton %1-%2").arg(row).arg(col), this);
            combiJ1->addWidget(button, row, col);
            button->setEnabled(false);
        }
    }

    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 9; ++col) {
            QPushButton *button = new QPushButton(QString("Bouton %1-%2").arg(row).arg(col), this);
            combiJ2->addWidget(button, row, col);
            button->setEnabled(false);
        }
    }
    setLayout(combiJ2);


    for (int i = 1; i <= 9; ++i) {
        QPushButton *border = new QPushButton(QString::number(i));
        border->setEnabled(false);
        border->setFixedSize(80, 80);
        border->setStyleSheet("QPushButton {"
                              "  border: 2px solid black;"
                              "  border-radius: 5px;"
                              "}"
                              "QPushButton:pressed {"
                              "  background-color: lightGray;"
                              "}");
        board->addWidget(border,4,i);
    }


    QVBoxLayout *bord = new QVBoxLayout;
    bord->addLayout(combiJ1);
    bord->addLayout(bord);
    bord->addLayout(combiJ2);

    setLayout(bord);
}
