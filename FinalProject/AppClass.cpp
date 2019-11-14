#include "AppClass.h"
using namespace Simplex;
void Application::InitVariables(void)
{
	//Set the position and target of the camera
	m_pCameraMngr->SetPositionTargetAndUpward(
		vector3(0.0f, 0.0f, 100.0f), //Position
		vector3(0.0f, 0.0f, 99.0f),	//Target
		AXIS_Y);					//Up

	m_pLightMngr->SetPosition(vector3(0.0f, 3.0f, 13.0f), 1); //set the position of first light (0 is reserved for ambient light)

//#ifdef DEBUG
//	uint uInstances = 1000;
//#else
//	uint uInstances = 1000;
//#endif
//	int nSquare = static_cast<int>(std::sqrt(uInstances));
//	m_uObjects = nSquare * nSquare;
//	uint uIndex = -1;
//	for (int i = 0; i < nSquare; i++)
//	{
//		for (int j = 0; j < nSquare; j++)
//		{
//			uIndex++;
//			m_pEntityMngr->AddEntity("Objects\\BowlingPinModel.obj");
//			vector3 v3Position = vector3(glm::sphericalRand(34.0f));
//			matrix4 m4Position = glm::translate(v3Position);
//			m_pEntityMngr->SetModelMatrix(m4Position);
//		}
//	}

	m_pEntityMngr->AddEntity("Objects\\BowlingPinModel.obj"); 
	vector3 v3Position = vector3(0.0f, 0.0f, 50.0f);
	matrix4 m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->UsePhysicsSolver(); 

	m_pEntityMngr->AddEntity("Objects\\BowlingPinModel.obj");
	v3Position = vector3(-0.625f, 0.0f, 48.75f);
	m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->UsePhysicsSolver();

	m_pEntityMngr->AddEntity("Objects\\BowlingPinModel.obj");
	v3Position = vector3(0.625f, 0.0f, 48.75f);
	m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->UsePhysicsSolver();

	m_pEntityMngr->AddEntity("Objects\\BowlingPinModel.obj");
	v3Position = vector3(-1.25f, 0.0f, 47.5f);
	m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->UsePhysicsSolver();

	m_pEntityMngr->AddEntity("Objects\\BowlingPinModel.obj");
	v3Position = vector3(0.0f, 0.0f, 47.5f);
	m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->UsePhysicsSolver();

	m_pEntityMngr->AddEntity("Objects\\BowlingPinModel.obj");
	v3Position = vector3(1.25f, 0.0f, 47.5f);
	m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->UsePhysicsSolver();

	m_pEntityMngr->AddEntity("Objects\\BowlingPinModel.obj");
	v3Position = vector3(-1.875f, 0.0f, 46.25f);
	m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->UsePhysicsSolver();

	m_pEntityMngr->AddEntity("Objects\\BowlingPinModel.obj");
	v3Position = vector3(-0.625f, 0.0f, 46.25f);
	m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->UsePhysicsSolver();

	m_pEntityMngr->AddEntity("Objects\\BowlingPinModel.obj");
	v3Position = vector3(0.625f, 0.0f, 46.25f);
	m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->UsePhysicsSolver();

	m_pEntityMngr->AddEntity("Objects\\BowlingPinModel.obj");
	v3Position = vector3(1.875f, 0.0f, 46.25f);
	m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->UsePhysicsSolver();

	m_pEntityMngr->AddEntity("Objects\\BowlingBallModel.obj");
	v3Position = vector3(0.0f, 0.0f, 80.0f);
	m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);

	m_uOctantLevels = 1;
	m_pRoot = new MyOctant(m_uOctantLevels, 5);
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