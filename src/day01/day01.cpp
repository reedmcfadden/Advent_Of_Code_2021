/*
 * day01.cpp
 *
 *  Created on: Jul 27, 2022
 *      Author: reed
 */

#include "day01.hpp"

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

int day01challenge01(string inputFile) {
	ifstream depthsFile;
	depthsFile.open(inputFile);
	string prevLine;
	string currLine;
	getline(depthsFile, prevLine);
	int numIncreases = 0;
	while (getline(depthsFile, currLine)) {
		if (stoi(currLine) > stoi(prevLine)) {
			numIncreases++;
		}

		prevLine = currLine;
	}

	return numIncreases;
}

//int day01challenge02(string inputFile) {
//}

int main() {
    cout << "Day 1 Challenge 1: " << day01challenge01("resources/depths.txt") << " depth increases." << endl;
}

