#include <SFML/Graphics.hpp>
#include "dijkstra.h"

int main() 
{
    int WIDTH = 1280;
    int HEIGHT = 720;

    int resolution = 10;
    int cols = WIDTH / resolution;
    int rows = HEIGHT / resolution;
    int margin = 1;

    sf::Color background(40,40,40);

    Node* grid = new Node[cols * rows];
    build_grid(grid, cols, rows, resolution, margin);
    generate_walls(grid, cols, rows, background);
    update_neighbors(grid, cols, rows);

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Dijkstra", sf::Style::Titlebar | sf::Style::Close);
    sf::Event event; 

    bool finished = false;
    Node* start = &grid[0];
    Node* end = &grid[cols * (rows - 1) + (cols - 1)];

    while (window.isOpen()) 
    {
        while (window.pollEvent(event)) 
        {
            switch (event.type) 
            {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }
        window.clear(background);

        if(!finished) {
            dijkstra(window, grid, cols, rows, start, end);
            finished = true;
        }

        draw_grid(window, grid, cols, rows);

        window.display();
    }
    delete[] grid;
    return 0;
}
