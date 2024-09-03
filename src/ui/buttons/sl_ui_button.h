#pragma once

#include <string>

#include "../sdk/sl_img_button.h"

namespace UiButtonsLayout {
    const int TOP_ROW_Y = 10;
    const int SECOND_ROW_Y = 160;
    const int SECOND_ROW_BOTTOM = 160;
    const int THIRD_ROW_BOTTOM = 10;
    const int FIRST_COL_RIGHT = 610;
    const int SECOND_COL_RIGHT = 460;
    const int THIRD_COL_RIGHT = 310;
    const int FOURTH_COL_RIGHT = 160;
    const int FIFTH_COL_RIGHT = 10;
}

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