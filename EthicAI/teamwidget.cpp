#include "teamwidget.h"
#include "qlabel.h"
#include "managementwindow.h"

TeamWidget::TeamWidget(QWidget* parent)
    : QWidget(parent)
{

    MainHorizontalLayout = new QHBoxLayout(this);
    MainHorizontalLayout->setHorizontalSizeConstraint(QHBoxLayout::SizeConstraint::SetMinimumSize);

    TeamName = new QLineEdit(this);
    TeamName->setStyleSheet("color: white");
    MainHorizontalLayout->addWidget(TeamName);

    ScoreLabel = new QLabel(this);
    ScoreLabel->setText("Score : 0");
    ScoreLabel->setStyleSheet("color: white");
    MainHorizontalLayout->addWidget(ScoreLabel);

    int l_PointsManagement[4] = { -3, -1, 1, 3 };
    void(TeamWidget:: * l_ScoreMethods[4])() = { &TeamWidget::removeScoreThree, &TeamWidget::removeScoreOne, &TeamWidget::addScoreOne, &TeamWidget::addScoreThree };

    for (int x = 0; x < 4; x++) {
        QPushButton* l_Button = new QPushButton(this);
        l_Button->setText(l_PointsManagement[x] > 0 ? "+" + QString::number(l_PointsManagement[x]) : QString::number(l_PointsManagement[x]));
        l_Button->setStyleSheet("color: white");
        MainHorizontalLayout->addWidget(l_Button);

        connect(l_Button, &QPushButton::clicked, this, l_ScoreMethods[x]);
        connect(l_Button, &QPushButton::clicked, this, &TeamWidget::updateScore);
    }

    DeleteTeamButton = new QPushButton(this);
    DeleteTeamButton->setText("X");
    DeleteTeamButton->setStyleSheet("color: white");
    MainHorizontalLayout->addWidget(DeleteTeamButton);

    connect(DeleteTeamButton, &QPushButton::clicked, this, &TeamWidget::on_DeleteTeamButton_clicked);
}

void TeamWidget::FinishInitialization() {
    TeamName->setText(TargetTeam->TeamName);

    connect(DeleteTeamButton, &QPushButton::clicked, this, &TeamWidget::on_DeleteTeamButton_clicked);
    connect(TeamName, &QLineEdit::textChanged, this, &TeamWidget::onTeamNameChanged);
}

bool TeamWidget::operator<(TeamWidget* x1)
{
    return TargetTeam->Score > x1->TargetTeam->Score;
}

void TeamWidget::on_DeleteTeamButton_clicked() {
    OwningWindow->DeleteTeam(TargetTeam);
}

void TeamWidget::onTeamNameChanged(const QString& value) {
    if (TargetTeam) {
        TargetTeam->TeamName = value;
    }
}

void TeamWidget::addScoreThree()
{
    TargetTeam->Score += 3;
}

void TeamWidget::addScoreOne()
{
    TargetTeam->Score++;
}

void TeamWidget::removeScoreOne()
{
    TargetTeam->Score--;
}

void TeamWidget::removeScoreThree()
{
    TargetTeam->Score -= 3;
}

void TeamWidget::updateScore()
{
    ScoreLabel->setText("Score : " + QString::number(TargetTeam->Score));
}

