#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <memory>

#include <X11/Xlib.h> 

#include "sl_button.h"
#include "sl_wnd.h"
#include "sl_event.h"
#include "sl_bitmap.h"
#include "sl_range_inc_but.h"
#include "sl_range_dec_but.h"
#include "sl_res.h"
#include "sl_name_edit_button.h"
#include "sl_harbour_mode_button.h"
#include "sl_settings_button.h"
#include "sl_range_ext_button.h"
#include "sl_range_red_button.h"
#include "sl_light_on_button.h"
#include "sl_light_off_button.h"
#include "sl_dimmer_ext_button.h"
#include "sl_dimmer_red_button.h"

class SearchMasterWnd: public Ui::Wnd {
    public:
        SearchMasterWnd(Display *display);

        void create() override;

    protected:
        long int _yellowClr;
        std::unique_ptr<Ui::Bitmap> _img;

        std::shared_ptr<NameEditButton> _butNameEdit;
        std::shared_ptr<HarbourModeButton> _butHarbourModeSwitch;
        std::shared_ptr<SettingsButton> _butSettings;
        std::shared_ptr<RangeExtendButton> _butRangeExt;
        std::shared_ptr<RangeReduceButton> _butRangeRed;
        std::shared_ptr<LightOnButton> _butLightOn;
        std::shared_ptr<LightOffButton> _butLightOff;
        std::shared_ptr<DimmerExtendButton> _butDimmerExt;
        std::shared_ptr<DimmerReduceButton> _butDimmerRed;

        void paint(GC ctx) const override;

        template<typename ButCls>
        void initButton(std::shared_ptr<ButCls>& button, Ui::Resources id) {
            button.reset(new ButCls(*this));
            addChild((uint16_t) id, button);
            button->create();
            button->show(true);
        }
};
