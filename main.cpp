#include "include/raylib.h"
#include <cmath>
#include <iostream>

struct {
	double mass = 1000.0;
	double gravitationalAcceleration = 0.1;
	double gravitationalForce = mass * gravitationalAcceleration;
	double coefficient = 1;

	double Fx = 0.0, Fy = 0.0;
	double Ax = 0.0, Ay = 0.0;
	double Vx = 0.0, Vy = 0.0;
} circle;


int main(void) {
	InitWindow(0, 0, "Window");
	SetTargetFPS(60);

	int display = GetCurrentMonitor();
	int width = GetMonitorWidth(display);
	int height = GetMonitorHeight(display);

	Vector2 circlePosition = {30, height - 30};
	Vector2 mousePosition;

	bool start = false;
	bool start2 = false;



	while(!WindowShouldClose()) {
		mousePosition = GetMousePosition();


		if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			start = true;
			circle.Fx = (mousePosition.x - circlePosition.x);
			circle.Fy =  (mousePosition.y - circlePosition.y);


			circle.Ax = (circle.Fx / circle.mass);
			circle.Ay = (circle.Fy / circle.mass);
		}
		else {
			start = false;
			circle.Ax = 0;
			circle.Ay = 0;
		}
		
		ClearBackground(BLACK);

		BeginDrawing();
			
			if(start) {
				DrawLine(circlePosition.x, circlePosition.y, mousePosition.x, mousePosition.y, WHITE);
			}

			circle.Vx +=  circle.Ax;
			circle.Vy +=  circle.Ay + circle.gravitationalAcceleration;
			if(circle.Vy <= -1 * circle.gravitationalAcceleration) circle.Vy += circle.gravitationalAcceleration;


			circlePosition.x += circle.Vx;
			circlePosition.y += circle.Vy;

			if(circlePosition.y >= height - 30) {
				double AFf = circle.gravitationalForce * circle.coefficient / circle.mass;
				if(circle.Vx > 0 and AFf >= circle.Vx) {
					circle.Vx = 0;
				}
				if(circle.Vx > 0 and AFf < circle.Vx) {
					circle.Vx -= AFf;
				}
				if(circle.Vx < 0 and AFf >= abs(circle.Vx)) {
					circle.Vx = 0;
				}
				if(circle.Vx < 0 and AFf < abs(circle.Vx)) {
					circle.Vx += AFf;
				}

				circle.Vy *= -1;
				circlePosition.y = height - 30;
			}
			if(circlePosition.y < 30) {
				circle.Vy *= -1;
				circlePosition.y = 30;
			}
			if(circlePosition.x < 30) {
				circle.Vx *= -1;
				circlePosition.x = 30;
			}
			if(circlePosition.x >= width - 30) {
				circle.Vx *= -1;
				circlePosition.x = width - 30;
			}
			

			DrawCircle(circlePosition.x, circlePosition.y, 30, RED);
			
		EndDrawing();


	}

	CloseWindow();


	return 0;
}
