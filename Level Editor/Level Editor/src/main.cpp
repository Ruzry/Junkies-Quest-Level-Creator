#define NOMINMAX

#include "imgui.h"
#include "imgui-SFML.h"
#include <fstream>
#include <json.hpp>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "Level Editor/LevelEditor.h"

const int WINDOW_WIDTH = 1200, WINDOW_HEIGHT = 800;


int main() {
    //Set up main window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Junkies Quest Level Editor");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    LevelEditor levelEditor = LevelEditor(&window);
    float deltaTime;

    //Game Loop
    sf::Clock deltaClock;
    while (window.isOpen())
    {
        deltaTime = deltaClock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed)
                window.close();
            //TODO Look into why only one view scales during window-resize
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

        levelEditor.update(deltaTime, worldPos);

        ImGui::ShowDemoWindow();

        window.clear();
        levelEditor.render();
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}
