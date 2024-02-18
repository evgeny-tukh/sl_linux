#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <memory>
#include <string>
#include <unordered_map>

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
#include "sl_labeled_value.h"
#include "sl_value_storage.h"

class SearchMasterWnd: public Ui::Wnd {
    public:
        SearchMasterWnd(Display *display);

        void create() override;

    protected:
        long int _yellowClr;
        std::unique_ptr<Ui::Bitmap> _img;
        std::unordered_map<std::string, std::shared_ptr<LabeledValue>&> _valueDisplays;
        ValueStorage _storage;

        std::shared_ptr<NameEditButton> _butNameEdit;
        std::shared_ptr<HarbourModeButton> _butHarbourModeSwitch;
        std::shared_ptr<SettingsButton> _butSettings;
        std::shared_ptr<RangeExtendButton> _butRangeExt;
        std::shared_ptr<RangeReduceButton> _butRangeRed;
        std::shared_ptr<LightOnButton> _butLightOn;
        std::shared_ptr<LightOffButton> _butLightOff;
        std::shared_ptr<DimmerExtendButton> _butDimmerExt;
        std::shared_ptr<DimmerReduceButton> _butDimmerRed;
        std::shared_ptr<LabeledValue> _hdg;
        std::shared_ptr<LabeledValue> _lat;
        std::shared_ptr<LabeledValue> _lon;

        void updateValues();

        void paint(GC ctx) const override;

        template<typename ButCls>
        void initButton(std::shared_ptr<ButCls>& button, Ui::Resources id) {
            button.reset(new ButCls(*this));
            addChild((uint16_t) id, button);
            button->create();
            button->show(true);
        }

        void initLabeledValue(std::shared_ptr<LabeledValue>& ctrl, const char *label, int x, int y, Ui::Resources id, int width = 100);

        std::string getValueOfParameter(const char *label) const;
};
