#include "followersintersection.h"
#include "ui_followersintersection.h"

followersIntersection::followersIntersection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::followersIntersection)
{
    ui->setupUi(this);
    this->setFixedHeight(450);
    this->setFixedWidth(680);
}

followersIntersection::~followersIntersection()
{
    delete ui;
}

void followersIntersection::on_pushButton_clicked()
{
    username=ui->lineEdit->text().toStdString();
    username2=ui->lineEdit_2->text().toStdString();
    try {
        getSharedFollowers();
        getSharedFriends();
    }
    catch (std::runtime_error& e) {
        QMessageBox qmsbox;
        qmsbox.setText(QString::fromStdString(e.what()));
        qmsbox.setWindowModality(Qt::WindowModal);
        qmsbox.exec();
    }
}

void followersIntersection::getSharedFollowers()
{
    ui->textBrowser->clear();

    try {
        folUsrnms=getFollowers(username);
        folUsrnms2=getFollowers(username2);
    }
    catch (std::runtime_error& e) {
        QMessageBox qmsbox;
        qmsbox.setText(QString::fromStdString(e.what()));
        qmsbox.setWindowModality(Qt::WindowModal);
        qmsbox.exec();
    }

    for (size_t i=0; i<folUsrnms.size(); i++) {
        for (size_t j=0; j<folUsrnms2.size(); j++) {
            if (folUsrnms[i]==folUsrnms2[j]) sharedFollowers.push_back(folUsrnms[i]);
            }
        }
        for (size_t i=0; i<sharedFollowers.size(); i++) ui->textBrowser->append(sharedFollowers[i]);
    qDebug() << folUsrnms.size() << folUsrnms2.size();
}

void followersIntersection::getSharedFriends()
{
    ui->textBrowser_2->clear();

    try {
        frUsrnms=getFriends(username);
        frUsrnms2=getFriends(username2);
    }
    catch (std::runtime_error& e) {
        QMessageBox qmsbox;
        qmsbox.setText(QString::fromStdString(e.what()));
        qmsbox.setWindowModality(Qt::WindowModal);
        qmsbox.exec();
    }

    for (size_t i=0; i<frUsrnms.size(); i++) {
            for (size_t j=0; j<frUsrnms2.size(); j++) {
                if (frUsrnms[i]==frUsrnms2[j]) sharedFriends.push_back(frUsrnms[i]);
            }
        }
        for (size_t i=0; i<sharedFriends.size(); i++) ui->textBrowser_2->append(sharedFriends[i]);
}
