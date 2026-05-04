#include "progressbar.h"
#include <qpainter.h>

void ProgressBar::paintEvent(QPaintEvent* event)
{
	
	drawBar();

}

ProgressBar::ProgressBar(QWidget *parent)
	: QFrame(parent), Value(0)
{
	setParent(parent);

	Device = new QPainter(this);
	//setStyleSheet(QString::fromUtf8("background-color: blue;"));
	//setGeometry(QRect(0, 0, 1000, 40));
	
}

ProgressBar::~ProgressBar() 
{}

void ProgressBar::setValue(float value) {
	Value = value;

	drawBar();
}

void ProgressBar::drawBar()
{

	auto l_Geo = geometry();

	int l_Width = l_Geo.width();
	int l_Height = l_Geo.height();

	int l_EndPointX = l_Geo.x() + (static_cast<float>(l_Width) * Value);

	QPen l_Pen = QPen(QColor(0, 150, 255));
	Device->setPen(l_Pen);
	Device->drawRect(0, l_Geo.y(), l_EndPointX, l_Geo.height());
	l_Pen.setColor(QColor(100, 100, 100));
	Device->drawRect(l_EndPointX, l_Geo.y(), l_Width, l_Geo.height());
}
