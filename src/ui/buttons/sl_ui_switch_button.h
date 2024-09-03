#pragma once

#include <string>

#include "sl_ui_button.h"

class UiButton: public Ui::ImgButton {
    public:
        UiButton(Ui::Wnd& parent, const std::string& folder, const std::string& text, int x, int y);

    protected:
        long int _whiteClr;
        long int _blackClr;

        void paint(GC ctx) override;

        virtual const std::string& getFontName() const override;
        virtual int getTextY() const override;
        virtual int getImageX(const BmpPtr& bmp) const override;
        virtual int getImageY(const BmpPtr& bmp) const override;

        virtual unsigned long getBgColor() const override;

    protected:
        long int _redClr;
        long int _yellowClr;
};