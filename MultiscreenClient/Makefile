#编译环境
DEBUG = debug
RELEASE = release
#当前的编译环境
BUILD_ENV = debug

#make命令
MAKE          = make
#qmake命令
QMAKE         = qmake
#目录跳转命令
CD = cd

#qmake的参数
QMAKE_ARG     = -r -spec win32-g++ CONFIG+=$(BUILD_ENV)

#qmake生成的Makefile中的清除任务
CLEAN = clean

#打包时所需要的库文件文件
LibGCC=$(shell which LIBGCC_S_DW2-1.DLL)
MinGW=$(shell which MINGWM10.DLL)
STDCPP=$(shell which libstdc++-6.dll)
ifeq ($(BUILD_ENV),$(RELEASE))
    QtCore=$(shell which QTCORE4.DLL)
    QtGUI=$(shell which QTGUI4.DLL)
    QtNetwork=$(shell which QTNETWORK4.DLL)
    QtXml=$(shell which QTXML4.DLL)
    QtWebkit=$(shell which QtWebKit4.dll)
    Phonon=$(shell which phonon4.dll)
else 
    QtCore=$(shell which QTCORED4.DLL)
    QtGUI=$(shell which QTGUID4.DLL)
    QtNetwork=$(shell which QTNETWORKD4.DLL)
    QtXml=$(shell which QTXMLD4.DLL)
    QtWebkit=$(shell which QtWebKitd4.dll)
    Phonon=$(shell which phonond4.dll)
endif


#编译

build:
	$(QMAKE) MultiScreenClient.pro $(QMAKE_ARG)
	$(MAKE)