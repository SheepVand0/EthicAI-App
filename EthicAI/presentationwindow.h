#ifndef PRESENTATIONWINDOW_H
#define PRESENTATIONWINDOW_H

#include <QMainWindow>
#include "QPropertyAnimation"
#include "QRandomGenerator"
#include "progressbar.h"

class LeaderboardTeam;

struct Question {

    Question(QString category, QString question, QList<QString> answers, QString description, int realAnswer) {
        Category = category;
        RawQuestion = question;
        Answers = answers;
        RealAnswer = realAnswer;
        Description = description;
    }

    QString Category;
    QString RawQuestion;
    QList<QString> Answers;
    QString Description;
    int RealAnswer;

};

enum GameState {
    MainMenu,
    InQuestion,
    InAnswer,
    InLeaderboard
};

class ManagementWindow;

QT_BEGIN_NAMESPACE
namespace Ui {
class PresentationWindow;
}
QT_END_NAMESPACE


class PresentationWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PresentationWindow(QWidget *parent = nullptr);
    ~PresentationWindow() override;

    ManagementWindow* ManagementWindowReference;

    QList<Question> Questions;
    QList<Question*> AlreadyDisplayedQuestions;
    QList<LeaderboardTeam*> LeaderboardWidgets;

    QColor TimeColorWhite = QColor(255, 255, 255);
    QColor TimeColorOrange = QColor(255, 90, 0);
    QColor TimeColorRed;

    Question* CurrentQuestion;
    bool Started = false;

    GameState State = MainMenu;

    //ProgressBar* TimeBar;
    QPropertyAnimation* BarAnimation;
    QRandomGenerator* RandomGenerator;

    void DisplayRandomQuestion();


    void DisplayResults();
    void DisplayLeaderboard(bool display);

    QString AddNewLines(QString base);
    
    virtual void resizeEvent(QResizeEvent* event) override;

protected:

    Q_PROPERTY(float TimeValue READ barProgress WRITE setBarProgress NOTIFY BarProgressChanged FINAL)

    float timeBarVal;

    float barProgress();
    void setBarProgress(float x);
    void BarProgressChanged(const QVariant& value);

private:


    Ui::PresentationWindow *ui;
};
#endif // PRESENTATIONWINDOW_H
