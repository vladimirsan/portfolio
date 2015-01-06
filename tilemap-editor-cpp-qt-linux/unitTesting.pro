#-------------------------------------------------
#
# Project created by QtCreator 2013-06-07T19:48:48
#
#-------------------------------------------------

QT       += core gui xml sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = unitTesting
CONFIG   += console

TEMPLATE = app


CCFLAG += -Wconversion-null

SOURCES += \  
    unitTestingMain.cpp \
    mainwindow.cpp \
    CoreData.cpp \
    Core.cpp \
    unitTesting/TileMatrixTests.cpp \
    model/PersistenceModel.cpp \
    model/PathManager.cpp \
    model/MainModel.cpp \
    model/sqlite/SQLiteDB.cpp \
    model/sqlite/NpcSQLiteManager.cpp \
    model/sqlite/MapSQLiteManager.cpp \
    model/sqlite/ConfigSQLiteManager.cpp \
    model/binaryModel/Tileset.cpp \
    model/binaryModel/NPC.cpp \
    model/binaryModel/Map.cpp \
    forms/MapPropertiesDialog.cpp \
    forms/EngineConfigDialog.cpp \
    forms/AddMapDialog.cpp \
    editor/TilesetView.cpp \
    editor/TileScene.cpp \
    editor/TileMatrixManager.cpp \
    editor/TileManager.cpp \
    editor/Tile.cpp \
    editor/MapTile.cpp \
    editor/MapScene.cpp \
    editor/GuiController.cpp \
    unitTesting/ConfigSQLiteManagerTests.cpp \
    unitTesting/MapSQLiteManagerTests.cpp \
    editor/NpcManager.cpp \
    editor/MapNpcManager.cpp \
    editor/MapNpc.cpp \
    unitTesting/NpcManagersTests.cpp \
    unitTesting/NpcSQLiteManagerTests.cpp

HEADERS  += \ 
    mainwindow.h \
    CoreData.h \
    Core.h \
    unitTesting/TileMatrixTests.h \
    model/PersistenceModel.h \
    model/PathManager.h \
    model/MainModel.h \
    model/INpcDBManager.h \
    model/IMapDBManager.h \
    model/IConfigDBManager.h \
    model/sqlite/SQLiteDB.h \
    model/sqlite/NpcSQLiteManager.h \
    model/sqlite/MapSQLiteManager.h \
    model/sqlite/ConfigSQLiteManager.h \
    model/binaryModel/Tileset.h \
    model/binaryModel/NPC.h \
    model/binaryModel/Map.h \
    forms/MapPropertiesDialog.h \
    forms/EngineConfigDialog.h \
    forms/AddMapDialog.h \
    editor/TilesetView.h \
    editor/TileScene.h \
    editor/TileMatrixManager.h \
    editor/TileManager.h \
    editor/Tile.h \
    editor/MapTile.h \
    editor/MapScene.h \
    editor/GuiController.h \
    editor/EditorDefinitions.h \
    unitTesting/ConfigSQLiteManagerTests.h \
    unitTesting/MapSQLiteManagerTests.h \
    editor/NpcManager.h \
    editor/MapNpc.h \
    editor/MapNpcManager.h \
    unitTesting/NpcManagersTests.h \
    unitTesting/NpcSQLiteManagerTests.h

LIBS += gtest.a

FORMS += \
    mainwindow.ui

RESOURCES += \
    resources/resources.qrc
