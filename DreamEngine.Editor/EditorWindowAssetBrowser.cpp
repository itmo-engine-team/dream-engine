#include "EditorWindowAssetBrowser.h"

#include "imgui.h"
#include "Editor.h"
#include "AssetManager.h"
#include "EditorPopupModalText.h"
#include "EditorPopupModalNewAsset.h"
#include "EditorPopupModalDelete.h"

EditorWindowAssetBrowser::EditorWindowAssetBrowser(Editor* editor)
    : EditorWindow("Asset Browser", editor)
{
    assetTree = editor->GetAssetManager()->GetContentAssetTree();
    assetManager = editor->GetAssetManager();

    iconFolder = new Texture(editor->GetGraphics(), editor->GetPathFromEditor(L"Icons/folder.png").c_str());
    iconFile = new Texture(editor->GetGraphics(), editor->GetPathFromEditor(L"Icons/file.png").c_str());
    iconFilter = new Texture(editor->GetGraphics(), editor->GetPathFromEditor(L"Icons/filter.png").c_str());
    iconAsset = new Texture(editor->GetGraphics(), editor->GetPathFromEditor(L"Icons/asset.png").c_str());
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

    // Add folder icon
    ImGui::Image(iconFolder->GetShaderResourceView(), ImVec2(15, 15));
    ImGui::SameLine();

    // Begin tree
    currentParentNode = assetTree->GetRootNode();

    if (ImGui::TreeNodeEx(assetTree->GetRootNode()->GetName().c_str(), ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_NoTreePushOnOpen))
    {
        drawPopupContextMenu();
        ImGui::SetKeyboardFocusHere();
        assetPath = AssetService::CreateFolderPath(currentParentNode);
        drawChildrenFolders(currentParentNode);

       // ImGui::TreePop();
    }
    
    ImGui::End();

    drawPopups();
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

void EditorWindowAssetBrowser::drawPopupContextMenu()
{
    if (ImGui::BeginPopupContextItem())
    {
        if (ImGui::Selectable("New"))
        {
            newAssetPopupModal = new EditorPopupModalNewAsset("New Asset");
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
}

void EditorWindowAssetBrowser::drawNewPopup()
{
    if (!EditorPopupModal::DrawPipeline(newAssetPopupModal))
        return;

    if (newAssetPopupModal->GetResult())
    {
        if (newAssetPopupModal->assetNamePublic != "")
        {
            assetManager->CreateAsset(newAssetPopupModal->selectedAssetType,newAssetPopupModal->assetNamePublic, currentParentNode);
        }
    }

    delete newAssetPopupModal;
    newAssetPopupModal = nullptr;
}

void EditorWindowAssetBrowser::drawDeletePopup()
{
    if (!EditorPopupModal::DrawPipeline(deleteAssetPopupModal))
        return;

    if (deleteAssetPopupModal->GetResult())
    {
        // TODO add functionality
    }

    delete deleteAssetPopupModal;
    deleteAssetPopupModal = nullptr;
}

void EditorWindowAssetBrowser::drawPopups()
{
    drawNewPopup();
    drawDeletePopup();
}

void EditorWindowAssetBrowser::drawFolderLayout(FolderNode* parentNode)
{
    ImVec2 buttonSize(40, 40);
    ImGuiStyle& style = ImGui::GetStyle();
    int foldersCount = parentNode->GetChildFolderList().size();
    float windowVisible = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;

    int assetsCount = parentNode->GetChildAssetList().size();

    for (int i = 0; i < foldersCount; i++)
    {
        ImGui::PushID(i);

        ImGui::BeginGroup();
        if (ImGui::ImageButton(iconFolder->GetShaderResourceView(), buttonSize)) // TODO: fix draw folders
        {
            currentParentNode = parentNode->GetChildFolderList()[i];
            drawFolderLayout(currentParentNode);
        }
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
        ImGui::ImageButton(iconAsset->GetShaderResourceView(), buttonSize); 
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

    if (ImGui::Button("Edit > "))
        ImGui::OpenPopup("my_select_popup");

    if (ImGui::BeginPopup("my_select_popup"))
    {
        if (ImGui::Selectable("New"))
        {
            newAssetPopupModal = new EditorPopupModalNewAsset("New Asset");
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

    ImGui::SameLine();
    if (ImGui::Button("Back")){}
}

void EditorWindowAssetBrowser::drawChildrenFolders(FolderNode* parentNode)
{
    for (auto childFolderNode : parentNode->GetChildFolderList())
    {
        ImGui::Image(iconFolder->GetShaderResourceView(), ImVec2(15, 15));
        ImGui::SameLine();
        
        if (ImGui::TreeNodeEx(childFolderNode->GetName().c_str(), ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_NoTreePushOnOpen))
        {
            currentParentNode = childFolderNode;
            assetPath = AssetService::CreateFolderPath(currentParentNode);
            
            drawChildrenFolders(currentParentNode);
            //ImGui::TreePop();
        }

        drawPopupContextMenu();
    }
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
