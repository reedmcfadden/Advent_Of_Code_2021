/*
 * main.cpp
 *
 * Created on: Jul 21, 2022
 *
 * Author: reed
 */

// TODO could add throwing errors rather than primitive print statement errors that
// don't stop execution

#include <unistd.h>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <cstring>

using namespace std;

const int WINDOW_SIZE = 3;
const string DEPTHS_FILE = "resources/depths.txt";
const string MOVEMENTS_FILE = "resources/movements.txt";

// Open depths input file and check validity
void openDepthsFile(ifstream &depthsFile) {
	depthsFile.open(DEPTHS_FILE);
}

void validateFile(ifstream &inFile) {
	if (!inFile.is_open() || !inFile.good()) {
		cout << "Error: Input file failed to open. Exiting...";
		printf("Current working directory: %s\n", get_current_dir_name());
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

void day1Challenge2() {
	ifstream depthsFile;
	openDepthsFile(depthsFile);
	validateFile(depthsFile);
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

	printf("2. Day 1 Challenge 2\n");
	printf("\t%d depth increases detected with a size 3 sliding window\n\n", numIncreases);

	depthsFile.close();
}

/**
 * Given the movements from resouces/movements.txt, this function calculates
 * the final depth and horizontal position. The product of those is then
 * determined, resulting in the rectangular total area of water between the
 * starting point of 0,0 and the final position of X,X.
 */
void day2Challenge1() {
	ifstream movementsFile;
	movementsFile.open(MOVEMENTS_FILE);
	validateFile(movementsFile);
	int horizontalPosition = 0;
	int depth = 0;
	string direction = "";
	string number = "";
	while (movementsFile >> direction && movementsFile >> number) {
		// TODO could add direction and number validation
		if (direction == "up") {
			depth -= stoi(number);
		} else if (direction == "down") {
			depth += stoi(number);
		} else if (direction == "forward") {
			horizontalPosition += stoi(number);
		}
	}
	printf("3. Day 2 Challenge 1\n");
	printf("\tDepth: %d and Horizontal: %d is the final position.\n", depth,
			horizontalPosition);
	printf("\tDepth * Horizontal = %d\n\n", depth * horizontalPosition);
}

int main() {
	// todo restore day1Challenge1 from previous git commit
	day1Challenge2();
	day2Challenge1();

	// day 2 challenge 2

}


