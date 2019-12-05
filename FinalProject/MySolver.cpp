#include "MySolver.h"
using namespace Simplex;
//  MySolver
void MySolver::Init(void)
{
	m_v3Acceleration = ZERO_V3;
	m_v3Position = ZERO_V3;
	m_v3Velocity = ZERO_V3;
	m_fMass = 1.0f;
}
void MySolver::Swap(MySolver& other)
{
	std::swap(m_v3Acceleration, other.m_v3Acceleration);
	std::swap(m_v3Velocity, other.m_v3Velocity);
	std::swap(m_v3Position, other.m_v3Position);
	std::swap(m_fMass, other.m_fMass);
}
void MySolver::Release(void) {/*nothing to deallocate*/ }
//The big 3
MySolver::MySolver(void) { Init(); }
MySolver::MySolver(MySolver const& other)
{
	m_v3Acceleration = other.m_v3Acceleration;
	m_v3Velocity = other.m_v3Velocity;
	m_v3Position = other.m_v3Position;
	m_fMass = other.m_fMass;
}
MySolver& MySolver::operator=(MySolver const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		MySolver temp(other);
		Swap(temp);
	}
	return *this;
}
MySolver::~MySolver() { Release(); }

//Accessors
void MySolver::SetPosition(vector3 a_v3Position) { m_v3Position = a_v3Position; }
vector3 MySolver::GetPosition(void) { return m_v3Position; }

void MySolver::SetSize(vector3 a_v3Size) { m_v3Size = a_v3Size; }
vector3 MySolver::GetSize(void) { return m_v3Size; }

void Simplex::MySolver::SetLane(bool a_bIsLane)
{
	m_bLane = a_bIsLane;
}
bool Simplex::MySolver::GetLane(void)
{
	return m_bLane;
}

void Simplex::MySolver::SetPin(bool a_bIsPin)
{
	m_bPin = a_bIsPin;
}
bool Simplex::MySolver::GetPin(void)
{
	return m_bPin;
}

void MySolver::SetVelocity(vector3 a_v3Velocity) { m_v3Velocity = a_v3Velocity; }
vector3 MySolver::GetVelocity(void) { return m_v3Velocity; }

void MySolver::SetMass(float a_fMass) { m_fMass = a_fMass; }
float MySolver::GetMass(void) { return m_fMass; }

//Methods
void MySolver::ApplyFriction(float a_fFriction)
{
	if (a_fFriction < 0.01f)
		a_fFriction = 0.01f;

	m_v3Velocity *= 1.0f - a_fFriction;

	//if velocity is really small make it zero
	if (glm::length(m_v3Velocity) < 0.01f)
		m_v3Velocity = ZERO_V3;
}
void MySolver::ApplyForce(vector3 a_v3Force)
{
	//check minimum mass
	if (m_fMass < 0.01f)
		m_fMass = 0.01f;
	//f = m * a -> a = f / m
	m_v3Acceleration += a_v3Force / m_fMass;
}
vector3 CalculateMaxVelocity(vector3 a_v3Velocity, float maxVelocity)
{
	if (glm::length(a_v3Velocity) > maxVelocity)
	{
		a_v3Velocity = glm::normalize(a_v3Velocity);
		a_v3Velocity *= maxVelocity;
	}
	return a_v3Velocity;
}
vector3 RoundSmallVelocity(vector3 a_v3Velocity, float minVelocity = 0.01f)
{
	if (glm::length(a_v3Velocity) < minVelocity)
	{
		a_v3Velocity = ZERO_V3;
	}
	return a_v3Velocity;
}
void MySolver::Update(void)
{
	ApplyForce(vector3(0.0f, -0.035f, 0.0f));

	m_v3Velocity += m_v3Acceleration;

	float fMaxVelocity = 5.0f;
	m_v3Velocity = CalculateMaxVelocity(m_v3Velocity, fMaxVelocity);

	if (this->m_v3Position.y == 0.0f)
		ApplyFriction(0.03f);
	else
		ApplyFriction(0.015f);

	if (this->m_bPin)
	{
		switch (m_uPinState)
		{
			// stores start position
			case 0:
				m_v3PinStart = m_v3Position;
				m_uPinState++;
				break;

			// checking for if they have move a certain distance from their starting location
			case 1:
				magStorage = m_v3Position - m_v3PinStart;
				magnitude = glm::sqrt(glm::pow2(magStorage.x) + glm::pow2(magStorage.y) + glm::pow2(magStorage.z));
				if (magnitude > 5)
					m_uPinState++;
				break;

			// Store velocity direction
			case 2:
				m_v3PinDirection = glm::normalize(m_v3Velocity);
				m_uPinState++;
				break;

			// Rotate in the direction of the velocity until 90 degrees
			case 3:

				break;
			default:
				break;
		}

		std::cout << "Pin State:" << m_uPinState << std::endl;
	}

	m_v3Velocity = RoundSmallVelocity(m_v3Velocity, 0.028f);

	m_v3Position += m_v3Velocity;

	if (m_v3Position.y <= 0)
	{
		m_v3Position.y = 0;
		m_v3Velocity.y = 0;
	}

	m_v3Acceleration = ZERO_V3;
}
void MySolver::ResolveCollision(MySolver* a_pOther)
{
	float fMagThis = glm::length(m_v3Velocity);
	float fMagOther = glm::length(a_pOther->GetVelocity());

	float fMassThis = this->GetMass();
	float fMassOther = a_pOther->GetMass();

	vector3 v3Direction = m_v3Position - a_pOther->m_v3Position;

	if (glm::length(v3Direction) != 0)
		v3Direction = glm::normalize(v3Direction);

	if (m_bLane || a_pOther->m_bLane)
		v3Direction = vector3(0.0f, 1.0f, 0.0f);

	if (fMagThis > 0.015f || fMagOther > 0.015f)
	{
		float fCollisionTime = 0.8f;

		vector3 m_v3VelDirThis = (-a_pOther->GetVelocity() * 0.1) * v3Direction;
		ApplyForce(fMassOther * m_v3VelDirThis / fCollisionTime);

		vector3 m_v3VelDirOther = (-m_v3Velocity * 0.1) * v3Direction;
		a_pOther->ApplyForce(fMassThis * m_v3VelDirOther / fCollisionTime);
	}

	v3Direction *= 0.05f;
	ApplyForce(v3Direction);
	a_pOther->ApplyForce(-v3Direction);
}
void MySolver::PinFallOver()
{
	vector3 m_v3VelocityDir = glm::normalize(m_v3Velocity);


}
