#include <string>
#include <iostream>

#include <GL/glew.h>
#include <SDL2/SDL.h>

class Disp {
	private:
		SDL_Window* win;

		SDL_GLContext ctx;

	public:
		bool open = false;

		Disp(const char* title, unsigned int wd, int unsigned ht);

		void clear(float r, float g, float b, float a);

		void update();

		~Disp();
};
