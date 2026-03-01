//MainMenu.cpp


#include  "MainMenu.h"
#include <QVBoxLayout>
#include <QApplication>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>
#include <QPainter>
#include <QPaintEvent>

MainMenu::MainMenu(QWidget* parent) : QWidget(parent) {
    
    //Title 
    titleLabel = new QLabel(
    "_ _ _              _    _____                        _    _      \n"
    "  | | | | ___  ___  _| |  |   __| ___  ___  ___  _____ | |_ | | ___ \n"
    "  | | | || . ||  _|| . |  |__   ||  _||  _|| .'||     || . || || -_|\n"
    "  |_____||___||_|  |___|  |_____||___||_|  |__,||_|_|_||___||_||___|\n"
);
    QFont titleFont;
    titleFont.setFamily("Monospace");   // font monospace, or otherwise ASCII get deformed
    titleFont.setPointSize(9);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet(R"(
    color: #E0E0E0;
    background-color: rgba(0, 0, 0, 180);
    border-radius: 10px;
    padding: 10px 20px;
)");

    //Buttons 
    newGameButton = new QPushButton("New Game");
    loadGameButton = new QPushButton("Load Game");

    leaderboardButton = new QPushButton("Leaderboard");
    exitButton = new QPushButton("Exit");

    // Stile comune per tutti i bottoni
    QString buttonStyle = R"(
        QPushButton {
            color: #E0E0E0;
            background: transparent;
            border: none;
            font-size: 18px;
            padding: 10px;
        }
        QPushButton:hover {
            color: #FFFFFF;
            text-decoration: underline;
        }
        QPushButton:pressed {
            color: #AAAAAA;
        }
    )";

    newGameButton->setStyleSheet(buttonStyle);
    loadGameButton->setStyleSheet(buttonStyle);

    leaderboardButton->setStyleSheet(buttonStyle);
    exitButton->setStyleSheet(buttonStyle + "QPushButton { color: #FF5555; }");


    //Layout
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(10);

    layout->addStretch();
    layout->addWidget(titleLabel);
    layout->addSpacing(40);
    layout->addWidget(newGameButton);
    layout->addWidget(loadGameButton);

    layout->addWidget(leaderboardButton);
    layout->addSpacing(20);
    layout->addWidget(exitButton);
    layout->addStretch();

    // background
    setStyleSheet(R"(
    QLabel {
        background: transparent;
    }
    QPushButton {
        background: transparent;
    }
)");
    setFixedSize(800, 500);
    setWindowTitle("Word Scramble");


    //Connections
    connect(newGameButton, &QPushButton::clicked, this, &MainMenu::newGameRequested);
    connect(loadGameButton, &QPushButton::clicked, this, &MainMenu:: loadNewGameRequested);

    connect(leaderboardButton, &QPushButton::clicked, this, &MainMenu::leaderboardRequested);
    connect(exitButton, &QPushButton::clicked, this, &MainMenu::onExit);


    //Music
    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    player->setAudioOutput(audioOutput);
    audioOutput->setVolume(0.5);  // volume 50%
    player->setSource(QUrl::fromLocalFile("Pixel_Ponder.mp3"));
    player->setLoops(QMediaPlayer::Infinite);  // loop infinito
    player->play();
}

void MainMenu::onExit() {
    QApplication::quit();
}

void MainMenu::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    QPixmap bg("menu_background.jpg");
    painter.drawPixmap(0, 0, width(), height(), bg);
}
