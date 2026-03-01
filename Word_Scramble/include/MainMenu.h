//MainMenu.h

#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMediaPlayer>
#include <QAudioOutput>


class MainMenu : public QWidget {
    Q_OBJECT

public:
    explicit MainMenu(QWidget* parent = nullptr);

signals:
    void newGameRequested();
    void loadNewGameRequested();

    void leaderboardRequested();

private slots:
    void onExit();

private:
    QLabel*      titleLabel;
    QPushButton* newGameButton;
    QPushButton* loadGameButton;

    QPushButton* leaderboardButton;
    QPushButton* exitButton;
    QMediaPlayer* player;    
    QAudioOutput* audioOutput; 

protected:
    void paintEvent(QPaintEvent* event) override;
};

#endif
