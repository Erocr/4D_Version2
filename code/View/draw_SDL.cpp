#include <View/draw_SDL.hpp>
#include <iostream>

View::View() {
	_exit = false;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
    }
    width = 800;
    height = 600;
    if (SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_SHOWN, &window, &renderer) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        SDL_Quit();
    }
    clear();
}

void View::clear(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

float View::get_aspect_ratio() {
    return (1. * height) / width;
}


void View::draw_2d_triangles(vector<vector<Vec2d>> &triangles) {
	clear();
	for (vector<Vec2d>& triangle : triangles) {
		drawTriangle(toCoord(triangle[0]), toCoord(triangle[1]), toCoord(triangle[2]));
	}
	SDL_RenderPresent(renderer);
}

Vec2d View::toCoord(Vec2d v) {
	return { (v.x+1) * width/2, (v.y+1) * height/2 };
}

void View::drawTriangle(Vec2d p1, Vec2d p2, Vec2d p3) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	drawLine(p1, p2);
	drawLine(p2, p3);
	drawLine(p1, p3);
}


void View::drawLine(Vec2d p1, Vec2d p2) {
	SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
}


void View::inputsUpdate() {
	_forwardMove = 0;
	_rightMove = 0;
	_upMove = 0;
	_XCamRotation = 0;
	_YCamRotation = 0;
	SDL_Event events;
	while (SDL_PollEvent(&events)) {
		switch (events.type) {
		case SDL_QUIT:
			_exit = true;
			break;
		case SDL_KEYDOWN:
			switch (events.key.keysym.sym) {
			case SDLK_z:
				_forwardMove += 0.1;
				break;
			case SDLK_s:
				_forwardMove -= 0.1;
				break;
			case SDLK_d:
				_rightMove += 0.1;
				break;
			case SDLK_q:
				_rightMove -= 0.1;
				break;
			case SDLK_i:
				_upMove += 0.1;
				break;
			case SDLK_k:
				_upMove -= 0.1;
				break;
			case SDLK_e:
				_XCamRotation += PI / 40;
				break;
			case SDLK_a:
				_XCamRotation -= PI / 40;
				break;
			}
			break;
		}
	}
}