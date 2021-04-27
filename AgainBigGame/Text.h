#ifndef TEXT_H
#define TEXT_H

#include "LTexture.h"

class Text : public LTexture
{
public:
    enum TextColor
    {
        RED_TEXT = 0,
        WHITE_TEXT = 1,
        BLUE_TEXT =2,
    };

    Text();
    ~Text();

    void SetText(const std::string &text){str_val = text;};
    void SetColor(const int & type);
    void CreateGameText(TTF_Font * font);
private:
    std::string str_val;
    SDL_Color text_color;
};

Text::Text()
{
    ;
}

Text::~Text()
{

}


void Text::SetColor(const int & type)
{
    if(type == RED_TEXT )
    {
        SDL_Color color = (255, 0, 0);
        text_color = color;
    }
    else if(type == WHITE_TEXT)
    {
        SDL_Color color = (255, 255, 255);
        text_color = color;
    }
    else
    {
        SDL_Color color = (0, 0, 0);
        text_color = color;
    }
}

void Text::CreateGameText(TTF_Font * font)
{
   // SDL_Surface* p_Text = TTF_RenderText_Solid(font, str_val.c_str(), text_color);
}

#endif // TEXT_H
