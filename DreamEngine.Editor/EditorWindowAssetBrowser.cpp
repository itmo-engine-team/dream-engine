#include "EditorWindowAssetBrowser.h"
#include "imgui.h"

EditorWindowAssetBrowser::EditorWindowAssetBrowser()
    : EditorWindow("Asset Browser")
{

}

void EditorWindowAssetBrowser::Update()
{

}

void EditorWindowAssetBrowser::Render()
{
    ImGui::Begin(" ");

    ImGui::End();

    ImGui::Begin(GetName().data());

    ImGuiIO& io = ImGui::GetIO();
    ImTextureID my_tex_id = io.Fonts->TexID;
    float my_tex_w = (float)io.Fonts->TexWidth;
    float my_tex_h = (float)io.Fonts->TexHeight;

    ImVec2 size = ImVec2(16.0f, 16.0f);                        // Size of the image we want to make visible
    ImVec2 uv0 = ImVec2(0.0f, 0.0f);                           // UV coordinates for lower-left
    ImVec2 uv1 = ImVec2(32.0f / my_tex_w, 32.0f / my_tex_h);   // UV coordinates for (32,32) in our texture
    ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);       // Black background
    ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);     // No tint
    ImGui::ImageButton(my_tex_id, size, uv0, uv1, 3, bg_col, tint_col);
    ImGui::SameLine();
    if (ImGui::Button("Add New >"))
    {
        ImGui::MenuItem("(demo menu)", NULL, false, false);
        if (ImGui::MenuItem("New", "")) {}
        if (ImGui::MenuItem("Save", "")) {}
        if (ImGui::MenuItem("Delete ", "")) {}
        if (ImGui::MenuItem("Move", "")) {}
        if (ImGui::MenuItem("Duplicate", " ")) {}
        if (ImGui::MenuItem("Rename", " ")) {}
        if (ImGui::MenuItem("Back", " ")) {}
    }

    ImGui::End();

    ImGui::Begin("Content");
    if (ImGui::TreeNode("Content"))
    {
        if (ImGui::TreeNode(" "))
        {
            ImGui::SameLine();
            ImGui::Text("Geometry");

            for (int i = 0; i < 5; i++)
            {
                if (i == 0)
                    ImGui::SetNextItemOpen(true, ImGuiCond_Once);

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

    if (ImGui::TreeNode("Engine Content"))
    {
        if (ImGui::TreeNode("Assests"))
        {
            for (int i = 0; i < 5; i++)
            {
                if (i == 0)
                    ImGui::SetNextItemOpen(true, ImGuiCond_Once);

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

    if (ImGui::TreeNode("C++"))
    {
        if (ImGui::TreeNode("Files"))
        {
            for (int i = 0; i < 5; i++)
            {
                if (i == 0)
                    ImGui::SetNextItemOpen(true, ImGuiCond_Once);

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
