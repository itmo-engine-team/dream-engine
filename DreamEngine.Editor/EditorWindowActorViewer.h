#pragma once

#include "EditorWindow.h"
#include "EditorPopupModalAssetChooser.h"
#include "EditorViewport.h"
#include "ActorViewer.h"

class ActorComponentInfo;
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

    void renderViewer();
    void renderInspector();
    void renderComponents();
    void renderComponent(ActorComponentInfo* component);

    void renderSceneComponentsSectionPopup();
    void renderFixedComponentsSectionPopup();

    void saveAsset();
    void reimportAsset();

};

