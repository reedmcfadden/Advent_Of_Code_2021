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
#include <vector>

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
		cout << "Error: Input file failed to open. Exiting...\n";
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

/*
 * Day 1 Challenge 2
 * calculateDepthIncreases reads in depths from a file and calculates depth
 * increases based on a sliding window of 3 depths.
 *
 * The results are then printed to stdout.
 */
void calculateDepthIncreases() {
	ifstream depthsFile;
	openDepthsFile(depthsFile);
	validateFile(depthsFile);
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
 * Day 2 Challenge 1
 * moveSubmarine reads in movement instructions from a file and keeps track
 * of the submarine's position based on those movements.
 *
 * The resulting position after all instructions contained in the file is then
 * printed to stdout.
 */
void moveSubmarine() {
	ifstream movementsFile;
	movementsFile.open(MOVEMENTS_FILE);
	validateFile(movementsFile);
	int horizontalPosition = 0;
	int depth = 0;
	int aim = 0;
	string direction = "";
	string number = "";
	while (movementsFile >> direction && movementsFile >> number) {
		// TODO could add direction and number validation
		if (direction == "up") {
			aim -= stoi(number);
		} else if (direction == "down") {
			aim += stoi(number);
		} else if (direction == "forward") {
			int unitsForward = stoi(number);
			horizontalPosition += unitsForward;
			depth += unitsForward * aim;
		}
	}
	printf("4. Day 2 Challenge 2\n");
	printf("\tFinal Depth: %d\n", depth);
	printf("\tFinal Horizontal Position: %d\n", horizontalPosition);
	printf("\tDepth * Horizontal = %d\n\n", depth * horizontalPosition);
}

void calculatePowerConsumption() {
	ifstream binaryDiagnosticsFile;
	binaryDiagnosticsFile.open("resources/diagnostics_binary.txt");
	validateFile(binaryDiagnosticsFile);
	string currLine;
	vector<int> onesPerColumn;
	int numBinaries = 0;
	while (getline(binaryDiagnosticsFile, currLine)) {
		++numBinaries;
		size_t strSize = currLine.size();
		for (size_t i = 0; i < strSize; ++i) {
			if (onesPerColumn.size() <= i) {
				onesPerColumn.push_back(0);
			}
			onesPerColumn[i] += currLine[i] - '0';
		}
	}
	string gammaRateString;
	string epsilonRateString;
	for (size_t i = 0; i < onesPerColumn.size(); ++i) {
		gammaRateString += numBinaries - onesPerColumn[i] > 500 ? '0' : '1';
		epsilonRateString += numBinaries - onesPerColumn[i] > 500 ? '1' : '0';
	}
	int gammaRate = stoi(gammaRateString, 0, 2);
	int epsilonRate = stoi(epsilonRateString, 0, 2);
	cout << "5. Day 3 Challenge 1" << endl;
	printf("\tGamme rate in dec (binary): %d (%s)\n", gammaRate,
			gammaRateString.c_str());
	printf("\tEpsilon rate in dec (binary): %d (%s)\n", epsilonRate,
			epsilonRateString.c_str());
	printf("\tTotal energy rate (gamma * epsilon): %d\n\n",
			gammaRate * epsilonRate);
}

/*
 * Returns the integer value of the most or least common binary string. The bool parameter
 * determines if the function will search for most of least common.
 */
int findMostOrLeastCommonBinaryString(vector<string> binaryStrings, bool mostCommon) {
	int sIndex = 0;
	while (binaryStrings.size() > 1) {
		size_t numStrings = binaryStrings.size();
		int numOnes = 0;
		for (size_t i = 0; i < numStrings; ++i) {
			if (binaryStrings[i][sIndex] - '0' == 1) {
				++numOnes;
			}
		}
		int numZeroes = numStrings - numOnes;
		int keepBit;
		if (mostCommon) {
			keepBit = numOnes >= numZeroes ? 1 : 0;
		}
		else {
			keepBit = numOnes >= numZeroes ? 0 : 1;
		}
		vector<string> keepStrings;
		for (auto it = binaryStrings.begin(); it != binaryStrings.end(); ++it) {
			if (binaryStrings.size() == 1) {
				break;
			}
			else if ((*it)[sIndex] - '0' == keepBit) {
				keepStrings.push_back(*it);
			}
			if (it == binaryStrings.end()) {
				break;
			}
		}
		binaryStrings = keepStrings;
		++sIndex;
	}

	return stoi(binaryStrings[0], 0, 2);
}

int findOxygenGeneratorRating(vector<string> binaryStrings) {
	return findMostOrLeastCommonBinaryString(binaryStrings, true);
}

int findCO2ScrubberRating(vector<string> binaryStrings) {
	return findMostOrLeastCommonBinaryString(binaryStrings, false);
}

void calculateLifeSupportRating() {
	ifstream binaryDiagnosticsFile;
	binaryDiagnosticsFile.open("resources/diagnostics_binary.txt");
	validateFile(binaryDiagnosticsFile);
	vector<string> binaryStrings;
	string currLine;
	while (getline(binaryDiagnosticsFile, currLine)) {
		binaryStrings.push_back(currLine);
	}
	int oxygenGeneratorRating = findOxygenGeneratorRating(binaryStrings);
	int co2ScrubberRating = findCO2ScrubberRating(binaryStrings);
	cout << "6. Day 3 Challenge 2" << endl;
	cout << "\tOxygen generator rating: " << oxygenGeneratorRating << endl;
	cout << "\tCO2 scrubber rating: " << co2ScrubberRating << endl;
	cout << "\tLife support rating (oxygen rating * co2 scubber rating): "
			<< oxygenGeneratorRating * co2ScrubberRating << endl;
}

int main() {
	calculateDepthIncreases();
	moveSubmarine();
	calculatePowerConsumption();
	calculateLifeSupportRating();
}


