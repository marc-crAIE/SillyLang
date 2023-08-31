#pragma once

#include "Objects/SiObject.h"

class SiInterpreter;
class SiError;

class SiThread final
{
public:
	SiThread(SiInterpreter* interp);
	~SiThread() = default;

	inline bool EnterRecursiveCall(const char* where) { return MakeRecursiveCheck() && CheckRecursiveCall(where); }
	inline bool LeaveRecursiveCall() { return m_CppRecursionRemaining++; }

	inline bool MakeRecursiveCheck() { return m_CppRecursionRemaining-- <= 0; }
	bool CheckRecursiveCall(const char* where);

	inline SiInterpreter* GetInterp() const { return m_Interp; }
	inline SiObject* GetException() const { return m_CurrException; }
private:
	// The interpreter this thread is owned by
	SiInterpreter* m_Interp;

	// The exception currently being raised
	SiObject* m_CurrException;

	// Recursion limits
	int m_SiRecursionRemaining;
	int m_SiRecursionLimit;
	int m_CppRecursionRemaining;
	int m_CppRecursionHeadroom = 50;
private:
	friend SiError;
};