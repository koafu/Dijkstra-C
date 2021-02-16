#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

struct Node
{
    int x, y;
    int score = 999999;
    bool wall = false;
    Node *previous;

    std::vector<Node*> neighbors;

    sf::RectangleShape rect;

    Node() = default;
    Node(int x, int y, int resolution, int margin); 

    void add_neighbors(Node grid[], int cols, int rows);
};

void dijkstra(sf::RenderWindow& window, Node grid[], int cols, int rows, Node* start, Node* end);

void make_path(Node* start, Node* end);

Node* get_min_score(std::vector<Node*> set);

double get_dist(Node* a, Node* b);

void build_grid(Node grid[], int cols, int rows, int resolution, int margin);

void draw_grid(sf::RenderWindow& window, Node grid[], int cols, int rows);

void update_neighbors(Node grid[], int cols, int rows);

void generate_walls(Node grid[], int cols, int rows, sf::Color background);
