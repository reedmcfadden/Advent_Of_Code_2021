/*
 * main.cpp
 *
 * Created on: Jul 21, 2022
 *
 * Author: reed
 */

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <stdio.h>

using std::ifstream;
using std::string;
using std::cout;
using std::endl;
using std::getline;
using std::stoi;

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

void initializePrevDepth(ifstream &depthsFile, string &prevLine, int &prevDepth) {
	getline(depthsFile, prevLine);
	prevDepth = stoi(prevLine);
}

int main() {

	ifstream depthsFile;

	openDepthsFile(depthsFile);
	validateDepthsFile(depthsFile);

	// Vars for depths comparisons
	string prevLine;
	string currLine;
	int prevDepth;
	int currDepth;

	initializePrevDepth(depthsFile, prevLine, prevDepth);

	// Calculate depth increases
	int numIncreases = 0;
	while (getline(depthsFile, currLine)) {

		currDepth = stoi(currLine);

		if (currDepth > prevDepth) {
			numIncreases++;
		}

		prevDepth = currDepth;
	}

	cout << "The depth increased " << numIncreases << " times.";
}


