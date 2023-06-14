#ifndef BOARDVIEW_H
#define BOARDVIEW_H
#include <QGridLayout>
#include <QWidget>


class BoardView : public QWidget
{
    Q_OBJECT

public:
    BoardView(QWidget *parent);
private :
    //QList<BorderView> bord;
};

#endif // BOARDVIEW_H
