#include "Life.h"

// Read map from the file
// Very error-prone, not safe!
Life::Life(const std::string& map) {
	std::ifstream file(map);

	if(!file.is_open()) {
		std::cout << "error" << std::endl;
		return;
	}

	std::string line;
	std::size_t count = 0;
	while(std::getline(file, line)) {
		currentGen.emplace_back();
		h++;
		std::stringstream values(line);
		while (std::getline(values, line, ' ')) {
			bool b;
			std::istringstream(line) >> b;
			currentGen[count].push_back(b);
		}
		count++;
	}

	w = currentGen[0].size();
}

int Life::GetCellsAround(int x, int y) {
	std::size_t CellCount = 0;

	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			if (i == 0 && j == 0) continue;

			int localX = x + i;
			int localY = y + j;

			if(localX >= 0 && localX < h && localY >= 0 && localY < w) {
				if(currentGen[localX][localY]) {
					CellCount++;
				}
			}
		}
	}

	return CellCount;
}

void Life::Tick() {
	nextGen = currentGen;

	for (std::size_t i = 0; i < h; ++i) {
		for (std::size_t j = 0; j < w; ++j) {

			int cellsAround = GetCellsAround(i, j);

			if(currentGen[i][j]) {
				if(cellsAround == 3 || cellsAround == 2) {
					continue;
				}else {
					nextGen[i][j]= 0;
				}

			}else { // Dead
				if(cellsAround == 3) {
					nextGen[i][j] = 1;
				}

			}
		}
	}

	currentGen = nextGen;
}

void Life::CopyGen() {
	for (std::size_t i = 0; i < w; ++i) {
		for (std::size_t j = 0; j < h; ++j) {
			nextGen[i][j] = currentGen[i][j];
		}
	}
}

void Life::FillNext() {
	for (std::size_t i = 0; i < w; ++i) {
		nextGen.emplace_back();
		for (std::size_t j = 0; j < h; ++j) {
			nextGen[i].push_back(false);
		}
	}
}


// Debug function
void Life::CoutGenerate() {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	int home = 0;
	for (auto it = currentGen.begin(); it != currentGen.end(); ++it) {
		for (auto jt = it->begin(); jt != it->end(); ++jt) {
			std::string out = "";
			if(*jt) {
				out += "X";
			}else {
				out += " ";
			}
			//std::cout << out;
			printw(out.c_str());
		}
		home++;
		move(home, 0);
		/*COORD pos = {0, 0};
		pos.Y = home;
		SetConsoleCursorPosition(console, pos);*/
	}
}