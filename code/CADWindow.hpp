#pragma once
#include "qmainwindow.h"
#include "qstatusbar.h"
#include "qlabel.h"
#include <QSplitter>
#include <QFileDialog> 

#include "CADWidget.hpp"
#include <QMessageBox> 
class CADWindow :
	public QMainWindow
{
	//Q_OBJECT
public:
	CADWindow(QWidget* parent = Q_NULLPTR);
	~CADWindow();

	void DrawWedge();
	void DrawBottle();
	void DrawStepModel();


private:
	CADWidget* m_Widget;
	QTreeWidget* tree;
	QSplitter* splitter;
	
};