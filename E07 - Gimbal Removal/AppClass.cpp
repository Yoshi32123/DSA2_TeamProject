#include "AppClass.h"
void Application::InitVariables(void)
{
	//init the mesh
	m_pMesh = new MyMesh();
	//m_pMesh->GenerateCube(1.0f, C_WHITE);
	m_pMesh->GenerateCone(2.0f, 5.0f, 3, C_WHITE);
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
	
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	// timer info
	static DWORD DStartingTime = GetTickCount();
	DWORD DCurrentTime = GetTickCount();
	DWORD DDelta = DCurrentTime - DStartingTime;
	float fTimer = static_cast<float>(DDelta / 1000.0f);
	std::cout << fTimer << std::endl;

	float fTotalTime = 5.5f;

	float fPercent = MapValue(fTimer, 0.0f, fTotalTime, 0.0f, 1.0f);

	static vector3 v3InitialPoint(0.0f, 0.0f, 0.0f);
	static vector3 v3EndPoint(5.0f, 0.0f, 0.0f);

	static float fStart = 0.0f;
	static float fEnd = 180.0f;
	// end timer info

	matrix4 m4View = m_pCameraMngr->GetViewMatrix();
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	
	//m_m4Model = glm::rotate(IDENTITY_M4, glm::radians(m_v3Rotation.x), vector3(1.0f, 0.0f, 0.0f));
	//m_m4Model = glm::rotate(m_m4Model, glm::radians(m_v3Rotation.y), vector3(0.0f, 1.0f, 0.0f));
	//m_m4Model = glm::rotate(m_m4Model, glm::radians(m_v3Rotation.z), vector3(0.0f, 0.0f, 1.0f));
	


	// ----------------- EXERCISE WORK -----------------------

	//matrix4 m4Rotation =
	//glm::radians(fTimer * 90.0f), vector3(0.0f, 0.0f, 1.0f));
	//m_qOrientation = m_qOrientation * glm::angleAxis(glm::radians(1.0f), vector3(1.0f));
	//m_pMesh->Render(m4Projection, m4View, ToMatrix4(m_qOrientation));

	/* SLERP METHOD
	quaternion q1;
	quaternion q2 = glm::angleAxis(glm::radians(180.0f), vector3(0.0f, 0.0f, 1.0f));
	quaternion q3 = glm::mix(q1, q2, MapValue(fTimer, 0.0f, 2.5f, 0.0f, 1.0f));
	
	m_m4Model = glm::toMat4(q3);
	*/

	// translate vector orientation into a matrix
	matrix4 m4RotX = glm::rotate(IDENTITY_M4, m_v3Rotation.x, AXIS_X);
	matrix4 m4RotY = glm::rotate(IDENTITY_M4, m_v3Rotation.y, AXIS_Y);
	matrix4 m4RotZ = glm::rotate(IDENTITY_M4, m_v3Rotation.z, AXIS_Z);

	matrix4 m4Orientation = m4RotX * m4RotY * m4RotZ;
	

	//m_m4Model = m4Orientation;
	m_m4Model = glm::toMat4(m_qOrientation);
	
	// ------------- END EXERCISE WORK -----------------------

	// render the object
	m_pMesh->Render(m4Projection, m4View, ToMatrix4(m_m4Model));

	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();
	
	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	SafeDelete(m_pMesh);

	//release GUI
	ShutdownGUI();
}