#ifndef GAME_H_
#define GAME_H_

#include <exception>
#include <string>
#include <unordered_map>
// #define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "scene_graph.h"
#include "resource_manager.h"
#include "camera.h"
#include "asteroid.h"
#include "player.h"
#include "beacon.h"
#include "enemy.h"
#include "random.h"
#include "light.h"
#include "trigger.h"
#include "collision_manager.h"
#include "defines.h"
#include "fp_player.h"

class Application;

// Exception type for the game
class GameException: public std::exception
{
    private:
        std::string message_;
    public:
        GameException(std::string message) : message_(message) {};
        virtual const char* what() const throw() { return message_.c_str(); };
        virtual ~GameException() throw() {};
};

enum GameState {
    RUNNING,
    WIN,
    LOSE
};

enum SceneEnum {
    FPTEST,
    ALL = -1
};


// Game application
class Game {
    public:

        Game(Application& app, ResourceManager& resman) : app(app), resman(resman) {};

        void Init(void); 
        void SetupResources(void);
        void SetupScene(void);
        void SetupFPScene(void);

        void Update(double dt, KeyMap& keys);
        SceneGraph& ActiveScene() { return *scene; }
        //TODO: Run SceneGraph Init()
        void SetActiveScene(SceneEnum sceneNum) { scene = scenes[sceneNum]; }

        Application& app;
        ResourceManager& resman;
        int rng_seed = 1804289383;
        RandGenerator rng {rng_seed};

    private:
        SceneGraph* scene;
        std::vector<SceneGraph *> scenes;

        float wind_speed = 1.5f;
        int camera_mode;

        void LoadMeshes();
        void LoadShaders();
        void LoadTextures();

        void AddToScene(SceneEnum sceneNum, SceneNode* node);
        void AddPlayerToScene(SceneEnum sceneNum, Player* node);
        void AddLightToScene(SceneEnum sceneNum, Light* l);

        void CreatePlayer();
        void CreatePlanets();
        void CreateTerrain();
        void CreateAsteroidField(int num_asteroids);
        void CreateHUD();
        void CreateTree();
        void CreateLights();
        void CreateTriggers();
        void GrowTree(SceneNode* root, int branches, float height, float width, int level, int max_iterations);
        void GrowLeaves(SceneNode* root, int leaves, float parent_length, float parent_width);

        void CheckControls(KeyMap& keys);
        void MouseControls(Mouse& mouse);

        void ChangeScene(int sceneIndex);

}; // class Game

#endif // GAME_H_
