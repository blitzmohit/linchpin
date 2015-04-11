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
    connect(ui->pushButtonStart,SIGNAL(clicked()),this,SLOT(startTime()));
//    connect(ui->pushButtonStart,SIGNAL(clicked()),timekeeper,SLOT(start()));

   }

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startTime()
{
    qCritical()<<"updated val called";
    ui->pushButtonStart->setEnabled(false);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start(1000);
    QTime *t = new QTime(0,25,0);
    ui->labelTime->setText(t->toString("mm:ss"));
    /*        QTime currTime=QTime::currentTime();
            int mintonextHour=60-currTime.toString("m").toInt();
            QTimer::singleShot(mintonextHour*60000,this,SLOT(singleFired()));*/
}


void MainWindow::singleFired()
{
    qCritical()<<"Entered singleFired at"+QTime::currentTime().toString();
    QTextToSpeech *qts=new QTextToSpeech();
    QVector<QVoice> availVoice=qts->availableVoices();
    qts->setVoice(availVoice.at(1));
    qts->say("It is "+QTime::currentTime().toString("HA"));


// so now the time should be HH:00 now we have to schedule it every hour
   //handles the rescheduling
   QTimer *qt = new QTimer(this);
   connect(qt, SIGNAL(timeout()), this, SLOT(singleFired()));
   qt->start(60*60000);
}

void MainWindow::showTime()
{

    QTime currLabel = QTime::fromString(ui->labelTime->text(),"mm:ss");
//    qCritical()<<currLabel.toString("mm:ss");
    currLabel=currLabel.addSecs(-1);
//    qCritical()<<currLabel.toString("mm:ss");
    ui->labelTime->setText(currLabel.toString("mm:ss"));
}
