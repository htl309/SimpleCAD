#include "CADWindow.hpp"
#include "QMenuBar.h"
#include "QToolBar.h"
#include <QTCore/QTextCodec>
CADWindow::CADWindow(QWidget* parent) :QMainWindow(parent)
{
	int size_X = 800;
	int size_Y = 800;
	this->setWindowTitle("SimpleCAD");
	this->resize(size_X, size_Y);
	m_Widget = new CADWidget();
	m_Widget->resize(size_X, size_Y);

	splitter = new QSplitter; 
	tree = new QTreeWidget();

	tree->setHeaderHidden(true);



	splitter->addWidget(tree);
	splitter->addWidget(m_Widget);
	
	
	QToolBar* toolBar = addToolBar("Main Toolbar");
	toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	// 创建操作（按钮）
	QAction* action1 = new QAction(QIcon(":/icons/icon1.png"), "StepFile", this);
	QAction* action2 = new QAction(QIcon(":/icons/icon2.png"), "Bottle", this);

	//// 为操作添加槽函数
	connect(action1, &QAction::triggered, this, &CADWindow::DrawStepModel);
	connect(action2, &QAction::triggered, this, &CADWindow::DrawBottle);

	// 将操作添加到工具栏
	toolBar->addAction(action1);
	toolBar->addAction(action2);

	
	setCentralWidget(splitter);
}
CADWindow::~CADWindow()
{
}

void CADWindow::DrawWedge() {
	m_Widget->DrawWedge();
}
void CADWindow::DrawBottle() {
	m_Widget->DrawBottle();


}

void CADWindow::DrawStepModel() {

	QString fileName = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("Simple CAD"), "", QString::fromLocal8Bit("(*.stp *.step)"));

	QByteArray byteArray = fileName.toUtf8();

	m_Widget->DrawStepModel(byteArray.data());
	delete tree;
	tree = new QTreeWidget(); 
	
	tree = m_Widget->tree;
	tree->setHeaderHidden(true);
	splitter->addWidget(tree);
	splitter->addWidget(m_Widget); 
}