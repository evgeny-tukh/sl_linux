#include "sl_wnd.h"
#include "sl_event.h"
#include <vector>

uint32_t Ui::Wnd::Properties::get(Property prop) {
    auto pos = find(prop);

    if (pos == end())
        return UNDEFINED;

    return pos->second;
}

Ui::Wnd::Wnd(Display *display, Properties& props, Window parent):
    _wnd(0),
    _parent(parent),
    _display(display),
    _bgClr(props.get(Wnd::Property::BgColor)),
    _borderClr(props.get(Wnd::Property::BorderColor)),
    _bordwerWidth(props.get(Wnd::Property::BorderWidth)),
    _width(props.get(Wnd::Property::Width)),
    _height(props.get(Wnd::Property::Height)),
    _x(props.get(Wnd::Property::X)),
    _y(props.get(Wnd::Property::Y)) {
    
    auto screen = DefaultScreen(display);
    
    if (_borderClr == Properties::UNDEFINED)
        _borderClr = getDefaultPropValue(Property::BorderColor);

    if (_bgClr == Properties::UNDEFINED)
        _bgClr = getDefaultPropValue(Property::BgColor);

    if (_bordwerWidth == Properties::UNDEFINED)
        _bordwerWidth = getDefaultPropValue(Property::BorderWidth);

    if (_width == Properties::UNDEFINED)
        _width = getDefaultPropValue(Property::Width);
        
    if (_height == Properties::UNDEFINED)
        _height = getDefaultPropValue(Property::Height);
        
    if (_x == Properties::UNDEFINED)
        _x = getDefaultPropValue(Property::X);
        
    if (_y == Properties::UNDEFINED)
        _y = getDefaultPropValue(Property::Y);
}

Ui::Wnd::~Wnd() {
    if (_wnd)
        destroy();
}

uint32_t Ui::Wnd::getDefaultPropValue(Property prop) {
    switch (prop) {
        case Property::BgColor: return WhitePixel(_display, DefaultScreen(_display));
        case Property::BorderColor: return BlackPixel(_display, DefaultScreen(_display));
        case Property::X: case Property::Y: return 100;
        case Property::Width: return 300;
        case Property::Height: return 100;
        case Property::BorderWidth: return 1;
        default: return Properties::UNDEFINED;
    }
}

void Ui::Wnd::create() {
    _wnd = XCreateSimpleWindow(
        _display,
        _parent,
        _x,
        _y,
        _width,
        _height,
        _bordwerWidth,
        _borderClr,
        _bgClr
    );
}

void Ui::Wnd::destroy() {
    if (_wnd) {
        XDestroyWindow(_display, _wnd);

        _wnd = 0;
    }
}

void Ui::Wnd::selectInput(long mask) const {
    XSelectInput(_display, _wnd, mask);
}

void Ui::Wnd::show (bool showFlag) const {
    if (showFlag)
        XMapWindow(_display, _wnd);
    else
        XUnmapWindow(_display, _wnd);
}

void Ui::Wnd::eventLoop(std::function<bool(Wnd& wnd, XEvent&)> cb) {
    bool keepRunning = true;

    while (keepRunning) {
        XEvent evt;

        XNextEvent(_display, &evt);

        auto wnd = findChildByHandle(evt.xany.window);

        if (!wnd)
            wnd = this;

        switch (evt.type) {
            case EnterNotify:
                wnd->onMouseEnter(evt.xcrossing); break;
            case LeaveNotify:
                wnd->onMouseLeave(evt.xcrossing); break;
            case ButtonPress:
                wnd->onButtonPress(evt.xbutton); break;
            case ButtonRelease:
                wnd->onButtonRelease(evt.xbutton); break;
            case ConfigureNotify:
                wnd->onConfigurationChanged(evt.xconfigure); break;
            case Expose:
                wnd->onPaint(evt.xexpose); break;
            default:
                keepRunning = cb(*wnd, evt);
        }

        Ui::Event uiEvent;
        while (popEvent(uiEvent)) {
            uiEvent.runHandler();
        }
    }
}

void Ui::Wnd::onConfigurationChanged(XConfigureEvent& evt) {
    if (evt.width != _width)
        _width = evt.width;
    if (evt.height != _height)
        _height = evt.height;
}

void Ui::Wnd::paint(GC ctx) const {
}

void Ui::Wnd::onPaint(XExposeEvent& evt) {
    if (evt.count != 0)
        return;

    GC ctx = XCreateGC(_display, _wnd, 0, nullptr);
    paint(ctx);
    XFreeGC(_display, ctx);
    XFlush(_display);

    for (auto child: _children)
        child.second->onPaint(evt);
}

Ui::Wnd *Ui::Wnd::addChild(uint16_t id, std::shared_ptr<Wnd> wnd) {
    _children.emplace(std::pair<uint16_t, std::shared_ptr<Wnd>>(id, wnd));
    return wnd.get();
}

Ui::Wnd *Ui::Wnd::findChildByHandle(Window handle) const {
    for (auto child: _children) {
        if (child.second->handle() == handle)
            return child.second.get();
    }
    return nullptr;
}

Ui::Wnd *Ui::Wnd::findChildById(uint16_t id) const {
    auto pos = _children.find(id);

    return (pos == _children.end()) ? nullptr : pos->second.get();
}

void Ui::Wnd::forceRedraw() {
    //XClearArea(_display, _wnd, 0, 0, _width, _height, true);
    //XFlush(_display);
    XExposeEvent evt;
    evt.count = 0;
    evt.display = _display;
    evt.height = _height;
    evt.type = Expose;
    evt.width = _width;
    evt.window = _wnd;
    evt.x = 0;
    evt.y = 0;
    onPaint(evt);
}