#include "dijkstra.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <cmath>
#include <SFML/Graphics.hpp>

void dijkstra(sf::RenderWindow& window, Node grid[], int cols, int rows, Node* start, Node* end)
{
    bool path_found = false;
    bool terminate = false;
    start->score = 0;

    std::vector<Node*> open_set;
    open_set.push_back(start);
    std::vector<Node*> closed_set;

    while(!open_set.empty())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    terminate = true;
                    break;
            }
        }

        if(terminate) {
            break;
        }

        Node* current = get_min_score(open_set);
        if(current == end) {
            std::cout << "path found, successful\n";
            path_found = true;
            make_path(start, end);
            break;
        }

        auto it = std::find(std::begin(open_set), std::end(open_set), current);
        int current_index = it - open_set.begin();
        open_set.erase(open_set.begin() + current_index);
        closed_set.push_back(current);
        current->rect.setFillColor(sf::Color(173,69,69));

        for(auto& neighbor: current->neighbors)
        {
            if(!std::count(closed_set.begin(), closed_set.end(), neighbor))
            {
                double alt = current->score + get_dist(current, neighbor);
                if(alt < neighbor->score)
                {
                    neighbor->score = alt;
                    neighbor->previous = current;
                }
                if(!std::count(open_set.begin(), open_set.end(), neighbor))
                {
                    open_set.push_back(neighbor);
                    neighbor->rect.setFillColor(sf::Color(50,168,115));
                }
            }
        }
        window.clear(sf::Color(40,40,40));
        draw_grid(window, grid, cols, rows);
        window.display();
    }
    if(!path_found)
    {
        std::cout << "no path found, unsuccessful\n";
    }
}

void make_path(Node* start, Node* end)
{
    Node* node = end;
    while(node->previous)
    {
        node->rect.setFillColor(sf::Color(82,153,186));
        node = node->previous;
    }
    start->rect.setFillColor(sf::Color(82,153,186));
}

Node* get_min_score(std::vector<Node*> set)
{
    int min_score = 999999;
    Node* current;
    for(auto& node: set)
    {
       if(node->score < min_score)
       {
           min_score = node->score;
           current = node;
       }
    }
    return current; 
}

double get_dist(Node* a, Node* b)
{
    double dstX = pow(std::abs(a->x - b->x), 2);
    double dstY = pow(std::abs(a->y - b->y), 2);
    return std::sqrt(dstX + dstY);
}

void build_grid(Node grid[], int cols, int rows, int resolution, int margin)
{
    for(int x = 0; x < cols; x++)
    {
        for(int y = 0; y < rows; y++)
        {
            grid[cols * y + x] = Node(x, y, resolution, margin);
        }
    }
}

void draw_grid(sf::RenderWindow& window, Node grid[], int cols, int rows)
{
    for(int x = 0; x < cols; x++)
    {
        for(int y = 0; y < rows; y++)
        {
            if(grid[cols * y + x].wall) {
                continue;
            }
            window.draw(grid[cols * y + x].rect);
        }
    }
}

void update_neighbors(Node grid[], int cols, int rows)
{
    for(int x = 0; x < cols; x++)
    {
        for(int y = 0; y < rows; y++)
        {
            grid[cols * y + x].add_neighbors(grid, cols, rows);
        }
    }
}

void generate_walls(Node grid[], int cols, int rows, sf::Color background)
{
    for(int x = 0; x < cols; x++)
    {
        for(int y = 0; y < rows; y++)
        {
            if(((double) rand() / (RAND_MAX)) < 0.3)
            {
                grid[cols * y + x].wall = true;
            }
        }
    }
}

void Node::add_neighbors(Node grid[], int cols, int rows)
{
    if(y-1 >= 0 && (cols * (y-1) + x) >= 0) {
        if(!grid[cols * (y-1) + x].wall) {
            neighbors.push_back(&grid[cols * (y-1) + x]);
        }
    } 
    if(y+1 < rows && (cols * (y+1) + x) <= cols*rows) {
        if(!grid[cols * (y+1) + x].wall) {
            neighbors.push_back(&grid[cols * (y+1) + x]);
        }
    }

    if(x-1 >= 0 && (cols * y + (x-1)) >= 0) {
        if(!grid[cols * y + (x-1)].wall) {
            neighbors.push_back(&grid[cols * y + (x-1)]);
        }
    } 
    if(x+1 < cols && (cols * y + (x+1)) <= cols*rows) {
        if(!grid[cols * y + (x+1)].wall) {
            neighbors.push_back(&grid[cols * y + (x+1)]);
        }
    }
}

Node::Node(int x, int y, int resolution, int margin)
    : x(x), y(y) 
{
    rect.setSize(sf::Vector2f(resolution - margin, resolution - margin));
    rect.setPosition(x * resolution, y * resolution);
    rect.setFillColor(sf::Color(255,255,255,255));
}
