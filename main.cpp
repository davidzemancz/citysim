#include <iostream>
#include <vector>
using namespace std;

// clang++ -o main main.cpp && ./main

const int MAP_WIDTH = 20;
const int MAP_HEIGHT = 20;

enum MapPointType {
    EMPTY,
    ROAD,
};

enum Direction {
    NONE,
    NORTH,
    EAST,
    SOUTH,
    WEST,
    INTERSECTION
};

class MapPoint{
    public:
        int x;
        int y;
        MapPointType type;
        Direction direction;
        MapPoint() : x(0), y(0), type(EMPTY), direction(NORTH) {}
        MapPoint(int x, int y, MapPointType type, Direction direction) : x(x), y(y), type(type), direction(direction) {}
};

vector<vector<MapPoint>> createEmptyMap();
void createRoads(vector<vector<MapPoint>>& map);
void printMap(const vector<vector<MapPoint>>& map);

int main() {
    cout << "Creating map..." << endl;
    auto map = createEmptyMap();
    cout << "Map created successfully!" << endl;
    cout << "Map size: " << MAP_WIDTH << "x" << MAP_HEIGHT << endl;
    cout << "Adding roads..." << endl;
    createRoads(map);
    cout << "Roads added." << endl;
    printMap(map);
    return 0;
}

vector<vector<MapPoint>> createEmptyMap() {
    vector<vector<MapPoint>> map(MAP_WIDTH, vector<MapPoint>(MAP_HEIGHT));

    for (int x = 0; x < MAP_WIDTH; x++) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            map[x][y] = MapPoint(x, y, EMPTY, NONE);
        }
    }
    return map;
}

void createRoads(vector<vector<MapPoint>>& map) {
    // Create a horizontal road in the middle of the map
    for (int x = 0; x < MAP_WIDTH; x++) {
        map[x][MAP_HEIGHT / 2].type = ROAD;
        map[x][MAP_HEIGHT / 2].direction = EAST;

        map[x][MAP_HEIGHT / 2 + 1].type = ROAD;
        map[x][MAP_HEIGHT / 2 + 1].direction = WEST;
    }

    // Create a vertical road in the middle of the map
    for (int y = 0; y < MAP_HEIGHT; y++) {
        if (map[MAP_WIDTH / 2][y].type == ROAD) {
             map[MAP_WIDTH / 2][y].direction = INTERSECTION;
        } else{
            map[MAP_WIDTH / 2][y].type = ROAD;
            map[MAP_WIDTH / 2][y].direction = NORTH;
        }

        if (map[MAP_WIDTH / 2 + 1][y].type == ROAD) {
             map[MAP_WIDTH / 2 + 1][y].direction = INTERSECTION;
        } else{
            map[MAP_WIDTH / 2 + 1][y].type = ROAD;
            map[MAP_WIDTH / 2 + 1][y].direction = SOUTH;
        }
    }
}

void printMap(const vector<vector<MapPoint>>& map) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            string symbol = ".";
            if (map[x][y].type == ROAD) {
                if (map[x][y].direction == NORTH) {
                    symbol = "↑"; // Vertical road
                } else if (map[x][y].direction == EAST) {
                    symbol = "→"; // Horizontal road
                } else if (map[x][y].direction == SOUTH) {
                    symbol = "↓"; // Vertical road
                } else if (map[x][y].direction == WEST) {
                    symbol = "←"; // Horizontal road
                } else if (map[x][y].direction == INTERSECTION) {
                    symbol = "┼"; // Intersection
                }
            }
            cout << symbol;
        }
        cout << endl;
    }
}



