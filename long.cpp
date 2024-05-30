#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int BAR_WIDTH = 5;
const int NUM_BARS = WINDOW_WIDTH / BAR_WIDTH;

void gennum(vector<int>& arr, int size) {
    for(int i = 0; i < size; i++) arr[i] = rand() % WINDOW_HEIGHT;
}

void drawBars(sf::RenderWindow& window, const vector<int>& arr) {
    window.clear();
    for(int i = 0; i < arr.size(); i++) {
        sf::RectangleShape bar(sf::Vector2f(BAR_WIDTH - 1, arr[i]));
        bar.setPosition(i * BAR_WIDTH, WINDOW_HEIGHT - arr[i]);
        bar.setFillColor(sf::Color::Green);
        window.draw(bar);
    }
    window.display();
}

void bubbleSort(sf::RenderWindow& window, vector<int>& arr) {
    for(int i = 0; i < arr.size(); i++) {
        for(int j = 0; j < arr.size() - 1; j++) {
            if(arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                drawBars(window, arr);
            }
        }
    }
}

int main() {
    srand(time(0));
    
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Sorting Visualization");

    vector<int> arr(NUM_BARS);
    gennum(arr, NUM_BARS);

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }

        drawBars(window, arr);
        bubbleSort(window, arr);
        break;  // Run the sort only once
    }

    return 0;
}
