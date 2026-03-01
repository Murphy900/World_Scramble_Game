#include "gameWindow.h"
#include "parser.h"
#include "rand.h"
#include "gameDynamic.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPainter>
#include <QPaintEvent>
#include <QMessageBox>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>
#include <QDir>
#include <QDateTime>
#include <QMessageBox>


GameWindow::GameWindow(const std::string& playerName,
                       const std::string& dictPath,
                       int initialScore ,
                       int initialLives ,
                       QWidget* parent)
    : QWidget(parent), player(playerName), timeLeft(30)
{
    dictionary = read(dictPath);
    player.setScore(initialScore);
    player.setLife(initialLives);

    // --- HUD (punteggio + vite) ---
    hudLabel = new QLabel();
    hudLabel->setAlignment(Qt::AlignCenter);
    hudLabel->setStyleSheet("color: #E0E0E0; font-size: 16px;");

    // --- Timer ---
    timerLabel = new QLabel();
    timerLabel->setAlignment(Qt::AlignCenter);
    timerLabel->setStyleSheet("color: #E0E0E0; font-size: 14px;");

    // --- Parola mischiata ---
    scrambledLabel = new QLabel();
    scrambledLabel->setAlignment(Qt::AlignCenter);
    QFont scrambleFont;
    scrambleFont.setPointSize(36);
    scrambleFont.setBold(true);
    scrambleFont.setLetterSpacing(QFont::AbsoluteSpacing, 8);
    scrambledLabel->setFont(scrambleFont);
    scrambledLabel->setStyleSheet(R"(
        color: #FFFFFF;
        background-color: rgba(0,0,0,160);
        border-radius: 10px;
        padding: 20px 40px;
    )");

    // --- Feedback ---
    feedbackLabel = new QLabel();
    feedbackLabel->setAlignment(Qt::AlignCenter);
    QFont feedbackFont;
    feedbackFont.setPointSize(14);
    feedbackLabel->setFont(feedbackFont);
    feedbackLabel->setFixedHeight(40);

    // --- Input ---
    inputField = new QLineEdit();
    inputField->setPlaceholderText("Type your answer...");
    inputField->setStyleSheet(R"(
        QLineEdit {
            background-color: rgba(255,255,255,20);
            color: #E0E0E0;
            border: 1px solid #555;
            border-radius: 5px;
            padding: 10px;
            font-size: 18px;
        }
        QLineEdit:focus {
            border: 1px solid #AAAAAA;
        }
    )");

    // --- Bottoni ---
    guessButton = new QPushButton("Confirm");
    hintButton  = new QPushButton("Hint 💡");
    backButton  = new QPushButton("Menu");
    saveButton = new QPushButton("Save Game");

    QString btnStyle = R"(
        QPushButton {
            color: #E0E0E0;
            background: transparent;
            border: none;
            font-size: 16px;
            padding: 8px 20px;
        }
        QPushButton:hover { color: #FFFFFF; text-decoration: underline; }
        QPushButton:pressed { color: #AAAAAA; }
    )";
    guessButton->setStyleSheet(btnStyle);
    hintButton->setStyleSheet(btnStyle);
    backButton->setStyleSheet(btnStyle + "QPushButton { color: #FF5555; }");
    saveButton->setStyleSheet(btnStyle);
    
    // --- Layout ---
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(40, 20, 40, 20);
    layout->setSpacing(10);

    layout->addWidget(hudLabel);
    layout->addWidget(timerLabel);
    layout->addStretch();
    layout->addWidget(scrambledLabel, 0, Qt::AlignCenter);
    layout->addWidget(feedbackLabel);
    layout->addStretch();
    layout->addWidget(inputField);

    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnLayout->addWidget(backButton);
    btnLayout->addStretch();
    btnLayout->addWidget(saveButton);
    btnLayout->addWidget(hintButton);
    btnLayout->addWidget(guessButton);
    layout->addLayout(btnLayout);

    // --- Timer countdown ---
    countdownTimer = new QTimer(this);
    connect(countdownTimer, &QTimer::timeout, this, &GameWindow::onTimerTick);

    // --- Connessioni ---
    connect(guessButton, &QPushButton::clicked,       this, &GameWindow::onGuess);
    connect(inputField,  &QLineEdit::returnPressed,   this, &GameWindow::onGuess);
    connect(hintButton,  &QPushButton::clicked,       this, &GameWindow::onHint);
    connect(backButton,  &QPushButton::clicked,       this, &GameWindow::backToMenuRequested);
    connect(saveButton,  &QPushButton::clicked,       this, &GameWindow::saveGameRequested);

    loadNewWord();
}

void GameWindow::loadNewWord() {
    currentIndex  = word_pick(dictionary);
    scrambledWord = shuffle_word(dictionary, currentIndex);
    scrambledLabel->setText(QString::fromStdString(scrambledWord).toUpper());
    feedbackLabel->setText("");
    inputField->clear();
    inputField->setFocus();

    // Reset timer
    timeLeft = 30;
    timerLabel->setStyleSheet("color: #E0E0E0; font-size: 14px;");
    countdownTimer->start(1000);

    updateHUD();
}

void GameWindow::updateHUD() {
    QString lives = "";
    for (int i = 0; i < player.getLife(); i++) lives += "❤️ ";
    hudLabel->setText(lives + QString("   Score: %1").arg(player.getScore()));
}

void GameWindow::onTimerTick() {
    timeLeft--;
    timerLabel->setText(QString("⏱ %1s").arg(timeLeft));

    if (timeLeft <= 10)
        timerLabel->setStyleSheet("color: #FF5555; font-size: 14px;");

    if (timeLeft <= 0) {
        countdownTimer->stop();
        player.updateLife();
        updateHUD();

        if (player.getLife() == 0) {
            QMessageBox::information(this, "Game Over",
                QString("Time's up! Game Over!\nFinal Score: %1")
                    .arg(player.getScore()));
            emit backToMenuRequested();
            return;
        }

        animateFeedback("⏱ Time's up!", "#FF5555");
        QTimer::singleShot(1000, this, &GameWindow::loadNewWord);
    }
}

void GameWindow::onGuess() {
    std::string guess = inputField->text().toStdString();
    if (guess.empty()) return;

    if (guess == dictionary[currentIndex]) {
        countdownTimer->stop();
        earnedPoints(player);
        player.resetCounter();
        animateFeedback("✅ Correct!", "#55FF55");
        QTimer::singleShot(1000, this, &GameWindow::loadNewWord);
    } else {
        player.updateCounter();
        player.updateLife();
        updateHUD();

        if (player.getLife() == 0) {
            countdownTimer->stop();
            QMessageBox::information(this, "Game Over",
                QString("Game Over!\nFinal Score: %1")
                    .arg(player.getScore()));
            emit backToMenuRequested();
            return;
        }

        animateFeedback("❌ Wrong! Try again", "#FF5555");
        inputField->clear();
    }
}

void GameWindow::onHint() {
    std::string h = hint(player, dictionary[currentIndex], scrambledWord);
    animateFeedback("💡 Hint: " + QString::fromStdString(h), "#FFAA00");
}

void GameWindow::animateFeedback(const QString& text, const QString& color) {
    feedbackLabel->setText(text);
    feedbackLabel->setStyleSheet(QString("color: %1; font-size: 14px;").arg(color));

    // Animazione opacity
    QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect(feedbackLabel);
    feedbackLabel->setGraphicsEffect(effect);

    QPropertyAnimation* anim = new QPropertyAnimation(effect, "opacity");
    anim->setDuration(300);
    anim->setStartValue(0.0);
    anim->setEndValue(1.0);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void GameWindow::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    QPixmap bg("menu_background.jpg");
    painter.drawPixmap(0, 0, width(), height(), bg);
}

void GameWindow::saveGameRequested() {
    // Crea la cartella di salvataggio se non esiste
    QString saveDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(saveDir);

    // Costruisci il JSON
    QJsonObject saveData;
    saveData["playerName"] = QString::fromStdString(player.getName());
    saveData["score"]      = player.getScore();
    saveData["lives"]      = player.getLife();
    saveData["date"]       = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm");

    // Nome file basato sul nome giocatore e data
    QString fileName = saveDir + "/" +
                       QString::fromStdString(player.getName()) + "_" +
                       QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") +
                       ".json";

    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(saveData).toJson());
        file.close();
        QMessageBox::information(this, "Saved", "Game saved successfully!");
        countdownTimer->stop();
        emit backToMenuRequested();
       
    } else {
        QMessageBox::warning(this, "Error", "Could not save the game.");
    }
}
