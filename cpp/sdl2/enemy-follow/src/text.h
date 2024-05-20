#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <string_view>

class Text {
public:
	Text(std::string_view, int);
	Text(const Text&);
	Text& operator=(const Text&);
	virtual ~Text();
	Text& setText(SDL_Renderer*, const std::wstring&);
	Text& setText(SDL_Renderer*, const std::string&);
	Text& setColor(const SDL_Color&);
	Text& setPosition(const SDL_FPoint&);
	Text& setFontSize(int);
	Text& setFontFace(std::string_view);
	Text& rotate(double);
	Text& render(SDL_Renderer*);
	SDL_FPoint getPosition() const;
	void fontClose();

private:
	SDL_Texture* textTexture = nullptr;
	SDL_Surface* textSurface = nullptr;
	TTF_Font* fontFace = nullptr;
	SDL_Color fg = { 255, 255, 255 };
	SDL_FPoint position = { 0.0f, 0.0f };
	SDL_FRect dest = { 0.0f, 0.0f, 0.0f, 0.0f };
	double angle = 0.0;
	std::string_view path;
	int fontSize;
};

#endif // TEXT_H