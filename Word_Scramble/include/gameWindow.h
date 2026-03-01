#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTimer>
#include <QPropertyAnimation>
#include <vector>
#include <string>
#include "player.h"

class GameWindow : public QWidget {
    Q_OBJECT



public:
    explicit GameWindow(const std::string&PlayerName, const std::string&dictPath, int score = 0, int life = 3,
                QWidget* parent = nullptr );

signals:
    void backToMenuRequested();

private slots:
    void onGuess();
    void onHint();
    void onTimerTick();

private:
    void loadNewWord();
    void updateHUD();
    void animateFeedback(const QString& text, const QString& color);
    void paintEvent(QPaintEvent* event) override;
    void saveGameRequested();

    // Logica di gioco
    Player player;
    std::vector<std::string> dictionary;
    int currentIndex;
    std::string scrambledWord;
    int timeLeft;

    // Widget Qt
    QLabel*      hudLabel;        // punteggio + vite
    QLabel*      scrambledLabel;  // parola mischiata
    QLabel*      feedbackLabel;   // corretto/sbagliato
    QLabel*      timerLabel;      // timer
    QLineEdit*   inputField;
    QPushButton* guessButton;
    QPushButton* hintButton;
    QPushButton* backButton;
    QPushButton* saveButton;

    // Timer
    QTimer* countdownTimer;

};
#endif
