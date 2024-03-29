/*----------------------------------------------
Programmer: Kyler McQuillan (kjm7088@g.rit.com)
Date: 2019/12
----------------------------------------------*/
#ifndef __MYSOLVER_H_
#define __MYSOLVER_H_

#include "MyRigidBody.h"
using namespace Simplex;

namespace Simplex
{
	class MySolver
	{
		vector3 m_v3Acceleration = ZERO_V3; //Acceleration of the MySolver
		vector3 m_v3Position = ZERO_V3; //Position of the MySolver
		vector3 m_v3Size = vector3(1.0f); //Size of the MySolver
		vector3 m_v3Velocity = ZERO_V3; //Velocity of the MySolver
		float m_fMass = 1.0f; //Mass of the solver
		bool m_bLane = false;
		float m_fFriction;

		// pin helper fields
		bool m_bPin = false;
		bool m_bBall = false; 
		uint m_uPinState = 0;
		vector3 m_v3PinStart = ZERO_V3;
		vector3 magStorage = ZERO_V3;
		uint magnitude = 0;
		vector3 m_v3PinDirection;

	public:
		/*
		USAGE: Constructor
		ARGUMENTS: ---
		OUTPUT: object instance
		*/
		MySolver(void);
		/*
		USAGE: Copy Constructor
		ARGUMENTS: object to copy
		OUTPUT: object instance
		*/
		MySolver(MySolver const& other);
		/*
		USAGE: Copy Assignment Operator
		ARGUMENTS: object to copy
		OUTPUT: this instance
		*/
		MySolver& operator=(MySolver const& other);
		/*
		USAGE: Destructor
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		~MySolver(void);
		/*
		USAGE: Content Swap
		ARGUMENTS: object to swap content with
		OUTPUT: ---
		*/
		void Swap(MySolver& other);

		/*
		USAGE: Sets the position of the solver
		ARGUMENTS: vector3 a_v3Position -> position to set
		OUTPUT: ---
		*/
		void SetPosition(vector3 a_v3Position);
		/*
		USAGE: Gets the position of the solver
		ARGUMENTS: ---
		OUTPUT: position of the solver
		*/
		vector3 GetPosition(void);

		/*
		USAGE: Sets the Size of the solver
		ARGUMENTS: vector3 a_v3Size -> position to set
		OUTPUT: ---
		*/
		void SetSize(vector3 a_v3Size);
		/*
		USAGE: Gets the size of the solver
		ARGUMENTS: ---
		OUTPUT: size of the solver
		*/
		vector3 GetSize(void);

		/*
		USAGE: ---
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void SetLane(bool a_bIsLane);
		/*
		USAGE: ---
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		bool GetLane(void);
		/*
		USAGE: Sets the Size of the solver
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void SetPin(bool a_bIsPin);
		/*
		USAGE: Sets the Size of the solver
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void SetBall(bool a_bIsBall);
		/*
		USAGE: Gets the size of the solver
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		bool GetPin(void);
		/*
		USAGE: Gets the size of the solver
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		bool GetBall(void);

		/*
		USAGE: Sets the velocity of the solver
		ARGUMENTS: vector3 a_v3Velocity -> velocity to set
		OUTPUT: ---
		*/
		void SetVelocity(vector3 a_v3Velocity);
		/*
		USAGE: Gets the velocity of the solver
		ARGUMENTS: ---
		OUTPUT: velocity of the solver
		*/
		vector3 GetVelocity(void);

		/*
		USAGE: Sets the mass of the solver
		ARGUMENTS: float a_fMass -> mass to set
		OUTPUT: ---
		*/
		void SetMass(float a_fMass);
		/*
		USAGE: Gets mass of the solver
		ARGUMENTS: ---
		OUTPUT: mass of the object
		*/
		float GetMass(void);

		/*
		USAGE: Applies friction to the movement
		ARGUMENTS: float a_fFriction = 0.1f -> friction to apply negative friction gets minimized to 0.01f
		OUTPUT: ---
		*/
		void ApplyFriction(float a_fFriction = 0.1f);
		/*
		USAGE: Applies a force to the solver
		ARGUMENTS: vector3 a_v3Force -> Force to apply
		OUTPUT: ---
		*/
		void ApplyForce(vector3 a_v3Force);
		/*
		USAGE: Updates the MySolver
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void Update(void);
		/*
		USAGE: Resolve the collision between two solvers
		ARGUMENTS: MySolver* a_pOther -> other solver to resolve collision with
		OUTPUT: ---
		*/
		void ResolveCollision(MySolver* a_pOther);
	private:
		/*
		Usage: Deallocates member fields
		Arguments: ---
		Output: ---
		*/
		void Release(void);
		/*
		Usage: Allocates member fields
		Arguments: ---
		Output: ---
		*/
		void Init(void);
	};//class

} //namespace Simplex

#endif //__SOLVER_H_

/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/