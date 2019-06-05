#include "wtypes.h"
#include "Game.h"
#include <math.h>
#include "GameObject.h"
#include "WhitekastObject.h"
#include "WhitekastVision.h"
#include "CubeComponent.h"
#include "WorldComponent.h"
#include "FlipComponent.h"
#include "GravityComponent.h"
#include "ModelComponent.h"
#include "CollideComponent.h"
#include "CircleCollideComponent.h"
#include "LineColliderComponent.h"
#include "Vec.h"
#include <vector>
#include <iostream>
#include "World.h"
#include <GL/freeglut.h>
#include "AudioManager.h"
#include "StateManager.h"
#include "HomeState.h"
#include "CollisionManager.h"

std::list<GameObject*> objects;
GameObject* ball;

static World* world;
static Game* instance;

int horizontal = 0;
int vertical = 0;

Game::Game(const char * title, int argc, char * argv[])
{
	instance = this;
	initGlut(title, argc, argv);
	initObjects();
	world = new World(horizontal, vertical, objects, ball);

	audiomanager = AudioManager::getInstance();
	StateManager::getInstance();

	CollisionManager* collision = new CollisionManager();
	audiomanager->playMusic("Audio/busta_loop.WAV");
}

Game::~Game()
{
	delete world;
	delete instance;

}

void Game::startGame()
{
	glutMainLoop();
}

void Game::initGlut(const char * title, int argc, char * argv[])
{
	getDesktopResolution(horizontal, vertical);
	glEnable(GL_DEPTH_TEST);

	Vision vision = Vision();
	std::vector<WhitekastObject*> whitekastObjects = vision.initVision();

	initFlippers();

	for (auto wkObject : whitekastObjects) 
	{
		GameObject* gameObject = new GameObject(true);
		gameObject->addComponent(wkObject);
		gameObject->position = ::Vec3f(0, 0, 0);
		gameObject->setCoordinates(wkObject->getCoordinates());
		gameObject->addComponent(new LineCollideComponent(gameObject, wkObject->getScale()));
		gameObject->isCollider = true;
		objects.push_back(gameObject);
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(horizontal, vertical);
	glutCreateWindow(title);

	glutIdleFunc([]()
	{
		World::getWorld()->idle();
		Game::getInstance()->handleEvents();
		
	});
	glutDisplayFunc([]() { World::getWorld()->display(); });
	
	glutReshapeFunc([](int horizontal, int vertical) { World::getWorld()->reshape(horizontal, vertical); });
	glutKeyboardFunc([](unsigned char key, int mouseX, int mouseY) { World::getWorld()->keyboard(key, mouseX, mouseY); });
	glutKeyboardUpFunc([](unsigned char key, int mouseX, int mouseY) { World::getWorld()->keyboardUp(key, mouseX, mouseY); });
	glutPassiveMotionFunc([](int mouseX, int mouseY) {World::getWorld()->mousePassiveMotion(mouseX, mouseY); });
	glutMouseFunc([](int button, int state, int x, int y) {World::getWorld()->mouseClick(button, state, x, y); });
}

void Game::handleEvents() 
{
	StateManager::getInstance()->handle(this);
}

void Game::reset()
{
	lives = 3;
	StateManager::getInstance()->setState(new HomeState());
}

void Game::getDesktopResolution(int& horizontal, int& vertical) 
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	horizontal = desktop.right;
	vertical = desktop.bottom;
}

void Game::stop() 
{
	delete this;
}

void Game::initObjects()
{
	GameObject* testball = new GameObject(false);
	testball->addComponent(new ModelComponent("Models/Pinballs/pinball_3.1.obj", testball));
	testball->position = ::Vec3f(2, 0, 0);
	testball->scale = ::Vec3f(0.1f, 0.1f, 0.1f);
	testball->addComponent(new GravityComponent(::Vec3f(0, 0, 0.5)));
	testball->addComponent(new CircleCollideComponent(testball));
	ball = testball;

	Texture texture1 = Texture("Textures/LeftWall.png");
	Texture texture2 = Texture("Textures/RightWall.png");
	Texture texture3 = Texture("Textures/Floor.png");
	Texture texture4 = Texture("Textures/Cealing.png");
	Texture texture5 = Texture("Textures/FrontWall.png");

	GameObject* roomCube = new GameObject(false);
	roomCube->addComponent(new WorldComponent(10, texture1, texture2, texture3, texture4, texture5));
	roomCube->position = ::Vec3f(0, 0, 0);
	objects.push_back(roomCube);
}


void Game::initFlippers()
{
	::Vec3f scale = ::Vec3f(0.1, 0.1, 0.1);
	GameObject* flipperLeft = new GameObject(true);
	flipperLeft->addComponent(new ModelComponent("Models/Flippers/flipperblend.obj", flipperLeft));	
	flipperLeft->position = ::Vec3f(0, 0, 0);	
	flipperLeft->rotationPoint = ::Vec3f(flipperLeft->position.x - 0.2f, flipperLeft->position.y, flipperLeft->position.z);
	flipperLeft->scale = scale;
	flipperLeft->addComponent(new FlipComponent());
	objects.push_back(flipperLeft);

	GameObject* flipperRight = new GameObject(true);
	flipperRight->addComponent(new ModelComponent("Models/Flippers/flipperblend.obj", flipperRight));

	flipperRight->position = ::Vec3f(0, 0, 5);
	flipperRight->scale = scale;
	flipperRight->rotationPoint = ::Vec3f(flipperRight->position.x - 0.2f, flipperRight->position.y, flipperRight->position.z);
	flipperRight->addComponent(new FlipComponent());
	objects.push_back(flipperRight);
}

Game* Game::getInstance()
{
	return instance;
}
