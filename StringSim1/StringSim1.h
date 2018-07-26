#pragma once

#ifdef STRINGSIM1_EXPORTS
#define STRINGSIM1_API __declspec(dllexport)
#else
#define STRINGSIM1_API __declspec(dllimport)
#endif

#ifndef STRINGSIM1_H__
#define STRINGSIM1_H__

#include <string>
#include "FormulaAddIn.h"


// Formula function signature.  The function exposed in the <Dll><EntryPoint> of the
// FormulaAddIn XML MUST have exactly this signature.
// this MUST be thread safe
//
// return 1 for success
//	If 1, place return value in pReturnValue.  If returning a string, it MUST be allocated with
//		GlobalAlloc and will be free'd with GlobalFree
// or 0 for failure.
//	If 0, place a string in the pReturnValue that represents the error message
//		Again, the string MUST be allocated with GlobalAlloc
typedef long(_stdcall * FormulaAddInPlugin)(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue);
#endif