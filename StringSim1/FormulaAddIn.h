#pragma once

#ifndef FORMULAADDIN_H__
#define FORMULAADDIN_H__

#include <string>

const int nVarType_DOUBLE = 1;
const int nVarType_WCHAR = 2;

//  API definition for Formula functions plug ins
struct FormulaAddInData
{
	int nVarType;  // 1 for double, 2 for wchar_t
	int isNull; // 1 if NULL, 0 if valid

	double dVal; // valid if nVarType==1 && isNull==0
	const wchar_t * pVal; // valid if nVarType==2 && isNull==0

	inline FormulaAddInData()
	{
		memset(this, 0, sizeof(*this)); // Requires <string>
	}
};
#endif