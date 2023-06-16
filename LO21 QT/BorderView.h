#ifndef BORDERVIEW_H
#define BORDERVIEW_H

#include <QWidget>
#include <Border.h>
#include <QVBoxLayout>
#include <QPushButton>
#include "CombinationView.h"

class BorderView : public QWidget
{
    Q_OBJECT

public :
    BorderView(QWidget *parent, Border* border);
    QPushButton* getBorderButton() const;
    void updateBoV();

private slots :
    void borderClicked();

signals :
    void borderSelected(int ID);

private :
    Border* border;
    int ID;
    QVBoxLayout *m_borderLayout;
    QPushButton *m_borderButton;
    CombinationView* combiJ1;
    CombinationView* combiJ2;
};
#endif // BORDERVIEW_H