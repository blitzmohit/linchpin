#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QDebug>
#include "timer.h"
#include <QTime>
#include <QtTextToSpeech/QTextToSpeech>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Timer *timekeeper= new Timer();
    connect(ui->pushButtonStart,SIGNAL(clicked()),this,SLOT(updatedval()));
    connect(ui->pushButtonStart,SIGNAL(clicked()),timekeeper,SLOT(start()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updatedval()
{
    qCritical()<<"updated val called";
    ui->pushButtonStart->setEnabled(false);
//    ui->labelTime->setText(QTime::currentTime().toString());
    QTime t = QTime::currentTime();
    int mintonextHour=60-t.toString("m").toInt();
    QTimer::singleShot(mintonextHour*60000,this,SLOT(singleFired()));

}


void MainWindow::singleFired()
{
    qCritical()<<"Entered singleFired at"+QTime::currentTime().toString();
    QTextToSpeech *qts=new QTextToSpeech();
    QVector<QVoice> availVoice=qts->availableVoices();
    qts->setVoice(availVoice.at(1));
    qts->say("It is "+QTime::currentTime().toString("HA"));
//Speak the system time
//QTextToSpeech qts=new QTextToSpeech();
//qts.say("hello");


// so now the time should be HH:00 now we have to schedule it every hour
   //handles the rescheduling
   QTimer *qt = new QTimer(this);
   connect(qt, SIGNAL(timeout()), this, SLOT(singleFired()));
   qt->start(60*60000);
}
