TEMPLATE     = vcapp
TARGET       = DummyKong
CONFIG      += warn_on qt debug_and_release windows console
HEADERS     += MainWindow.h Help.h Options.h Levels.h GameWindow.h GameEngine/Game.h GameEngine/Barrel.h GameEngine/Character.h GameEngine/Hammer.h GameEngine/Level.h GameEngine/Movement.h GameEngine/timer.h GameEngine/Tool.h GameEngine/XController.h
SOURCES     += MainWindow.cpp main.cpp Help.cpp Options.cpp Levels.cpp GameWindow.cpp GameEngine/Game.cpp GameEngine/Barrel.cpp GameEngine/Character.cpp GameEngine/Hammer.cpp GameEngine/Level.cpp GameEngine/Movement.cpp GameEngine/timer.cpp GameEngine/Tool.cpp GameEngine/XController.cpp
INCLUDEPATH += .
LIBS	      += 
QT += widgets
