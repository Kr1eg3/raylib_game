#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include <vector>
#include <string>
#include "include/World.h"

#define RLIGHTS_IMPLEMENTATION
#include "include/rlights.h"

#define GLSL_VERSION 330

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

    SetConfigFlags(FLAG_MSAA_4X_HINT);  // Enable Multi Sampling Anti Aliasing 4x (if available)
    InitWindow(screenWidth, screenHeight, "GggggWpp");

    int framesCounter = 0;

    // Create Player class instance
    Player* player {nullptr};
    player = new Player;

    // Create World class instance
    World *world {nullptr};
    world = new World; 


    const char start_message[128] = "This is bla bla bla bla bla bla bla bla bla xDDDDDDDDDDDDDDDDDDD";
    

    // Church object
    //--------------------------------------------------------------------
    Model church_model = LoadModel("resources/objects/church.obj");
    Vector3 church_position {10.0f, 0.0f, 5.0f};
    Texture2D church_texture = LoadTexture("resources/textures/church_diffuse.png");
    Static_object church {church_model, church_texture, church_position, 1.1f};
    world->push_static_object(church); 
    //--------------------------------------------------------------------

    // Plane and cube from mesh
    Model model = LoadModelFromMesh(GenMeshPlane(100.0f, 100.0f, 3, 3));
    Model cube = LoadModelFromMesh(GenMeshCube(2.0f, 2.0f, 2.0f));


    // Apply textures for all static objects in World
    world->apply_textures_for_static_objects();

    
    Camera camera = { 0 };
    camera.position = (Vector3){ 2.0f, 2.0f, 2.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 30.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetCameraMode(camera, CAMERA_FIRST_PERSON);

    GameScreen currentScreen = LOGO;
    
    // Load cubicmap image (RAM)
    Image imMap = LoadImage("resources/textures/Limon.png");                
    //Texture2D cubicmap = LoadTextureFromImage(imMap);

    // Load basic lighting shader
    Shader shader = LoadShader(TextFormat("resources/shaders/glsl%i/base_lighting.vs", GLSL_VERSION),
                               TextFormat("resources/shaders/glsl%i/lighting.fs", GLSL_VERSION));
    
    shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");

    // Ambient light level (some basic lighting)
    int ambientLoc = GetShaderLocation(shader, "ambient");
    const float val[4]  = {0.1f, 0.1f, 0.1f, 1.0f};
    //(float[4]){ 0.1f, 0.1f, 0.1f, 1.0f }
    SetShaderValue(shader, ambientLoc, val, SHADER_UNIFORM_VEC4);

    // Assign out lighting shader to model
    model.materials[0].shader = shader;
    cube.materials[0].shader = shader;

    // Create lights
    Light lights[MAX_LIGHTS] = { 0 };
    lights[0] = CreateLight(LIGHT_POINT, (Vector3){ -2, 1, -2 }, Vector3Zero(), YELLOW, shader);
    lights[1] = CreateLight(LIGHT_POINT, (Vector3){ 2, 1, 2 }, Vector3Zero(), RED, shader);
    lights[2] = CreateLight(LIGHT_POINT, (Vector3){ -2, 1, 2 }, Vector3Zero(), GREEN, shader);
    lights[3] = CreateLight(LIGHT_POINT, (Vector3){ 2, 1, -2 }, Vector3Zero(), BLUE, shader);

    //Vector3 cubePosition = { 0.0f, 1.0f, 0.0f };  // {x, y ,z}

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
                framesCounter++;    // Count frames

                if (IsKeyDown(KEY_SPACE)) framesCounter += 8;
                

                // Wait for 2 seconds (120 frames) before jumping to TITLE screen
                if (framesCounter > 400)
                {
                    currentScreen = TITLE;
                }
            } break;
            case TITLE:
            {
                // Press enter to change to GAMEPLAY screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = GAMEPLAY;
                }
            } break;
            case GAMEPLAY:
            {
                // Press enter to change to ENDING screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = ENDING;
                }
            } break;
            case ENDING:
            {
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
                    DrawText("LOGO SCREEN", 20, 20, 40, LIGHTGRAY);
                    DrawText("WAIT for 2 SECONDS...", 290, 220, 20, GRAY);
                    DrawText(TextSubtext(start_message, 0, framesCounter/10), screenWidth/2, screenHeight/2, 40, MAROON);

                } break;
                case TITLE:
                {
                    DrawRectangle(0, 0, screenWidth, screenHeight, GREEN);
                    DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);
                    DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", 120, 220, 20, DARKGREEN);

                } break;
                case GAMEPLAY:
                {
                    //BeginTextureMode(target);
                        ClearBackground(SKYBLUE);
                        BeginMode3D(camera);
                        //-----------------------------------------------------------------------------
                            DrawModel(model, {0.0f, 0.0f, 0.0f}, 1.0f, WHITE);
                            DrawModel(cube, {0.0f, 1.0f, 0.0f}, 1.0f, WHITE);
                            //DrawPlane((Vector3){ 0, 0, 0 }, (Vector2){ 100, 100 }, GREEN);
                            player->position.x = camera.position.x;
                            player->position.z = camera.position.z;

                            world->draw_static_objects();
                            //DrawModel(church, {10.0f, 0.0f, 5.0f}, 1.1f, WHITE);
                            //DrawCubeTexture(cubicmap, cubePosition, 2.0f, 2.0f, 2.0f, WHITE);
                            //DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);
                            //DrawGrid(100, 1.0f);
                        //-----------------------------------------------------------------------------

                        EndMode3D();
                    
                        DrawText(TextFormat("Player x position: %f", player->position.x), 10, 60, 20, DARKGRAY);  
                        DrawText(TextFormat("Player z position: %f", player->position.z), 10, 80, 20, DARKGRAY);  

                    //EndTextureMode();

                } break;
                case ENDING:
                {
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
    delete player;
    delete world;
    UnloadShader(shader);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}