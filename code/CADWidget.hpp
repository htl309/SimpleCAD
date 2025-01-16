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

	int m_ActionMode;//�������״̬:0,nothing;1,��ѡ;2,ƽ��;3,��ת;
	int mouseX, mouseY;//�������

	int m_DisplayMode;//��ʾģʽ��0=wireframe;1=shaded

	//��ѡ����ʱ����ҪҪ�ÿ�ѡ�񣬰����϶�����ѡ��ɨ���ĵ�һ����
	int m_SelectMode;//��ѡģʽ��0=shape;1=vertex;2=edge;3=wire;4=face;5=shell;6=solid;7=compsolid;8=compound

	int m_HilightMode;//�߹�ģʽ��0=wireframe;1=shaded

	Geometry g;
	StepReader s;
	QTreeWidget* tree;
};