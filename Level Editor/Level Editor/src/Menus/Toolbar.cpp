#include "Toolbar.h"

Toolbar::Toolbar()
{
    loadAssetComboGroups();
}

void Toolbar::update(float deltaTime)
{
}

void Toolbar::loadAssetComboGroups()
{
    std::ifstream f("Assets/AssetGroup.json");
    json data = json::parse(f);

    std::cout << data.dump(4) << std::endl;

    //for amount of asset_groups in the json
    int amountOfGroups = data["asset_group"].size();

    for (int i = 0; i < amountOfGroups; i++)
    {
        const std::string comboTitle = data["asset_group"].at(i)["asset_type"];
        const int amountOfObjects = data["asset_group"].at(i)["amount_of_objects"].get<unsigned int>();

        AssetGroup assetGroup = AssetGroup(comboTitle, amountOfObjects);
        std::vector<GridObject> objects = {};

        for (int j = 0; j < data["asset_group"].at(i)["objects"].size(); j++)
        {
            const std::string objectName = data["asset_group"].at(i)["objects"].at(j)["name"];
            const std::string filePath = data["asset_group"].at(i)["objects"].at(j)["file_path"];
            const bool intangible = data["asset_group"].at(i)["objects"].at(j)["intangible"];
            const int size = data["asset_group"].at(i)["objects"].at(j)["size"];

            GridObject object = GridObject(objectName, filePath, intangible, size);

            objects.push_back(object);

            if (textureMap.find(objectName) == textureMap.end())
            {
                sf::Texture texture;
                texture.loadFromFile(filePath);

                textureMap.insert(std::make_pair(objectName, texture));
            }
        }

        assetGroup.setAssets(objects);

        assetGroups.push_back(assetGroup);
    }

    bool STOPHERE = true;
}

void Toolbar::AssetMenu(const float TOOLBAR_WIDTH)
{
    assetTypeCombo();
    
    assetList(TOOLBAR_WIDTH);

    assetProperties(TOOLBAR_WIDTH);
}

GridObject* Toolbar::getSelectedAsset()
{
    if (assetSelected)
        return selectedAsset;
    else
        return nullptr;
}

void Toolbar::assetTypeCombo()
{
    ImGui::SetNextItemWidth(150);
    if (ImGui::BeginCombo("Asset Type", assetGroups[selectedGroupIndex].getComboTitle().c_str()))
    {
        for (int i = 0; i < assetGroups.size(); ++i)
        {
            const bool isSelected = (selectedGroupIndex == i);
            if (ImGui::Selectable(assetGroups[i].getComboTitle().c_str(), isSelected))
            {
                selectedGroupIndex = i;

                selectedGroup = assetGroups[selectedGroupIndex].getAssets_();

                assetSelected = false;
            }

            if (isSelected) 
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }
}

/**
* Populates the IMGUI List Box with assets as image buttons.
* 
**/
void Toolbar::assetList(const float TOOLBAR_WIDTH)
{
    if (ImGui::BeginListBox("##listbox 2", ImVec2((TOOLBAR_WIDTH - LIST_BOX_X_OFFSET), LIST_BOX_HEIGHT)))
    {
        bool newLine = true;

        for (int assetIndex = 0; assetIndex < assetGroups[selectedGroupIndex].getAssets().size(); assetIndex++)
        {
            sf::Sprite* sprite = assetGroups[selectedGroupIndex].getAsset_(assetIndex);
            sprite->setTexture(textureMap.at(assetGroups[selectedGroupIndex].getAsset_(assetIndex)->getName()));
            sprite->scale(sf::Vector2f(2.25f, 2.25f));

            if (!newLine)
                ImGui::SameLine();

            newLine = ((assetIndex + 1) % 4 ? false : true);

            ImGui::PushID(assetIndex);

            if (ImGui::ImageButton(assetGroups[selectedGroupIndex].getAssets()[assetIndex]))
                selectAsset(assetIndex);

            ImGui::PopID();

            sprite->setScale(sf::Vector2f(1.f, 1.f));
        }

        ImGui::EndListBox();
    }
}

void Toolbar::assetProperties(const float TOOLBAR_WIDTH)
{
    ImGui::SeparatorText("Asset Properties");
    {
        ImGui::SetNextWindowSizeConstraints(ImVec2(0.0f, ImGui::GetTextLineHeightWithSpacing() * 1),
            ImVec2(TOOLBAR_WIDTH, PROPERTIES_HEIGHT));

        ImGui::BeginChild("ConstrainedChild", ImVec2(-FLT_MIN, 0.0f), ImGuiChildFlags_Border | ImGuiChildFlags_AutoResizeY);

        if (assetSelected)
        {
            const std::string isIntangible = selectedAsset->getIsIntangible() ? "Yes" : "No";
                
            ImGui::Text(("Name: " + selectedAsset->getName()).c_str());
            ImGui::Text(("Intangible: " + isIntangible).c_str());
            ImGui::Text(("Size: " + std::to_string(selectedAsset->getSize())).c_str());
        }

        ImGui::EndChild();
    }
}

void Toolbar::selectAsset(int ID)
{
    ImGui::SetItemDefaultFocus();

    assetSelected = true;
    selectedAsset = assetGroups[selectedGroupIndex].getAsset_(ID);
}
