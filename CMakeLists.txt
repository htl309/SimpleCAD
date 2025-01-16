cmake_minimum_required(VERSION 3.18)

project(SimpleCAD
    VERSION 0.1.0
    DESCRIPTION "SDU"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DHWPCB_BUILD)

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    # 要求VC正确设置C++识别宏
    add_compile_options(/Zc:__cplusplus)
    add_compile_options(/source-charset:utf-8)
    add_compile_options(/W4)
    add_compile_options(/Zi) # 生成调试信息，用于性能剖析

    # 指定用Unicode
    add_definitions("-DUNICODE" "-D_UNICODE" "-D_USE_MATH_DEFINES")
else()
    add_compile_options(-x c++ -std=c++20 -g -O2 -Wall -Wextra -Weffc++ -Wpedantic)
    set(CMAKE_EXECUTABLE_SUFFIX_CXX .elf)
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
    # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
    # set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg")
endif()




link_directories(
OCC/lib
QT/lib
)

include_directories(
OCC/inc
QT/include
QT/include/QtWidgets
code
)


add_executable(SimpleCAD
code/CADWidget.hpp
code/CADWindow.hpp
code/Geometry.hpp
code/StepReader.hpp


code/CADWidget.cpp
code/CADWindow.cpp
code/Geometry.cpp
code/SimpleCAD.cpp
)

target_link_libraries(SimpleCAD
Qt5Core.lib
Qt5Gui.lib
Qt5Widgets.lib
TKBin.lib
TKBinL.lib
TKBinTObj.lib
TKBinXCAF.lib
TKBO.lib
TKBool.lib
TKBRep.lib
TKCAF.lib
TKCDF.lib
TKD3DHost.lib
TKD3DHostTest.lib
TKDCAF.lib
TKDE.lib
TKDECascade.lib
TKDEGLTF.lib
TKDEIGES.lib
TKDEOBJ.lib
TKDEPLY.lib
TKDESTEP.lib
TKDESTL.lib
TKDEVRML.lib
TKDFBrowser.lib
TKDraw.lib
TKernel.lib
TKFeat.lib
TKFillet.lib
TKG2d.lib
TKG3d.lib
TKGeomAlgo.lib
TKGeomBase.lib
TKHLR.lib
TKIVtk.lib
TKIVtkDraw.lib
TKLCAF.lib
TKMath.lib
TKMesh.lib
TKMeshVS.lib
TKMessageModel.lib
TKMessageView.lib
TKOffset.lib
TKOpenGl.lib
TKOpenGles.lib
TKOpenGlTest.lib
TKPrim.lib
TKQADraw.lib
TKRWMesh.lib
TKService.lib
TKShapeView.lib
TKShHealing.lib
TKStd.lib
TKStdL.lib
TKTInspector.lib
TKTInspectorAPI.lib
TKTObj.lib
TKTObjDRAW.lib
TKToolsDraw.lib
TKTopAlgo.lib
TKTopTest.lib
TKTreeModel.lib
TKV3d.lib
TKVCAF.lib
TKView.lib
TKViewerTest.lib
TKVInspector.lib
TKXCAF.lib
TKXDEDRAW.lib
TKXMesh.lib
TKXml.lib
TKXmlL.lib
TKXmlTObj.lib
TKXmlXCAF.lib
TKXSBase.lib
TKXSDRAW.lib
TKXSDRAWDE.lib
TKXSDRAWGLTF.lib
TKXSDRAWIGES.lib
TKXSDRAWOBJ.lib
TKXSDRAWPLY.lib
TKXSDRAWSTEP.lib
TKXSDRAWSTL.lib
TKXSDRAWVRML.lib

)


