#include "BorderButton.h"

#include <QWidget>
#include <QDebug>

BorderButton::BorderButton(QWidget* parent)
    : QPushButton(parent)
{
    setText("Border Button");
}

BorderButton::~BorderButton(){

}
