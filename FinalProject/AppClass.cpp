#include "AppClass.h"
using namespace Simplex;
void Application::InitVariables(void)
{
	m_ballPinSoundBuffer.loadFromFile("Bowling_Pins_Strike_Sound_Effect.mp3"); 
	m_ballRollingSoundBuffer.loadFromFile("Bowling_Ball_Rolling_Sound_Effect.mp3");

	m_ballPinSound = sf::Sound(m_ballPinSoundBuffer); 
	m_ballRollingSound = sf::Sound(m_ballRollingSoundBuffer); 

	//Set the position and target of the camera
	m_pCameraMngr->SetPositionTargetAndUpward(
		vector3(0.0f, 8.0f, 100.0f), //Position
		vector3(0.0f, 8.0f, 99.0f),	//Target
		AXIS_Y);					//Up

	m_pMeshMngr->GenerateSkybox();
	m_pLightMngr->SetPosition(vector3(0.0f, 3.0f, 13.0f), 1); //set the position of first light (0 is reserved for ambient light)

	m_v3BowlingBallStart = vector3(0.5f, 2.5f, 80.0f);
	matrix4 m4Position = glm::translate(m_v3BowlingBall);

	m_pEntityMngr->AddEntity("Objects\\BowlingBallModel.obj", "Ball");
	m_v3BowlingBall = vector3(0.5f, 2.5f, 80.0f);
	m4Position = glm::translate(m_v3BowlingBall);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->UsePhysicsSolver();
	m_pEntityMngr->GetEntity(0)->GetSolver()->SetMass(16.0f);

	float fLaneHeight = 2.5f;
	float fPinMass = 3.0f;
	uPinStartIndex = 1;
	uPinCount = 10;

#pragma region Pins

#pragma region Center Pins
	m_pEntityMngr->AddEntity("Objects\\BowlingPinModel.obj");
	vector3 v3Position = vector3(0.0f, fLaneHeight, 50.0f);
	m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->UsePhysicsSolver();
	m_pEntityMngr->GetEntity(1)->GetSolver()->SetMass(fPinMass);
	m_lPinLocations.push_back(v3Position);

	m_pEntityMngr->AddEntity("Objects\\BowlingPinModel.obj");
	v3Position = vector3(-0.625f, fLaneHeight, 48.75f);
	m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->UsePhysicsSolver();
	m_pEntityMngr->GetEntity(2)->GetSolver()->SetMass(fPinMass);
	m_lPinLocations.push_back(v3Position);

	m_pEntityMngr->AddEntity("Objects\\BowlingPinModel.obj");
	v3Position = vector3(0.625f, fLaneHeight, 48.75f);
	m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->UsePhysicsSolver();
	m_pEntityMngr->GetEntity(3)->GetSolver()->SetMass(fPinMass);
	m_lPinLocations.push_back(v3Position);

	m_pEntityMngr->AddEntity("Objects\\BowlingPinModel.obj");
	v3Position = vector3(-1.25f, fLaneHeight, 47.5f);
	m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->UsePhysicsSolver();
	m_pEntityMngr->GetEntity(4)->GetSolver()->SetMass(fPinMass);
	m_lPinLocations.push_back(v3Position);

	m_pEntityMngr->AddEntity("Objects\\BowlingPinModel.obj");
	v3Position = vector3(0.0f, fLaneHeight, 47.5f);
	m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->UsePhysicsSolver();
	m_pEntityMngr->GetEntity(5)->GetSolver()->SetMass(fPinMass);
	m_lPinLocations.push_back(v3Position);

	m_pEntityMngr->AddEntity("Objects\\BowlingPinModel.obj");
	v3Position = vector3(1.25f, fLaneHeight, 47.5f);
	m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->UsePhysicsSolver();
	m_pEntityMngr->GetEntity(6)->GetSolver()->SetMass(fPinMass);
	m_lPinLocations.push_back(v3Position);

	m_pEntityMngr->AddEntity("Objects\\BowlingPinModel.obj");
	v3Position = vector3(-1.875f, fLaneHeight, 46.25f);
	m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->UsePhysicsSolver();
	m_pEntityMngr->GetEntity(7)->GetSolver()->SetMass(fPinMass);
	m_lPinLocations.push_back(v3Position);

	m_pEntityMngr->AddEntity("Objects\\BowlingPinModel.obj");
	v3Position = vector3(-0.625f, fLaneHeight, 46.25f);
	m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->UsePhysicsSolver();
	m_pEntityMngr->GetEntity(8)->GetSolver()->SetMass(fPinMass);
	m_lPinLocations.push_back(v3Position);

	m_pEntityMngr->AddEntity("Objects\\BowlingPinModel.obj");
	v3Position = vector3(0.625f, fLaneHeight, 46.25f);
	m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->UsePhysicsSolver();
	m_pEntityMngr->GetEntity(9)->GetSolver()->SetMass(fPinMass);
	m_lPinLocations.push_back(v3Position);

	m_pEntityMngr->AddEntity("Objects\\BowlingPinModel.obj");
	v3Position = vector3(1.875f, fLaneHeight, 46.25f);
	m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->UsePhysicsSolver();
	m_pEntityMngr->GetEntity(10)->GetSolver()->SetMass(fPinMass);
	m_lPinLocations.push_back(v3Position);

	for (int i = 0; i < uPinCount; i++)
	{
		m_pEntityMngr->GetEntity(i + uAlleyStartIndex)->GetSolver()->SetPin(true);
	}
#pragma endregion

#pragma region Right Pins
	m_pEntityMngr->AddEntity("Objects\\BowlingPinModel.obj");
	v3Position = vector3(15.05f, 0.3f, 50.0f);
	m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);

	m_pEntityMngr->AddEntity("Objects\\BowlingPinModel.obj");
	v3Position = vector3(14.425f, 0.3f, 48.75f);
	m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);

	m_pEntityMngr->AddEntity("Objects\\BowlingPinModel.obj");
	v3Position = vector3(15.675f, 0.3f, 48.75f);
	m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);

	m_pEntityMngr->AddEntity("Objects\\BowlingPinModel.obj");
	v3Position = vector3(13.8f, 0.3f, 47.5f);
	m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);

	m_pEntityMngr->AddEntity("Objects\\BowlingPinModel.obj");
	v3Position = vector3(15.05f, 0.3f, 47.5f);
	m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);

	m_pEntityMngr->AddEntity("Objects\\BowlingPinModel.obj");
	v3Position = vector3(16.3f, 0.3f, 47.5f);
	m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);

	m_pEntityMngr->AddEntity("Objects\\BowlingPinModel.obj");
	v3Position = vector3(13.175f, 0.3f, 46.25f);
	m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);

	m_pEntityMngr->AddEntity("Objects\\BowlingPinModel.obj");
	v3Position = vector3(14.425f, 0.3f, 46.25f);
	m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);

	m_pEntityMngr->AddEntity("Objects\\BowlingPinModel.obj");
	v3Position = vector3(15.675f, 0.3f, 46.25f);
	m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);

	m_pEntityMngr->AddEntity("Objects\\BowlingPinModel.obj");
	v3Position = vector3(16.925f, 0.3f, 46.25f);
	m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);
