# Junkies-Quest-Level-Creator

 A level editor designed to create and edit levels for Junkies Quest. The goal is to speed up development of Junkies Quest. Building alongside the level renderer for the game to aid compatibilty.
 

 **Goals:**
 
Level renderer: 
 Displays a current level being edited.
 Levels will be saved to a json that the game can read.
 
Asset Menu: 
 Menu that sits along side the displayed level. 
 Contains a drop down of asset groups that display the asset as selectable icons. 
 Assets and asset Groups can be manipulated within the menu. (new, delete, etc)
 Assets will be selectable and placeble on the grid with a snapping feature to align on the grid.
 Asset groups settings will be saved to json file.
 

 **Project Information:**

 Built in C++.

 Game rendering built with SFML 2.6.1 to match rendering library for the game. https://www.sfml-dev.org/download/sfml/2.6.1/
 
 GUI provided by IMGUI Library: https://github.com/ocornut/imgui
 
 Library to use ImGui and SFML together: https://github.com/SFML/imgui-sfml
 
 nlohmann/json to manipulate json files in C++: https://github.com/nlohmann/json#examples
 
