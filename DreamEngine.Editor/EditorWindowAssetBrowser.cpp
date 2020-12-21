#include "EditorWindowAssetBrowser.h"

#include "imgui.h"
#include "Editor.h"
#include "AssetManager.h"
#include "EditorPopupModalText.h"

#include "ErrorLogger.h"

EditorWindowAssetBrowser::EditorWindowAssetBrowser(Editor* editor)
    : EditorWindow("Asset Browser", editor)
{
    assetTree = editor->GetAssetManager()->GetContentAssetTree();
    assetManager = editor->GetAssetManager();

    setCurrentParentNode(assetTree->GetRootNode());

    iconFolder = new Texture(editor->GetGraphics(), editor->GetPathFromEditor(L"Icons/folder.png").c_str());
    iconFile = new Texture(editor->GetGraphics(), editor->GetPathFromEditor(L"Icons/file.png").c_str());
    iconFilter = new Texture(editor->GetGraphics(), editor->GetPathFromEditor(L"Icons/filter.png").c_str());
    iconAsset = new Texture(editor->GetGraphics(), editor->GetPathFromEditor(L"Icons/asset.png").c_str());
    iconActor = new Texture(editor->GetGraphics(), editor->GetPathFromEditor(L"Icons/actorIcon.png").c_str());
    iconScene = new Texture(editor->GetGraphics(), editor->GetPathFromEditor(L"Icons/sceneIcon.png").c_str());
    iconModel = new Texture(editor->GetGraphics(), editor->GetPathFromEditor(L"Icons/modelIcon.png").c_str());
    iconTexture = new Texture(editor->GetGraphics(), editor->GetPathFromEditor(L"Icons/textureIcon.png").c_str());
    iconBP = new Texture(editor->GetGraphics(), editor->GetPathFromEditor(L"Icons/blueprintIcon.png").c_str());
    iconBT = new Texture(editor->GetGraphics(), editor->GetPathFromEditor(L"Icons/btIcon.png").c_str());

    MAP_ASSET_TYPE_TO_TEXTURE = {
       { AssetType::Actor, iconActor },
       { AssetType::Scene, iconScene },
       { AssetType::Model, iconModel },
       { AssetType::Texture, iconTexture },
    };
}

void EditorWindowAssetBrowser::Update()
{

}

void EditorWindowAssetBrowser::Render()
{
    ImGui::Begin(" ");

    drawFilter();
    if (currentParentNode)
    {
        drawFolderLayout(currentParentNode);
    }

    ImGui::End();

    ImGui::Begin(GetName().data());

    drawCommandMenu();

    ImGui::SameLine();
    ImGui::Text(assetPath.c_str());
   
    ImGui::End();

    ImGui::Begin("Content");
    
    drawFolderTreeNode(assetTree->GetRootNode());
    
    ImGui::End();

    drawPopups();
}

void EditorWindowAssetBrowser::setCurrentParentNode(FolderNode* newParentNode)
{
    currentParentNode = newParentNode;
    assetPath = AssetService::CreateFolderPath(currentParentNode);
}

Texture* EditorWindowAssetBrowser::getAssetIconType(AssetNode* currentAssetNode)
{
    return MAP_ASSET_TYPE_TO_TEXTURE.find(currentAssetNode->GetAssetInfo()->GetAssetType())->second;
}

void EditorWindowAssetBrowser::drawFilter()
{
    ImGui::Image(iconFilter->GetShaderResourceView(), ImVec2(20, 20));
    ImGui::SameLine();

    static ImGuiTextFilter filter;
    filter.Draw();
    ImGui::Separator();
    const char* fileNames[] = { "aaa1.c", "bbb1.c", "ccc1.c", "aaa2.cpp", "bbb2.cpp", "ccc2.cpp", "abc.h", "hello, world" };
    for (int i = 0; i < IM_ARRAYSIZE(fileNames); i++)
        if (filter.PassFilter(fileNames[i]))
            ImGui::BulletText("%s", fileNames[i]);
}

