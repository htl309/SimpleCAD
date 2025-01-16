#include <QtWidgets/QWidget>
#include <QtCore/QEvent>
#include <QtGui/QMouseEvent>
#include "WNT_Window.hxx"
//建模
#include <TopoDS.hxx>
//可视化
#include <AIS_InteractiveContext.hxx>

#include"Geometry.hpp"
#include"StepReader.hpp"
class CADWidget : public QWidget
{
	

public:

    CADWidget(QWidget* parent = Q_NULLPTR);
    ~CADWidget();
	void paintEvent(QPaintEvent* evn);

	QPaintEngine* paintEngine() const;
	void resizeEvent(QResizeEvent* evn); 

	////鼠标键盘操作事件
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void wheelEvent(QWheelEvent* event) override;

	void DrawWedge();
	void DrawBottle();
	void DrawStepModel(const char* filename);
	void clearView();
	
public:
	Handle(V3d_Viewer) m_Viewer;
	Handle(V3d_View) m_View;
	Handle(AIS_InteractiveContext) m_Context;
	Handle(WNT_Window) m_Window;
	double m_Precision;//默认容差

	int m_ActionMode;//键鼠操作状态:0,nothing;1,平移;2,旋转;
	int mouseX, mouseY;//鼠标坐标

	int m_DisplayMode;//显示模式：0=wireframe;1=shaded



	Geometry g;
	StepReader s;
	QTreeWidget* tree;
};