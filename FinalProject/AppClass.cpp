#include "AppClass.h"
using namespace Simplex;
void Application::InitVariables(void)
{
	//Set the position and target of the camera
	m_pCameraMngr->SetPositionTargetAndUpward(
		vector3(0.0f, 8.0f, 100.0f), //Position
		vector3(0.0f, 8.0f, 99.0f),	//Target
		AXIS_Y);					//Up

	m_pMeshMngr->GenerateSkybox();
	m_pLightMngr->SetPosition(vector3(0.0f, 3.0f, 13.0f), 1); //set the position of first light (0 is reserved for ambient light)

	m_v3BowlingBallStart = vector3(0.5f, 0.0f, 80.0f);
	matrix4 m4Position = glm::translate(m_v3BowlingBall);

	m_pEntityMngr->AddEntity("Objects\\BowlingBallModel.obj", "Ball");
	m_v3BowlingBall = vector3(0.5f, 0.0f, 80.0f);
	m4Position = glm::translate(m_v3BowlingBall);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->UsePhysicsSolver();
	m_pEntityMngr->GetEntity(0)->GetSolver()->SetMass(16.0f);


#pragma region Pins
	m_pEntityMngr->AddEntity("Objects\\BowlingPinModel.obj");
	vector3 v3Position = vector3(0.0f, 0.3f, 50.0f);
	m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->UsePhysicsSolver();
	m_pEntityMngr->GetEntity(1)->GetSolver()->SetMass(3.0f);
	m_lPinLocations.push_back(v3Position);

	m_pEntityMngr->AddEntity("Objects\\BowlingPinModel.obj");
	v3Position = vector3(-0.625f, 0.3f, 48.75f);
	m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->UsePhysicsSolver();
	m_pEntityMngr->GetEntity(2)->GetSolver()->SetMass(3.0f);
	m_lPinLocations.push_back(v3Position);

	m_pEntityMngr->AddEntity("Objects\\BowlingPinModel.obj");
	v3Position = vector3(0.625f, 0.3f, 48.75f);
	m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->UsePhysicsSolver();
	m_pEntityMngr->GetEntity(3)->GetSolver()->SetMass(3.0f);
	m_lPinLocations.push_back(v3Position);

	m_pEntityMngr->AddEntity("Objects\\BowlingPinModel.obj");
	v3Position = vector3(-1.25f, 0.3f, 47.5f);
	m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->UsePhysicsSolver();
	m_pEntityMngr->GetEntity(4)->GetSolver()->SetMass(3.0f);
	m_lPinLocations.push_back(v3Position);

	m_pEntityMngr->AddEntity("Objects\\BowlingPinModel.obj");
	v3Position = vector3(0.0f, 0.3f, 47.5f);
	m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->UsePhysicsSolver();
	m_pEntityMngr->GetEntity(5)->GetSolver()->SetMass(3.0f);
	m_lPinLocations.push_back(v3Position);

	m_pEntityMngr->AddEntity("Objects\\BowlingPinModel.obj");
	v3Position = vector3(1.25f, 0.3f, 47.5f);
	m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->UsePhysicsSolver();
	m_pEntityMngr->GetEntity(6)->GetSolver()->SetMass(3.0f);
	m_lPinLocations.push_back(v3Position);

	m_pEntityMngr->AddEntity("Objects\\BowlingPinModel.obj");
	v3Position = vector3(-1.875f, 0.3f, 46.25f);
	m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->UsePhysicsSolver();
	m_pEntityMngr->GetEntity(7)->GetSolver()->SetMass(3.0f);
	m_lPinLocations.push_back(v3Position);

	m_pEntityMngr->AddEntity("Objects\\BowlingPinModel.obj");
	v3Position = vector3(-0.625f, 0.3f, 46.25f);
	m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->UsePhysicsSolver();
	m_pEntityMngr->GetEntity(8)->GetSolver()->SetMass(3.0f);
	m_lPinLocations.push_back(v3Position);

	m_pEntityMngr->AddEntity("Objects\\BowlingPinModel.obj");
	v3Position = vector3(0.625f, 0.3f, 46.25f);
	m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->UsePhysicsSolver();
	m_pEntityMngr->GetEntity(9)->GetSolver()->SetMass(3.0f);
	m_lPinLocations.push_back(v3Position);

	m_pEntityMngr->AddEntity("Objects\\BowlingPinModel.obj");
	v3Position = vector3(1.875f, 0.3f, 46.25f);
	m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->UsePhysicsSolver();
	m_pEntityMngr->GetEntity(10)->GetSolver()->SetMass(3.0f);
	m_lPinLocations.push_back(v3Position);
#pragma endregion

#pragma region Lane
	// Make lane
	m_pEntityMngr->AddEntity("Objects\\BowlingAlleyModel.obj");
	m_v3BowlingAlley = vector3(0.0f, -1.5f, 55.0f);
	m4Position = glm::translate(m_v3BowlingAlley);
	m_pEntityMngr->SetModelMatrix(m4Position);

	m_pEntityMngr->AddEntity("Objects\\BowlingAlleyModel.obj");
	m_v3BowlingAlley = vector3(3.05f, -1.5f, 55.0f);
	m4Position = glm::translate(m_v3BowlingAlley);
	m_pEntityMngr->SetModelMatrix(m4Position);

	m_pEntityMngr->AddEntity("Objects\\BowlingAlleyModel.obj");
	m_v3BowlingAlley = vector3(-3.05f, -1.5f, 55.0f);
	m4Position = glm::translate(m_v3BowlingAlley);
	m_pEntityMngr->SetModelMatrix(m4Position);

	m_pEntityMngr->AddEntity("Objects\\BowlingAlleyModel.obj");
	m_v3BowlingAlley = vector3(0.0f, -1.5f, 77.74f);
	m4Position = glm::translate(m_v3BowlingAlley);
	m_pEntityMngr->SetModelMatrix(m4Position);

	m_pEntityMngr->AddEntity("Objects\\BowlingAlleyModel.obj");
	m_v3BowlingAlley = vector3(3.05f, -1.5f, 77.74f);
	m4Position = glm::translate(m_v3BowlingAlley);
	m_pEntityMngr->SetModelMatrix(m4Position);

	m_pEntityMngr->AddEntity("Objects\\BowlingAlleyModel.obj");
	m_v3BowlingAlley = vector3(-3.05f, -1.5f, 77.74f);
	m4Position = glm::translate(m_v3BowlingAlley);
	m_pEntityMngr->SetModelMatrix(m4Position);

	m_pEntityMngr->AddEntity("Objects\\PinStopTop.obj");
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

#pragma endregion

	/*m_uOctantLevels = 1;
	m_pRoot = new MyOctant(m_uOctantLevels, 5);*/
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
	
	if (m_bStartTimeTrack)
	{
		m_uTimeBowled = (int)dTimer;
		m_bStartTimeTrack = false;
	}
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

				for (int i = 0; i < 10; i++)
				{
					m_pEntityMngr->SetPosition(m_lPinLocations[i], i + 1);
				}
			}
		}
	}
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

	//Add objects to render list
	if (m_uOctantID == -1) 
	{
		m_pEntityMngr->AddEntityToRenderList(-1, true);
	}
	else
	{
		for (uint i = 0; i < m_pEntityMngr->GetEntityCount(); i++)
		{
			if (m_pEntityMngr->IsInDimension(i, m_uOctantID))
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

	////display octree
	//if (m_uOctantID == -1) //If -1, display base
	//{
	//	m_pRoot->Display();
	//}
	//else //otherwise display
	//{
	//	m_pRoot->Display(m_uOctantID);
	//}

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