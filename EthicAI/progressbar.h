#pragma once

#include <QWidget>
#include <qframe.h>

class ProgressBar : public QFrame
{
	Q_OBJECT

protected:

	virtual void paintEvent(QPaintEvent* event);

public:
	ProgressBar(QWidget* parent);
	~ProgressBar();

	float Value;

	QPainter* Device;

	void setValue(float value);
	inline float getValue() { return Value; }


	Q_PROPERTY(float value READ getValue WRITE setValue FINAL);

	void drawBar();
};

