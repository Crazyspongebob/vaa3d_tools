TEMPLATE    = lib
CONFIG	+= qt plugin warn_off
#CONFIG	+= x86_64
VAA3DPATH = ../../../../v3d_external/v3d_main
INCLUDEPATH	+= $$VAA3DPATH/basic_c_fun
INCLUDEPATH += $$VAA3DPATH/common_lib/include
INCLUDEPATH += ../../zhi/deep_learning/prediction
INCLUDEPATH += ../../../released_plugins/v3d_plugins/mean_shift_center

win32 {
    DEFINES += "CMAKE_WINDOWS_BUILD"
    CAFFEPATH = $$(CAFFE_PATH) 
    USERPATH = $$(USERPROFILE)
    CUDACHECK = $$(CUDA_PATH)
    BOOSTPATH = $$(BOOST_PATH)
    MSVCVERSION = $$(QMAKESPEC)
    OTHERINCLUDEPATH = $$USERPATH\\.caffe\\dependencies\\libraries_v120_x64_py27_1.1.0\\libraries\\include
    OTHERLIBPATH = $$USERPATH\\.caffe\\dependencies\\libraries_v120_x64_py27_1.1.0\\libraries

    INCLUDEPATH += $$BOOSTPATH
    INCLUDEPATH += $$OTHERINCLUDEPATH
    INCLUDEPATH	+= $$CAFFEPATH\\include
    INCLUDEPATH += $$CAFFEPATH\\include\\caffe\\util
    INCLUDEPATH	+= $$CAFFEPATH\\src\\caffe
    INCLUDEPATH += $$CAFFEPATH\\build\\include
    INCLUDEPATH += $$CAFFEPATH\\scripts\\build
    INCLUDEPATH += $$CAFFEPATH\\scripts\\build\\include
    LIBS += -L$$CAFFEPATH\\build\\lib\\Release
    LIBS += -L$$CAFFEPATH\\scripts\\build\\lib\\Release
    LIBS += -lcaffe -lcaffeproto

    # cuda
    equals(CUDACHECK, "") {
        message(No CUDA detected in the system. Building with CPU_ONLY flag)
        DEFINES += "CPU_ONLY"
        DEFINES += "GLOG_NO_ABBREVIATED_SEVERITIES"
    } else {
        message(CUDA detected. Path:$$(CUDA_PATH))
        CUDAPATH = "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v8.0"
        INCLUDEPATH += $$CUDAPATH\\include
        LIBS += -L$$CUDAPATH\\lib\\x64
        LIBS += -lcudart -lcublas -lcurand     
    }
    
    # opencv
    INCLUDEPATH += $$OTHERINCLUDEPATH\\opencv
    INCLUDEPATH += $$OTHERINCLUDEPATH\\opencv2
    INCLUDEPATH += $$OTHERINCLUDEPATH\\opencv2\\core
    LIBS += -L$$OTHERLIBPATH\\x64\\vc12\\lib
    LIBS += -lopencv_core310 -lopencv_imgproc310 -lopencv_highgui310 -lopencv_imgcodecs310 

    # other dependencies
    equals(MSVCVERSION, "win32-msvc2013") {
        LIBS += -LcaffeLibs_win_VS2013
		LIBS += -L$$BOOSTPATH\\lib64-msvc-12.0
        LIBS += -lboost_system-vc120-mt-1_61 -lboost_thread-vc120-mt-1_61 -lboost_python-vc120-mt-1_61 -lboost_filesystem-vc120-mt-1_61
	}
	equals(MSVCVERSION, "win32-msvc2010") {
        LIBS += -LcaffeLibs_win_VS2010
		LIBS += -L$$BOOSTPATH\\lib64-msvc-10.0
        LIBS += -lboost_system-vc100-mt-1_61 -lboost_thread-vc100-mt-1_61 -lboost_python-vc100-mt-1_61 -lboost_filesystem-vc100-mt-1_61
	}
    LIBS += -L3rdPartyLibs_win
    LIBS += -llibprotobuf -lcaffehdf5 -lcaffehdf5_hl -llibopenblas -lglog -lgflags -llmdb -lleveldb -lntdll 
    
}

