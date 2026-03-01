//main.cpp 
// This is the main file for the Word Scramble game
// It initializes the game, loads the dictionary, and handles user input and game logic.

#include <QApplication>
#include <QStackedWidget>
#include "MainMenu.h"
#include "playerSetup.h"
#include "gameWindow.h"
#include "LoadGameWindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QStackedWidget stack;
    stack.setFixedSize(800, 500);

    MainMenu*    menu  = new MainMenu();
    PlayerSetup* setup = new PlayerSetup();
    GameWindow*  game  = nullptr;
    LoadGameWindow* loadGame = new LoadGameWindow();

    stack.addWidget(menu);   // page 0
    stack.addWidget(setup);  // page 1
    stack.addWidget(loadGame);  // pagina 2
    stack.show();

    // Menu → Setup
    QObject::connect(menu, &MainMenu::newGameRequested, [&]() {
        stack.setCurrentIndex(1);
    });

    // Setup → Menu
    QObject::connect(setup, &PlayerSetup::backRequested, [&]() {
        stack.setCurrentIndex(0);
    });

    // Setup → Game
    QObject::connect(setup, &PlayerSetup::setupConfirmed,
                     [&](const QString& name, const QString& dictPath) {
        if (game) {
            stack.removeWidget(game);
            delete game;
        }
        game = new GameWindow(name.toStdString(), dictPath.toStdString());
        stack.addWidget(game);  // pagina 3
        stack.setCurrentIndex(3);

        // Game → Menu
        QObject::connect(game, &GameWindow::backToMenuRequested, [&]() {
            stack.setCurrentIndex(0);
        });
    });

   // Menu → LoadGame
QObject::connect(menu, &MainMenu::loadNewGameRequested, [&]() {
    loadGame->loadSaveList();  // ricarica lista ogni volta che si apre
    stack.setCurrentIndex(2);
});

// LoadGame → Menu
QObject::connect(loadGame, &LoadGameWindow::backRequested, [&]() {
    stack.setCurrentIndex(0);
});

// LoadGame → Gioco
QObject::connect(loadGame, &LoadGameWindow::gameLoaded,
    [&](const QString& name, int score, int lives, const QString& dictPath) {
        if (game) {
            stack.removeWidget(game);
            delete game;
        }
        game = new GameWindow(name.toStdString(), dictPath.toStdString(), score, lives);
        stack.addWidget(game);
        stack.setCurrentIndex(3);

        QObject::connect(game, &GameWindow::backToMenuRequested, [&]() {
            stack.setCurrentIndex(0);
        });
});
    
    return app.exec();
}