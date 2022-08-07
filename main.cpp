#include <iostream>
#include "raylib.h"
#include <vector>
#include "include/World.h"

class Player
{
private:
public:
    int health_points {100};
    Vector3 position {0.0f, 1.0f, 0.0f};
};

Vector3 sub_vec3(Vector3 a, Vector3 b)
{
    Vector3 result {a.x - b.x, a.y - b.y, a.z - b.z};

    return result; 
}

Vector3 add_vec3(Vector3 a, Vector3 b)
{
    Vector3 result {a.x + b.x, a.y + b.y, a.z + b.z};

    return result; 
}

Vector3 scale_vec3(Vector3 a, int b)
{
    Vector3 result {a.x * b, a.y * b, a.z * b};

    return result; 
}

typedef enum GameScreen { LOGO = 0, 
                          TITLE, 
                          GAMEPLAY, 
                          ENDING } GameScreen;



int main() 
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "GggggWpp");

    int framesCounter = 0;

    // Create World class instance
    World *world {nullptr};
    world = new World; 

    Model church_model = LoadModel("resources/objects/church.obj");
    Vector3 church_position {10.0f, 0.0f, 5.0f};
    Texture2D church_texture = LoadTexture("resources/textures/church_diffuse.png");
    Static_object church {church_model, church_texture, church_position, 1.1f};
    world->push_static_object(church); 

    //church_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = church_texture;

    // Apply textures for all static objects in World
    world->apply_textures_for_static_objects();

    Player player; 
    Camera camera = { 0 };
    camera.position = (Vector3){ 2.0f, 2.0f, 2.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 30.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetCameraMode(camera, CAMERA_FIRST_PERSON);

    GameScreen currentScreen = LOGO;
    
    Image imMap = LoadImage("resources/textures/Limon.png");                // Load cubicmap image (RAM)
    Texture2D cubicmap = LoadTextureFromImage(imMap);

    Vector3 cubePosition = { 0.0f, 1.0f, 0.0f };  // {x, y ,z}

    //RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        // Update
        //----------------------------------------------------------------------------------
        switch(currentScreen)
        {
            case LOGO:
            {
                // TODO: Update LOGO screen variables here!
                framesCounter++;    // Count frames

                // Wait for 2 seconds (120 frames) before jumping to TITLE screen
                if (framesCounter > 120)
                {
                    currentScreen = TITLE;
                }
            } break;
            case TITLE:
            {
                // TODO: Update TITLE screen variables here!

                // Press enter to change to GAMEPLAY screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = GAMEPLAY;
                }
            } break;
            case GAMEPLAY:
            {
                // TODO: Update GAMEPLAY screen variables here!

                // Press enter to change to ENDING screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = ENDING;
                }
            } break;
            case ENDING:
            {
                // TODO: Update ENDING screen variables here!
                // Press enter to return to TITLE screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = TITLE;
                }
            } break;
            default: break;
        }

        UpdateCamera(&camera);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            switch(currentScreen)
            {
                case LOGO:
                {
                    // TODO: Draw LOGO screen here!
                    DrawText("LOGO SCREEN", 20, 20, 40, LIGHTGRAY);
                    DrawText("WAIT for 2 SECONDS...", 290, 220, 20, GRAY);

                } break;
                case TITLE:
                {
                    // TODO: Draw TITLE screen here!
                    DrawRectangle(0, 0, screenWidth, screenHeight, GREEN);
                    DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);
                    DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", 120, 220, 20, DARKGREEN);

                } break;
                case GAMEPLAY:
                {
                    // TODO: Draw GAMEPLAY screen here!
                    //BeginTextureMode(target);
                        ClearBackground(SKYBLUE);
                        BeginMode3D(camera);
                        //-----------------------------------------------------------------------------
                            DrawPlane((Vector3){ 0, 0, 0 }, (Vector2){ 100, 100 }, GREEN);
                            player.position.x = camera.position.x;
                            player.position.z = camera.position.z;

                            world->draw_static_objects();
                            //DrawModel(church, {10.0f, 0.0f, 5.0f}, 1.1f, WHITE);
                            DrawCubeTexture(cubicmap, cubePosition, 2.0f, 2.0f, 2.0f, WHITE);
                            DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);
                            //DrawGrid(100, 1.0f);
                        //-----------------------------------------------------------------------------

                        EndMode3D();
                    
                        DrawText(TextFormat("Player x position: %f", player.position.x), 10, 60, 20, DARKGRAY);  
                        DrawText(TextFormat("Player z position: %f", player.position.z), 10, 80, 20, DARKGRAY);  

                    //EndTextureMode();

                } break;
                case ENDING:
                {
                    // TODO: Draw ENDING screen here!
                    DrawRectangle(0, 0, screenWidth, screenHeight, BLUE);
                    DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);
                    DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);

                } break;
                default: break;
            }
            

            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}