unix:!macx {
    INCLUDEPATH	+= /local1/work/caffe/include
    INCLUDEPATH	+= /local1/cuda-8.0/include/
    INCLUDEPATH	+= /local1/work/caffe/.build_release/src

    QMAKE_CXXFLAGS += -fopenmp
    LIBS += -fopenmp
    LIBS += -L$$VAA3DPATH/jba/c++ -lv3dnewmat

  #  LIBS += -L/local2/zhi/caffe/build/lib
    LIBS += -L/local1/work/caffe/build/lib
    LIBS += -lcaffe

    # cuda
    INCLUDEPATH += /usr/local/cuda/include
    LIBS += -L/usr/local/cuda/lib64
    LIBS += -lcudart -lcublas -lcurand
    
    # opencv
   # INCLUDEPATH += /local2/zhi/opencv-2.4.12/include/opencv
   # LIBS += -L/local2/zhi/opencv-2.4.12/release/lib
    INCLUDEPATH += /local1/Downloads/opencv-2.4.12/include/opencv
    LIBS += -L/local1/Downloads/opencv-2.4.12/release/lib
    LIBS += -lopencv_core -lopencv_imgproc -lopencv_highgui

    # other dependencies
   # INCLUDEPATH += /local2/zhi/boost_1_63_0
   # LIBS += -L/local2/zhi/boost_1_63_0/stage/lib
   # LIBS += -L/local2/cuda/cuda-8.0/lib64
   # LIBS += -L/local2/zhi/caffe/.build_release/lib

    INCLUDEPATH += /local1/Downloads/boost_1_63_0
    LIBS += -L/local1/Downloads/boost_1_63_0/stage/lib
    LIBS += -L/local1/Downloads/cuda/lib64
    LIBS += -L/local1/work/caffe/.build_release/lib

    LIBS += -L/usr/lib64/atlas
    LIBS += -L/usr/local/lib
    LIBS += -lglog -lgflags -lprotobuf -lboost_system -lboost_thread -llmdb -lleveldb -lstdc++ -lcblas -latlas
}


macx{
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9

    LIBS += -L$$VAA3DPATH/common_lib/lib_mac64 -lv3dtiff
    LIBS += -L$$VAA3DPATH/jba/c++ -lv3dnewmat

    INCLUDEPATH	+= /Users/zhiz/Documents/work/caffe/include
    INCLUDEPATH	+= /Users/zhiz/Documents/work/caffe/build/include
    INCLUDEPATH	+= /Users/zhiz/Documents/work/caffe/.build_release/src
    INCLUDEPATH	+= /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks/Accelerate.framework/Versions/A/Frameworks/vecLib.framework/Versions/A/Headers/

    LIBS += -L ../../zhi/deep_learning/caffe/lib_mac -Wl,-all_load -lcaffe
    LIBS += -L/usr/local/lib
    LIBS += -lglog -lgflags -lprotobuf -llmdb  -lcblas -lm -lhdf5 -lsz  -lz -lhdf5_hl
    LIBS += -lsnappy
    LIBS += -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs
    LIBS += -lboost_system -lboost_filesystem -lboost_thread-mt

    DEFINES += USE_OPENCV CPU_ONLY
    HEADERS += ../../../released_plugins/v3d_plugins/neurontracing_vn2/app2/my_surf_objs.h
    SOURCES += ../../../released_plugins/v3d_plugins/neurontracing_vn2/app2/my_surf_objs.cpp

}


HEADERS	+= Deep_Neuron_plugin.h 
HEADERS += ../../zhi/deep_learning/prediction/classification.h
HEADERS += ../../../released_plugins/v3d_plugins/mean_shift_center/mean_shift_fun.h
HEADERS += $$VAA3DPATH/basic_c_fun/basic_surf_objs.h
HEADERS += tester.h
HEADERS += DeepNeuronUI.h
HEADERS += imgOperator.h
HEADERS += DLOperator.h

SOURCES	+= Deep_Neuron_plugin.cpp 
SOURCES	+= $$VAA3DPATH/basic_c_fun/v3d_message.cpp
SOURCES += ../../zhi/deep_learning/prediction/classification.cpp
SOURCES += ../../../released_plugins/v3d_plugins/mean_shift_center/mean_shift_fun.cpp
SOURCES += $$VAA3DPATH/basic_c_fun/basic_surf_objs.cpp
SOURCES += tester.cpp
SOURCES += DeepNeuronUI.cpp
SOURCES += imgOperator.cpp
SOURCES += DLOperator.cpp
SOURCES += ../../../released_plugins/v3d_plugins/neurontracing_vn2/app2/my_surf_objs.cpp

FORMS += DeepNeuronForm.ui

TARGET	= $$qtLibraryTarget(Deep_Neuron)
DESTDIR	= ../../../../v3d_external/bin/plugins/DeepNeuron_toolbox/
