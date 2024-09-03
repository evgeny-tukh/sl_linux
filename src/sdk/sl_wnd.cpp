#include "sl_wnd.h"
#include "sl_event.h"
#include <vector>
#include <string.h>

uint32_t Ui::Wnd::Properties::get(Property prop) {
    auto pos = find(prop);

    if (pos == end())
        return UNDEFINED;

    return pos->second;
}

Ui::Wnd::Properties::Properties (uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    clear();
    (*this)[Ui::Wnd::Property::X] = x;
    (*this)[Ui::Wnd::Property::Y] = y;
    (*this)[Ui::Wnd::Property::Width] = width;
    (*this)[Ui::Wnd::Property::Height] = height;
}

Ui::Wnd::Properties& Ui::Wnd::Properties::populate(Ui::Wnd::Properties& props, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    props.clear();
    props.emplace(std::pair<Ui::Wnd::Property, uint32_t>(Ui::Wnd::Property::X, x));
    props.emplace(std::pair<Ui::Wnd::Property, uint32_t>(Ui::Wnd::Property::Y, y));
    props.emplace(std::pair<Ui::Wnd::Property, uint32_t>(Ui::Wnd::Property::Width, width));
    props.emplace(std::pair<Ui::Wnd::Property, uint32_t>(Ui::Wnd::Property::Height, height));

    return props;
}

Ui::Wnd::Wnd(Display *display, int x, int y, int width, int height, Window parent):
    DrawableObject(display, x, y, width, height, parent),
    _wnd(0),
    _borderClr(getDefaultPropValue(Property::BorderColor)),
    _bordwerWidth(getDefaultPropValue(Property::BorderWidth)),
    _actualWidth(0),
    _actualHeight(0) {
    _bgClr = getDefaultPropValue(Property::BgColor);
}

Ui::Wnd::Wnd(Display *display, Properties& props, Window parent):
    DrawableObject(display, props.get(Wnd::Property::X), props.get(Wnd::Property::Y), props.get(Wnd::Property::Width), props.get(Wnd::Property::Height), parent),
    _wnd(0),
    _borderClr(props.get(Wnd::Property::BorderColor)),
    _bordwerWidth(props.get(Wnd::Property::BorderWidth)) {
    _bgClr = props.get(Wnd::Property::BgColor);
    
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

void Ui::Wnd::show (bool showFlag) {
    if (showFlag) {
        XMapWindow(_display, _wnd);
        XMapSubwindows(_display, _wnd);
    } else {
        XUnmapWindow(_display, _wnd);
    }
    XFlush(_display);
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
    bool sizeChanged = false;

    if (evt.width != _width) {
        _width = evt.width;
        sizeChanged = true;
    }
    
    if (evt.height != _height) {
        _height = evt.height;
        sizeChanged = true;
    }

    if (sizeChanged) {
        bool notifyChildren = false;
        onSizeChanged(_width, _height, notifyChildren);

        if (notifyChildren) {
            for (auto child: _children)
                child.second->onParentSizeChanged(_width, _height);
        }
    }
}

void Ui::Wnd::paint(GC ctx) {
}

void Ui::Wnd::onPaint(XExposeEvent& evt) {
    if (evt.count != 0)
        return;

    GC ctx = XCreateGC(_display, _wnd, 0, nullptr);
    paint(ctx);

    for (auto child: _children) {
        if (!child.second->isWindow()) {
            child.second->updateUi();
            child.second->paint(ctx);
        }
    }

    XFreeGC(_display, ctx);
    XFlush(_display);

    for (auto child: _children) {
        if (child.second->isWindow()) {
            Wnd *window = dynamic_cast<Wnd *>(child.second.get());

            if (window) {
                window->updateUi();
                window->onPaint(evt);
            }
        }
    }
}

Ui::DrawableObject *Ui::Wnd::addChild(uint16_t id, std::shared_ptr<DrawableObject> child) {
    _children.emplace(std::pair<uint16_t, std::shared_ptr<DrawableObject>>(id, child));
    return child.get();
}

Ui::Wnd *Ui::Wnd::findChildByHandle(Window handle) const {
    for (auto child: _children) {
        if (child.second->isWindow()) {
            Wnd *window = dynamic_cast<Wnd *>(child.second.get());

            if (window && window->handle() == handle)
                return window;
        }
    }
    return nullptr;
}

Ui::DrawableObject *Ui::Wnd::findChildById(uint16_t id) const {
    auto pos = _children.find(id);

    if (pos == _children.end())
        return nullptr;

    return dynamic_cast<Wnd *>(pos->second.get());
}

void Ui::Wnd::resize(uint16_t width, uint16_t height) {
    DrawableObject::resize(width, height);
    XResizeWindow(_display, _wnd, width, height);
}

void Ui::Wnd::move(int x, int y) {
    DrawableObject::move(x, y);
    XMoveWindow(_display, _wnd, x, y);
}

void Ui::Wnd::forceRedraw() {
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

void Ui::Wnd::textOut(int x, int y, GC ctx, const char *txt) const {
    XDrawString(_display, _wnd, ctx, x, y, txt, strlen(txt));
}

void Ui::Wnd::onSizeChanged(int width, int height, bool& notifyChildren) {
    notifyChildren = true;
    _actualWidth = width;
    _actualHeight = height;
}

void Ui::Wnd::onParentSizeChanged(int width, int height) {
    applyAnchorage();
}

std::shared_ptr<Ui::Wnd> Ui::Wnd::attach(Display *display, Window wnd) {
    XWindowAttributes attrs;
    XGetWindowAttributes(display, wnd, &attrs);

    std::shared_ptr<Ui::Wnd> result = std::make_shared<Wnd>(display, attrs.x, attrs.y, attrs.width, attrs.height, attrs.root);

    result->_wnd = wnd;

    return result;
}

bool Ui::Wnd::getActualSize(int& width, int& height) {
    if (_actualWidth > 0 && _actualHeight > 0){
        width = _actualWidth;
        height = _actualHeight;

        return true;
    }

    return false;
}