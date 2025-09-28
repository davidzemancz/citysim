#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <iostream>
#include <vector>
using namespace std;

const int MAP_WIDTH = 20;
const int MAP_HEIGHT = 20;
const int CELL_SIZE = 25; // Size of each cell in pixels

enum MapPointType {
    EMPTY,
    ROAD,
    INTERSECTION
};

enum Direction {
    NONE,
    NORTH,
    EAST,
    SOUTH,
    WEST,
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

class MapWidget : public QWidget {
    Q_OBJECT

private:
    vector<vector<MapPoint>> map;

public:
    MapWidget(QWidget *parent = nullptr) : QWidget(parent) {
        setFixedSize(MAP_WIDTH * CELL_SIZE, MAP_HEIGHT * CELL_SIZE);
        setWindowTitle("City Simulation");
        
        // Initialize the map
        map = createEmptyMap();
        createRoads(map);
        
        cout << "Map created with Qt window!" << endl;
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                QRect rect(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE);
                
                // Set colors based on map point type
                if (map[x][y].type == EMPTY) {
                    painter.fillRect(rect, QColor(34, 139, 34)); // Forest green for empty
                } else if (map[x][y].type == ROAD) {
                    painter.fillRect(rect, QColor(64, 64, 64)); // Dark gray for roads
                    
                    // Draw direction arrows
                    painter.setPen(QPen(Qt::white, 2));
                    QPoint center = rect.center();
                    
                    switch (map[x][y].direction) {
                        case NORTH:
                            painter.drawLine(center, center + QPoint(0, -8));
                            painter.drawLine(center + QPoint(0, -8), center + QPoint(-3, -5));
                            painter.drawLine(center + QPoint(0, -8), center + QPoint(3, -5));
                            break;
                        case EAST:
                            painter.drawLine(center, center + QPoint(8, 0));
                            painter.drawLine(center + QPoint(8, 0), center + QPoint(5, -3));
                            painter.drawLine(center + QPoint(8, 0), center + QPoint(5, 3));
                            break;
                        case SOUTH:
                            painter.drawLine(center, center + QPoint(0, 8));
                            painter.drawLine(center + QPoint(0, 8), center + QPoint(-3, 5));
                            painter.drawLine(center + QPoint(0, 8), center + QPoint(3, 5));
                            break;
                        case WEST:
                            painter.drawLine(center, center + QPoint(-8, 0));
                            painter.drawLine(center + QPoint(-8, 0), center + QPoint(-5, -3));
                            painter.drawLine(center + QPoint(-8, 0), center + QPoint(-5, 3));
                            break;
                        default:
                            break;
                    }
                } else if (map[x][y].type == INTERSECTION) {
                    painter.fillRect(rect, QColor(128, 128, 128)); // Light gray for intersections
                    
                    // Draw intersection symbol
                    painter.setPen(QPen(Qt::white, 3));
                    QPoint center = rect.center();
                    painter.drawLine(center + QPoint(-8, 0), center + QPoint(8, 0));
                    painter.drawLine(center + QPoint(0, -8), center + QPoint(0, 8));
                }
                
                // Draw grid lines
                painter.setPen(QPen(Qt::black, 1));
                painter.drawRect(rect);
            }
        }
    }

private:
    vector<vector<MapPoint>> createEmptyMap();
    void createRoads(vector<vector<MapPoint>>& map);
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    QMainWindow window;
    MapWidget *mapWidget = new MapWidget();
    window.setCentralWidget(mapWidget);
    window.setWindowTitle("City Simulation");
    window.show();
    
    cout << "Qt City Simulation started!" << endl;
    
    return app.exec();
}

vector<vector<MapPoint>> MapWidget::createEmptyMap() {
    vector<vector<MapPoint>> map(MAP_WIDTH, vector<MapPoint>(MAP_HEIGHT));

    for (int x = 0; x < MAP_WIDTH; x++) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            map[x][y] = MapPoint(x, y, EMPTY, NONE);
        }
    }
    return map;
}

void MapWidget::createRoads(vector<vector<MapPoint>>& map) {
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
            map[MAP_WIDTH / 2][y].type = INTERSECTION;
            map[MAP_WIDTH / 2][y].direction = NONE;
        } else{
            map[MAP_WIDTH / 2][y].type = ROAD;
            map[MAP_WIDTH / 2][y].direction = NORTH;
        }

        if (map[MAP_WIDTH / 2 + 1][y].type == ROAD) {
            map[MAP_WIDTH / 2 + 1][y].type = INTERSECTION;
             map[MAP_WIDTH / 2 + 1][y].direction = NONE;
        } else{
            map[MAP_WIDTH / 2 + 1][y].type = ROAD;
            map[MAP_WIDTH / 2 + 1][y].direction = SOUTH;
        }
    }
}

// Include the MOC file for Qt's meta-object system
#include "main.moc"



