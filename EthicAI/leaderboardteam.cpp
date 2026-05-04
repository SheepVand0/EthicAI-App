#include "leaderboardteam.h"
#include "managementwindow.h"
#include <qsizepolicy.h>
#include <qfont.h>

LeaderboardTeam::LeaderboardTeam(Team* targetTeam, QWidget* parent) : QWidget(parent)
{
	MainLayout = new QHBoxLayout(this);

	TeamNameLabel = new QLabel(parent);
	TeamNameLabel->setAlignment(Qt::AlignLeft);
	auto l_Font = TeamNameLabel->font();
	l_Font.setPointSize(24);
	TeamNameLabel->setFont(l_Font);
	TeamNameLabel->setStyleSheet("color: black;");
	TeamNameLabel->setMaximumHeight(50);
	MainLayout->addWidget(TeamNameLabel, 0);

	ScoreLabel = new QLabel(parent);
	ScoreLabel->setAlignment(Qt::AlignRight);
	ScoreLabel->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
	ScoreLabel->setStyleSheet("color: black;");
	ScoreLabel->setMaximumHeight(50);
	l_Font = ScoreLabel->font();
	l_Font.setPointSize(24);

	ScoreLabel->setFont(l_Font);
	MainLayout->addWidget(ScoreLabel, 0);

	PositionAnimation = new QPropertyAnimation(this, "yPosition");
	PositionAnimation->setDuration(650);
	PositionAnimation->setEndValue(0);

	yPosition = 0;

	TargetTeam = targetTeam;

	setStyleSheet("background-color: white; border-radius: 50%;");

	setEnabled(true);
	MainLayout->setSizeConstraint(QLayout::SizeConstraint::SetNoConstraint);

	setAttribute(Qt::WA_TranslucentBackground);
	setWindowFlags(Qt::FramelessWindowHint);
}

void LeaderboardTeam::setPosition(int x)
{
	//auto l_Geometry = geometry();
	//setGeometry(QRect(parentWidget()->geometry().width() * 0.025f, x, parentWidget()->geometry().width() * 0.95f, parentWidget()->geometry().height() * 0.1f));
	//setGeometry(QRect(10, x, 100, 10));
}

void LeaderboardTeam::updateScore(int position)
{
	/*PositionAnimation->setStartValue(PositionAnimation->endValue());
	PositionAnimation->setEndValue(position * 100);
	PositionAnimation->setCurrentTime(0);
	PositionAnimation->start();*/

	TeamNameLabel->setText(TargetTeam->TeamName);
	ScoreLabel->setText(QString::number(TargetTeam->Score));
}

bool LeaderboardTeam::operator<(const LeaderboardTeam* x1)
{
	return TargetTeam->Score > x1->TargetTeam->Score;
}


LeaderboardTeam::~LeaderboardTeam()
{}

