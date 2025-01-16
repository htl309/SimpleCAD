#include <QtWidgets/QWidget>
#include <QtCore/QEvent>
#include <QtGui/QMouseEvent>
#include "WNT_Window.hxx"
//��ģ
#include <TopoDS.hxx>
//���ӻ�
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

	////�����̲����¼�
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
	double m_Precision;//Ĭ���ݲ�

	int m_ActionMode;//�������״̬:0,nothing;1,ƽ��;2,��ת;
	int mouseX, mouseY;//�������

	int m_DisplayMode;//��ʾģʽ��0=wireframe;1=shaded



	Geometry g;
	StepReader s;
	QTreeWidget* tree;
};