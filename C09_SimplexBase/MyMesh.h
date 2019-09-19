#pragma once
/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2017/06
----------------------------------------------*/
#ifndef __MyMesh_H_
#define __MyMesh_H_

#include "Simplex\Simplex.h"

namespace Simplex
{

	//System Class
	class MyMesh
	{
		int m_nData = 0; //Number of elements in the list of elements
		std::vector<int> m_lData; //list of elements

	public:
		/*
		Usage: Constructor
		Arguments: ---
		Output: class object instance
		*/
		MyMesh(void);
		/*
		Usage: Copy Constructor
		Arguments: class object to copy
		Output: class object instance
		*/
		MyMesh(MyMesh const& other);
		/*
		Usage: Copy Assignment Operator
		Arguments: class object to copy
		Output: ---
		*/
		MyMesh& operator=(MyMesh const& other);
		/*
		Usage: Destructor
		Arguments: ---
		Output: ---
		*/
		~MyMesh(void);

		/*
		Usage: Changes object contents for other object's
		Arguments: other -> object to swap content from
		Output: ---
		*/
		void Swap(MyMesh& other);

		/*
		Usage: Gets data member
		Arguments: ---
		Output: data
		*/
		int GetData(void);
		/*
		Usage: Sets data member
		Arguments: int a_nData = 1 -> data to set
		Output: ---
		*/
		void SetData(int a_nData = 1);
		/* Property */
		//__declspec(property(get = GetData, put = SetData)) int Data;

		/*
		Usage: adds data on vector
		Arguments: int a_nData -> data to add
		Output: ---
		*/
		void SetDataOnVector(int a_nData);
		/*
		Usage: gets data on vector at the specified entry
		Arguments: int a_nIndex -> entry index
		Output: entry's content
		*/
		int& GetDataOnVector(int a_nIndex);

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

#endif //__MyMesh_H__

/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/