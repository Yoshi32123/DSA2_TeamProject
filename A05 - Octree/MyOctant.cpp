#include "MyOctantExample.h"
using namespace Simplex;

/// myOctant
uint MyOctant::m_uOctantCount = 0;
uint MyOctant::m_uMaxLevel = 3;
uint MyOctant::m_uIdealEntityCount = 5;
uint MyOctant::GetOctantCount(void) { return m_uOctantCount; }

/// Initialize all starter variables
void MyOctant::Init(void)
{
	// start with no children and a size of zero
	m_uChildren = 0;
	m_fSize = 0.0f;

	// starting ID and level
	m_uID = m_uOctantCount;
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
	for (uint i = 0; i < 8; i++)
	{
		m_pChild[i] = nullptr;
	}
}

/// Swap main variables to new octant
void MyOctant::Swap(MyOctant& other)
{
	// children info
	std::swap(m_uChildren, other.m_uChildren);

	// octant info
	std::swap(m_fSize, other.m_fSize);
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
	for (uint i = 0; i < 8; i++)
	{
		std::swap(m_pChild[i], other.m_pChild[i]);
	}
}

MyOctant* MyOctant::GetParent(void) { return m_pParent; }

/// Calls when deleting
void MyOctant::Release(void)
{
	// only happens for root
	if (m_uLevel == 0)
	{
		KillBranches();
	}

	// sets main values to default/clears
	m_uChildren = 0;
	m_fSize = 0.0f;
	m_EntityList.clear();
	m_lChild.clear();
}

/// The "Big 3"
MyOctant::MyOctant(uint a_MaxLevel, uint a_IdealEntity)
{
	//Initalize defaults
	Init();

	m_uOctantCount = 0;
	m_uMaxLevel = a_MaxLevel;
	m_uIdealEntityCount = a_IdealEntity;
	m_uID = m_uOctantCount;

	// this is the root, clear any children
	m_pRoot = this;
	m_lChild.clear();

	//List to hold all of the Mins and Maxs
	std::vector<vector3> lMinMax;

	//get # of objects
	uint objects = m_pEntityMngr->GetEntityCount();

	// loop through objects and store their rigidbody and entity
	for (uint i = 0; i < objects; i++)
	{
		// Get the rigidbody through the entity
		MyEntity* pEntity = m_pEntityMngr->GetEntity(i);
		MyRigidBody* pRigidBody = pEntity->GetRigidBody();

		// Add their min/max to list
		lMinMax.push_back(pRigidBody->GetMaxGlobal());
		lMinMax.push_back(pRigidBody->GetMinGlobal());
	}

	MyRigidBody* pRigidBody = new MyRigidBody(lMinMax);

	// determining max based on halfwidths
	vector3 halfWidth = pRigidBody->GetHalfWidth();
	float fMax = halfWidth.x;
	for (int i = 1; i < 3; i++)
	{
		if (fMax < halfWidth[i])
		{
			fMax = halfWidth[i];
		}
	}

	// prep for creation
	vector3 v3Center = pRigidBody->GetCenterLocal();
	lMinMax.clear();
	SafeDelete(pRigidBody);

	// setting values since checks are done
	m_fSize = fMax * 2.0f;
	m_v3Center = v3Center;
	m_v3Min = m_v3Center - (vector3(fMax));
	m_v3Max = m_v3Center + (vector3(fMax));
	m_uOctantCount++;

	// construct the octree
	ConstructTree(m_uMaxLevel);

}
MyOctant::MyOctant(vector3 a_v3Center, float a_fSize)
{
	//Initalize default values
	Init();
	m_v3Center = a_v3Center;
	m_fSize = a_fSize;

	m_v3Max = m_v3Center + (vector3(m_fSize) / 2.0f);
	m_v3Min = m_v3Center - (vector3(m_fSize) / 2.0f);

	m_uOctantCount++;
}
MyOctant::MyOctant(MyOctant const& other)
{
	m_uChildren = other.m_uChildren;
	m_v3Center = other.m_v3Center;
	m_v3Max = other.m_v3Max;
	m_v3Min = other.m_v3Min;

	m_fSize = other.m_fSize;
	m_uID = other.m_uID;
	m_uLevel = other.m_uLevel;
	m_pParent = other.m_pParent;

	m_pRoot = other.m_pRoot;
	m_lChild = other.m_lChild;

	m_pMeshMngr = MeshManager::GetInstance();
	m_pEntityMngr = MyEntityManager::GetInstance();

	for (uint i = 0; i < 8; i++)
	{
		m_pChild[i] = other.m_pChild[i];
	}
}

MyOctant& MyOctant::operator=(MyOctant const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyOctant temp(other);
		Swap(temp);
	}
	return *this;
}
MyOctant::~MyOctant() { Release(); }

/// Accessors
float MyOctant::GetSize(void) { return m_fSize; }
vector3 MyOctant::GetCenterGlobal(void) { return m_v3Center; }
vector3 MyOctant::GetMaxGlobal(void) { return m_v3Max; }
vector3 MyOctant::GetMinGlobal(void) { return m_v3Min; }

