#pragma once

class SiInterpreter;

class SiThread final
{
public:
	SiThread(SiInterpreter* interp);
	~SiThread() = default;

	inline SiInterpreter* GetInterp() const { return m_Interp; }
private:
	// The interpreter this thread is owned by
	SiInterpreter* m_Interp;
};