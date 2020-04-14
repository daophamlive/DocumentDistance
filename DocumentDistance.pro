TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        DistanceCalculatorCosine.cpp \
        FileReaderIFstream.cpp \
        main.cpp

HEADERS += \
    DefaultDefines.h \
    DistanceCalculatorCosine.h \
    FileReaderIFstream.h \
    IDistanceCalculator.h \
    IFileReader.h \
    enDistanceResult.h
