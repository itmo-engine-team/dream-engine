#include "EditorWindowAssetBrowser.h"
#include "imgui.h"

EditorWindowAssetBrowser::EditorWindowAssetBrowser(Graphics* graphics)
    : EditorWindow("Asset Browser", graphics)
{
    assetTree = AssetServices::CreateDebugAssetTree();

    iconFolder = new Texture(graphics, L"Engine/Editor/icons/folder.png");
    iconFile = new Texture(graphics, L"Engine/Editor/icons/file.png");
    iconFilter = new Texture(graphics, L"Engine/Editor/icons/filter.png");
    iconAsset = new Texture(graphics, L"Engine/Editor/icons/asset.png");
}

void EditorWindowAssetBrowser::Update()
{

}

void EditorWindowAssetBrowser::Render()
{
    ImGui::Begin(" ");

    createFilter();
    if (currentParentNode)
    {
        folderLayout(currentParentNode);
    }

    ImGui::End();

    ImGui::Begin(GetName().data());

    createCommandMenu();

    ImGui::End();

    ImGui::Begin("Content");

    //add folder icon
    ImGui::Image(iconFolder->GetShaderResourceView(), ImVec2(15, 15));
    ImGui::SameLine();

    //begin tree
    if (ImGui::TreeNode(assetTree->GetRootNode()->GetName().c_str()))
    {
        currentParentNode = assetTree->GetRootNode();
        addTreeFolders(currentParentNode);

        ImGui::TreePop();
    }

    ImGui::End();
}

void EditorWindowAssetBrowser::createFilter()
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

void EditorWindowAssetBrowser::popupContextMenu()
{
    if (ImGui::BeginPopupContextItem())
    {
        if (ImGui::MenuItem("New", "")) {}
        if (ImGui::MenuItem("Save", "")) {}
        if (ImGui::MenuItem("Delete ", "")) {}
        if (ImGui::MenuItem("Move", "")) {}
        if (ImGui::MenuItem("Duplicate", " ")) {}
        if (ImGui::MenuItem("Rename", " ")) {}
        if (ImGui::MenuItem("Back", " "))
            ImGui::CloseCurrentPopup();
        ImGui::EndPopup();
    }
}

void EditorWindowAssetBrowser::folderLayout(FolderNode* parentNode)
{
    ImVec2 buttonSize(40, 40);
    ImGuiStyle& style = ImGui::GetStyle();
    int folders_count = parentNode->GetChildFolderList().size();
    float windowVisible = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;

    int assets_count = parentNode->GetChildAssetList().size();

    for (int i = 0; i < folders_count; i++)
    {
        ImGui::PushID(i);

        ImGui::BeginGroup();
        if (ImGui::ImageButton(iconFolder->GetShaderResourceView(), buttonSize)) //need to fix
        {
            currentParentNode = parentNode->GetChildFolderList()[i];
            folderLayout(currentParentNode);
        }
        ImGui::Text(parentNode->GetChildFolderList()[i]->GetName().c_str());
        ImGui::EndGroup();

        float lastButton = ImGui::GetItemRectMax().x;
        float nextButton = lastButton + style.ItemSpacing.x + buttonSize.x; // Expected position if next button was on same line
        if (i + 1 < folders_count && nextButton < windowVisible)
            ImGui::SameLine();
        ImGui::PopID();
    }

    if (folders_count)
        ImGui::SameLine();

    for (int i = 0; i < assets_count; i++)
    {
        ImGui::PushID(i);

        ImGui::BeginGroup();
        ImGui::ImageButton(iconAsset->GetShaderResourceView(), buttonSize); 
        ImGui::Text(parentNode->GetChildAssetList()[i]->GetName().c_str());
        ImGui::EndGroup();

        float lastButton = ImGui::GetItemRectMax().x;
        float nextButton = lastButton + style.ItemSpacing.x + buttonSize.x; // Expected position if next button was on same line
        if (i + 1 < assets_count && nextButton < windowVisible)
            ImGui::SameLine();
        ImGui::PopID();
    }
}

void EditorWindowAssetBrowser::createCommandMenu()
{
    ImGui::Image(iconFile->GetShaderResourceView(), ImVec2(20, 20));
    ImGui::SameLine();

    if (ImGui::Button("Add > "))
        ImGui::OpenPopup("my_select_popup");

    if (ImGui::BeginPopup("my_select_popup"))
    {
        if (ImGui::Selectable("New")) {}
        if (ImGui::Selectable("Save")) {}
        if (ImGui::Selectable("Delete")) {}
        if (ImGui::Selectable("Move")) {}
        if (ImGui::Selectable("Duplicate")) {}
        if (ImGui::Selectable("Rename")) {}
        if (ImGui::Selectable("Back")) {}

        ImGui::EndPopup();
    }
}

void EditorWindowAssetBrowser::addTreeFolders(FolderNode* parentNode)
{
    for (int i = 0; i < parentNode->GetChildFolderList().size(); i++)
    {
        ImGui::Image(iconFolder->GetShaderResourceView(), ImVec2(15, 15));
        ImGui::SameLine();
        if (ImGui::TreeNode(parentNode->GetChildFolderList()[i]->GetName().c_str()))
        {
            currentParentNode = parentNode->GetChildFolderList()[i];
            addTreeFolders(currentParentNode);
            ImGui::TreePop();
        }
    }
}

void EditorWindowAssetBrowser::addTreeAssets(FolderNode* parentNode)
{
    for (int i = 0; i < parentNode->GetChildAssetList().size(); i++)
    {
        ImGui::Image(iconAsset->GetShaderResourceView(), ImVec2(15, 15));
        ImGui::SameLine();
        ImGui::Selectable(parentNode->GetChildAssetList()[i]->GetName().c_str());
    }
}
