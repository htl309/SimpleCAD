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


    //occ的成员函数
    Handle(XCAFDoc_ShapeTool) aShapeTool;
    Handle(XCAFDoc_Location)  aLocation;

    //字符串转化函数，把occ里的字符串格式转化成Ot的格式
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
        //创建文档
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
        //获取名字
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
        //读取组合体
        if (ShapeTool->GetComponents(Label, components))
        {

            //读取该组合体下的每一个零件
            for (Standard_Integer compIndex = 1; compIndex <= components.Length(); ++compIndex)
            {

                TDF_Label ChildLabel = components.Value(compIndex);
                if (ShapeTool->IsReference(ChildLabel))
                {
                    //获取零件标签，然后进行读取
                    TDF_Label ShapeLabel;
                    if (ShapeTool->GetReferredShape(ChildLabel, ShapeLabel))
                    {
                        TopLoc_Location LocalLocation = Location * ShapeTool->GetLocation(ChildLabel);
                        //深度遍历，因为组合体里面也可能包含组合体
                        MakeTree(ShapeTool, ShapeLabel, LocalLocation, child);
                    }
                }
            }
        }

    }

};