#pragma endregion
#pragma endregion

#pragma region Lane
#pragma region Main Lane
	float fMakeLane = -0.5f;

	// Make lane
	m_pEntityMngr->AddEntity("Objects\\BowlingAlleyModel.obj", "firstLane");
	m_v3BowlingAlley = vector3(0.0f, fMakeLane, 55.0f);
	m4Position = glm::translate(m_v3BowlingAlley);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->UsePhysicsSolver();

	m_pEntityMngr->AddEntity("Objects\\BowlingAlleyModel.obj");
	m_v3BowlingAlley = vector3(3.05f, fMakeLane, 55.0f);
	m4Position = glm::translate(m_v3BowlingAlley);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->UsePhysicsSolver();

	m_pEntityMngr->AddEntity("Objects\\BowlingAlleyModel.obj");
	m_v3BowlingAlley = vector3(-3.05f, fMakeLane, 55.0f);
	m4Position = glm::translate(m_v3BowlingAlley);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->UsePhysicsSolver();

	m_pEntityMngr->AddEntity("Objects\\BowlingAlleyModel.obj");
	m_v3BowlingAlley = vector3(0.0f, fMakeLane, 77.74f);
	m4Position = glm::translate(m_v3BowlingAlley);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->UsePhysicsSolver();

	m_pEntityMngr->AddEntity("Objects\\BowlingAlleyModel.obj");
	m_v3BowlingAlley = vector3(3.05f, fMakeLane, 77.74f);
	m4Position = glm::translate(m_v3BowlingAlley);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->UsePhysicsSolver();

	m_pEntityMngr->AddEntity("Objects\\BowlingAlleyModel.obj");
	m_v3BowlingAlley = vector3(-3.05f, fMakeLane, 77.74f);
	m4Position = glm::translate(m_v3BowlingAlley);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->UsePhysicsSolver();

	uAlleyStartIndex = m_pEntityMngr->GetEntityIndex("firstLane");
	for (int i = 0; i < uAlleyPieces; i++)
	{
		m_pEntityMngr->GetEntity(i + uAlleyStartIndex)->GetSolver()->SetMass(1000.0f);
		m_pEntityMngr->GetEntity(i + uAlleyStartIndex)->GetSolver()->SetLane(true);
	}

