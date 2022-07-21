/*
 * main.cpp
 *
 * Created on: Jul 21, 2022
 *
 * Author: reed
 */

#include <unistd.h>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>

using std::ifstream;
using std::string;
using std::cout;
using std::endl;
using std::getline;
using std::stoi;
using std::queue;

const int WINDOW_SIZE = 3;

// Open depths input file and check validity
void openDepthsFile(ifstream &depthsFile) {
	depthsFile.open("resources/depths.txt");
}

void validateDepthsFile(ifstream &depthsFile) {
	if (!depthsFile.is_open() || !depthsFile.good()) {
		cout << "Error: Depths input file failed to open. Exiting...";
		printf("Current working dir: %s\n", get_current_dir_name());
	}
}

// return the sum of the first 3 window depths
int initializeFirstWindow(queue<int>& slidingWindow, ifstream &depthsFile, string &currLine) {
	int sum = 0;
	while (slidingWindow.size() < WINDOW_SIZE && getline(depthsFile, currLine)) {
		int newDepth = stoi(currLine);
		slidingWindow.push(newDepth);
		sum += newDepth;
	}
	return sum;
}

void slideWindow(int newDepth, queue<int> &slidingWindow) {
	slidingWindow.pop();
	slidingWindow.push(newDepth);
}

int calculateNewWindowSum(int prevWindowSum, int oldDepth, int newDepth) {
	return prevWindowSum - oldDepth + newDepth;
}

bool increaseDetected(int currWindowSum, int prevWindowSum) {
	return currWindowSum > prevWindowSum;
}

int main() {

	ifstream depthsFile;

	openDepthsFile(depthsFile);
	validateDepthsFile(depthsFile);

	// Vars for depths comparisons
	string currLine;
	int prevWindowSum = 0;
	int currWindowSum = 0;
	queue<int> slidingWindow;

	prevWindowSum = initializeFirstWindow(slidingWindow, depthsFile, currLine);

	// Calculate depth increases
	int numIncreases = 0;
	while (getline(depthsFile, currLine)) {
		int newDepth = stoi(currLine);
		int oldDepth = slidingWindow.front();
		slideWindow(newDepth, slidingWindow);

		currWindowSum = calculateNewWindowSum(prevWindowSum, oldDepth,
				newDepth);

		if (increaseDetected(currWindowSum, prevWindowSum)) {
			++numIncreases;
		}

		prevWindowSum = currWindowSum;
	}

	cout << "The sliding window depth increased " << numIncreases << " times.";
}


