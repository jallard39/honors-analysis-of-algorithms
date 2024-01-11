// Jordan Allard
// CSCI 264-01
// Homework 5

#include <iostream>

using namespace std;

bool**** visited;

struct Configuration {
	// Using a and b instead of x and y so I don't get confused
	// In this case, a = y and b = x since it goes in a row-column format
	int a1 = 0;
	int b1 = 0;
	int a2 = 0;
	int b2 = 0;
	int depth = 0;
};

// Return if Thing 1 or Thing 2 is outside while the other is still inside
bool IsValidConfig(Configuration config, int a, int b) {
	// Thing 1 outside bounds but Thing 2 is not
	if ((config.a1 < 0 || config.b1 < 0 || config.a1 >= a || config.b1 >= b) &&
		!(config.a2 < 0 || config.b2 < 0 || config.a2 >= a || config.b2 >= b))
		return false;
	// Thing 2 outside bounds but Thing 1 is not
	else if (!(config.a1 < 0 || config.b1 < 0 || config.a1 >= a || config.b1 >= b) &&
		(config.a2 < 0 || config.b2 < 0 || config.a2 >= a || config.b2 >= b))
		return false;
	// Thing 1 and Thing 2 in the same spot
	else if (config.a1 == config.a2 && config.b1 == config.b2)
		return false;
	return true;
}

// Returns true if this configuration has already been checked
bool IsVisited(Configuration config) {
	return visited[config.a1][config.b1][config.a2][config.b2];
}

// Returns true if both Things are outside the bounds of the map
bool IsSolution(Configuration config, int a, int b) {
	if ((config.a1 < 0 || config.b1 < 0 || config.a1 >= a || config.b1 >= b) &&
		(config.a2 < 0 || config.b2 < 0 || config.a2 >= a || config.b2 >= b)) {
		return true;
	}
	else return false;
}

// Updates the a coordinate if the new position is valid
int IncrementPositionA(int a, int b, int increment, bool** map, int boundA) {
	if (a + increment < 0 || a + increment >= boundA)
		a += increment;
	else if (map[a + increment][b])
		a += increment;
	return a;
}

// Updates the b coordinate if the new position is valid
int IncrementPositionB(int a, int b, int increment, bool** map, int boundB) {
	if (b + increment < 0 || b + increment >= boundB)
		b += increment;
	else if (map[a][b + increment])
		 b+= increment;
	return b;
}

// Returns a new configuration with duplicate parameters to the input
Configuration DuplicateConfig(Configuration config) {
	Configuration newConfig;
	newConfig.a1 = config.a1;
	newConfig.a2 = config.a2;
	newConfig.b1 = config.b1;
	newConfig.b2 = config.b2;
	newConfig.depth = config.depth;
	return newConfig;
}

void DoubleTrouble() {
	// Get parameters
	int a, b;
	cin >> a >> b;
	char temp;
	Configuration start;
	start.a1 = 0;
	start.b1 = 0;
	start.a2 = 0;
	start.b2 = 0;
	start.depth = 0;

	// Initialize the visited array
	visited = new bool*** [a];
	for (int w = 0; w < a; w++) {
		visited[w] = new bool** [b];
		for (int x = 0; x < b; x++) {
			visited[w][x] = new bool* [a];
			for (int y = 0; y < a; y++) {
				visited[w][x][y] = new bool[b];
				for (int z = 0; z < b; z++) {
					visited[w][x][y][z] = false;
				}
			}
		}
	}
	
	// Build layout matrix
	bool** map = new bool* [a];
	for (int i = 0; i < a; i++) {
		map[i] = new bool[b];
		for (int j = 0; j < b; j++) {
			cin >> temp;
			switch (temp) {
			case 'x':
				map[i][j] = false;
				break;
			case '.':
				map[i][j] = true;
				break;
			case '1':
				start.a1 = i;
				start.b1 = j;
				map[i][j] = true;
				break;
			case '2':
				start.a2 = i;
				start.b2 = j;
				map[i][j] = true;
				break;
			}
		}
	}

	
	// Prepare for BFS
	Configuration* queue = new Configuration[(a * b) * (a * b)];
	int beg = 0;
	int end = 1;
	queue[beg] = start;
	visited[start.a1][start.b1][start.a2][start.b2] = true;
	Configuration* nextConfigs = new Configuration[4];
	Configuration current, north, south, east, west;
	int solutionDepth = -1;
	
	// BFS
	while (solutionDepth == -1 && beg < end) {
		current = queue[beg];

		// Both things move north
		north = DuplicateConfig(current);
		north.a1 = IncrementPositionA(north.a1, north.b1, -1, map, a);
		north.a2 = IncrementPositionA(north.a2, north.b2, -1, map, a);
		nextConfigs[0] = north;

		// Both things move south
		south = DuplicateConfig(current);
		south.a1 = IncrementPositionA(south.a1, south.b1, 1, map, a);
		south.a2 = IncrementPositionA(south.a2, south.b2, 1, map, a);
		nextConfigs[1] = south;

		// Both things move east
		east = DuplicateConfig(current);
		east.b1 = IncrementPositionB(east.a1, east.b1, 1, map, b);
		east.b2 = IncrementPositionB(east.a2, east.b2, 1, map, b);
		nextConfigs[2] = east;

		// Both things move west
		west = DuplicateConfig(current);
		west.b1 = IncrementPositionB(west.a1, west.b1, -1, map, b);
		west.b2 = IncrementPositionB(west.a2, west.b2, -1, map, b);
		nextConfigs[3] = west;

		for (int i = 0; i < 4; i++) {
			if (IsValidConfig(nextConfigs[i], a, b)) {
				if (IsSolution(nextConfigs[i], a, b)) {
					solutionDepth = current.depth + 1;
					break;
				}
				else if (!IsVisited(nextConfigs[i])) {
					nextConfigs[i].depth = current.depth + 1;
					queue[end] = nextConfigs[i];
					visited[nextConfigs[i].a1][nextConfigs[i].b1][nextConfigs[i].a2][nextConfigs[i].b2] = true;
					end++;
				}
			}
		}
		beg++;
	}
	
	if (solutionDepth == -1) {
		cout << "STUCK" << endl;
	}
	else {
		cout << solutionDepth << endl;
	}

	// Cleanup
	delete[] queue;
	delete[] nextConfigs;
	for (int i = 0; i < a; i++)
		delete[] map[i];
	delete[] map;
	for (int x = 0; x < a; x++) {
		for (int y = 0; y < b; y++) {
			for (int z = 0; z < a; z++) {
				delete[] visited[x][y][z];
			}
			delete[] visited[x][y];
		}
		delete[] visited[x];
	}
	delete[] visited;
}

int main() {
	DoubleTrouble();
}