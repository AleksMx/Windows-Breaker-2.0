#pragma once

#include <string>

using namespace std;

/*
	This class implements main logic of application
*/

class CBreaker {
public:
	CBreaker();
	~CBreaker();
	bool start (string fileName);
private:
	HANDLE hThread;
};

/*
	Data for breaking thread
*/
struct SBreakInfo {
	string fileName;
};