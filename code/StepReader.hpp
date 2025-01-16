#include <STEPControl_Writer.hxx>
#include <STEPControl_Reader.hxx>

#include<STEPCAFControl_Reader.hxx>
#include<Standard_Handle.hxx>


#include<Standard_Handle.hxx>
#include<XCAFDoc_ColorTool.hxx>
#include<XCAFDoc_ShapeTool.hxx>
#include<TDataStd_Name.hxx>
#include<TDF_ChildIterator.hxx>
#include <XCAFDoc_Location.hxx>
#include<TDocStd_Document.hxx>
#include<XCAFApp_Application.hxx>
#include<XCAFDoc_DocumentTool.hxx>
#include<TDF_LabelSequence.hxx>
#include<QTreeWidget>
#include<vector>
class StepReader {
private:


    //occ�ĳ�Ա����
    Handle(XCAFDoc_ShapeTool) aShapeTool;
    Handle(XCAFDoc_Location)  aLocation;

    //�ַ���ת����������occ����ַ�����ʽת����Ot�ĸ�ʽ
    std::string toString(const TCollection_ExtendedString& extstr)
    {
        char* str = new char[extstr.LengthOfCString() + 1];
        extstr.ToUTF8CString(str);
        std::string text(str);
        delete[] str;
        return text;
    }
public:
   
    std::vector< TopoDS_Shape> stepmodel;

    QTreeWidget* CreateQwidgettree(const char* path) {
        //�����ĵ�
        Handle(TDocStd_Document) aDoc;
        XCAFApp_Application::GetApplication()->NewDocument("MDTV-XCAF", aDoc);
  

        STEPCAFControl_Reader myReader;
     

        if (myReader.ReadFile(path)) {
            myReader.SetColorMode(true);
            myReader.SetNameMode(true);
            myReader.SetLayerMode(true);
            myReader.SetPropsMode(true);
            myReader.SetGDTMode(true);
            myReader.SetMatMode(true);
            myReader.SetViewMode(true);
            Handle_Message_ProgressIndicator indicator;


            myReader.Transfer(aDoc);
        }

        TDF_Label mainLabel = aDoc->Main();
        Handle(XCAFDoc_ShapeTool) myAssembly = XCAFDoc_DocumentTool::ShapeTool(mainLabel);


        TDF_LabelSequence FreeShape;
        myAssembly->GetFreeShapes(FreeShape);

        QTreeWidget*  tree = new QTreeWidget();

        QTreeWidgetItem* father = new  QTreeWidgetItem();
        father->setText(0, QLatin1String("modeltree"));
        father->setIcon(0, QIcon("svg\\file.svg"));
        tree->addTopLevelItem(father);

        int Roots = FreeShape.Length();

        for (int index = 1; index <= Roots; index++)
        {
            TDF_Label Label = FreeShape.Value(index);


            MakeTree(myAssembly, Label, TopLoc_Location(), father);

        }
        return tree;

    }

    void MakeTree(const Handle(XCAFDoc_ShapeTool)& ShapeTool, const TDF_Label& Label, TopLoc_Location Location, QTreeWidgetItem* father)
    {
        //��ȡ����
         Handle(TDataStd_Name) aName;

        QTreeWidgetItem* child = new  QTreeWidgetItem();
       
        if (Label.FindAttribute(TDataStd_Name::GetID(), aName)) { 
            
            TopoDS_Shape aShape;
            ShapeTool->GetShape(Label, aShape);
            if (aShape.ShapeType() == 0) {
                child->setIcon(0, QIcon("svg\\xde-assembly.svg"));
                aShape.Location(Location);
                stepmodel.push_back(aShape);
            }
            if (aShape.ShapeType() == 2) {
                child->setIcon(0, QIcon("svg\\xde-simple-shape.svg"));
               /* aShape.Location(Location);
                stepmodel.push_back(aShape);*/
            }
     
         
          
            std::string s = toString(aName->Get());
           

            child->setText(0, QString::fromLocal8Bit(s.c_str()));
            child->setFlags(child->flags() | Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);
            father->addChild(child);
        }




        TDF_LabelSequence components;
        //��ȡ�����
        if (ShapeTool->GetComponents(Label, components))
        {

            //��ȡ��������µ�ÿһ�����
            for (Standard_Integer compIndex = 1; compIndex <= components.Length(); ++compIndex)
            {

                TDF_Label ChildLabel = components.Value(compIndex);
                if (ShapeTool->IsReference(ChildLabel))
                {
                    //��ȡ�����ǩ��Ȼ����ж�ȡ
                    TDF_Label ShapeLabel;
                    if (ShapeTool->GetReferredShape(ChildLabel, ShapeLabel))
                    {
                        TopLoc_Location LocalLocation = Location * ShapeTool->GetLocation(ChildLabel);
                        //��ȱ�������Ϊ���������Ҳ���ܰ��������
                        MakeTree(ShapeTool, ShapeLabel, LocalLocation, child);
                    }
                }
            }
        }

    }

};