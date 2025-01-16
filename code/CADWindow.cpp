#include "CADWindow.hpp"
#include "QMenuBar.h"
#include "QToolBar.h"
#include <QTCore/QTextCodec>
CADWindow::CADWindow(QWidget* parent) :QMainWindow(parent)
{
	int size_X = 800;
	int size_Y = 800;
	this->setWindowTitle("Direct Modeling");
	this->resize(size_X, size_Y);
	m_Widget = new CADWidget();
	m_Widget->resize(size_X, size_Y);

	splitter = new QSplitter; 
	tree = new QTreeWidget();

	//DrawStepModel();
	//tree = m_Widget->tree;
	tree->setHeaderHidden(true);
	//QIcon myGroupIcon("../data/images/gear.svg");

	//QList<QString> allItemName{QString::fromLocal8Bit("����")};
	//QTreeWidgetItem* root = new QTreeWidgetItem(allItemName);
	////root->setText(0, QLatin1String("adfaf"));
	//root->setIcon(0, myGroupIcon);
	//m_Widget->tree->addTopLevelItem(root);


	//QTreeWidgetItem* child = new QTreeWidgetItem();
	//child->setText(0, QString::fromLocal8Bit("����"));
	//root->addChild(child);


	//QTreeWidgetItem* childx = new QTreeWidgetItem();
	//childx->setText(0, QString::fromLocal8Bit("����x"));
	//child->addChild(childx);


	splitter->addWidget(tree);
	splitter->addWidget(m_Widget);
	
	
	QToolBar* toolBar = addToolBar("Main Toolbar");
	toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	// ������������ť��
	QAction* action1 = new QAction(QIcon(":/icons/icon1.png"), "StepFile", this);
	QAction* action2 = new QAction(QIcon(":/icons/icon2.png"), "Bottle", this);

	//// Ϊ������Ӳۺ���
	connect(action1, &QAction::triggered, this, &CADWindow::DrawStepModel);
	connect(action2, &QAction::triggered, this, &CADWindow::DrawBottle);

	// ��������ӵ�������
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

	QString fileName = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("ѡ��һ��Step�ļ�"), "", QString::fromLocal8Bit("�����ļ� (*.stp *.step)"));

	QByteArray byteArray = fileName.toUtf8();

	m_Widget->DrawStepModel(byteArray.data());
	delete tree;
	tree = new QTreeWidget(); 
	
	tree = m_Widget->tree;
	tree->setHeaderHidden(true);
	splitter->addWidget(tree);
	splitter->addWidget(m_Widget); 
}