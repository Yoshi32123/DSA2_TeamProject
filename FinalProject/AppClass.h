/*----------------------------------------------
Programmer: Kyler McQuillan (kjm7088@g.rit.edu)
Date: 2019/10
----------------------------------------------*/
#ifndef __APPLICATIONCLASS_H_
#define __APPLICATIONCLASS_H_

#include "Definitions.h"

#include "ControllerConfiguration.h"
#include "imgui\ImGuiObject.h"

#include "MyEntityManager.h"

#include "MyGrid.h"
namespace Simplex
{
	//Adding Application to the Simplex namespace
class Application
{
	MyEntityManager* m_pEntityMngr = nullptr; //Entity Manager
	MyGrid* m_pRoot = nullptr;//Root octant
	uint m_uGridID = -1; //Index of Octant to display
	uint m_uObjects = 0; //Number of objects in the scene
	uint m_uGridLevels = 0; //Number of levels in the octree

	// bowling ball fields
	vector3 m_v3BowlingBall; // Ball Position
	vector3 m_v3BowlingBallStart; //Ball starting/reset position
	vector3 m_v3BowlingAlley; // Bowling alley position
	bool m_bManualMove = true; //Toggles manual ball movement
	bool m_bCanBowl = true; //Toggles bowling with space functionality
	bool m_bCanCurve = false; // Toggle curving ability after the ball has been bowled
	bool m_bStartTimeTrack = false; //starts time tracking for time since bowled
	bool m_bBumpersEnabled = false; //Toggles bumpers
	bool m_bBumpersMade = false; // Bool so that bumpers aren't made each frame
	bool m_bBumpersDestroyed = true; // Bool so that bumpers aren't destroyed each frame
	bool m_bRandomCrapMade = false; // Bool so that the random crap thing isn't made each frame
	bool m_bRandomCrapDestroyed = true; // Bool so that the random crap thing isn't destroyed each frame
	uint m_uTimeBowled = 0; //Start time for when space was pressed to bowl
	uint m_uTimeSinceBowled = 0; //Time since space was pressed to bowl
	uint m_uTimesBowled = 0; //Tracks times bowled for resetting pins

	// pin fields
	std::vector<vector3> m_lPinLocations;
	uint uPinStartIndex;
	uint uPinCount;

	// alley fields
	uint uAlleyStartIndex;
	uint uAlleyPieces = 6;
	uint uPinStopStartIndex;
	uint uPinStopPieces = 5;

private:
	String m_sProgrammer = "Kyler McQuillan - kjm7088@g.rit.edu\nTrenton Plager - tlp6760@g.rit.edu\nAlex Pecore - app2076@g.rit.edu\nJerry Wexler - jzw5422@g.rit.edu\nAkshat Rawat - axr@g.rit.edu"; //programmer

	static ImGuiObject gui; //GUI object
	bool m_bGUI_Main = true; //show Main GUI window?
	bool m_bGUI_Console = true; //show Credits GUI window?
	bool m_bGUI_Test = false; //show Test GUI window?
	bool m_bGUI_Controller = false; //show Controller GUI window?

	uint m_uRenderCallCount = 0; //count of render calls per frame
	uint m_uControllerCount = 0; //count of controllers connected

	bool m_bFocused = true; //is the window focused?

	float m_fMovementSpeed = 0.1f; //how fast the camera will move

	vector3 m_v3Mouse = vector3(); //position of the mouse in the window
	bool m_bFPC = false;// First Person Camera flag
	bool m_bArcBall = false;// ArcBall flag
	quaternion m_qArcBall; //ArcBall quaternion

	vector4 m_v4ClearColor; //Color of the scene
	bool m_bRunning = false; //Is App running?
	bool m_bModifier = false; //is shift pressed?

	sf::Window* m_pWindow = nullptr; //SFML window
	SystemSingleton* m_pSystem = nullptr; //Singleton of the system
	LightManager* m_pLightMngr = nullptr; //Light Manager of the system
	MeshManager* m_pMeshMngr = nullptr; //Mesh Manager
	CameraManager* m_pCameraMngr = nullptr; //Singleton for the camera manager
	
	ControllerInput* m_pController[8]; //Controller
	uint m_uActCont = 0; //Active Controller of the Application

