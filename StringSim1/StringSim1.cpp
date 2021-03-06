// StringSim1.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "StringSim1.h"
#include "FormulaAddInUtils.h"
#include <string>
#include <numeric>
#include <algorithm>



// The Levenshtein Distance function:
// Ref: https://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Levenshtein_distance#C++
size_t levenshtein_distance(const std::wstring &s1, const std::wstring &s2)
{
	// To change the type this function manipulates and returns, change
	// the return type and the types of the two variables below.
	size_t s1len = s1.size();
	size_t s2len = s2.size();

	auto column_start = (decltype(s1len))1;

	auto column = new decltype(s1len)[s1len + 1];
	std::iota(column + column_start - 1, column + s1len + 1, column_start - 1);

	for (auto x = column_start; x <= s2len; x++) {
		column[0] = x;
		auto last_diagonal = x - column_start;
		for (auto y = column_start; y <= s1len; y++) {
			auto old_diagonal = column[y];
			auto possibilities = {
				column[y] + 1,
				column[y - 1] + 1,
				last_diagonal + (s1[y - 1] == s2[x - 1] ? 0 : 1)
			};
			column[y] = (std::min)(possibilities); // SH; brackets added around std::min to stop it being resolved as a macro
			last_diagonal = old_diagonal;
		}
	}
	auto result = column[s1len];
	delete[] column;
	return result;
}

// The exposed function
extern "C" long STRINGSIM1_API _stdcall LevenshteinDistance(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue)
{
	pReturnValue->nVarType = nVarType_WCHAR;

	// Check Input Parameters
	if (nNumArgs != 2 ||
		pArgs[0].nVarType != nVarType_WCHAR ||
		pArgs[1].nVarType != nVarType_WCHAR) {
		return FormulaAddInUtils::ReturnError(L"Syntax: Function(String, String)", pReturnValue, nNumArgs, pArgs);
	}

	// Handle Nulls; Only create strings if input is not null, and pointer is indeed not null...
	std::wstring s1 = (pArgs[0].isNull == 0 && pArgs[0].pVal != 0) ? std::wstring(pArgs[0].pVal) : L"";
	std::wstring s2 = (pArgs[1].isNull == 0 && pArgs[1].pVal != 0) ? std::wstring(pArgs[1].pVal) : L"";

	// Do the thing
	size_t ldResult = levenshtein_distance(s1, s2);

	// Prepare a value to return
	pReturnValue->nVarType = nVarType_DOUBLE;
	pReturnValue->isNull = 0;
	pReturnValue->dVal = (double)ldResult;

	return FormulaAddInUtils::ReturnSuccess(nNumArgs, pArgs);
}

