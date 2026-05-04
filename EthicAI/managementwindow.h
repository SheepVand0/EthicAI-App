#ifndef MANAGEMENTWINDOW_H
#define MANAGEMENTWINDOW_H

#include <QMainWindow>
#include <QList>
#include "presentationwindow.h"

class TeamWidget;

namespace Ui {
class ManagementWindow;
}

struct Team {

    Team(int teamIndex, QString teamName) {
        TeamIndex = teamIndex;
        TeamName = teamName;
        Score = 0;
    }

    int TeamIndex;
    int Score;
    QString TeamName;

};

class ManagementWindow : public QMainWindow
{
    Q_OBJECT

protected:

    //virtual void resizeEvent(const QResizeEvent* event) override;

public:
    explicit ManagementWindow(QWidget *parent = nullptr);
    ~ManagementWindow();

    static void ChangeFontSizeByWindowSize(QLabel* label, int originalSize, int winx);
    
    QList<TeamWidget*> TeamWidgets;
    QList<TeamWidget*> Leaderboard;

    PresentationWindow* TargetPresentation;

    void DeleteTeam(Team* team);
    void SetDescription(QString desc);

private slots:

    void addTeamButtonClicked();

    void startButtonClicked();

    void onAnswerTimeSpinBoxModified(int value);

    void onEndGameButtonClicked();

private:
    Ui::ManagementWindow *ui;
};

#endif // MANAGEMENTWINDOW_H
