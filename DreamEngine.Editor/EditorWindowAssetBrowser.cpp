#include "EditorWindowAssetBrowser.h"
#include "imgui.h"

EditorWindowAssetBrowser::EditorWindowAssetBrowser(Graphics* graphics)
    : EditorWindow("Asset Browser", graphics)
{
    iconFolder = new Texture(graphics, L"Engine/Editor/icons/folder.png");
    iconFile = new Texture(graphics, L"Engine/Editor/icons/file.png");
    iconFilter = new Texture(graphics, L"Engine/Editor/icons/filter.png");
}

void EditorWindowAssetBrowser::Update()
{

}

void EditorWindowAssetBrowser::Render()
{
    ImGui::Begin(" ");

    ImGui::Image(iconFilter->GetShaderResourceView(),ImVec2(20,20));
    ImGui::SameLine();
    //filtering
    static ImGuiTextFilter filter;
    filter.Draw();
    ImGui::Separator();
    const char* fileNames[] = { "aaa1.c", "bbb1.c", "ccc1.c", "aaa2.cpp", "bbb2.cpp", "ccc2.cpp", "abc.h", "hello, world" }; //здесь названия всех файлов
    for (int i = 0; i < IM_ARRAYSIZE(fileNames); i++)
        if (filter.PassFilter(fileNames[i]))
            ImGui::BulletText("%s", fileNames[i]);
    //end filtering

    if (layoutChange)
    {
        folderLayout();
    }

    ImGui::End();

    ImGui::Begin(GetName().data());

   /* ImGuiIO& io = ImGui::GetIO();
    ImTextureID my_tex_id = io.Fonts->TexID;
    float my_tex_w = (float)io.Fonts->TexWidth;
    float my_tex_h = (float)io.Fonts->TexHeight;

    ImVec2 size = ImVec2(40.0f, 40.0f);                        // Size of the image we want to make visible
    ImVec2 uv0 = ImVec2(0.0f, 0.0f);                           // UV coordinates for lower-left
    ImVec2 uv1 = ImVec2(32.0f / my_tex_w, 32.0f / my_tex_h);   // UV coordinates for (32,32) in our texture
    ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);       // Black background
    ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);     // No tint
    ImGui::ImageButton(iconFolder->GetShaderResourceView(), size, uv0, uv1, 3, bg_col, tint_col);
    ImGui::SameLine();*/

    ImGui::Image(iconFile->GetShaderResourceView(), ImVec2(20, 20));
    ImGui::SameLine();

    if (ImGui::Button("Add > "))
        ImGui::OpenPopup("my_select_popup");

    if (ImGui::BeginPopup("my_select_popup"))
    {
        if (ImGui::Selectable("New")){}
        if (ImGui::Selectable("Save")) {}
        if (ImGui::Selectable("Delete")) {}
        if (ImGui::Selectable("Move")) {}
        if (ImGui::Selectable("Duplicate")) {}
        if (ImGui::Selectable("Rename")) {}
        if (ImGui::Selectable("Back")) {}

        ImGui::EndPopup();
    }

    ImGui::End();

    ImGui::Begin("Content");
    ImGui::Image(iconFolder->GetShaderResourceView(), ImVec2(15, 15));
    ImGui::SameLine();
    if (ImGui::TreeNode("Content"))
    {

        layoutChange = true;
        ImGui::Image(iconFolder->GetShaderResourceView(), ImVec2(15, 15));
        ImGui::SameLine();
        if (ImGui::TreeNode("Geometry"))
        {
            for (int i = 0; i < 5; i++)
            {
                if (i == 0)
                    ImGui::SetNextItemOpen(true, ImGuiCond_Once);

                ImGui::Image(iconFolder->GetShaderResourceView(), ImVec2(15, 15));
                ImGui::SameLine();
                if (ImGui::TreeNode((void*)(intptr_t)i, "Child %d", i))
                {
                    ImGui::Text("geometry element");
                    ImGui::SameLine();
                    if (ImGui::SmallButton("open")) { /* do something*/ }
                    ImGui::TreePop();
                }
            }
            ImGui::TreePop();
        }
        ImGui::TreePop();
    }

    ImGui::Image(iconFolder->GetShaderResourceView(), ImVec2(15, 15));
    ImGui::SameLine();
    if (ImGui::TreeNode("Engine Content"))
    {
        ImGui::Image(iconFolder->GetShaderResourceView(), ImVec2(15, 15));
        ImGui::SameLine();
        if (ImGui::TreeNode("Assests"))
        {
            for (int i = 0; i < 5; i++)
            {
                if (i == 0)
                    ImGui::SetNextItemOpen(true, ImGuiCond_Once);

                ImGui::Image(iconFolder->GetShaderResourceView(), ImVec2(15, 15));
                ImGui::SameLine();
                if (ImGui::TreeNode((void*)(intptr_t)i, "Child %d", i))
                {
                    ImGui::Text("asset");
                    ImGui::SameLine();
                    if (ImGui::SmallButton("open")) {}
                    ImGui::TreePop();
                }
            }
            ImGui::TreePop();
        }
        ImGui::TreePop();
    }

    ImGui::Image(iconFolder->GetShaderResourceView(), ImVec2(15, 15));
    ImGui::SameLine();
    if (ImGui::TreeNode("C++"))
    {
        ImGui::Image(iconFolder->GetShaderResourceView(), ImVec2(15, 15));
        ImGui::SameLine();
        if (ImGui::TreeNode("Files"))
        {
            for (int i = 0; i < 5; i++)
            {
                if (i == 0)
                    ImGui::SetNextItemOpen(true, ImGuiCond_Once);

                ImGui::Image(iconFolder->GetShaderResourceView(), ImVec2(15, 15));
                ImGui::SameLine();
                if (ImGui::TreeNode((void*)(intptr_t)i, "Child %d", i))
                {
                    ImGui::Text("file");
                    ImGui::SameLine();
                    if (ImGui::SmallButton("open")) {}
                    ImGui::TreePop();
                }
            }
            ImGui::TreePop();
        }
        ImGui::TreePop();
    }

    ImGui::End();
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

void EditorWindowAssetBrowser::folderLayout()
{
    ImVec2 button_sz(40, 40);
    ImGuiStyle& style = ImGui::GetStyle();
    int buttons_count = 20;
    float window_visible_x2 = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;
    for (int n = 0; n < buttons_count; n++)
    {
        ImGui::PushID(n);

        ImGui::BeginGroup();
        ImGui::ImageButton(iconFolder->GetShaderResourceView(), button_sz); //здесь, ессли нажали - обновляем весь layout
        ImGui::Text("folder name");
        ImGui::EndGroup();

        float last_button_x2 = ImGui::GetItemRectMax().x;
        float next_button_x2 = last_button_x2 + style.ItemSpacing.x + button_sz.x; // Expected position if next button was on same line
        if (n + 1 < buttons_count && next_button_x2 < window_visible_x2)
            ImGui::SameLine();
        ImGui::PopID();
    }


}
