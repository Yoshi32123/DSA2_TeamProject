#include "MyGrid.h"
using namespace Simplex;

/// MyGrid
uint MyGrid::m_uGridCount = 0;
uint MyGrid::m_uMaxLevel = 3;
uint MyGrid::m_uIdealEntityCount = 5;
uint MyGrid::GetOctantCount(void) { return m_uGridCount; }

/// Initialize all starter variables
void MyGrid::Init(void)
{
	// start with no children and a size of zero
	m_uChildren = 0;
	m_fSizeX = 0.0f;
	m_fSizeZ = 0.0f; 

	// starting ID and level
	m_uID = m_uGridCount;
	m_uLevel = 0;

	// start center, max, min at 0
	m_v3Center = vector3(0.0f);
	m_v3Max = vector3(0.0f);
	m_v3Min = vector3(0.0f);

	// setup managers
	m_pMeshMngr = MeshManager::GetInstance();
	m_pEntityMngr = MyEntityManager::GetInstance();

	// root octant and parent octants are null
	m_pRoot = nullptr;
	m_pParent = nullptr;

	// set all child octants as nullptr
	for (uint i = 0; i < 6; i++)
	{
		m_pChild[i] = nullptr;
	}
}

/// Swap main variables to new octant
void MyGrid::Swap(MyGrid& other)
{
	// children info
	std::swap(m_uChildren, other.m_uChildren);

	// octant info
	std::swap(m_fSizeX, other.m_fSizeX);
	std::swap(m_fSizeZ, other.m_fSizeZ);
	std::swap(m_uID, other.m_uID);
	std::swap(m_pRoot, other.m_pRoot);
	std::swap(m_lChild, other.m_lChild);

	// vector info
	std::swap(m_v3Center, other.m_v3Center);
	std::swap(m_v3Max, other.m_v3Max);
	std::swap(m_v3Min, other.m_v3Min);

	// managers
	m_pMeshMngr = MeshManager::GetInstance();
	m_pEntityMngr = MyEntityManager::GetInstance();

	// levels, parents
	std::swap(m_uLevel, other.m_uLevel);
	std::swap(m_pParent, other.m_pParent);

	// recursive call for all existing children
	for (uint i = 0; i < 6; i++)
	{
		std::swap(m_pChild[i], other.m_pChild[i]);
	}
}

MyGrid* MyGrid::GetParent(void) { return m_pParent; }

/// Calls when deleting
void MyGrid::Release(void)
{
	// only happens for root
	if (m_uLevel == 0)
	{
		KillBranches();
	}

	// sets main values to default/clears
	m_uChildren = 0;
	m_fSizeX = 0.0f;
	m_fSizeZ = 0.0f;
	m_EntityList.clear();
	m_lChild.clear();
}

/// The "Big 3"
MyGrid::MyGrid(uint a_MaxLevel, uint a_IdealEntity)
{
	//Initalize defaults
	Init();

	m_uGridCount = 0;
	m_uMaxLevel = a_MaxLevel;
	m_uIdealEntityCount = a_IdealEntity;
	m_uID = m_uGridCount;

	// this is the root, clear any children
	m_pRoot = this;
	m_lChild.clear();

	//List to hold all of the Mins and Maxs
	std::vector<vector3> lMinMax;

	//get # of objects
	uint objects = m_pEntityMngr->GetEntityCount();

	//// loop through objects and store their rigidbody and entity
	//for (uint i = 0; i < objects; i++)
	//{
	//	// Get the rigidbody through the entity
	//	MyEntity* pEntity = m_pEntityMngr->GetEntity(i);
	//	MyRigidBody* pRigidBody = pEntity->GetRigidBody();

	//	// Add their min/max to list
	//	lMinMax.push_back(pRigidBody->GetMaxGlobal());
	//	lMinMax.push_back(pRigidBody->GetMinGlobal());
	//}

	lMinMax.push_back(vector3(18.0f, 10.0f, 55.0f));
	lMinMax.push_back(vector3(-18.0f, -10.0f, 25.0f));

	MyRigidBody* pRigidBody = new MyRigidBody(lMinMax);

	// determining max based on halfwidths
	vector3 halfWidth = pRigidBody->GetHalfWidth();
	float fMaxX = halfWidth.x;
	float fMaxZ = halfWidth.z; 
	//for (int i = 1; i < 3; i++)
	//{
	//	if (fMax < halfWidth[i])
	//	{
	//		fMax = halfWidth[i];
	//	}
	//}

	// prep for creation
	vector3 v3Center = pRigidBody->GetCenterLocal();
	lMinMax.clear();
	SafeDelete(pRigidBody);

	// setting values since checks are done
	m_fSizeX = fMaxX * 2.0f;
	m_fSizeZ = fMaxZ * 2.0f;
	m_v3Center = v3Center;
	m_v3Min = m_v3Center - (vector3(fMaxX, 0, fMaxZ));
	m_v3Max = m_v3Center + (vector3(fMaxX, 0, fMaxZ));
	m_uGridCount++;

	// construct the octree
	ConstructTree(m_uMaxLevel);

}
MyGrid::MyGrid(vector3 a_v3Center, float a_fSizeX, float a_fSizeZ)
{
	//Initalize default values
	Init();
	m_v3Center = a_v3Center;
	m_fSizeX = a_fSizeX;
	m_fSizeZ = a_fSizeZ; 

	m_v3Max = m_v3Center + (vector3(m_fSizeX, 10.0f, m_fSizeZ) / 2.0f);
	m_v3Min = m_v3Center - (vector3(m_fSizeX, 10.0f, m_fSizeZ) / 2.0f);

	m_uGridCount++;
}
MyGrid::MyGrid(MyGrid const& other)
{
	m_uChildren = other.m_uChildren;
	m_v3Center = other.m_v3Center;
	m_v3Max = other.m_v3Max;
	m_v3Min = other.m_v3Min;

	m_fSizeX = other.m_fSizeX;
	m_fSizeZ = other.m_fSizeZ;
	m_uID = other.m_uID;
	m_uLevel = other.m_uLevel;
	m_pParent = other.m_pParent;

	m_pRoot = other.m_pRoot;
	m_lChild = other.m_lChild;

	m_pMeshMngr = MeshManager::GetInstance();
	m_pEntityMngr = MyEntityManager::GetInstance();

	for (uint i = 0; i < 6; i++)
	{
		m_pChild[i] = other.m_pChild[i];
	}
}

