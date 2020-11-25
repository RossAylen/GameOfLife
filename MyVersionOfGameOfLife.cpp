#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Windows.h>
#include <iostream>

using namespace sf;
using namespace std;

int cellSize = 5;
int boardsizeX = 250 * 1.7;
int boardsizeY = 200;
bool Board[1000][1000] = {};
int Neighbour[1000][1000] = {};

RenderWindow* window;
Event ev;
VideoMode videoMode;

RectangleShape aliveCell;
RectangleShape deadCell;

void initVar();
void initWIndow();
void initCell();
void Game();
void pollEvents();
void drawBoard(int sizeX, int sizeY);
void generateBoard(int sizeX, int sizeY);
void printBoardTerminal(int sizeX, int sizeY);
void updateBoard(int sizeX, int sizeY);
void CheckNeighbour(int sizeX, int sizeY);
void printNeighbourTerminal(int sizeX, int sizeY);
void update();
void render();

int main() {
    Game();
    generateBoard(boardsizeX, boardsizeY);
    while (window->isOpen()) {
        update();
        render();
    }
}

void initVar()
{
    window = nullptr;
}

void initWIndow()
{
    videoMode.height = 1080;
    videoMode.width = 1920;
    window = new RenderWindow(VideoMode(1920, 1080), "Game of Life", Style::Fullscreen);
    window->setFramerateLimit(60);
}

void initCell()
{
    aliveCell.setSize(Vector2f(cellSize, cellSize));
    aliveCell.setFillColor(Color::White);
    deadCell.setSize(Vector2f(cellSize, cellSize));
    deadCell.setFillColor(Color::Black);

}

void Game()
{
    initVar();
    initWIndow();
    initCell();
}

void pollEvents() {
    //Event polling
    while (window->pollEvent(ev)) {
        switch (ev.type) {
        case Event::Closed:
            window->close();
            break;
        case Event::KeyPressed:
            if (ev.key.code == Keyboard::Escape)
                window->close();
            break;
        }
    }
}

void drawBoard(int sizeX, int sizeY) {
    int x = 0;
    int y = 0;
    for (int i = 0; i < (sizeX * sizeY); i++) {
        if (Board[x][y] == true) {
            aliveCell.setPosition(x * cellSize + 1, y * cellSize + 1);
            window->draw(aliveCell);
        }
        else {
            deadCell.setPosition(x * cellSize + 1, y * cellSize + 1);
            window->draw(deadCell);
        }
        x++;
        if (x == sizeX) {
            x = 0;
            y++;
        }
    }
}

//debug functions
void printBoardTerminal(int sizeX, int sizeY) {
    int x = 0;
    int y = 0;
    for (int i = 0; i < (sizeX * sizeY); i++) {
        if (Board[x][y] == true) {
            printf("%c%c", 219, 219);
        }
        else {
            printf("  ");
        }
        x++;
        if (x == sizeX) {
            cout << endl;
            x = 0;
            y++;
        }
    }
}
void printNeighbourTerminal(int sizeX, int sizeY) {
    int x = 0;
    int y = 0;
    for (int i = 0; i < (sizeX * sizeY); i++) {
        printf("%d", Neighbour[x][y]);
        x++;
        if (x == sizeX) {
            cout << endl;
            x = 0;
            y++;
        }
    }
}

void generateBoard(int sizeX, int sizeY) {
    int x = 0;
    int y = 0;
    for (int i = 0; i < (sizeX * sizeY); i++) {
        int random = rand() % 4;
        if (random == 1) {
            Board[x][y] = true;
        }
        x++;
        if (x == sizeX)
        {
            x = 0;
            y++;
        }
    }
}

void updateBoard(int sizeX, int sizeY) {
    int x = 0;
    int y = 0;
    CheckNeighbour(sizeX,sizeY);
    x = 0;
    y = 0;
    for (int i = 0; i < (sizeX * sizeY); i++) {
        if ((Board[x][y] == true) && ((Neighbour[x][y] < 2) || (Neighbour[x][y] > 3))) {
            Board[x][y] = false;
        }
        else {
            if (Neighbour[x][y] == 3) {
                Board[x][y] = true;
            }
        }
        x++;
        if (x == sizeX) {
            x = 0;
            y++;
        }
    }
    x = 0;
    y = 0;
    for (int i = 0; i < (sizeX * sizeY); i++) {
        Neighbour[x][y] = 0;
        x++;
        if (x == sizeX) {
            x = 0;
            y++;
        }
    }
}
//works dont know what that green is about though
void CheckNeighbour(int sizeX, int sizeY) {
    int x = 0;
    int y = 0;
    for (int i = 0; i < (sizeX * sizeY); i++) {
        if (Board[x][y] == true) {
            /*
            for (int w = -1; i < 1; w++) {
                for (int z = -1; z < 1; z++) {
                    if ((0 <= (w + x) <= sizeX) || (0 <= (z + y) <= sizeX)) {
                        if ((w != 0) && (z != 0)) {
                            Neighbour[x + w][y + z] += 1;
                        }
                    }
                }
            }
            */
            Neighbour[x - 1][y - 1] += 1;
            Neighbour[x][y - 1] += 1;
            Neighbour[x + 1][y - 1] += 1;
            Neighbour[x - 1][y] += 1;
            Neighbour[x + 1][y] += 1;
            Neighbour[x - 1][y + 1] += 1;
            Neighbour[x][y + 1] += 1;
            Neighbour[x + 1][y + 1] += 1;
            
        }
        x++;
        if (x == sizeX) {
            x = 0;
            y++;
        }
    }
}

void update()
{
    pollEvents();
    updateBoard(boardsizeX,boardsizeY);
}

void render()
{
    window->clear();
    
    drawBoard(boardsizeX,boardsizeY);
    
    window->display();
}


