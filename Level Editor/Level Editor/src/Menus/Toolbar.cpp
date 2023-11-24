#include "Toolbar.h"

Toolbar::Toolbar()
{
    //TODO Load relavent info from save file about what asset Types exsist for the combo
    assetTypeComboNames.push_back("Buildings");
    assetTypeComboNames.push_back("Paths");
    assetTypeComboNames.push_back("Trees");
}

void Toolbar::update(float deltaTime)
{
}

void Toolbar::fileMenu(bool *isActive)
{
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New", "Ctrl+N"))
                newFile();

            if (ImGui::MenuItem("Open..", "Ctrl+O"))
                open();

            if (ImGui::MenuItem("Save", "Ctrl+S"))
                save();

            if (ImGui::MenuItem("Export", "Ctrl+E"))
                exportLevel();

            if (ImGui::MenuItem("Close", "Ctrl+W"))
                *isActive = false;

            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
}

void Toolbar::newFile()
{
}

void Toolbar::open()
{
}

void Toolbar::save()
{
}

void Toolbar::exportLevel()
{
}

void Toolbar::AssetMenu()
{
    assetTypeCombo();
}

void Toolbar::assetTypeCombo()
{
    if (ImGui::BeginCombo("Asset Types", assetTypeComboNames[selectedIndex].c_str())) {
        for (int i = 0; i < assetTypeComboNames.size(); ++i) {
            const bool isSelected = (selectedIndex == i);
            if (ImGui::Selectable(assetTypeComboNames[i].c_str(), isSelected)) {
                selectedIndex = i;
            }

            // Set the initial focus when opening the combo
            // (scrolling + keyboard navigation focus)
            if (isSelected) {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }
}
