#ifndef LOADGAMEWINDOW_H
#define LOADGAMEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>

class LoadGameWindow : public QWidget {
    Q_OBJECT

public:
    explicit LoadGameWindow(QWidget* parent = nullptr);
    void loadSaveList();

signals:
    void gameLoaded(const QString& playerName, int score, int lives, const QString& dictPath);
    void backRequested();

private slots:
    void onLoad();
    void onDelete();

private:
   
    void paintEvent(QPaintEvent* event) override;

    QLabel*       titleLabel;
    QListWidget*  saveList;      // lista dei salvataggi
    QPushButton*  loadButton;
    QPushButton*  deleteButton;
    QPushButton*  backButton;
};

#endif