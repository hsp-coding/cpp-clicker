//============================================================================
// Name        : MouseClicker.cpp
// Author      : 
// Version     :
// Copyright   : GOOOO
// Description : Playing with VisualStudio
//============================================================================

#include <iostream>
#include "windows.h"
#include <thread>
#include <chrono>

using namespace std;

const int MAXCLICK = 500;
const int CLICKPAUSE = 100; //Pause between Clicks in ms
const int CLICKDURATION = 50; //How long should the button be pressed in ms
const int CLICKDURATIONDEVIATION = 5; //Deviation around the mean click duration in ms
const int POSITIONDEVIATION = 10; //Deviation around the mean click duration in ms

int percCount = 1;//counts the percentile (10%, 20%,...)
unsigned __int64 start;
void LeftClick(const int x, const int y)
{
	POINT pos;
	GetCursorPos(&pos);		
	SetCursorPos(x, y);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 100, 200, 0, 0);
	//std::this_thread::sleep_for(chrono::milliseconds(CLICKDURATION));
	Sleep(CLICKDURATION - (CLICKDURATIONDEVIATION /2) + rand() % CLICKDURATIONDEVIATION );//in millisec
	mouse_event(MOUSEEVENTF_LEFTUP, 100, 200, 0, 0);
	SetCursorPos(pos.x, pos.y);
}

void infoOutput(const int x, const unsigned __int64 startTime) {
	if (x >= MAXCLICK * percCount / 10) {
		unsigned __int64 now = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
		unsigned __int64 elapsed = now - start;
		unsigned __int64 maxDuration = (elapsed * 10) / percCount;
		unsigned __int64 remaining = maxDuration - elapsed;
		cout << percCount << "0% der Clicks erreicht, " << remaining/1000 << "seconds remaining" << endl;
		percCount++;
	}

}

void RandomizeMousePosition(int* x, int* y) {
	*x = *x - POSITIONDEVIATION/2 + rand() % POSITIONDEVIATION;
	*y = *y - POSITIONDEVIATION/2 + rand() % POSITIONDEVIATION;
	//cout << "Randomized Position: x= "<<*x <<" y= "<< *y <<endl;
}

int main() {
	POINT pos;
	//config_lc conf = new config_lc();
	cout << "5 Seconds to Click!" << endl;
	Sleep(5000);//warte vor der ersten Messung
	GetCursorPos(&pos);
	int x = (int)pos.x;
	int y = (int)pos.y;
	int i = 1;
	start = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();

	cout << "Initial Position: Pos.x= " << x << "Pos.y= " << y << endl;
	while (i <= MAXCLICK) {
		GetCursorPos(&pos);
		x = (int)pos.x;
		y = (int)pos.y;
		// cout << i<<".Position: Pos.x= "<<x <<"Pos.y= "<< y <<endl;
		RandomizeMousePosition(&x, &y);
		LeftClick(x, y);
		Sleep(CLICKPAUSE);
		i++;
		infoOutput(i, start);
	}
	cout << "Finished";
	return 0;
}