MyGrid& MyGrid::operator=(MyGrid const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyGrid temp(other);
		Swap(temp);
	}
	return *this;
}
MyGrid::~MyGrid() { Release(); }

/// Accessors
float MyGrid::GetSizeX(void) { return m_fSizeX; }
float MyGrid::GetSizeZ(void) { return m_fSizeZ; }
vector3 MyGrid::GetCenterGlobal(void) { return m_v3Center; }
vector3 MyGrid::GetMaxGlobal(void) { return m_v3Max; }
vector3 MyGrid::GetMinGlobal(void) { return m_v3Min; }

/// Non Standard Singleton Methods
void MyGrid::Display(uint a_Index, vector3 a_v3Color)
{
	if (m_uID == a_Index)
	{
		m_pMeshMngr->AddWireCubeToRenderList(glm::translate(IDENTITY_M4, m_v3Center) * glm::scale(vector3(m_fSizeX, 10.0f, m_fSizeZ)), a_v3Color, RENDER_WIRE);
		return;
	}

	for (uint i = 0; i < m_uChildren; i++)
	{
		m_pChild[i]->Display(a_Index);
	}
}
void MyGrid::Display(vector3 a_v3Color)
{
	for (uint i = 0; i < m_uChildren; i++)
	{
		m_pChild[i]->Display(a_v3Color);
	}
	m_pMeshMngr->AddWireCubeToRenderList(glm::translate(IDENTITY_M4, m_v3Center) * glm::scale(vector3(m_fSizeX, 10.0f, m_fSizeZ)), a_v3Color, RENDER_WIRE);
}
void MyGrid::Subdivide(void)
{
	//If maxed out, do nothing
	if (m_uLevel >= m_uMaxLevel) { return; }

	//If already subdivided, do nothing
	if (m_uChildren != 0) { return; }

	m_uChildren = 6;
	float fSizeX = m_fSizeX / 6.0f;
	float fSizeZ = m_fSizeZ / 4.0f; 
	float fsizeDoubleX = fSizeX * 2.0f;
	float fsizeDoubleZ = fSizeZ * 2.0f;
	vector3 v3Center;

	/* CREATING OCTANTS
	* JUST MOVE THE CENTER POINT AROUND
	* CLOCKWISE STARTING AT BOTTOM LEFT CORNER, MOVE TO TOP AFTER
	*/

	//Octant 0: Left Backside
	v3Center = m_v3Center;
	v3Center.x -= fsizeDoubleX;
	v3Center.z -= fSizeZ;
	m_pChild[0] = new MyGrid(v3Center, fsizeDoubleX, fsizeDoubleZ);

	//Octant 1: Center Backside
	v3Center.x += fsizeDoubleX;
	m_pChild[1] = new MyGrid(v3Center, fsizeDoubleX, fsizeDoubleZ);

	//Octant 2: Right Backside
	v3Center.x += fsizeDoubleX;
	m_pChild[2] = new MyGrid(v3Center, fsizeDoubleX, fsizeDoubleZ);

	//Octant 3: Right Frontside
	v3Center.z += fsizeDoubleZ;
	m_pChild[3] = new MyGrid(v3Center, fsizeDoubleX, fsizeDoubleZ);

	//Octant 4: Center Frontside
	v3Center.x -= fsizeDoubleX;
	m_pChild[4] = new MyGrid(v3Center, fsizeDoubleX, fsizeDoubleZ);

	//Octant 5: Left Frontside
	v3Center.x -= fsizeDoubleX;
	m_pChild[5] = new MyGrid(v3Center, fsizeDoubleX, fsizeDoubleZ);

	for (uint i = 0; i < 6; i++)
	{
		//set root parent and level
		m_pChild[i]->m_pRoot = m_pRoot;
		m_pChild[i]->m_pParent = this;
		m_pChild[i]->m_uLevel = m_uLevel + 1;

		////if more objects than ideal, subdivide
		//if (m_pChild[i]->ContainsMoreThan(m_uIdealEntityCount))
		//{
		//	m_pChild[i]->Subdivide();
		//}
	}

}
MyGrid* MyGrid::GetChild(uint a_child)
{
	if (a_child > 5) { return nullptr; }
	return m_pChild[a_child];
}
bool MyGrid::IsColliding(uint a_uIndex)
{
	uint objCount = m_pEntityMngr->GetEntityCount();

	//if index > objCount in bounds, no collision
	if (a_uIndex >= objCount) { return false; }

	//Only have to check AABB since nothing is rotating/scaling (no SAT implemented)
	//Get vectors in global space
	MyEntity* pEntity = m_pEntityMngr->GetEntity(a_uIndex);
	MyRigidBody* pRigidBody = pEntity->GetRigidBody();
	vector3 v3MinG = pRigidBody->GetMinGlobal();
	vector3 v3MaxG = pRigidBody->GetMaxGlobal();

	//Check X
	if (m_v3Max.x < v3MinG.x) { return false; }
	if (m_v3Min.x > v3MaxG.x) { return false; }
	//Check Y
	if (m_v3Max.y < v3MinG.y) { return false; }
	if (m_v3Min.y > v3MaxG.y) { return false; }
	//Check Z
	if (m_v3Max.z < v3MinG.z) { return false; }
	if (m_v3Min.z > v3MaxG.z) { return false; }

	return true;
}
bool MyGrid::IsLeaf(void) { return m_uChildren == 0; }
bool MyGrid::ContainsMoreThan(uint a_Entities)
{
	uint count = 0;
	uint objCount = m_pEntityMngr->GetEntityCount();

	for (uint i = 0; i < objCount; i++)
	{
		if (IsColliding(i)) { count++; }
		if (count > a_Entities) { return true; }
	}

	return false;
}
void MyGrid::KillBranches(void)
{
	// starts as low as possible and deletes all children for each layer recursively until back at root

	for (uint i = 0; i < m_uChildren; i++)
	{
		m_pChild[i]->KillBranches();
		delete m_pChild[i];
		m_pChild[i] = nullptr;
	}
	m_uChildren = 0;
}
void MyGrid::DisplayLeafs(vector3 a_v3Color)
{
	uint leaves = m_lChild.size();
	for (uint i = 0; i < leaves; i++)
	{
		m_lChild[i]->DisplayLeafs(a_v3Color);
	}
	m_pMeshMngr->AddWireCubeToRenderList(glm::translate(IDENTITY_M4, m_v3Center) * glm::scale(vector3(m_fSizeX, 0, m_fSizeZ)), a_v3Color, RENDER_WIRE);
}
void MyGrid::ClearEntityList(void)
{
	for (uint i = 0; i < m_uChildren; i++)
	{
		m_pChild[i]->ClearEntityList();
	}

	m_EntityList.clear();
}
void MyGrid::ConstructTree(uint a_MaxLevel)
{
	// only allow to be applied to root
	if (m_uLevel != 0) { return; }

	m_uMaxLevel = a_MaxLevel;
	m_uGridCount = 1;

	// clear tree
	m_EntityList.clear();
	KillBranches();
	m_lChild.clear();

	// if base
	if (ContainsMoreThan(m_uIdealEntityCount))
	{
		Subdivide();
	}

	// assign ID
	AssignIDtoEntity();

	// construct list
	ConstructList();
}
void MyGrid::AssignIDtoEntity(void)
{
	// go until reach a leaf
	for (uint i = 0; i < m_uChildren; i++)
	{
		m_pChild[i]->AssignIDtoEntity();
	}

	if (m_uChildren == 0)
	{
		uint entities = m_pEntityMngr->GetEntityCount();
		for (uint i = 0; i < entities; i++)
		{
			if (IsColliding(i))
			{
				m_EntityList.push_back(i);
				m_pEntityMngr->AddDimension(i, m_uID);
			}
		}
	}
}
void MyGrid::ConstructList(void)
{
	for (uint i = 0; i < m_uChildren; i++)
	{
		m_pChild[i]->ConstructList();
	}

	if (m_EntityList.size() > 0)
	{
		m_pRoot->m_lChild.push_back(this);
	}
}