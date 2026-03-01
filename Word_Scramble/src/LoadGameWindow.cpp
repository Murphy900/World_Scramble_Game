#include "LoadGameWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPainter>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>
#include <QMessageBox>

LoadGameWindow::LoadGameWindow(QWidget* parent) : QWidget(parent) {

    // --- Titolo ---
    titleLabel = new QLabel("Load Game");
    QFont titleFont;
    titleFont.setPointSize(24);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet(R"(
        color: #E0E0E0;
        background-color: rgba(0,0,0,180);
        border-radius: 10px;
        padding: 10px 20px;
    )");

    // --- Lista salvataggi ---
    saveList = new QListWidget();
    saveList->setStyleSheet(R"(
        QListWidget {
            background-color: rgba(0,0,0,160);
            color: #E0E0E0;
            border: 1px solid #555;
            border-radius: 5px;
            font-size: 14px;
            padding: 5px;
        }
        QListWidget::item {
            padding: 10px;
            border-bottom: 1px solid #333;
        }
        QListWidget::item:selected {
            background-color: rgba(255,255,255,40);
        }
        QListWidget::item:hover {
            background-color: rgba(255,255,255,20);
        }
    )");

    // --- Bottoni ---
    loadButton   = new QPushButton("Load");
    deleteButton = new QPushButton("Delete");
    backButton   = new QPushButton("Back");

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
    loadButton->setStyleSheet(btnStyle);
    deleteButton->setStyleSheet(btnStyle + "QPushButton { color: #FF5555; }");
    backButton->setStyleSheet(btnStyle + "QPushButton { color: #FF5555; }");

    // --- Layout ---
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(60, 40, 60, 40);
    layout->setSpacing(15);

    layout->addWidget(titleLabel);
    layout->addSpacing(10);
    layout->addWidget(saveList);

    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnLayout->addWidget(backButton);
    btnLayout->addStretch();
    btnLayout->addWidget(deleteButton);
    btnLayout->addWidget(loadButton);
    layout->addLayout(btnLayout);

    // --- Connessioni ---
    connect(loadButton,   &QPushButton::clicked, this, &LoadGameWindow::onLoad);
    connect(deleteButton, &QPushButton::clicked, this, &LoadGameWindow::onDelete);
    connect(backButton,   &QPushButton::clicked, this, &LoadGameWindow::backRequested);

    loadSaveList();
}

void LoadGameWindow::loadSaveList() {
    saveList->clear();

    QString saveDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(saveDir);
    QStringList files = dir.entryList(QStringList() << "*.json", QDir::Files, QDir::Time);

    if (files.isEmpty()) {
        saveList->addItem("No saved games found.");
        loadButton->setEnabled(false);
        deleteButton->setEnabled(false);
        return;
    }

    for (const QString& fileName : files) {
        QFile file(saveDir + "/" + fileName);
        if (file.open(QIODevice::ReadOnly)) {
            QJsonObject data = QJsonDocument::fromJson(file.readAll()).object();
            file.close();

            QString display = QString("%1   |   Score: %2   |   Lives: %3   |   %4")
                .arg(data["playerName"].toString())
                .arg(data["score"].toInt())
                .arg(data["lives"].toInt())
                .arg(data["date"].toString());

            QListWidgetItem* item = new QListWidgetItem(display);
            item->setData(Qt::UserRole, saveDir + "/" + fileName); // salva il path nel item
            saveList->addItem(item);
        }
    }
}

void LoadGameWindow::onLoad() {
    QListWidgetItem* selected = saveList->currentItem();
    if (!selected) {
        QMessageBox::warning(this, "Warning", "Select a save file first!");
        return;
    }

    QString filePath = selected->data(Qt::UserRole).toString();
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly)) {
        QJsonObject data = QJsonDocument::fromJson(file.readAll()).object();
        file.close();

        emit gameLoaded(
            data["playerName"].toString(),
            data["score"].toInt(),
            data["lives"].toInt(),
            "dictionary.txt"  // dizionario default, puoi salvarlo nel JSON in futuro
        );
    }
}

void LoadGameWindow::onDelete() {
    QListWidgetItem* selected = saveList->currentItem();
    if (!selected) {
        QMessageBox::warning(this, "Warning", "Select a save file first!");
        return;
    }

    QMessageBox::StandardButton reply = QMessageBox::question(this,
        "Delete", "Are you sure you want to delete this save?",
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        QString filePath = selected->data(Qt::UserRole).toString();
        QFile::remove(filePath);
        loadSaveList();  // ricarica la lista
    }
}

void LoadGameWindow::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    QPixmap bg("menu_background.jpg");
    painter.drawPixmap(0, 0, width(), height(), bg);
}