	sf::SoundBuffer m_ballRollingSoundBuffer; //buffer to play sound from
	sf::Sound m_ballRollingSound; //sound effect
	//sf::Music m_soundBGM; //background music

public:
#pragma region Constructor / Run / Destructor
	/*
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	Application();
	/*
	USAGE: Initializes the window and rendering context
	ARGUMENTS:
	-	String a_sApplicationName -> Name of the window if blank will use project Name
	-	int size -> formated size, relate to BTO_RESOLUTIONS
	-	bool a_bFullscreen = false -> is the window fullscreen?
	-	bool a_bBorderless = false -> is the window borderless?
	OUTPUT: ---
	*/
	void Init(String a_sApplicationName = "", int a_uSize = BTO_RESOLUTIONS::RES_C_1280x720_16x9_HD,
		bool a_bFullscreen = false, bool a_bBorderless = false);
	/*
	USAGE: Initializes the window and rendering context
	ARGUMENTS:
	-	String a_sApplicationName = "" -> Name of the window if blank will use project Name
	-	uint a_nWidth -> Window Width
	-	uint a_nHeight -> Window Height
	-	bool a_bFullscreen -> is the window fullscreen?
	-	bool a_bBorderless -> is the window borderless?
	OUTPUT: ---
	*/
	void Init(String a_sApplicationName, uint a_uWidth, uint a_uHeight, bool a_bFullscreen, bool a_bBorderless);
	/*
	USAGE: Runs the main loop of this class DO NOT OVERRIDE
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Run(void);
	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~Application(void);
#pragma endregion

private:
#pragma region Initialization / Release
	/*
	USAGE: Initialize the window
	ARGUMENTS: String a_sWindowName = "GLFW" -> Window name
	OUTPUT: ---
	*/
	void InitWindow(String a_sWindowName = "Application");
	/*
	USAGE: Initializes user specific variables, this is executed right after InitWindow,
	the purpose of this member function is to initialize member variables specific for this project.
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void InitVariables(void);
	/*
	USAGE: Reads the configuration of the application to a file
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ReadConfig(void);
	/*
	USAGE: Writes the configuration of the application to a file
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void WriteConfig(void);
	/*
	USAGE: Releases the application
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);
#pragma endregion

#pragma region Main Loop
	/*
	USAGE: Updates the scene
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Update(void);
	/*
	USAGE: Displays the scene
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Display(void);
	/*
	USAGE: Clears the OpenGL screen by the specified color
	ARGUMENTS: vector4 a_v4ClearColor = vector4(-1.0f) -> Color to clear the screen with
	OUTPUT: ---
	*/
	void ClearScreen(vector4 a_v4ClearColor = vector4(-1.0f));
	/*
	USAGE: Will initialize the controllers generically
	ARGUMENTS:
	OUTPUT: ---
	*/
	void InitControllers(void);
	/*
	USAGE: Will Release the controllers
	ARGUMENTS:
	OUTPUT: ---
	*/
	void ReleaseControllers(void);
#pragma endregion

#pragma region Application Controls
	/*
	USAGE: Manage constant keyboard state
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ProcessKeyboard(void);
	/*
	USAGE: Manage constant keyboard state
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ProcessJoystick(void);
	/*
	USAGE: Process the arcball of the scene, rotating an object in the center of it	a_fSensitivity is
	a factor of change
	ARGUMENTS: float a_fSensitivity = 0.1f -> indicates how fast the arcball is going to change
	OUTPUT: ---
	*/
	void ArcBall(float a_fSensitivity = 0.1f);
	/*
	USAGE: Manages the rotation of the camera a_fSpeed is a factor of change
	ARGUMENTS: float a_fSpeed = 0.005f
	OUTPUT: ---
	*/
	void CameraRotation(float a_fSpeed = 0.005f);
#pragma endregion

#pragma region Process Events
	/*
	USAGE: Resizes the window
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Reshape(void);
	/*
	USAGE: Manage the response of key presses
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ProcessKeyPressed(sf::Event a_event);
	/*
	USAGE: Manage the response of key releases
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ProcessKeyReleased(sf::Event a_event);
	/*
	USAGE: Manage the response of mouse movement
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ProcessMouseMovement(sf::Event a_event);
	/*
	USAGE: Manage the response of mouse key presses
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ProcessMousePressed(sf::Event a_event);
	/*
	USAGE: Manage the response of mouse key release
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ProcessMouseReleased(sf::Event a_event);
	/*
	USAGE: Manage the response of mouse scrolling
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ProcessMouseScroll(sf::Event a_event);
	/*
	USAGE: Manage the response of joystick just connected
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ProcessJoystickConnected(uint nController = 0);
	/*
	USAGE: Manage the response of joystick key presses
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ProcessJoystickPressed(sf::Event a_event);
	/*
	USAGE: Manage the response of joystick key release
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ProcessJoystickReleased(sf::Event a_event);
	/*
	USAGE: Manage the response of joystick axis movement
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ProcessJoystickMoved(sf::Event a_event);
#pragma endregion

#pragma region GUI
	/*
	USAGE: Initialize gui
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void InitIMGUI(void);
	/*
	USAGE: Draw GUI elements
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void DrawGUI(void);
	/*
	USAGE: //release gui
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ShutdownGUI(void);
	/*
	USAGE: Render gui lists
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	static void RenderDrawLists(ImDrawData* draw_data);
	/*
	USAGE: Creates fonts for gui
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	bool CreateFontsTexture(void);
	/*
	USAGE: Create OpenGL resources for gui
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	bool CreateDeviceObjects(void);
	/*
	USAGE: creates a new frame for gui
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void NewFrame(void);
#pragma endregion

#pragma region The Rule of Three
	/*
	USAGE: copy constructor, private so it does not let object copy
	ARGUMENTS: GLFWApp const& input -> object to copy (well in this case not)
	OUTPUT: ---
	*/
	Application(Application const& input);
	/*
	USAGE: copy assignment, private so it does not let object copy
	ARGUMENTS: GLFWApp const& input -> object to copy (well in this case not)
	OUTPUT: ---
	*/
	Application& operator=(Application const& input);
#pragma endregion
};

}//namespace Simplex

#endif //__APPLICATIONCLASS_H_

/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/