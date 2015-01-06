#ifndef VIEWDEFINITIONS_H
#define VIEWDEFINITIONS_H

typedef enum
{
	InitialState,InitialDirLoadedState,MapLoadedState,NPCSelectedState
}MainWindowState;

typedef enum
{
    NoAction,PencilAction,EraserAction,PaintCanAction,InformationAction,MagicEraserAction,SelectorAction
}ToolbarAction;

enum Layer
{
	vBackgroundLayer,vSolidLayer,vForegroundLayer,vTopLayer = 10
	
};

#endif // VIEWDEFINITIONS_H
