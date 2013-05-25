#-------------------------------------------------
#
# Project created by QtCreator 2013-03-11T13:05:59
#
#-------------------------------------------------


SOURCES +=  mainwidget.cpp \
    titlewidget.cpp \
    screencontrolwidget.cpp \
    screenconfigwidget.cpp \
    toolbarwidget.cpp \
    layout/rectangle.cpp \
    layout/layoutwidget.cpp \
    layout/screenwidget.cpp \
    entity/displayinfo.cpp \
    entity/basewidget.cpp \
    entity/screen.cpp \
    cardconfig/cardconfigwidget.cpp \
    entity/basedata.cpp \
    config/configini.cpp \
    skin/skinmanager.cpp \
    socket/msocket.cpp \
    entity/screenconfig.cpp \
    layout/montagelayout.cpp\
    treewidget/organizationtree.cpp \
    treewidget/basetreewidget.cpp \
    request/restrequest.cpp \
    request/requestManager.cpp \
    request/organizationrequest.cpp \
    entity/organization.cpp \
    entity/entity.cpp \
    entity/dvr.cpp \
    entity/channel.cpp \
    request/http.cpp \
    request/get_rest.cpp \
    request/NetCommon.cpp\
    entity/subscreen.cpp\
    cardconfig/screentoolbar.cpp \
    layout/playerlayout.cpp \
    entity/playscreen.cpp \
    entity/playwindow.cpp \
    entity/previewwindow.cpp \
    entity/interactdata.cpp \
    config/baseitem.cpp \
    config/configitem.cpp \
    config/configxml.cpp \
    config/mergeitem.cpp \
    config/mergexml.cpp \
    login.cpp \
    request/loginrequest.cpp \
    pollingschemewidget.cpp \
    request/grouprequest.cpp \
    entity/group.cpp \
    selectgroupdlg.cpp \
    treewidget/grouptree.cpp \
    config/schemeitem.cpp \
    config/schemexml.cpp \
    treewidget/schemetree.cpp \
    layoutmanager/walllayout.cpp \
    layoutmanager/smallscreen.cpp \
    layoutmanager/layoutarea.cpp \
    layoutmanager/windowlayout.cpp

HEADERS  += mainwidget.h \
    titlewidget.h \
    screencontrolwidget.h \
    screenconfigwidget.h \
    toolbarwidget.h \
    layout/rectangle.h \
    layout/layoutwidget.h \
    layout/screenwidget.h \
    entity/displayinfo.h \
    entity/basewidget.h \
    entity/screen.h \
    cardconfig/cardconfigwidget.h \
#    socket/isocket.h \
    entity/basedata.h \
#    socket/initsocket.h \
#    socket/identific.h \
    config/configini.h \
#    socket/isocketfactory.h \
#    socket/identificfactory.h \
#    socket/initsocketfactory.h \
    socket/socket_cmd.h \
    skin/skinmanager.h \
    socket/msocket.h \
    entity/screenconfig.h \
    layout/montagelayout.h\
    treewidget/organizationtree.h \
    treewidget/basetreewidget.h \
    request/restrequest.h \
    request/requestManager.h \
    request/organizationrequest.h \
    entity/organization.h \
    entity/entity.h \
    entity/dvr.h \
    entity/channel.h \
    const.h \
    request/request_global.h \
    request/request_const.h \
    request/http.h \
    request/get_rest.h \
    request/NetCommon.h\
    entity/subscreen.h\
    cardconfig/screentoolbar.h \
    layout/playerlayout.h \
    entity/playscreen.h \
    entity/playwindow.h \
    entity/previewwindow.h \
    entity/interactdata.h \
    config/baseitem.h \
    config/configitem.h \
    config/configxml.h \
    config/mergeitem.h \
    config/mergexml.h \
    login.h \
    request/loginrequest.h \
    pollingschemewidget.h \
    request/grouprequest.h \
    entity/group.h \
    selectgroupdlg.h \
    treewidget/grouptree.h \
    config/schemeitem.h \
    config/schemexml.h \
    treewidget/schemetree.h \
    layoutmanager/walllayout.h \
    layoutmanager/smallscreen.h \
    layoutmanager/layoutarea.h \
    layoutmanager/windowlayout.h


LIBS += ../MultiscreenClient/json/libqjson.a

FORMS    += mainwidget.ui \
    titlewidget.ui \
    screencontrolwidget.ui \
    screenconfigwidget.ui \
    toolbarwidget.ui \
    layout/rectangle.ui \
    layout/layoutwidget.ui \
    layout/screenwidget.ui \
    entity/basewidget.ui \
    cardconfig/cardconfigwidget.ui\
    cardconfig/screentoolbar.ui \
    toolbarwidget.ui \
    login.ui \
    pollingschemewidget.ui \
    selectgroupdlg.ui \
    layoutmanager/walllayout.ui \
    layoutmanager/smallscreen.ui

INCLUDEPATH = layout\
                entity\
                cardconfig\
                socket\
                skin\
                json\
                treewidget\
                request\
                config\
                layoutmanager
