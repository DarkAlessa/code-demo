#include "text.h"
#include <iostream>
#include <cstring>

Text::Text(std::string_view path, int fontSize) : path(path), fontSize(fontSize) {
    fontFace = TTF_OpenFont(std::string(path).c_str(), fontSize);
    if (fontFace == nullptr) {
        std::cout << "[1] fontFace Error : " << std::string(path).c_str() << TTF_GetError() << '\n';
        TTF_CloseFont(fontFace);
    }
}

Text::Text(const Text& obj)
:   fg(obj.fg),
    position(obj.position),
    angle(obj.angle),
    path(obj.path),
    fontSize(obj.fontSize)
{
    fontFace = TTF_OpenFont(std::string(path).c_str(), fontSize);
    if (fontFace == nullptr) {
        std::cout << "[2] fontFace Error : " << std::string(path).c_str() << TTF_GetError() << '\n';
        TTF_CloseFont(fontFace);
    }
}

Text& Text::operator=(const Text& obj) {
    if (this != &obj) {
        textTexture = obj.textTexture;
        textSurface = obj.textSurface;
        path = obj.path;
        fg = obj.fg;
        fontSize = fontSize;
        position = obj.position;
        angle = obj.angle;
    }
    return *this;
}

Text::~Text() noexcept = default;

Text& Text::setText(SDL_Renderer* renderer, const std::wstring& text) {
    if (textTexture) {
        SDL_DestroyTexture(textTexture);
        textTexture = nullptr;
    }
    textSurface = TTF_RenderUNICODE_Blended(fontFace, reinterpret_cast<const Uint16*>(text.c_str()), fg);
    if (textSurface == nullptr) {
        std::cout << "textSurface Error : " << TTF_GetError() << '\n';
    }
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == nullptr) {
        std::cout << "textTexture Error : " << SDL_GetError() << '\n';
    }
    dest = { position.x, position.y, (float)textSurface->w, (float)textSurface->h };
    if (textSurface) {
        SDL_FreeSurface(textSurface);
        textSurface = nullptr;
    }
    return *this;
}

Text& Text::setText(SDL_Renderer* renderer, const std::string& text) {
    if (textTexture) {
        SDL_DestroyTexture(textTexture);
        textTexture = nullptr;
    }
    textSurface = TTF_RenderUTF8_Blended(fontFace, text.c_str(), fg);
    if (textSurface == nullptr) {
        std::cout << "textSurface Error : " << TTF_GetError() << '\n';
    }
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == nullptr) {
        std::cout << "textTexture Error : " << SDL_GetError() << '\n';
    }
    dest = { position.x, position.y, (float)textSurface->w, (float)textSurface->h };
    if (textSurface) {
        SDL_FreeSurface(textSurface);
        textSurface = nullptr;
    }
    return *this;   
}

Text& Text::setColor(const SDL_Color& color) {
    fg = color;
    return *this;
}

Text& Text::setPosition(const SDL_FPoint& pos) {
    position = pos;
    return *this;
}

Text& Text::setFontSize(int fontSize) {
    this->fontSize = fontSize;
    if (TTF_SetFontSize(fontFace, fontSize) == -1) {
        std::cout << "set font size error: " << TTF_GetError() << '\n';
    }
    return *this;
}

Text& Text::setFontFace(std::string_view path) {
    this->path = path;
    fontFace = TTF_OpenFont(std::string(path).c_str(), fontSize);
    if (fontFace == nullptr) {
        std::cout << "setFontFace() Error : " << std::string(path).c_str() << TTF_GetError() << '\n';
        TTF_CloseFont(fontFace);
    }       
    return *this;
}

Text& Text::rotate(double angle) {
    this->angle = angle;
    return *this;
}

Text& Text::render(SDL_Renderer* renderer) {
    SDL_RenderCopyExF(renderer, textTexture, NULL, &dest, angle, NULL, SDL_FLIP_NONE);
    return *this;
}

SDL_FPoint Text::getPosition() const {
    return SDL_FPoint{ dest.x, dest.y };
}

void Text::fontClose() {
    if (fontFace) {
        TTF_CloseFont(fontFace);
        fontFace = nullptr;
    }
}
