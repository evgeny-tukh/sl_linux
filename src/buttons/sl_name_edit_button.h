#pragma once

#include "sdk/sl_button.h"

class NameEditButton: public Ui::Button {
    public:
        NameEditButton(Ui::Wnd& parent, int x, int y);

    protected:
        long int _whiteClr;
        long int _blackClr;

        virtual void loadImages() override;

        void paint(GC ctx) const override;

        virtual const std::string& getFontName() const override;
        virtual int getTextY() const override;
        virtual int getImageY() const override;
};