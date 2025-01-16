#include <iostream>

#include <Quantity_HArray1OfColor.hxx>
#include <TopTools_HSequenceOfShape.hxx>
#include <Interface_Static.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <AIS_InteractiveContext.hxx>
#include <AIS_Shape.hxx>
#include <V3d_Viewer.hxx>
#include <V3d_View.hxx>

#include <TopoDS.hxx>
#include <TopoDS_Iterator.hxx>
#include <TopExp_Explorer.hxx>
#include <BRepAdaptor_Curve.hxx>
#include <BRepAdaptor_Surface.hxx>
#include <GeomAdaptor_Surface.hxx>
#include <StdSelect_BRepOwner.hxx>
#include <BRepTools.hxx>
#include <BRep_Builder.hxx>
#include <BRepPrimAPI_MakeWedge.hxx>
#include <BRepMesh_IncrementalMesh.hxx>
//数据交换



#include <QtWidgets/QWidget>
#include <QtCore/QEvent> 

#include <QtWidgets/QApplication>
#include "CADWidget.hpp"
void CADWidget::DrawWedge() { 
	
	clearView();
	Quantity_Color color = Quantity_Color(0.3, 0.5, 0.3, Quantity_TOC_RGB);
	Handle(AIS_Shape) abox = new AIS_Shape(g.MakeWedge());
	m_Context->SetMaterial(abox, Graphic3d_NameOfMaterial_Stone, Standard_False);
	m_Context->SetColor(abox, color, Standard_False);
	m_Context->Display(abox, 1, 1, Standard_True);

	m_View->FitAll();
}

void CADWidget::DrawBottle() {

	clearView();
	Quantity_Color color = Quantity_Color(0.3, 0.5, 0.3, Quantity_TOC_RGB);
	Handle(AIS_Shape) abox = new AIS_Shape(g.MakeBottle(50, 70, 30));
	m_Context->SetMaterial(abox, Graphic3d_NameOfMaterial_Stone, Standard_False);
	m_Context->SetColor(abox, color, Standard_False);
	m_Context->Display(abox, 1, 1, Standard_True);

	m_View->FitAll();

}
void CADWidget::DrawStepModel(const char* filename) {
	clearView();
	s.stepmodel.clear();
	tree = new QTreeWidget();
	tree = s.CreateQwidgettree(filename);
	
	Quantity_Color color = Quantity_Color(0.7, 0.7, 0.7, Quantity_TOC_RGB);
	for(int i=0;i<s.stepmodel.size();i++)
	{
		Handle(AIS_Shape) abox = new AIS_Shape(s.stepmodel[i]);
		m_Context->SetMaterial(abox, Graphic3d_NameOfMaterial_Stone, Standard_False);
		m_Context->SetColor(abox, color, Standard_False);
		m_Context->Display(abox, 1, 1, Standard_True);
	}


}
void CADWidget::clearView()
{
	
	AIS_ListOfInteractive alist;
	m_Context->DisplayedObjects(alist);
	AIS_ListIteratorOfListOfInteractive aiter;
	for (aiter.Initialize(alist); aiter.More(); aiter.Next()) {
		m_Context->Remove(aiter.Value(), true);
	}
}
CADWidget::CADWidget(QWidget* parent)
	: QWidget(parent)
{
	Handle(Aspect_DisplayConnection) displayConnection = new Aspect_DisplayConnection();
	Handle(OpenGl_GraphicDriver) driver = new OpenGl_GraphicDriver(displayConnection);
	m_Viewer = new V3d_Viewer(driver);
	m_View = m_Viewer->CreateView();
	WId win_handle = (WId)winId();
	m_Window = new WNT_Window((Aspect_Handle)win_handle);
	m_View->SetWindow(m_Window);
	if (!m_Window->IsMapped()) {
		m_Window->Map();
	}


	m_DisplayMode = 1;

	//Handle(Prs3d_Drawer) drawer;
	m_Context = new AIS_InteractiveContext(m_Viewer);
	m_Context->SetDisplayMode(m_DisplayMode, Standard_True);
	//setHighlightStyle();
	//setSelectStyle();
	/*drawer = m_Context->HighlightStyle();
	Quantity_Color color = Quantity_Color(0.8, 0.8, 0.8, Quantity_TOC_RGB);
	drawer->SetColor(color);
	m_Context->SetHighlightStyle(drawer);*/
	m_View->SetBackgroundColor(Quantity_TOC_RGB, 1, 1, 1);
	m_View->MustBeResized();
	m_View->TriedronDisplay(Aspect_TOTP_LEFT_LOWER, Quantity_NOC_BLACK, 0.08, V3d_ZBUFFER);
	m_Viewer->SetDefaultLights();

	setAttribute(Qt::WA_PaintOnScreen);
	

	
}
CADWidget::~CADWidget()
{

}


void CADWidget::resizeEvent(QResizeEvent* evn) {
	if (!m_View.IsNull()) {
		m_View->MustBeResized();
	}
}
void CADWidget::paintEvent(QPaintEvent* evn) {

	m_View->Redraw();
}
QPaintEngine* CADWidget::paintEngine() const {
	return 0;
}
void CADWidget::wheelEvent(QWheelEvent* event) {
	m_View->StartZoomAtPoint(event->pos().x(), event->pos().y());
	m_View->ZoomAtPoint(0, 0, event->angleDelta().y() / 5, 0);

}

void CADWidget::mousePressEvent(QMouseEvent* event) {
	if ((event->buttons() & Qt::LeftButton )) {//左键拣选
		m_ActionMode = 1;
		mouseX = event->pos().x();
		mouseY = event->pos().y();
		
		
	
		return;
	}
	else if ((event->buttons()) & Qt::RightButton) {
		
			m_ActionMode = 2;
			m_View->StartRotation(event->pos().x(), event->pos().y());
			return;
	
	}
}

void CADWidget::mouseMoveEvent(QMouseEvent* event) {
	
	switch (m_ActionMode)
	{
	
	case 1:
		m_View->Pan(event->pos().x() - mouseX,mouseY - event->pos().y());
		mouseX = event->pos().x();
		mouseY = event->pos().y();
		break;
	case 2:
		m_View->Rotation(event->pos().x(),event->pos().y());
		break;
	case 0:
		break;

	}
}

