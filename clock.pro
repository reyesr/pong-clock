TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += $$system(sdl2-config --cflags) -O2 -Wall

LIBS += $$system(sdl2-config --libs) -lSDL2 -lSDL2_image

SOURCES += src/main.cpp \
    src/simpleclock.cpp \
    src/ponggame.cpp \
    src/graphics.cpp \
    src/utils.cpp \
    src/resourcefont.cpp \
    src/sdlcontext.cpp \
    src/resources.cpp

HEADERS += \
    src/simpleclock.h \
    src/ponggame.h \
    src/graphics.h \
    src/utils.h \
    src/resourcefont.h \
    src/sdlcontext.h \
    src/resources.h

