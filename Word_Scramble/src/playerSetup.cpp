

#include "playerSetup.h"
#include <QVBoxLayout>
#include <QApplication>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QPainter>
PlayerSetup:: PlayerSetup(QWidget* parent) : QWidget(parent) {
  titleLabel =  new QLabel("New Game");
  
  //window title
  QFont titleFont;
  titleFont.setPointSize(24);
  titleFont.setBold(true);
  titleLabel->setFont(titleFont);
  titleLabel->setAlignment(Qt::AlignCenter);
  titleLabel->setStyleSheet("color: #E0E0E0;");

   //input name 
  QLabel* nameLabel = new QLabel("Player Name:");
    nameLabel->setStyleSheet("color: #E0E0E0; font-size: 14px;");
    nameInput = new QLineEdit();
    nameInput->setPlaceholderText("Enter your name...");
    nameInput->setStyleSheet(R"(
        QLineEdit {
            background-color: rgba(255,255,255,20);
            color: #E0E0E0;
            border: 1px solid #555;
            border-radius: 5px;
            padding: 8px;
            font-size: 14px;
        }
        QLineEdit:focus {
            border: 1px solid #AAAAAA;
        }
    )");

    // --- Dizionario ---
    QLabel* dictLabel = new QLabel("Dictionary:");
    dictLabel->setStyleSheet("color: #E0E0E0; font-size: 14px;");

    defaultDictRadio = new QRadioButton("Default dictionary");
    customDictRadio  = new QRadioButton("Custom dictionary");
    defaultDictRadio->setChecked(true);
    defaultDictRadio->setStyleSheet("color: #E0E0E0; font-size: 13px;");
    customDictRadio->setStyleSheet("color: #E0E0E0; font-size: 13px;");

    dictPathInput = new QLineEdit();
    dictPathInput->setPlaceholderText("Path to dictionary file...");
    dictPathInput->setEnabled(false);
    dictPathInput->setStyleSheet(R"(
        QLineEdit {
            background-color: rgba(255,255,255,10);
            color: #888;
            border: 1px solid #444;
            border-radius: 5px;
            padding: 8px;
            font-size: 13px;
        }
        QLineEdit:enabled {
            background-color: rgba(255,255,255,20);
            color: #E0E0E0;
            border: 1px solid #555;
        }
    )");

    browseButton = new QPushButton("Browse...");
    browseButton->setEnabled(false);
    browseButton->setStyleSheet(R"(
        QPushButton {
            color: #E0E0E0;
            background: rgba(255,255,255,20);
            border: 1px solid #555;
            border-radius: 5px;
            padding: 8px 16px;
            font-size: 13px;
        }
        QPushButton:hover { background: rgba(255,255,255,40); }
        QPushButton:disabled { color: #555; border-color: #333; }
    )");

    // Abilita/disabilita campo dizionario custom
    connect(customDictRadio, &QRadioButton::toggled, dictPathInput, &QLineEdit::setEnabled);
    connect(customDictRadio, &QRadioButton::toggled, browseButton,  &QPushButton::setEnabled);

    // --- Bottoni ---
    confirmButton = new QPushButton("Start Game");
    backButton    = new QPushButton("Back");

    QString btnStyle = R"(
        QPushButton {
            color: #E0E0E0;
            background: transparent;
            border: none;
            font-size: 16px;
            padding: 10px;
        }
        QPushButton:hover { color: #FFFFFF; text-decoration: underline; }
        QPushButton:pressed { color: #AAAAAA; }
    )";
    confirmButton->setStyleSheet(btnStyle);
    backButton->setStyleSheet(btnStyle + "QPushButton { color: #FF5555; }");

    // --- Layout ---
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(60, 40, 60, 40);
    layout->setSpacing(15);

    layout->addWidget(titleLabel);
    layout->addSpacing(20);
    layout->addWidget(nameLabel);
    layout->addWidget(nameInput);
    layout->addSpacing(10);
    layout->addWidget(dictLabel);
    layout->addWidget(defaultDictRadio);
    layout->addWidget(customDictRadio);

    QHBoxLayout* pathLayout = new QHBoxLayout();
    pathLayout->addWidget(dictPathInput);
    pathLayout->addWidget(browseButton);
    layout->addLayout(pathLayout);

    layout->addStretch();
    layout->addWidget(confirmButton);
    layout->addWidget(backButton);

    setStyleSheet("background-color: #1E1E2E;");

    // --- Connessioni ---
    connect(confirmButton, &QPushButton::clicked, this, &PlayerSetup::onConfirm);
    connect(backButton,    &QPushButton::clicked, this, &PlayerSetup::backRequested);
    connect(browseButton,  &QPushButton::clicked, this, &PlayerSetup::onBrowse);
}

void PlayerSetup::onConfirm() {
    QString name = nameInput->text().trimmed();
    if (name.isEmpty()) {
        nameInput->setPlaceholderText("⚠ Enter your name!");
        return;
    }

    QString dictPath = defaultDictRadio->isChecked()
                       ? "dictionary.txt"
                       : dictPathInput->text();

    emit setupConfirmed(name, dictPath);
}

void PlayerSetup::onBrowse() {
    QString path = QFileDialog::getOpenFileName(this,
        "Select Dictionary", "", "Text Files (*.txt)");
    if (!path.isEmpty())
        dictPathInput->setText(path);
}

void PlayerSetup::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    QPixmap bg("menu_background.jpg");
    painter.drawPixmap(0, 0, width(), height(), bg);
}
