#ifndef COMBINATIONVIEW_H
#define COMBINATIONVIEW_H

#include "Card.h"
#include "CardView.h"
#include "Combination.h"
#include <QGridLayout>

class CombinationView : public QWidget
{
    Q_OBJECT

public :
    CombinationView(QWidget *parent, Combination* combi);
    void updateCoV();
    //void updateCombination(Combination* combi);

private :
    Combination* combination;
    QGridLayout *m_combiLayout;
    QList<CardView*> m_combiList;
};
#endif // COMBINATIONVIEW_H
