TEMPLATE     = vcapp
TARGET       = DummyKong
CONFIG      += warn_on qt debug_and_release windows console
HEADERS     += MainWindow.h Help.h Options.h Levels.h GameWindow.h GameEngine/Game.h GameEngine/Character.h GameEngine/Level.h Tile.h Ladder.h Pauline.h
SOURCES     += MainWindow.cpp main.cpp Help.cpp Options.cpp Levels.cpp GameWindow.cpp GameEngine/Game.cpp GameEngine/Character.cpp GameEngine/Level.cpp Tile.cpp Ladder.cpp Pauline.cpp
INCLUDEPATH += .
LIBS	      += 
QT += core gui  widgets  multimedia