/// Non Standard Singleton Methods
void MyOctant::Display(uint a_Index, vector3 a_v3Color)
{
	if (m_uID == a_Index)
	{
		m_pMeshMngr->AddWireCubeToRenderList(glm::translate(IDENTITY_M4, m_v3Center) * glm::scale(vector3(m_fSize)), a_v3Color, RENDER_WIRE);
		return;
	}

	for (uint i = 0; i < m_uChildren; i++)
	{
		m_pChild[i]->Display(a_Index);
	}
}
void MyOctant::Display(vector3 a_v3Color)
{
	for (uint i = 0; i < m_uChildren; i++)
	{
		m_pChild[i]->Display(a_v3Color);
	}
	m_pMeshMngr->AddWireCubeToRenderList(glm::translate(IDENTITY_M4, m_v3Center) * glm::scale(vector3(m_fSize)), a_v3Color, RENDER_WIRE);
}
void MyOctant::Subdivide(void)
{
	//If maxed out, do nothing
	if (m_uLevel >= m_uMaxLevel) { return; }

	//If already subdivided, do nothing
	if (m_uChildren != 0) { return; }

	m_uChildren = 8;
	float fSize = m_fSize / 4.0f;
	float fsizeDouble = fSize * 2.0f;
	vector3 v3Center;

	/* CREATING OCTANTS
	* JUST MOVE THE CENTER POINT AROUND
	* CLOCKWISE STARTING AT BOTTOM LEFT CORNER, MOVE TO TOP AFTER
	*/

	//Octant 0: Bottom Left Backside
	v3Center = m_v3Center;
	v3Center.x -= fSize;
	v3Center.y -= fSize;
	v3Center.z -= fSize;
	m_pChild[0] = new MyOctant(v3Center, fsizeDouble);

	//Octant 1: Bottom Right Backside
	v3Center.x += fsizeDouble;
	m_pChild[1] = new MyOctant(v3Center, fsizeDouble);

	//Octant 2: Bottom Right Frontside
	v3Center.z += fsizeDouble;
	m_pChild[2] = new MyOctant(v3Center, fsizeDouble);

	//Octant 3: Bottom Left Frontside
	v3Center.x -= fsizeDouble;
	m_pChild[3] = new MyOctant(v3Center, fsizeDouble);

	//Octant 4: Top Left Frontside
	v3Center.y += fsizeDouble;
	m_pChild[4] = new MyOctant(v3Center, fsizeDouble);

	//Octant 5: Top Left Backside
	v3Center.z -= fsizeDouble;
	m_pChild[5] = new MyOctant(v3Center, fsizeDouble);

	//Octant 6: Top Right Backside
	v3Center.x += fsizeDouble;
	m_pChild[6] = new MyOctant(v3Center, fsizeDouble);

	//Octant 7: Top Right Frontside
	v3Center.z += fsizeDouble;
	m_pChild[7] = new MyOctant(v3Center, fsizeDouble);


	for (uint i = 0; i < 8; i++)
	{
		//set root parent and level
		m_pChild[i]->m_pRoot = m_pRoot;
		m_pChild[i]->m_pParent = this;
		m_pChild[i]->m_uLevel = m_uLevel + 1;

		//if more objects than ideal, subdivide
		if (m_pChild[i]->ContainsMoreThan(m_uIdealEntityCount))
		{
			m_pChild[i]->Subdivide();
		}
	}

}
MyOctant* MyOctant::GetChild(uint a_child)
{
	if (a_child > 7) { return nullptr; }
	return m_pChild[a_child];
}
bool MyOctant::IsColliding(uint a_uIndex)
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
bool MyOctant::IsLeaf(void) { return m_uChildren == 0; }
bool MyOctant::ContainsMoreThan(uint a_Entities)
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
void MyOctant::KillBranches(void)
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
void MyOctant::DisplayLeafs(vector3 a_v3Color)
{
	uint leaves = m_lChild.size();
	for (uint i = 0; i < leaves; i++)
	{
		m_lChild[i]->DisplayLeafs(a_v3Color);
	}
	m_pMeshMngr->AddWireCubeToRenderList(glm::translate(IDENTITY_M4, m_v3Center) * glm::scale(vector3(m_fSize)), a_v3Color, RENDER_WIRE);
}
void MyOctant::ClearEntityList(void)
{
	for (uint i = 0; i < m_uChildren; i++)
	{
		m_pChild[i]->ClearEntityList();
	}

	m_EntityList.clear();
}
void MyOctant::ConstructTree(uint a_MaxLevel)
{
	// only allow to be applied to root
	if (m_uLevel != 0) { return; }

	m_uMaxLevel = a_MaxLevel;
	m_uOctantCount = 1;

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
void MyOctant::AssignIDtoEntity(void)
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
void MyOctant::ConstructList(void)
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