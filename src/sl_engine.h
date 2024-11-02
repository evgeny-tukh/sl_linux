#pragma once

#include <io/sl_udp_channel.h>
#include <io/sl_channel_host.h>
#include "sl_main_wnd.h"

class Engine {
    public:
        Engine(Display *display);
        ~Engine();

        void run();
        
    private:
        Display *_display;
        Io::ChannelHost _channelHost;
        SearchMasterWnd *_smWindow;
};
