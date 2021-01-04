#pragma once

#include "EditorWindow.h"
#include "EditorPopupModalAssetChooser.h"
#include "EditorViewport.h"
#include "TextureAssetInfo.h"
#include "ActorViewer.h"

class ActorAssetInfo;

class EditorWindowActorViewer : public EditorWindow 
{

public:

    EditorWindowActorViewer(Editor* editor, ActorAssetInfo* actorAssetInfo);

    void Update() override;
    void Render() override;

private:

    EditorViewport* viewport = new EditorViewport(ImVec2(16, 9));
    ActorViewer* actorViewer;

    ActorAssetInfo* actorAssetInfo;

    void renderViewer();
    void renderInspector();

    void saveAsset();
    void reimportAsset();

};

