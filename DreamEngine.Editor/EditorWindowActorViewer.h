#pragma once

#include "EditorWindow.h"
#include "EditorViewport.h"
#include "ActorViewer.h"
#include "EditorParamViewer.h"
#include <ActorType.h>

class ActorComponentInfo;
class ActorComponentFixedInfo;
class ActorComponentSceneInfo;
class ActorAssetInfo;

class EditorWindowActorViewer : public EditorWindow 
{

public:

    EditorWindowActorViewer(Editor* editor, ActorAssetInfo* actorAssetInfo);

    void Init() override;
    void Update() override;
    void Render() override;

private:

    EditorViewport* viewport = new EditorViewport(ImVec2(16, 9));
    ActorViewer* actorViewer;

    ActorAssetInfo* actorAssetInfo;
    ActorType actorType;

    ActorComponentSceneInfo* selectedSceneComponent;
    ActorComponentFixedInfo* selectedFixedComponent;
    EditorParamViewer* paramViewer = nullptr;

    int sizeStr;
    std::string* tempStrMass;
    std::string selectableActorType;
    int currentType;

    void renderViewer();
    void renderInspector();
    void renderActorTypeSelectable();
    void renderComponents();
    void renderComponent(ActorComponentInfo* component, bool isSelected);

    void renderSceneComponentInspector();
    void renderFixedComponentInspector();
    void renderComponentParams(ActorComponentInfo* componentInfo);

    void renderSceneComponentsSectionPopup();
    void renderFixedComponentsSectionPopup();

    void saveAsset();
    void reimportAsset();

};

