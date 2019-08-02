#include "Font.h"

Font::Font() {
}

Font::~Font() {
}

bool Font::Init(int w, int h) {
	if (FT_Init_FreeType(&library)) {
		printf("Failed to initialize freetype library instance!\n");
		return false;
	}

	if (FT_New_Face(library, "C:\\Windows\\Fonts\\Arial.ttf", 0, &face)) {
		printf("Failed to initialize font face!\n");
		return false;
	}

	if (FT_Set_Char_Size(face, 0, 16 * 64, w, h)) {
		printf("Failed to initialize font character size!\n");
		return false;
	}

	return true;
}

void* Font::DrawText(std::string text, Actor* owner) {
	int pen_x = 0, pen_y = 0;
	for (const auto& c : text) {
		FT_UInt glyph_index = FT_Get_Char_Index(face, c);
		if (FT_Load_Glyph(face, glyph_index, FT_LOAD_RENDER)) {
			printf("Failed to load glyph at index: %d\n", glyph_index);
		}

		// TODO: Draw to buffer
		Sprite* sprite = new Sprite();
		const FT_Bitmap& bitmap = face->glyph->bitmap;
		tex->CreateFromBuffer(bitmap.buffer, bitmap.rows, bitmap.width);
		textures.push_back(tex);

		pen_x += face->glyph->advance.x >> 6;
		pen_y += face->glyph->advance.y >> 6;
	}
}

bool Text::Init(Font* _font, std::string& text) {
	font = _font;
}

void Text::Draw() {

}
