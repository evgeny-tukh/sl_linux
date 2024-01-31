#pragma once

#include "sdk/sl_button.h"

class NameEditButton: public Ui::Button {
    public:
        NameEditButton(Ui::Wnd& parent, int x, int y);

    protected:
        virtual void loadImages();

        virtual const std::string& getFontName() const;
        virtual int getTextY() const;
        virtual int getImageY() const;
};