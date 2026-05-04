#ifndef TEAMWIDGET_H
#define TEAMWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>

class ManagementWindow;
struct Team;

class TeamWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TeamWidget(QWidget* parent = nullptr);

    QHBoxLayout* MainHorizontalLayout;
    QLineEdit* TeamName;
    QLabel* ScoreLabel;
    QList<QPushButton*> PointsManagementButtons;
    QPushButton* DeleteTeamButton;

    Team* TargetTeam;

    ManagementWindow* OwningWindow;

    bool operator <(TeamWidget* x1);

    void FinishInitialization();


private slots:

    void on_DeleteTeamButton_clicked();
    void onTeamNameChanged(const QString& newValue);

    void addScoreThree();
    void addScoreOne();
    void removeScoreOne();
    void removeScoreThree();

    void updateScore();

private:
};

#endif // TEAMWIDGET_H
