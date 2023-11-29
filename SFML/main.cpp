#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <thread>

const int HEIGHT = 500;
const int WIDTH = HEIGHT * (16.0 / 9);

struct Point
{
	int x;
	int y;
	int z;
};

struct Pixel
{
	int x;
	int y;
};

std::vector<Point> createCube(const Point& c ,const int& cubeLength) {
	std::vector<Point> cube;

	int half = cubeLength / 2;

	//Position of cube
	// Front face
	cube.push_back({ - half, - half, - half });		// left, up, front
	cube.push_back({ + half, - half, - half });		// right, up, front
	cube.push_back({ - half, + half, - half });		// left, down, front
	cube.push_back({ + half, + half, - half });		// right, down, front

	// Secondary points
	cube.push_back({ - half, - half, + half });		// left, up, back
	cube.push_back({ + half, - half, + half });		// right, up, back
	cube.push_back({ - half, + half, + half });		// left, down, back
	cube.push_back({ + half, + half, + half });		// right, down, back

	return cube;
}

std::vector<Pixel> calculateCube(const Point& center,const std::vector<Point>& cube, const int& inAngle, const int& distance) {
	float PI = 3.141592;
	float uholRad = inAngle / 180.0 * PI;
	//float uholRad = 0.5 * PI;

	std::vector<Pixel> points;
	for (const auto& p : cube)
	{
		const float d = sqrt(pow(static_cast<float>(p.x), 2) + pow(static_cast<float>(p.z), 2.)); //prepona

		Pixel pixel = {p.x, p.y};

		float wholeAngle = atan2f(p.z, p.x) + uholRad;

		pixel.x = sinf(wholeAngle) * d;

		float k = distance / (static_cast<float>(distance) - cosf(wholeAngle) * d);

		points.push_back(Pixel{
			static_cast<int>(pixel.x * k),
			static_cast<int>(pixel.y * k)
			});
	}

	return points;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Rotating CUBE!");

	int cubeLength = 200;
	int distance = 400; // vzdialenost kamery od centra kocky

	const Point center = { WIDTH/2, HEIGHT/2, 0}; // constant center point

	std::vector<Point> cube = createCube(center, cubeLength);

	int angle = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

		if (angle == 360) {
			angle = 0;
			//distance -= 10;
		}

		std::vector<Pixel> points = calculateCube(center, cube, angle, distance);

		for (const auto& p : points) {
			sf::RectangleShape vrchol(sf::Vector2f(1, 1));
			vrchol.setPosition(center.x + p.x,center.y + p.y);
			vrchol.setFillColor(sf::Color(255, 0, 0, 255));
			window.draw(vrchol);

			for (const auto& l : points) {
				sf::VertexArray line(sf::Lines, 2);
				line[0] = sf::Vector2f(center.x + p.x, center.y + p.y);
				line[1] = sf::Vector2f(center.x + l.x, center.y + l.y);

				line[0].color = sf::Color::White;
				//line[1].color = sf::Color::Blue;

				window.draw(line);
			}
		}

		sf::RectangleShape stred(sf::Vector2f(5, 5));
		stred.setPosition(center.x, center.y);
		stred.setFillColor(sf::Color(0, 255, 0, 255));
		window.draw(stred);



		angle++;

		window.display();
		
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

	return 0;
}