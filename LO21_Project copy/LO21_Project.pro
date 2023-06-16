QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    board/Board.cpp \
    board/Border.cpp \
    board/Combination.cpp \
    board/GameTracker.cpp \
    buttons/BorderButton.cpp \
    buttons/CardButton.cpp \
    console/console.cpp \
    deck/Card.cpp \
    deck/Deck.cpp \
    deck/DeckFactory.cpp \
    game/Game.cpp \
    gameconfiguration/GameConfiguration.cpp \
    mainwindow/MainWindow.cpp \
    player/Player.cpp \
    player/TacticHandler.cpp \
    main.cpp

HEADERS += \
    board/Board.h \
    board/Border.h \
    board/Combination.h \
    board/GameTracker.h \
    buttons/BorderButton.h \
    buttons/CardButton.h \
    console/console.h \
    deck/Card.h \
    deck/Deck.h \
    deck/DeckFactory.h \
    game/Game.h \
    gameconfiguration/GameConfiguration.h \
    mainwindow/MainWindow.h \
    player/Player.h \
    player/TacticHandler.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
