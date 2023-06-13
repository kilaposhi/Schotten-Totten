#ifndef CARDVIEW_H
#define CARDVIEW_H

#include <QWidget>
#include <QPen>
#include <QBrush>
#include <QPushButton>

#include "deck/Card.h"


class CardView : public QPushButton
{
    Q_OBJECT
public:
    CardView(const Card& c, QWidget* parent = nullptr);
    explicit CardView(QWidget* parent = nullptr);

    void setCard(const Card& c);

    void setNoCard();
    const Card& getCard() const;
    bool presentCard() const;

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    const Card* card = nullptr;
    QPen pen;
    QBrush brush;

signals:
    void cardClicked(CardView*);

public slots:
private slots:
    void clickedEvent();
};

#endif // CARDVIEW_H
