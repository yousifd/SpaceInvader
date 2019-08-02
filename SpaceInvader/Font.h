#pragma once

#include <string>
#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Sprite.h"
#include "Actor.h"

class Font {
public:
	Font();
	~Font();

	bool Init(int w, int h);
	void* DrawText(std::string text, Actor* owner);
	std::vector<Sprite*> textures;

private:
	FT_Library library;
	FT_Face face;
};

class Text {
	bool Init(Font* _font, std::string& text);
	void Draw();

private:
	Font* font;
};

