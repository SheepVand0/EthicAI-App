#include "presentationwindow.h"
#include "./ui_presentationwindow.h"
#include "QFile.h"
#include "QStyle"
#include "qlabel.h"
#include "QPropertyAnimation"
#include "QRandomGenerator"
#include "managementwindow.h"
#include "teamwidget.h"
#include <random>
#include "leaderboardteam.h"
#include <stdlib.h>
#include <qprogressbar.h>

PresentationWindow::PresentationWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PresentationWindow)
{
    ui->setupUi(this);

    QFile l_File = QFile("./questions.csv");
    if (l_File.open(QFile::OpenModeFlag::ReadWrite)) {

        QString l_Line = "-";
        while (!l_Line.isEmpty()) {
            l_Line = l_File.readLine();

            if (l_Line.isEmpty()) break;

            QStringList l_Data = l_Line.split(";");
            //if (l_Data[0].isEmpty()) break;

            QString l_RawQuestion = l_Data[1];
            QString l_ResultQuestion = AddNewLines(l_Data[1]);
            

            Question l_Question = Question(l_Data[0], l_ResultQuestion, QList<QString>{ l_Data[2], l_Data[3], l_Data[4] }, AddNewLines(l_Data[5]), l_Data[6].size() > 0 ? (int)(l_Data[6].toLower()[0].toLatin1() - 'a') : 0);
            Questions.append(l_Question);
        }

        l_File.close();

        ui->centralwidget->setVisible(false);
        //ui->centralwidget->setStyleSheet("background-image: url(./Palais de Justice.png)");

        

        //ui->centralwidget->layout()->setAlignment(Qt::AlignTop);

        /*TimeBar = new ProgressBar(ui->verticalLayoutWidget);
        ui->TimeBarLayout->addWidget(TimeBar);
        //TimeBar->setValue(0.0f);
        TimeBar->setSizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        TimeBar->setMinimumSize(QSize(100, 100));
        TimeBar->show();
        TimeBar->setStyleSheet(QString::fromUtf8("background-color: blue;"));
        /*QSizePolicy sizePolicy;
        sizePolicy.setHeightForWidth(TimeBar->sizePolicy().hasHeightForWidth());
        TimeBar->setSizePolicy(sizePolicy);*/
        

        //QLabel* test = new QLabel("ZOUIFBHZJIOPEVB ZHIOPFVB ZYHIO VBFZ", ui->centralwidget);
        //ui->TimeBarLayout->addWidget(test);

        BarAnimation = new QPropertyAnimation(this, "TimeValue");
        BarAnimation->setStartValue(0); // Useless
        BarAnimation->setEndValue(100); // Same
        BarAnimation->setDuration(15000);

        RandomGenerator = new QRandomGenerator();

        connect(BarAnimation, &QPropertyAnimation::valueChanged, this, &PresentationWindow::BarProgressChanged);
    } else {
        QLabel* l_Label = new QLabel(ui->centralwidget);
        l_Label->setText("INVALID QUESTION FILE");
        l_Label->setStyleSheet("color: red");
    }
}

PresentationWindow::~PresentationWindow()
{
    delete ui;
}

float PresentationWindow::barProgress() {
    return timeBarVal;
}

void PresentationWindow::setBarProgress(float x) {
    timeBarVal = x;

    float l_Duration = static_cast<float>(BarAnimation->duration());
    float l_Value = (l_Duration - (float)BarAnimation->currentTime()) / 1000.f;

    QString l_asText = QString::number(l_Value, 'f', 0) + "s";
    ui->TimeText->setText(l_asText);

    if (l_Value > 5.f) {
        ui->TimeText->setStyleSheet("color: black; background-color: white; border-radius: 100%;");
    }
    else {
        float l_Perc =  1 - (l_Value / 5.f);

        int whitered = TimeColorWhite.red();
        int whitegreen = TimeColorWhite.green();
        int whiteblue = TimeColorWhite.blue();

        QColor l_Color = QColor(
            whitered + ((TimeColorOrange.red() - whitered) * l_Perc),
            whitegreen + ((TimeColorOrange.green() - whitegreen) * l_Perc),
            whiteblue + ((TimeColorOrange.blue() - whiteblue) * l_Perc)
        );

        ui->TimeText->setStyleSheet("color: black; background-color: rgb(" + QString::number(l_Color.red()) + ", " + QString::number(l_Color.green()) + ", " + QString::number(l_Color.blue()) + "); border-radius: 100%;");
    }

    if (x >= 100) {
        DisplayResults();
    }

    resizeEvent(nullptr);
}

void PresentationWindow::DisplayResults()
{
    State = GameState::InAnswer;

    ui->TimeText->setVisible(false);

    QList<QLabel*> l_Values = QList<QLabel*> { ui->answer0, ui->answer1, ui->answer2 };

    for (int x = 0; x < l_Values.size(); x++) {
        l_Values[x]->setVisible(true);
        if (x == CurrentQuestion->RealAnswer) {
            l_Values[x]->setStyleSheet(QString("color: green"));
        }
    }

    resizeEvent(nullptr);
}

