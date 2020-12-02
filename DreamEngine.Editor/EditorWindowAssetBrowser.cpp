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

    drawFilter();
    if (currentParentNode)
    {
        drawFolderLayout(currentParentNode);
    }

    ImGui::End();

    ImGui::Begin(GetName().data());

    drawCommandMenu();

    ImGui::End();

    ImGui::Begin("Content");

    // Add folder icon
    ImGui::Image(iconFolder->GetShaderResourceView(), ImVec2(15, 15));
    ImGui::SameLine();

    // Begin tree
    if (ImGui::TreeNode(assetTree->GetRootNode()->GetName().c_str()))
    {
        currentParentNode = assetTree->GetRootNode();
        drawChildrenFolders(currentParentNode);

        ImGui::TreePop();
    }

    ImGui::End();
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

void EditorWindowAssetBrowser::drawChildrenFolders(FolderNode* parentNode)
{
    for (auto childFolderNode : parentNode->GetChildFolderList())
    {
        ImGui::Image(iconFolder->GetShaderResourceView(), ImVec2(15, 15));
        ImGui::SameLine();
        if (ImGui::TreeNode(childFolderNode->GetName().c_str()))
        {
            currentParentNode = childFolderNode;
            drawChildrenFolders(currentParentNode);
            ImGui::TreePop();
        }
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
