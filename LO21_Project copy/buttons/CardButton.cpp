#include "CardButton.h"

#include <QWidget>
#include <QDebug>
#include <QString>

CardButton::CardButton(QWidget* parent, const QString& text)
    : QPushButton(parent)
{
    setText(text);
}

CardButton::~CardButton(){

}
