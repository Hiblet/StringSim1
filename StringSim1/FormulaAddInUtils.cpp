#include "stdafx.h"
#include "FormulaAddInUtils.h"

void FormulaAddInUtils::DoSetString(FormulaAddInData* pReturnValue, const wchar_t* pString)
{
	size_t nLen = wcslen(pString);
	auto *pStringRet = static_cast<wchar_t *>(GlobalAlloc(GMEM_FIXED, (nLen + 1) * sizeof(wchar_t)));
	wcscpy_s(pStringRet, nLen + 1, pString);
	pReturnValue->pVal = pStringRet;
}

void FormulaAddInUtils::DoResetNull(int nNumArgs, FormulaAddInData* pArgs)
{
	for (int x = 0; x < nNumArgs; x++)
	{
		pArgs[x].isNull = 0;
	}
}

void FormulaAddInUtils::SetString(FormulaAddInData* pReturnValue, const wchar_t *pString)
{
	DoSetString(pReturnValue, pString);
	pReturnValue->nVarType = 2;
}

long FormulaAddInUtils::ReturnError(const wchar_t *pString, FormulaAddInData* pReturnValue, int nNumArgs, FormulaAddInData* pArgs) {
	pReturnValue->isNull = 1;
	DoSetString(pReturnValue, pString);
	DoResetNull(nNumArgs, pArgs);
	return 0;
}

long FormulaAddInUtils::ReturnSuccess(int nNumArgs, FormulaAddInData *pArgs) {
	DoResetNull(nNumArgs, pArgs);
	return 1;
}

void FormulaAddInUtils::CopyValue(const FormulaAddInData *source, FormulaAddInData *target) {
	target->nVarType = source->nVarType;

	if (!source->isNull) {
		target->isNull = 0;
		if (1 == source->nVarType) {
			target->dVal = source->dVal;
		}
		else {
			SetString(target, source->pVal);
		}
	}
	else {
		target->isNull = 1;
	}
}