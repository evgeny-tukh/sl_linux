#include "sl_engine.h"
#include "sl_util.h"

Engine::Engine(Display *display): _display(display), _smWindow(new SearchMasterWnd(display)) {
    uint16_t width, height;
    Ui::Util::getScreenSize(display, width, height);
    _smWindow->create();
    _smWindow->show(true);
    _smWindow->resize(width, height);

    _channelHost.addChannel("nmea", Io::ChannelHost::UDP);
    _channelHost.addChannel("ais", Io::ChannelHost::UDP);

    auto nmeaParser = [this] (std::vector<uint8_t>& data, const Nmea::Parser& parser) {
        _smWindow->processNmea((const char *) data.data(), data.size(), parser);
    };
    
    Io::Udp::Config cfg;
    cfg.port = 8888;
    cfg.bindAddr = "";

    _channelHost.configure("nmea", &cfg);
    _channelHost.setReadCb("nmea", nmeaParser);

    cfg.port = 8889;
    _channelHost.configure("ais", &cfg);
    _channelHost.setReadCb("ais", nmeaParser);
}

void Engine::run() {
    _channelHost.openAll();
    _channelHost.startAll();

    _smWindow->eventLoop([] (Ui::Wnd& wnd, XEvent&) { return true; });

    _channelHost.stopAll();
    _channelHost.closeAll();
}

Engine::~Engine() {
    XCloseDisplay(_display);
}
