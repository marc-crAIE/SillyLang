#pragma once

enum SiStatusType
{
	STATUS_TYPE_OK = 0,
	STATUS_TYPE_ERROR = 1,
	STATUS_TYPE_EXIT = 2,
};

struct SiStatus
{
public:
	bool IsException() const { return Type != STATUS_TYPE_OK; }
public:
	static SiStatus Ok();
	static SiStatus Error(const char* errorMsg);
	static SiStatus NoMemory();
	static SiStatus Exit(int exitCode = 0);
public:
	SiStatusType Type;
	const char* FuncName;
	const char* ErrorMsg;
	int ExitCode;
};