void EditorWindowAssetBrowser::drawFolderContextMenu(FolderNode* selectedFolderNode)
{
    if (ImGui::BeginPopupContextItem())
    {
        if (ImGui::Selectable("New Folder"))
        {
            newFolderPopupModal = new EditorPopupModalNewFolder(selectedFolderNode);
        }

        if (ImGui::Selectable("New Asset"))
        {
            newAssetPopupModal = new EditorPopupModalNewAsset(selectedFolderNode);
        }

        if (ImGui::Selectable("Delete"))
        {
            deleteFolderPopupModal = new EditorPopupModalDeleteFolder(selectedFolderNode);
        }

        if (ImGui::Selectable("Move")) {}

        if (ImGui::Selectable("Rename")) 
        {
            renameFolderPopupModal = new EditorPopupModalRenameFolder(selectedFolderNode, selectedFolderNode->GetName());
        }
        
        ImGui::EndPopup();
    }
}

void EditorWindowAssetBrowser::drawAssetContextMenu(AssetNode* selectedAssetNode)
{
    if (ImGui::BeginPopupContextItem())
    {
        if (ImGui::Selectable("Open"))
        {
            //TODO: open asset
        }

        if (ImGui::Selectable("Delete"))
        {
            deleteAssetPopupModal = new EditorPopupModalDeleteAsset(selectedAssetNode);
            currentAssetNode = selectedAssetNode;
        }

        if (ImGui::Selectable("Move")) {}
        if (ImGui::Selectable("Duplicate")) 
        {
            duplicateAssetPopupModal = new EditorPopupModalDuplicateAsset(selectedAssetNode);
            currentAssetNode = selectedAssetNode;
        }
        if (ImGui::Selectable("Rename")) 
        {
            renameAssetPopupModal = new EditorPopupModalRenameAsset(selectedAssetNode, selectedAssetNode->GetName());
            currentAssetNode = selectedAssetNode;
        }

        ImGui::EndPopup();
    }
}

void EditorWindowAssetBrowser::drawNewAssetPopup()
{
    if (!EditorPopupModal::DrawPipeline(newAssetPopupModal))
        return;

    if (newAssetPopupModal->GetResult())
    {
        auto result = assetManager->CreateAsset(
            newAssetPopupModal->GetAssetType(),
            newAssetPopupModal->GetAssetName(),
            newAssetPopupModal->GetFolderNode()
        );

        if (!result.isSuccess)
        {
            errorPopupModal = new EditorPopupModalError(result.error);
        }
    }

    delete newAssetPopupModal;
    newAssetPopupModal = nullptr;
}

void EditorWindowAssetBrowser::drawNewFolderPopup()
{
    if (!EditorPopupModal::DrawPipeline(newFolderPopupModal))
        return;

    if (newFolderPopupModal->GetResult())
    {
        auto result = assetManager->CreateFolder(
            newFolderPopupModal->GetFolderName(),
            newFolderPopupModal->GetFolderNode()
        );

        if (!result.isSuccess)
        {
            errorPopupModal = new EditorPopupModalError(result.error);
        }
    }

    delete newFolderPopupModal;
    newFolderPopupModal = nullptr;
}

void EditorWindowAssetBrowser::drawDeleteFolderPopup()
{
    if (!EditorPopupModal::DrawPipeline(deleteFolderPopupModal))
        return;

    if (deleteFolderPopupModal->GetResult())
    {
       auto result = assetManager->RemoveFolder(deleteFolderPopupModal->GetFolderNode(), deleteFolderPopupModal->GetIsRecursive());

       if (result.isSuccess)
       {
           setCurrentParentNode(assetTree->GetRootNode());
       }
       else
       {
           errorPopupModal = new EditorPopupModalError(result.error);
       }
    }

    delete deleteFolderPopupModal;
    deleteFolderPopupModal = nullptr;
}

