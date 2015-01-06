    #-------------------------------------------------
#
# Project created by QtCreator 2013-01-02T17:48:01
#
#-------------------------------------------------

QT       += core gui xml sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = figaroEditor

TEMPLATE = app

SOURCES += \	
    mainwindow.cpp \
    main.cpp \
    CoreData.cpp \
    Core.cpp \
    editor/GuiController.cpp \
    editor/TilesetView.cpp \
    editor/TileScene.cpp \
    editor/TileMatrixManager.cpp \
    editor/TileManager.cpp \
    editor/Tile.cpp \
    editor/NpcManager.cpp \
    editor/MapTile.cpp \
    editor/MapScene.cpp \
    editor/MapNpcManager.cpp \
    editor/MapNpc.cpp \
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
    forms/AddMapDialog.cpp

HEADERS  += \	
    mainwindow.h \
    CoreHeader.h \
    CoreData.h \
    Core.h \
    editor/GuiController.h \
    editor/TilesetView.h \
    editor/TileScene.h \
    editor/TileMatrixManager.h \
    editor/TileManager.h \
    editor/Tile.h \
    editor/NPCManager.h \
    editor/MapTile.h \
    editor/MapScene.h \
    editor/MapNPCManager.h \
    editor/MapNpc.h \
    editor/EditorDefinitions.h \
    model/PersistenceModel.h \
    model/PathManager.h \
    model/MainModel.h \
    model/sqlite/SQLiteDB.h \
    model/sqlite/NpcSQLiteManager.h \
    model/sqlite/MapSQLiteManager.h \
    model/sqlite/ConfigSQLiteManager.h \
    model/INpcDBManager.h \
    model/IMapDBManager.h \
    model/IConfigDBManager.h \
    model/binaryModel/Tileset.h \
    model/binaryModel/NPC.h \
    model/binaryModel/Map.h \
    forms/MapPropertiesDialog.h \
    forms/EngineConfigDialog.h \
    forms/AddMapDialog.h

FORMS += mainwindow.ui \
    importtilesetdialog.ui \
    forms/AddMapDialog.ui \
    forms/EngineConfigDialog.ui \
    forms/MapProperties.ui

RESOURCES += \
    resources/resources.qrc

CONFIG += console
