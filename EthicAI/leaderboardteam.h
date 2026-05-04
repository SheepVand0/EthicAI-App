#pragma once

#include <QWidget>
#include <qproperty.h>
#include <qlabel.h>
#include <qpropertyanimation.h>
#include <qboxlayout.h>

struct Team;


class LeaderboardTeam  : public QWidget
{
	Q_OBJECT

public:
	LeaderboardTeam(Team* targetTeam, QWidget *parent = nullptr);
	~LeaderboardTeam();

	QHBoxLayout* MainLayout;

	QLabel* ScoreLabel;
	QLabel* TeamNameLabel;
	QPropertyAnimation* PositionAnimation;

	Team* TargetTeam;

	int yPosition;

	Q_PROPERTY(int yPosition READ getYPosition WRITE setPosition FINAL);

	void setPosition(int x);
	inline int getYPosition() { return yPosition; }

	void updateScore(int position);

	bool operator < (const LeaderboardTeam* x1);
};