#pragma endregion

#pragma region Other Lanes
	//right bowling lane
	m_pEntityMngr->AddEntity("Objects\\BowlingAlleyModel.obj");
	m_v3BowlingAlley = vector3(12.0f, -2.5f, 55.0f);
	m4Position = glm::translate(m_v3BowlingAlley);
	m_pEntityMngr->SetModelMatrix(m4Position);

	m_pEntityMngr->AddEntity("Objects\\BowlingAlleyModel.obj");
	m_v3BowlingAlley = vector3(15.05f, -2.5f, 55.0f);
	m4Position = glm::translate(m_v3BowlingAlley);
	m_pEntityMngr->SetModelMatrix(m4Position);

	m_pEntityMngr->AddEntity("Objects\\BowlingAlleyModel.obj");
	m_v3BowlingAlley = vector3(15.05f, -2.5f, 77.74f);
	m4Position = glm::translate(m_v3BowlingAlley);
	m_pEntityMngr->SetModelMatrix(m4Position);

	m_pEntityMngr->AddEntity("Objects\\BowlingAlleyModel.obj");
	m_v3BowlingAlley = vector3(18.10f, -2.5f, 77.74f);
	m4Position = glm::translate(m_v3BowlingAlley);
	m_pEntityMngr->SetModelMatrix(m4Position);

	m_pEntityMngr->AddEntity("Objects\\BowlingAlleyModel.obj");
	m_v3BowlingAlley = vector3(18.10f, -2.5f, 55.0f);
	m4Position = glm::translate(m_v3BowlingAlley);
	m_pEntityMngr->SetModelMatrix(m4Position);

	m_pEntityMngr->AddEntity("Objects\\BowlingAlleyModel.obj");
	m_v3BowlingAlley = vector3(12.0f, -2.5f, 77.74f);
	m4Position = glm::translate(m_v3BowlingAlley);
	m_pEntityMngr->SetModelMatrix(m4Position);

	//left bowling lane
	m_pEntityMngr->AddEntity("Objects\\BowlingAlleyModel.obj");
	m_v3BowlingAlley = vector3(-12.0f, -1.5f, 55.0f);
	m4Position = glm::translate(m_v3BowlingAlley);
	m_pEntityMngr->SetModelMatrix(m4Position);

	m_pEntityMngr->AddEntity("Objects\\BowlingAlleyModel.obj");
	m_v3BowlingAlley = vector3(-12.0f, -1.5f, 77.74f);
	m4Position = glm::translate(m_v3BowlingAlley);
	m_pEntityMngr->SetModelMatrix(m4Position);

	m_pEntityMngr->AddEntity("Objects\\BowlingAlleyModel.obj");
	m_v3BowlingAlley = vector3(-15.05f, -1.5f, 77.74f);
	m4Position = glm::translate(m_v3BowlingAlley);
	m_pEntityMngr->SetModelMatrix(m4Position);

	m_pEntityMngr->AddEntity("Objects\\BowlingAlleyModel.obj");
	m_v3BowlingAlley = vector3(-15.05f, -1.5f, 55.0f);
	m4Position = glm::translate(m_v3BowlingAlley);
	m_pEntityMngr->SetModelMatrix(m4Position);

	m_pEntityMngr->AddEntity("Objects\\BowlingAlleyModel.obj");
	m_v3BowlingAlley = vector3(-18.10f, -1.5f, 77.74f);
	m4Position = glm::translate(m_v3BowlingAlley);
	m_pEntityMngr->SetModelMatrix(m4Position);

	m_pEntityMngr->AddEntity("Objects\\BowlingAlleyModel.obj");
	m_v3BowlingAlley = vector3(-18.10f, -1.5f, 55.0f);
	m4Position = glm::translate(m_v3BowlingAlley);
	m_pEntityMngr->SetModelMatrix(m4Position);
