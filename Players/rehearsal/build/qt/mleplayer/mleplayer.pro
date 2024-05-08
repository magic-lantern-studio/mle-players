QT += widgets opengl

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

unix {
    MLE_ROOT=/opt/MagicLantern
}
# Suppress the default RPATH
unix: QMAKE_LFLAGS_RPATH=
unix: QMAKE_LFLAGS += \
    "-Wl,-rpath,$${MLE_ROOT}/lib/mle/qt/rehearsal \
     -Wl,-rpath,$${MLE_ROOT}/lib/mle/rehearsal \
     -Wl,-rpath,$${MLE_ROOT}/lib \
     -Wl,-rpath,/usr/lib/qt5/bin"
#unix: QMAKE_LFLAGS += "-Wl,-rpath,\'\$$ORIGIN\'"

INCLUDEPATH += \
    $$PWD/../../../include \
    /opt/MagicLantern/include \
    /usr/local/include

DEFINES += \
    MLE_NOT_DLL \
    MLE_DIGITAL_WORKPRINT \
    MLE_REHEARSAL \
    MLE_SOQT \
    MLE_QT

SOURCES += \
        $$PWD/../../../src/main.cxx \
        $$PWD/../../../src/title.cxx

unix:!macx {
LIBS = \
        -L$${MLE_ROOT}/lib/mle/rehearsal -lmlert \
        -L$${MLE_ROOT}/lib/mle/qt/rehearsal -lmleatk \
        -L$${MLE_ROOT}/lib -lDWP -lmlmath -lmlutil \
        -L$${MLE_ROOT}/lib/mle/qt/rehearsal -livroles \
        $${MLE_ROOT}/lib/mle/qt/rehearsal/libMle3dRole.so \
        $${MLE_ROOT}/lib/mle/qt/rehearsal/libMle3dColorMapMediaRef.so \
        $${MLE_ROOT}/lib/mle/qt/rehearsal/libMle3dModelMediaRef.so \
        $${MLE_ROOT}/lib/mle/qt/rehearsal/libMle3dTextureMapMediaRef.so \
        $${MLE_ROOT}/lib/mle/qt/rehearsal/libMle3dSet.so \
        $${MLE_ROOT}/lib/mle/qt/rehearsal/libMleIvStage.so \
        $${MLE_ROOT}/lib/mle/qt/rehearsal/libMle2dRole.so \
        $${MLE_ROOT}/lib/mle/qt/rehearsal/libMle2dSet.so \
        $${MLE_ROOT}/lib/mle/qt/rehearsal/libmlloaders.so \
        -lCoin -lSoQt
}

macx {
LIBS = \
        -L$${MLE_ROOT}/lib/mle/qt/rehearsal -lmlert \
        -L$${MLE_ROOT}/lib/mle/qt/rehearsal -lmleatk \
        -L$${MLE_ROOT}/lib -lDWP -lmlmath -lmlutil \
        -L$${MLE_ROOT}/lib/mle/qt.rehearsal -livroles \
        $${MLE_ROOT}/lib/mle/qt/rehearsal/libMle3dRole.dylib \
        $${MLE_ROOT}/lib/mle/qt/rehearsal/libMle3dColorMapMediaRef.dylib \
        $${MLE_ROOT}/lib/mle/qt/rehearsal/libMle3dModelMediaRef.dylib \
        $${MLE_ROOT}/lib/mle/qt/rehearsal/libMle3dTextureMapMediaRef.dylib \
        $${MLE_ROOT}/lib/mle/qt/rehearsal/libMle3dSet.dylib \
        $${MLE_ROOT}/lib/mle/qt/rehearsal/libMleIvStage.dylib \
        $${MLE_ROOT}/lib/mle/qt/rehearsal/libMle2dRole.dylib \
        $${MLE_ROOT}/lib/mle/qt/rehearsal/libMle2dSet.dylib \
        $${MLE_ROOT}/lib/mle/qt/rehearsal/libmlloaders.dylib \
        -L/usr/local/lib -lCoin -lSoQt
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/MagicLantern/bin
!isEmpty(target.path): INSTALLS += target
