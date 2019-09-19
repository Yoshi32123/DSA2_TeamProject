#include "MyMesh.h"
using namespace Simplex;
//  MyMesh
void MyMesh::Init(void)
{
	m_nData = 0;
}
void MyMesh::Swap(MyMesh& other)
{
	std::swap(m_nData, other.m_nData);
	std::swap(m_lData, other.m_lData);
}
void MyMesh::Release(void)
{
	m_lData.clear();
}
//The big 3
MyMesh::MyMesh() { Init(); }
MyMesh::MyMesh(MyMesh const& other)
{
	m_nData = other.m_nData;
	m_lData = other.m_lData;
}
MyMesh& MyMesh::operator=(MyMesh const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyMesh temp(other);
		Swap(temp);
	}
	return *this;
}
MyMesh::~MyMesh() { Release(); };
//Accessors
void MyMesh::SetData(int a_nData) { m_nData = a_nData; }
int MyMesh::GetData(void) { return m_nData; }
void MyMesh::SetDataOnVector(int a_nData) { m_lData.push_back(a_nData); }
int& MyMesh::GetDataOnVector(int a_nIndex)
{
	int nIndex = static_cast<int>(m_lData.size());
	assert(a_nIndex >= 0 && a_nIndex < nIndex);
	return m_lData[a_nIndex];
}
//--- Non Standard Singleton Methods

