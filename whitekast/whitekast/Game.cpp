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
#include "PointCounter.h"
#include "LivesCounter.h"
#include <thread> 
#include <math.h>  

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
	world = new World(horizontal, vertical, objects, vision, ball);

	audiomanager = AudioManager::getInstance();
	pointCounter = PointCounter::getInstance();
	livesCounter = LivesCounter::getInstance();

	StateManager::getInstance();

	CollisionManager* collision = new CollisionManager();
	//audiomanager->playMusic("Audio/busta_loop.WAV");
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

void Game::startVisionThread()
{
	vision.startThread();
}

void Game::initGlut(const char * title, int argc, char * argv[])
{
	getDesktopResolution(horizontal, vertical);
	glEnable(GL_DEPTH_TEST);

	vision = WhitekastVision();
	std::vector<WhitekastObject*> whitekastObjects = vision.initVision();
	boardWidth = whitekastObjects.at(0)->getWidth();
	boardHeight = whitekastObjects.at(0)->getSize();
	initFlippers();
	

	for (auto wkObject : whitekastObjects) 
	{
		GameObject* gameObject = new GameObject(true);
		gameObject->addComponent(wkObject);
		gameObject->position = ::Vec3f(0, 0, 0);
		gameObject->setCoordinates(wkObject->getCoordinates());
		gameObject->addComponent(new LineCollideComponent(gameObject, wkObject->getScale()));
		if(wkObject->getObjectColor() == RED)
		{
			gameObject->bounceFactor = 1.2f;
		}
		else
			gameObject->bounceFactor = 0.8f;
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
	pointCounter->hitFlipper();
	StateManager::getInstance()->handle(this);
	
}

void Game::reset()
{
	livesCounter->resetLives();
	pointCounter->resetPoints();
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
	ball = new GameObject(true);
	ball->addComponent(new ModelComponent("Models/Pinballs/pinball_3.1.obj", ball));
	ball->position = ::Vec3f(3, -2, 3.5f);
	ball->scale = ::Vec3f(0.1f, 0.1f, 0.1f);
	ball->addComponent(new GravityComponent(::Vec3f(-0.3, 0, 0)));
	ball->addComponent(new CircleCollideComponent(ball));

	Texture texture1 = Texture("Textures/LeftWall.png");
	Texture texture2 = Texture("Textures/RightWall.png");
	Texture texture3 = Texture("Textures/Floor.png");
	Texture texture4 = Texture("Textures/Cealing.png");
	Texture texture5 = Texture("Textures/FrontWall.png");

	GameObject* roomCube = new GameObject(false);
	roomCube->addComponent(new WorldComponent(10, texture1, texture2, texture3, texture4, texture5));
	roomCube->position = ::Vec3f(0, 0, 0);
	//objects.push_back(roomCube);
}

void Game::initFlippers()
{
	::Vec3f scale = ::Vec3f(0.1, 0.1, 0.1);
	GameObject* flipperLeft = new GameObject(true);
	flipperLeft->color = ::Vec3f(0.0f, 0.0f, 0.0f);
	flipperLeft->addComponent(new ModelComponent("Models/Flippers/flipperblend.obj", flipperLeft));
	flipperLeft->position = ::Vec3f(0.875f, -2, 1.4f);
	flipperLeft->rotationPoint = ::Vec3f(flipperLeft->position.x - 0.2f, flipperLeft->position.y, flipperLeft->position.z);
	flipperLeft->scale = scale;
	flipperLeft->rotation.y = -105;
	flipperLeft->bounceFactor = 2.0f;
	flipperLeft->addComponent(new FlipComponent(true));
	std::vector<cv::Point> flipperLeftCoordinates;
	/*flipperLeftCoordinates.push_back(cv::Point((flipperLeft->rotationPoint.x + 0.1)*100, flipperLeft->rotationPoint.z*100));
	flipperLeftCoordinates.push_back(cv::Point((flipperLeft->rotationPoint.x + 0.1 - (sin(15)*0.3f)) *100,(flipperLeft->rotationPoint.z + (cos(15) *0.3f))*100));*/
	flipperLeftCoordinates.push_back(cv::Point((flipperLeft->rotationPoint.x + 0.1)*100, flipperLeft->rotationPoint.z*100));
	flipperLeftCoordinates.push_back(cv::Point((flipperLeft->rotationPoint.x + 0.1) *100,(flipperLeft->rotationPoint.z + 0.3f)*100));
	flipperLeft->setCoordinates(flipperLeftCoordinates);
	flipperLeft->addComponent(new LineCollideComponent(flipperLeft, 0.1));
	objects.push_back(flipperLeft);

	GameObject* flipperRight = new GameObject(true);
	flipperRight->color = ::Vec3f(0.0f, 0.0f, 0.0f);
	flipperRight->addComponent(new ModelComponent("Models/Flippers/flipperblend.obj", flipperRight));
	flipperRight->position = ::Vec3f(0.875f, -2, 2.595f);
	flipperRight->scale = scale;
	flipperRight->rotationPoint = ::Vec3f(flipperRight->position.x - 0.2f, flipperRight->position.y, flipperRight->position.z);
	flipperRight->rotation.y = 105;
	flipperRight->bounceFactor = 2.0f;
	flipperRight->addComponent(new FlipComponent(false));
	std::vector<cv::Point> flipperRightCoordinates;
	/*flipperRightCoordinates.push_back(cv::Point((flipperRight->rotationPoint.x + 0.1) *100, flipperRight->rotationPoint.z*100));
	flipperRightCoordinates.push_back(cv::Point((flipperRight->rotationPoint.x + 0.1 - (sin(15)*0.3f)) * 100, (flipperRight->rotationPoint.z - (cos(15) *0.3f)) * 100));*/
	flipperRightCoordinates.push_back(cv::Point((flipperRight->rotationPoint.x + 0.1) *100, flipperRight->rotationPoint.z*100));
	flipperRightCoordinates.push_back(cv::Point((flipperRight->rotationPoint.x + 0.1) * 100, (flipperRight->rotationPoint.z - 0.3f) * 100));
	flipperRight->setCoordinates(flipperRightCoordinates);
	flipperRight->addComponent(new LineCollideComponent(flipperRight, 0.1f));
	objects.push_back(flipperRight);
}


Game* Game::getInstance()
{
	return instance;
}
