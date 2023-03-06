#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdio>
#include <sstream>
#include <curses.h>
#include <Windows.h>


class Life {
	int w = 0, h = 0;
	std::vector< std::vector<bool> > currentGen;
	std::vector< std::vector<bool> > nextGen;

private:
	int GetCellsAround(int x, int y);
	void CopyGen();
	void FillNext();

public:
	bool isActive = true;

	// Generating map for user's size
	Life(std::size_t width = 8, std::size_t height = 8) : w(width), h(height) {
		srand(time(NULL));

		//initscr();

		for (std::size_t i = 0; i < h; ++i) {
			currentGen.emplace_back();
			for (std::size_t j = 0; j < w; ++j) {
				currentGen.at(i).push_back(rand() % 2);
			}
		}
	}
	// Read map from the file
	Life(const std::string& map);

	// Update condition
	void Tick();

	void CoutGenerate();

	//std::vector< std::vector<bool> > GetCurrentGeneration();
};