#include "managementwindow.h"
#include "ui_managementwindow.h"
#include "teamwidget.h"
#include "progressbar.h"
#include "leaderboardteam.h"
#include <qspinbox.h>

/*void ManagementWindow::resizeEvent(const QResizeEvent* event)
{
    
}*/

ManagementWindow::ManagementWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ManagementWindow)
{
    ui->setupUi(this);

    /*auto p = new ProgressBar(this);
    p->setGeometry(0, 0, 100, 100);
    p->setStyleSheet(QString::fromUtf8("background-color: blue"));*/
    
    connect(ui->AnswerTimeSpinBox, &QSpinBox::valueChanged, this, &ManagementWindow::onAnswerTimeSpinBoxModified);
    connect(ui->endGameButton, &QPushButton::clicked, this, &ManagementWindow::onEndGameButtonClicked);
    connect(ui->StartButton, &QPushButton::clicked, this, &ManagementWindow::startButtonClicked);
    connect(ui->endGameButton, &QPushButton::clicked, this, &ManagementWindow::onEndGameButtonClicked);
    connect(ui->AddTeamButton, &QPushButton::clicked, this, &ManagementWindow::addTeamButtonClicked);
    connect(ui->AnswerTimeSpinBox, &QSpinBox::valueChanged, this, &ManagementWindow::onAnswerTimeSpinBoxModified);
}

ManagementWindow::~ManagementWindow()
{
    delete ui;
}

void ManagementWindow::DeleteTeam(Team* team)
{
    // TODO: delete team
    for (int x = 0; x < TeamWidgets.size();x++) {
        if (TeamWidgets[x]->TargetTeam == team) {
            delete TeamWidgets[x];
            TeamWidgets.removeAt(x);
        }
    }

}

void ManagementWindow::ChangeFontSizeByWindowSize(QLabel* label, int originalSize, int winx)
{
    float l_Percentage = (float)winx / 1920.f;

    int l_NewSize = originalSize * l_Percentage;

    QFont l_Font = label->font();
    l_Font.setPointSize(l_NewSize);
    label->setFont(l_Font);
}

void ManagementWindow::SetDescription(QString desc)
{
    ui->questionDescription->setText(desc);
}

void ManagementWindow::addTeamButtonClicked()
{
    TeamWidget* l_New = new TeamWidget(ui->centralwidget);
     
    ui->TeamManagementLayout->addWidget(l_New);
    Team* l_NewTeam = new Team(TeamWidgets.size(), "Equipe " + QString::number(TeamWidgets.size()));
    l_New->TargetTeam = l_NewTeam;
    l_New->OwningWindow = this;
    l_New->FinishInitialization();

    TeamWidgets.append(l_New);
}


void ManagementWindow::startButtonClicked()
{
    if (TargetPresentation) {
        if (TargetPresentation->State == GameState::InAnswer || TargetPresentation->State == GameState::MainMenu) {
            TargetPresentation->DisplayRandomQuestion();
            ui->questionCountLabel->setText(QString::number(TargetPresentation->AlreadyDisplayedQuestions.size()) + "/" + QString::number(TargetPresentation->Questions.size()));
        }
        else
        if (TargetPresentation->State == GameState::InQuestion) {
            TargetPresentation->DisplayResults();
        }
        else
        if (TargetPresentation->State == GameState::InAnswer && false) {
            TargetPresentation->DisplayLeaderboard(true);
        }

       //TargetPresentation->DisplayRandomQuestion();
    }
}

void ManagementWindow::onAnswerTimeSpinBoxModified(int value)
{
    TargetPresentation->BarAnimation->setDuration(value * 1000);
}

void ManagementWindow::onEndGameButtonClicked()
{
    TargetPresentation->DisplayLeaderboard(true);
}