void EditorWindowAssetBrowser::drawDeleteAssetPopup()
{
    if (!EditorPopupModal::DrawPipeline(deleteAssetPopupModal))
        return;

    if (deleteAssetPopupModal->GetResult())
    {
        auto result = assetManager->RemoveAsset(currentAssetNode);

        if (result.isSuccess)
        {
            currentAssetNode = nullptr;
        }
        else
        {
            errorPopupModal = new EditorPopupModalError(result.error);
        }
    }

    delete deleteAssetPopupModal;
    deleteAssetPopupModal = nullptr;
}

void EditorWindowAssetBrowser::drawRenameFolderPopup()
{
    if (!EditorPopupModal::DrawPipeline(renameFolderPopupModal))
        return;

    if (renameFolderPopupModal->GetResult())
    {
        auto result = assetManager->RenameFolder(renameFolderPopupModal->GetFolderNode(), renameFolderPopupModal->GetNewFolderName());
        
        if (!result.isSuccess)
        {
            errorPopupModal = new EditorPopupModalError(result.error);
        }
    }

    delete renameFolderPopupModal;
    renameFolderPopupModal = nullptr;
}

void EditorWindowAssetBrowser::drawRenameAssetPopup()
{
    if(!EditorPopupModal::DrawPipeline(renameAssetPopupModal))
        return;

    if (renameAssetPopupModal->GetResult())
    {
        auto result = assetManager->RenameAsset(currentAssetNode, renameAssetPopupModal->GetNewAssetName());
        
        if (!result.isSuccess)
        {
            errorPopupModal = new EditorPopupModalError(result.error);
        }
    }

    delete renameAssetPopupModal;
    renameAssetPopupModal = nullptr;
}

void EditorWindowAssetBrowser::drawDuplicateAssetPopup()
{
    if (!EditorPopupModal::DrawPipeline(duplicateAssetPopupModal))
        return;

    if (duplicateAssetPopupModal->GetResult())
    {
        auto result = assetManager->DuplicateAsset(currentAssetNode, duplicateAssetPopupModal->GetNewAssetName());
        
        if (!result.isSuccess)
        {
            errorPopupModal = new EditorPopupModalError(result.error);
        }
    }

    delete duplicateAssetPopupModal;
    duplicateAssetPopupModal = nullptr;
}

void EditorWindowAssetBrowser::drawErrorPopup()
{
    if (!EditorPopupModal::DrawPipeline(errorPopupModal))
        return;

    delete errorPopupModal;
    errorPopupModal = nullptr;
}

void EditorWindowAssetBrowser::drawPopups()
{
    drawNewAssetPopup();
    drawNewFolderPopup();
    drawDeleteFolderPopup();
    drawDeleteAssetPopup();
    drawRenameFolderPopup();
    drawRenameAssetPopup();
    drawDuplicateAssetPopup();
    drawErrorPopup();
}

void EditorWindowAssetBrowser::drawFolderLayout(FolderNode* parentNode)
{
    ImVec2 buttonSize(40, 40);
    ImGuiStyle& style = ImGui::GetStyle();
    float windowVisible = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;

    int foldersCount = parentNode->GetChildFolderList().size();
    int assetsCount = parentNode->GetChildAssetList().size();

    for (int i = 0; i < foldersCount; i++)
    {
        ImGui::PushID(i);

        ImGui::BeginGroup();
        if (ImGui::ImageButton(iconFolder->GetShaderResourceView(), buttonSize))
        {
            setCurrentParentNode(parentNode->GetChildFolderList()[i]);
        }
        
        drawFolderContextMenu(parentNode->GetChildFolderList()[i]);

        ImGui::Text(parentNode->GetChildFolderList()[i]->GetName().c_str());
        ImGui::EndGroup();

        float lastButton = ImGui::GetItemRectMax().x;
        float nextButton = lastButton + style.ItemSpacing.x + buttonSize.x; // Expected position if next button was on same line
        if (i + 1 < foldersCount && nextButton < windowVisible)
            ImGui::SameLine();
        ImGui::PopID();
    }

    if (foldersCount)
        ImGui::SameLine();

    for (int i = 0; i < assetsCount; i++)
    {
        ImGui::PushID(i);

        ImGui::BeginGroup();

        iconAsset = getAssetIconType(parentNode->GetChildAssetList()[i]);

        if (ImGui::ImageButton(iconAsset->GetShaderResourceView(), buttonSize))
        {
            currentAssetNode = parentNode->GetChildAssetList()[i];
        }

        drawAssetContextMenu(parentNode->GetChildAssetList()[i]);

        ImGui::Text(parentNode->GetChildAssetList()[i]->GetName().c_str());
        ImGui::EndGroup();

        float lastButton = ImGui::GetItemRectMax().x;
        float nextButton = lastButton + style.ItemSpacing.x + buttonSize.x; // Expected position if next button was on same line
        if (i + 1 < assetsCount && nextButton < windowVisible)
            ImGui::SameLine();
        ImGui::PopID();
    }
}

