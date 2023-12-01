#include "Toolbar.h"

Toolbar::Toolbar()
{
    //TODO Load relavent info from save file about what asset Types exsist for the combo
    assetTypeComboNames.push_back("Buildings");
    assetTypeComboNames.push_back("Paths");
    assetTypeComboNames.push_back("Trees");

    grassTexture.loadFromFile("Assets/Basic/16x16 Grass Square.png", sf::IntRect(0, 0, 16, 16));
    textures.push_back(grassTexture);

    grass2Texture.loadFromFile("Assets/Basic/16x16 Grass 2 Square.png", sf::IntRect(0, 0, 16, 16));
    textures.push_back(grass2Texture);

    bushTexture.loadFromFile("Assets/Basic/16x16 Bush Square.png", sf::IntRect(0, 0, 16, 16));
    textures.push_back(bushTexture);

    blackTexture.loadFromFile("Assets/Basic/16x16 Black Square.png", sf::IntRect(0, 0, 16, 16));
    textures.push_back(blackTexture);

    redTexture.loadFromFile("Assets/Basic/16x16 Red Square.png", sf::IntRect(0, 0, 16, 16));
    textures.push_back(redTexture);

    whiteTexture.loadFromFile("Assets/Basic/16x16 White Square.png", sf::IntRect(0, 0, 16, 16));
    textures.push_back(whiteTexture);

    loadAssetComboGroups();
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

void Toolbar::assetTypeCombo()
{
    ImGui::SetNextItemWidth(150);
    if (ImGui::BeginCombo("Asset Type", assetGroups[selectedIndex].getComboTitle().c_str()))
    {
        for (int i = 0; i < assetGroups.size(); ++i)
        {
            const bool isSelected = (selectedIndex == i);
            if (ImGui::Selectable(assetGroups[i].getComboTitle().c_str(), isSelected))
                selectedIndex = i;

            // Set the initial focus when opening the combo
            // (scrolling + keyboard navigation focus)
            if (isSelected) 
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }
}

void Toolbar::assetList(const float TOOLBAR_WIDTH)
{
    if (ImGui::BeginListBox("##listbox 2", ImVec2((TOOLBAR_WIDTH - LIST_BOX_X_OFFSET), LIST_BOX_HEIGHT)))
    {
        sf::Sprite sprite;
        sprite.setTexture(grassTexture);
        sprite.scale(sf::Vector2f(2.25f, 2.25f));

        for (int y = 0; y < 12; y++)
        {
            for (int x = 0; x < 4; x++)
            {
                sprite.setTexture(textures[x]);

                if (x > 0)
                    ImGui::SameLine();

                ImGui::PushID(y * 4 + x);

                if (ImGui::ImageButton(sprite))
                    selectAsset((x + y));

                ImGui::PopID();
            }
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
        for (int n = 0; n < 15; n++)
            ImGui::Text("Line %04d", n);
        //Properties Here
        ImGui::EndChild();
    }
}

void Toolbar::selectAsset(int ID)
{
    ImGui::SetItemDefaultFocus();
    std::cout << "Asset Button Pressed " << ID << " ";
}
