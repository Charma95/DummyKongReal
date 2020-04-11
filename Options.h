#pragma once

#include <qmainwindow.h>
#include <QWidget>
#include <qpushbutton.h>
#include <qslider.h>
#include <qlayout.h>
#include <qcheckbox.h>
#include <qradiobutton.h>
#include <qbuttongroup.h>
#include <qlabel.h>

class OptionsPage : public QMainWindow
{
	Q_OBJECT
public:
	OptionsPage(QWidget *parent = nullptr);
	~OptionsPage();
	int volume;
private:
	QWidget *centralWidget;
	QVBoxLayout *mainLayout;
	QLabel *optionsLabel;
	QLabel *volumeLabel;
	QSlider *volumeSlider;
	QLabel *sensitivityLabel;
	QSlider *sensitivitySlider;
	QPushButton *recordButton;
	QRadioButton *FPS30;
	QRadioButton *FPS60;
	QPushButton *okButton;
public slots:
	void adjustVolume();

};
