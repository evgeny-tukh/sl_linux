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

class SearchMasterWnd: public Ui::Wnd {
    public:
        SearchMasterWnd(Display *display);

    protected:
        void paint(GC ctx) const override;
};
