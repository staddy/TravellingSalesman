QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle
CONFIG -= qt

unix|win32-g++ {
    QMAKE_CXXFLAGS_RELEASE -= -O2
    QMAKE_CXXFLAGS_RELEASE += -O3
    QMAKE_CXXFLAGS += -fopenmp
    LIBS += -fopenmp
}
else:win32: {
    QMAKE_CXXFLAGS += /openmp
}

HEADERS += \
    csvdocument.h

SOURCES += \
        csvdocument.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