void PresentationWindow::DisplayLeaderboard(bool display)
{
    ui->QuestionCategoryLabel->setVisible(!display);
    ui->QuestionLabel->setVisible(!display);
    ui->TimeText->setVisible(!display);

    QList<QLabel*> l_Values = QList<QLabel*>{ ui->answer0, ui->answer1, ui->answer2 };

    for (auto x : l_Values) {
        x->setVisible(!display);
        x->setStyleSheet("color: black");
    }

    ui->answer0->setVisible(!display);
    ui->answer1->setVisible(!display);
    ui->answer2->setVisible(!display);
//    ui->leaderboardWidget->setVisible(display);
    BarAnimation->stop();

    //resizeEvent(nullptr);

    if (display) {
        State = GameState::InLeaderboard;

        QList<QSpacerItem*> l_Spacers = QList<QSpacerItem*>{ ui->verticalSpacer_2, ui->verticalSpacer, ui->verticalSpacer_3, ui->verticalSpacer_4, ui->verticalSpacer_5, ui->horizontalSpacer, ui->horizontalSpacer_2, ui->horizontalSpacer_3, ui->horizontalSpacer_4, ui->horizontalSpacer_5, ui->horizontalSpacer_6 };

        for (auto x : l_Spacers) {
            x->changeSize(0, 0);
        }
        
        std::sort(ManagementWindowReference->TeamWidgets.begin(), ManagementWindowReference->TeamWidgets.end(), &TeamWidget::operator<);

        if (LeaderboardWidgets.isEmpty()) {
            for (int x = 0; x < ManagementWindowReference->TeamWidgets.size(); x++) {
                LeaderboardTeam* l_Team = new LeaderboardTeam(ManagementWindowReference->TeamWidgets[x]->TargetTeam, ui->centralwidget);
                LeaderboardWidgets.append(l_Team);
                //ui->vertiMainLayoutcalLayout->addWidget(l_Team, 1);
            }
        }


        std::sort(LeaderboardWidgets.begin(), LeaderboardWidgets.end(), &LeaderboardTeam::operator<);

        int x = 0;
        for (auto team : LeaderboardWidgets) {
            ui->vertiMainLayoutcalLayout->addWidget(team, 0);

            //auto geo = team->geometry();

            team->updateScore(x);
            x++;
        }

        
    }

    //ui->centralwidget->updateGeometry();
    resizeEvent(nullptr);
}

void PresentationWindow::resizeEvent(QResizeEvent* event)
{
    //ui->vertiMainLayoutcalLayout->setGeometry(ui->centralwidget->geometry());

    auto geo = geometry().width();
    ManagementWindow::ChangeFontSizeByWindowSize(ui->QuestionCategoryLabel, 25, geo);
    ManagementWindow::ChangeFontSizeByWindowSize(ui->QuestionLabel, 39, geo);
    ManagementWindow::ChangeFontSizeByWindowSize(ui->TimeText, 25, geo);
    ManagementWindow::ChangeFontSizeByWindowSize(ui->answer0, 30, geo);
    ManagementWindow::ChangeFontSizeByWindowSize(ui->answer1, 30, geo);
    ManagementWindow::ChangeFontSizeByWindowSize(ui->answer2, 30, geo);
}

QString PresentationWindow::AddNewLines(QString base)
{
    QString l_ResultQuestion = "<html><body>";

    int i = 0;

    QString temp = "";

    for (auto x : base) {
        if (x == ' ' && i >= 32) {
            l_ResultQuestion += "<p>" + temp + "</p></br>";
            temp = "";
            i = 0;
            continue;
        }

        temp += x;

        i++;
    }

    if (!temp.isEmpty()) {
        l_ResultQuestion += "<p>" + temp + "</p></body></html>";
    }

    return l_ResultQuestion;
}

void PresentationWindow::BarProgressChanged(const QVariant& value) {

    float x = value.toFloat();

    if (x >=  100) {
        DisplayResults();
    }

    //ui->TimeBar->setValue(x);
}

void PresentationWindow::DisplayRandomQuestion() {
    //State = GameState::InQuestion;

    if (AlreadyDisplayedQuestions.size() == Questions.size()) {
        DisplayLeaderboard(true);
        return;
    }

    DisplayLeaderboard(false);

    qint32 l_FoundIndex = -1;

    do {
        l_FoundIndex = rand() % Questions.size();
            // distribution in range [1, 6]
    } while (AlreadyDisplayedQuestions.contains(&Questions[l_FoundIndex]));

    State = GameState::InQuestion;
    ui->centralwidget->setVisible(true);

    Question* l_Question = &Questions[l_FoundIndex];

    AlreadyDisplayedQuestions.append(l_Question);

    ui->QuestionLabel->setText(l_Question->RawQuestion);
    //QFont l_Font = ui->QuestionLabel->font();
    //l_Font.setPointSizeF(39 - (l_Question->RawQuestion.length() / 32));
    //ui->QuestionLabel->setFont(l_Font);
    ui->QuestionCategoryLabel->setText(l_Question->Category);

    ui->answer0->setText("A : " + l_Question->Answers[0]);
    ui->answer0->setVisible(true);
    ui->answer1->setText("B : " + l_Question->Answers[1]);
    ui->answer1->setVisible(true);
    ui->answer2->setText("C : " + l_Question->Answers[2]);
    ui->answer2->setVisible(true);

    CurrentQuestion = l_Question;

    BarAnimation->setCurrentTime(0);
    BarAnimation->start();

    ManagementWindowReference->SetDescription(l_Question->Description);

    resizeEvent(nullptr);

   
}