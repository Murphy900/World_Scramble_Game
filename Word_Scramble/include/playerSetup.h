//palyerSetup.h

#ifndef PLAYERSETUP_H
#define PLAYERSETUP_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>


class PlayerSetup : public QWidget {
    Q_OBJECT

public:
    explicit PlayerSetup(QWidget* parent = nullptr);

signals:
    void setupConfirmed(const QString& playerName, const QString& dictPath);
    void backRequested();

private slots:
    void onConfirm();
    void onBrowse();

private:
    QLabel*       titleLabel;
    QLineEdit*    nameInput;
    QRadioButton* defaultDictRadio;
    QRadioButton* customDictRadio;
    QLineEdit*    dictPathInput;
    QPushButton*  browseButton;
    QPushButton*  confirmButton;
    QPushButton*  backButton;

protected:
    void paintEvent(QPaintEvent* event) override;
};

#endif
