/*
 *  COMPILE THIS FILE WITH AT LEAST -std=c++11
 */

#include <iostream> // to use std I/O
#include <stdint.h> // to use int32_t
#include <sys/ioctl.h>	// to get terminal size
#include <chrono> // to figure out how much to wait
#include <thread> // to wait

using namespace std;

int XMax;
int YMax;

void printBall(int X, int Y)
{
	for(int i = 0; i < YMax; ++ i)
	{
		cout << "\033[A"; // puts the cursor on the previous line
	}
	cout << "\r"; // puts the cursor on the first row
	for(int i = 1; i < Y; ++ i)
	{
		cout << "\033[2K" << endl; // deletes the contents of the current line and then steps to the next line
	}
	
	string s = "";
	for(int j = 1; j < X; ++ j) // add X-1 spaces to the beginning of the line, so the Xth can be the ball's position
		s += " ";
	cout << s << "\033[41;31m" << " " << "\033[0m" << endl; // output a space with red on red text and then reset terminal colours to their default value, then step to the next line
	
	for(int i = Y + 1; i < YMax; ++ i)
	{
		cout << "\033[2K" << endl; // delete all lines after the ball so if the ball is currently going up, previous positions won't be seen
	}
}

int main()
{
	// this way we can get the terminal size
	struct winsize termsize;
	ioctl(0, TIOCGWINSZ, &termsize);
	
	XMax = termsize.ws_col;
	YMax = termsize.ws_row;
	
	// scroll down a page
	for(int i = 0; i < YMax; ++ i)
	{
		cout << endl; 
	}
	
	/* 'Cur': current ball position, originally set to starting pos.
	 * 'min', 'max': the points at which to change direction
	 * 'direction': 1 or -1 at the end of operations, 
	 */
	int32_t curX = 5;
	int32_t maxX = XMax - 1;
	int32_t minX = 2;
	int32_t directionX = 1;
	int32_t curY = 2;
	int32_t maxY = YMax - 2; // When this is YMax -1, the terminal window scrolls down at the last line at every hit. Not cool.
	int32_t minY = 2;
	int32_t directionY = -1;
	while(true)
	{
		// This only works on 32 bit numbers which have their most significant bit copied upon >> rather than moved, thus int32_t (because of >>= 31)
		// handle maximum X
		// Yes, this could be done in one assignment like the others, but I like to write comments.
		int32_t substr = maxX - curX;	// positive if we can still go towards maxX, negative if not
		substr &= 0x80000000;			// delete everything except the most significant bit. this results in 10000... (INT_MIN) for negative numbers and 00000... (0) for positives.
		substr >>= 31;					// shift to the right by 31. This results in all 1-s for negative numbers (-1) and all 0-s for positive numbers (0).
		substr |= 0x00000001;			// set the least significant bit to 1. This does nothing to -1-s, but adds one to 0-s. Now originally positive values are 1, and originally negatives are -1.
		directionX *= substr;			// if the value was originally negative (we've gone too far), switch directions.
		directionX *= (((int32_t)((curX - minX) & 0x80000000)) >> 31) | 0x00000001; // handle minimum X
		directionY *= (((int32_t)((maxY - curY) & 0x80000000)) >> 31) | 0x00000001; // handle maximum Y
		directionY *= (((int32_t)((curY - minY) & 0x80000000)) >> 31) | 0x00000001; // handle minimum Y
		
		// set new positions
		curX += directionX;
		curY += directionY;
		
		printBall(curX, curY);
		
		this_thread::sleep_for(chrono::milliseconds(50)); // wait for some time so the user sees something of what just happened
	}
}