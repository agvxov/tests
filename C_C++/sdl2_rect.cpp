#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

int main(int argc, char *argv[]){
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Point p;
	p.x = 1;
	p.y = 1;

	SDL_Rect r;
	r.w = 4;
	r.h = 4;
	r.x = 0;
	r.y = 0;

	SDL_Rect r2;

	cout << SDL_PointInRect(&p, &r) << ':' << SDL_RectEquals(&r, &r2) << endl;
	
	SDL_Quit();
}