#pragma endregion

#pragma endregion

#pragma region Pin stop

	//centre pin stops
	m_pEntityMngr->AddEntity("Objects\\PinStopTop.obj", "firstPinStop");
	m_v3BowlingAlley = vector3(0.0f, -8.0f, 43.5f);
	m4Position = glm::translate(m_v3BowlingAlley);
	m_pEntityMngr->SetModelMatrix(m4Position);

	m_pEntityMngr->AddEntity("Objects\\PinStopTop.obj");
	m_v3BowlingAlley = vector3(0.0f, -20.0f, 43.5f);
	m4Position = glm::translate(m_v3BowlingAlley);
	m_pEntityMngr->SetModelMatrix(m4Position);

	m_pEntityMngr->AddEntity("Objects\\PinStopWall.obj");
	m_v3BowlingAlley = vector3(0.0f, -8.0f, 43.5f);
	m4Position = glm::translate(m_v3BowlingAlley);
	m_pEntityMngr->SetModelMatrix(m4Position);

	m_pEntityMngr->AddEntity("Objects\\PinStopWall.obj");
	m_v3BowlingAlley = vector3(-10.0f, -8.0f, 43.5f);
	m4Position = glm::translate(m_v3BowlingAlley);
	m_pEntityMngr->SetModelMatrix(m4Position);

	m_pEntityMngr->AddEntity("Objects\\PinStopBack.obj");
	m_v3BowlingAlley = vector3(0.0f, -8.0f, 43.5f);
	m4Position = glm::translate(m_v3BowlingAlley);
	m_pEntityMngr->SetModelMatrix(m4Position);

	uPinStopStartIndex = m_pEntityMngr->GetEntityIndex("firstPinStop");
	for (int i = 0; i < uPinStopPieces; i++)
	{
		m_pEntityMngr->GetEntity(i + uPinStopStartIndex)->GetSolver()->SetMass(1000.0f);
	}

	//left pin stops
	m_pEntityMngr->AddEntity("Objects\\PinStopTop.obj");
	m_v3BowlingAlley = vector3(-15.05f, -8.0f, 43.5f);
	m4Position = glm::translate(m_v3BowlingAlley);
	m_pEntityMngr->SetModelMatrix(m4Position);

	m_pEntityMngr->AddEntity("Objects\\PinStopTop.obj");
	m_v3BowlingAlley = vector3(-15.05f, -20.0f, 43.5f);
	m4Position = glm::translate(m_v3BowlingAlley);
	m_pEntityMngr->SetModelMatrix(m4Position);

	m_pEntityMngr->AddEntity("Objects\\PinStopWall.obj");
	m_v3BowlingAlley = vector3(-15.05f, -8.0f, 43.5f);
	m4Position = glm::translate(m_v3BowlingAlley);
	m_pEntityMngr->SetModelMatrix(m4Position);

	m_pEntityMngr->AddEntity("Objects\\PinStopWall.obj");
	m_v3BowlingAlley = vector3(-25.05f, -8.0f, 43.5f);
	m4Position = glm::translate(m_v3BowlingAlley);
	m_pEntityMngr->SetModelMatrix(m4Position);

	m_pEntityMngr->AddEntity("Objects\\PinStopBack.obj");
	m_v3BowlingAlley = vector3(-15.05f, -8.0f, 43.5f);
	m4Position = glm::translate(m_v3BowlingAlley);
	m_pEntityMngr->SetModelMatrix(m4Position);

	//right
	m_pEntityMngr->AddEntity("Objects\\PinStopTop.obj");
	m_v3BowlingAlley = vector3(15.05f, -8.0f, 43.5f);
	m4Position = glm::translate(m_v3BowlingAlley);
	m_pEntityMngr->SetModelMatrix(m4Position);

	m_pEntityMngr->AddEntity("Objects\\PinStopTop.obj");
	m_v3BowlingAlley = vector3(15.05f, -20.0f, 43.5f);
	m4Position = glm::translate(m_v3BowlingAlley);
	m_pEntityMngr->SetModelMatrix(m4Position);

	m_pEntityMngr->AddEntity("Objects\\PinStopWall.obj");
	m_v3BowlingAlley = vector3(15.05f, -8.0f, 43.5f);
	m4Position = glm::translate(m_v3BowlingAlley);
	m_pEntityMngr->SetModelMatrix(m4Position);

	m_pEntityMngr->AddEntity("Objects\\PinStopWall.obj");
	m_v3BowlingAlley = vector3(5.05f, -8.0f, 43.5f);
	m4Position = glm::translate(m_v3BowlingAlley);
	m_pEntityMngr->SetModelMatrix(m4Position);

	m_pEntityMngr->AddEntity("Objects\\PinStopBack.obj");
	m_v3BowlingAlley = vector3(15.05f, -8.0f, 43.5f);
	m4Position = glm::translate(m_v3BowlingAlley);
	m_pEntityMngr->SetModelMatrix(m4Position);
