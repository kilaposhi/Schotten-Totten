#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include "Board.h"
#include "border/BorderView.h"

#include <QWidget>
#include <QList>
#include <QHBoxLayout>
#include <QPushButton>


class BoardView : public QWidget
{
    Q_OBJECT

public :
    BoardView(QWidget *parent, Board* border);
    QList<BorderView*> getBordersV() const;
    void updateBV();

signals :
    void borderChoice(int ID);

private slots :
    void handleBorderSelected(int ID);
    void handlePlayed();


private :
    Board* board;
    QHBoxLayout *m_boardLayout;
    QList<BorderView*> m_boardList;
};

#endif // BOARDVIEW_H