void EditorWindowAssetBrowser::drawCommandMenu()
{
    ImGui::Image(iconFile->GetShaderResourceView(), ImVec2(20, 20));
    ImGui::SameLine();

    /* if (ImGui::Button("Edit > "))
        ImGui::OpenPopup("my_select_popup");

    if (ImGui::BeginPopup("my_select_popup"))
    {
        if (ImGui::Selectable("New"))
        {
            newAssetPopupModal = new EditorPopupModalNewAsset(currentParentNode);
        }

        if (ImGui::Selectable("Delete")) 
        {
            // TODO: init draw delete popup
        }

        if (ImGui::Selectable("Move")) {}
        if (ImGui::Selectable("Duplicate")) {}
        if (ImGui::Selectable("Rename")) {}
        
        ImGui::EndPopup();
    }
    
    ImGui::SameLine();*/
    if (ImGui::Button("Back"))
    {
        if (currentParentNode->GetParent() != nullptr)
            setCurrentParentNode(currentParentNode->GetParent());
    }
}

void EditorWindowAssetBrowser::drawFolderTreeNode(FolderNode* folderNode, int level)
{
    drawFolderTreeNodePadding(level);

    ImGui::Image(iconFolder->GetShaderResourceView(), ImVec2(15, 15));
    ImGui::SameLine();

    bool treeExpanded = false;

    auto flags = ImGuiTreeNodeFlags_OpenOnDoubleClick
        | ImGuiTreeNodeFlags_FramePadding
        | ImGuiTreeNodeFlags_NoTreePushOnOpen;

    if (currentParentNode == folderNode)
        flags |= ImGuiTreeNodeFlags_Selected;

    if (ImGui::TreeNodeEx(folderNode->GetName().c_str(), flags))
    {

        if (ImGui::IsItemClicked())
        {
            setCurrentParentNode(folderNode);
        }

        treeExpanded = true;

        setCurrentParentNode(currentParentNode);

        drawFolderContextMenu(folderNode);

        for (auto childFolderNode : folderNode->GetChildFolderList())
        {
            drawFolderTreeNode(childFolderNode, level + 1);
        }
    }

    if (!treeExpanded)
    {
        if (ImGui::IsItemClicked())
        {
            setCurrentParentNode(folderNode);
        }

        drawFolderContextMenu(folderNode);
    }
    
}

void EditorWindowAssetBrowser::drawFolderTreeNodePadding(int level)
{
    if (level == 0) return;

    const static std::string PADDING_CONST = " ";
    std::string padding;

    for (int i = 0; i < level; i++)
    {
        padding += PADDING_CONST;
    }
    ImGui::Text(padding.data());
    ImGui::SameLine();
}

void EditorWindowAssetBrowser::drawChildrenAssets(FolderNode* parentNode)
{
    for (auto assetNode : parentNode->GetChildAssetList())
    {
        ImGui::Image(iconAsset->GetShaderResourceView(), ImVec2(15, 15));
        ImGui::SameLine();
        ImGui::Selectable(assetNode->GetName().c_str());
    }
}