#pragma endregion

	m_uGridLevels = 1;
	m_pRoot = new MyGrid(m_uGridLevels, 5);
	m_pEntityMngr->Update();
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the ArcBall active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();

	/* -------- Main Project Code -------- */

	// update canBowl based on time
	static uint uClock = m_pSystem->GenClock();
	static double dTimer = m_pSystem->GetDeltaTime(uClock);
	dTimer += m_pSystem->GetDeltaTime(uClock);
	
	// will add to the amount of times bowled
	if (m_bStartTimeTrack)
	{
		m_uTimeBowled = (int)dTimer;
		m_bStartTimeTrack = false;
	}

	// Set up bumpers if they are enabled or not
	if (!m_bBumpersMade && m_bBumpersEnabled)
	{
		m_pEntityMngr->AddEntity("Objects\\BumpersModel.obj", "bumper");
		m_v3BowlingAlley = vector3(-4.0f, 1.25f, 60.0f);
		matrix4 m4Position = glm::translate(m_v3BowlingAlley);
		m_pEntityMngr->SetModelMatrix(m4Position);

		m_pEntityMngr->AddEntity("Objects\\BumpersModel.obj", "bumper");
		m_v3BowlingAlley = vector3(-4.0f, 1.25f, 77.5f);
		m4Position = glm::translate(m_v3BowlingAlley);
		m_pEntityMngr->SetModelMatrix(m4Position);

		m_pEntityMngr->AddEntity("Objects\\BumpersModel.obj", "bumper");
		m_v3BowlingAlley = vector3(4.0f, 1.25f, 60.0f);
		m4Position = glm::translate(m_v3BowlingAlley);
		m_pEntityMngr->SetModelMatrix(m4Position);

		m_pEntityMngr->AddEntity("Objects\\BumpersModel.obj", "bumper");
		m_v3BowlingAlley = vector3(4.0f, 1.25f, 77.5f);
		m4Position = glm::translate(m_v3BowlingAlley);
		m_pEntityMngr->SetModelMatrix(m4Position);

		// Set the bumpers made bool to true so that bumpers aren't constantly being made
		m_bBumpersMade = true;
		m_bBumpersDestroyed = false;
	}
	else if(!m_bBumpersDestroyed && !m_bBumpersEnabled)
	{
		for (uint i = 0; i < 4; i++)
		{
			m_pEntityMngr->RemoveEntity("bumper");
		}

		// Set bools so that code doesn't commit un-alive
		m_bBumpersDestroyed = true;
		m_bBumpersMade = false;
	}

	// If the ball cannot be bowled, that means that it is currently being bowled so all positions and fields should be updated
	if (!m_bCanBowl)
	{
		m_uTimeSinceBowled = (int)dTimer - m_uTimeBowled;

		if (m_uTimeSinceBowled >= 5)
		{
			m_pEntityMngr->SetPosition(m_v3BowlingBallStart, "Ball");
			m_uTimeBowled = 0;
			m_uTimeSinceBowled = 0;
			m_bCanBowl = true;

			if (m_uTimesBowled == 2)
			{
				m_uTimesBowled = 0;
				

				for (int i = 0; i < uPinCount; i++)
				{
					m_pEntityMngr->SetPosition(m_lPinLocations[i], uPinStartIndex + i);
				}
			}
		}
	}
	// prevents left and right movement before bowl to go off the lane
	else
	{
		if (m_v3BowlingBall.x > 2 && m_bManualMove)
			m_v3BowlingBall.x = 2;
		else if (m_v3BowlingBall.x < -2 && m_bManualMove)
			m_v3BowlingBall.x = -2;

		m_pEntityMngr->SetPosition(m_v3BowlingBall, "Ball");
	}

	//Update bowling ball position
	if (!m_bManualMove)
		m_pEntityMngr->SetPosition(m_v3BowlingBall, "Ball");
	else
		m_v3BowlingBall = m_pEntityMngr->GetEntity(0)->GetPosition();

	//Update Entity Manager
	m_pEntityMngr->Update();

	m_pEntityMngr->ClearDimensionSetAll();
	//m_pRoot->ClearEntityList();
	//m_pRoot->AssignIDtoEntity(); 
	SafeDelete(m_pRoot);
	m_pRoot = new MyGrid(m_uGridLevels, 5);

	//Add objects to render list
	if (m_uGridID == -1) 
	{
		m_pEntityMngr->AddEntityToRenderList(-1, true);
	}
	else
	{
		for (uint i = 0; i < m_pEntityMngr->GetEntityCount(); i++)
		{
			if (m_pEntityMngr->IsInDimension(i, m_uGridID))
			{
				m_pEntityMngr->AddEntityToRenderList(i, true);
			}
		}
	}

	/* -------- End Main Project Code -------- */

	
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	//display octree
	if (m_uGridID == -1) //If -1, display base
	{
		m_pRoot->Display();
	}
	else //otherwise display
	{
		m_pRoot->Display(m_uGridID);
	}

	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();
	
	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui,
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	// deleting the octree
	SafeDelete(m_pRoot);

	//release GUI
	ShutdownGUI();
}