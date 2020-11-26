#include "Editor.h"

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "EditorWindowAssetBrowser.h"

Editor::Editor(ID3D11Device* device, ID3D11DeviceContext* context, const HWND hWnd)
{
    initImGui(device, context, hWnd);

    windows.push_back(new EditorWindowAssetBrowser);
}

Editor::~Editor()
{
    for (EditorWindow* window : windows)
    {
        delete window;
    }
}

void Editor::Update()
{
    updateWindows();
}

void Editor::Render()
{
    startImGuiFrame();
    renderWindows();
    finishImGuiFrame();
}

void Editor::initImGui(ID3D11Device* device, ID3D11DeviceContext* context, const HWND hWnd)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

#if 1
    io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleFonts;
    io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleViewports;
#endif

    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX11_Init(device, context);
}

void Editor::startImGuiFrame()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}

void Editor::finishImGuiFrame()
{
    // assemble together draw data
    ImGui::Render();

    // render draw data
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }
}

void Editor::updateWindows()
{
    for (EditorWindow* window : windows)
    {
        window->Update();
    }
}

void Editor::renderWindows()
{
    renderMainEditorMenu();

    for (EditorWindow* window : windows)
    {
        if (!window->IsVisible())
            continue;

        window->Render();
    }
}

void Editor::renderMainEditorMenu()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New")) {}
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Editor"))
        {
            if (ImGui::MenuItem("Save Layout", "")) {}
            if (ImGui::MenuItem("Load Layout", "")) {}
            ImGui::Separator();
            if (ImGui::MenuItem("Close All ", "")) {}
            if (ImGui::BeginMenu("Windows", ""))
            {
                for (EditorWindow* window : windows)
                {
                    bool selected = window->IsVisible();
                    ImGui::MenuItem(window->GetName().data(), " ", &selected);
                    window->SetVisible(selected);
                }
                
                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}
