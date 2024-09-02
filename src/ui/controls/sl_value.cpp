#include "sl_value.h"

namespace {
const int WIDTH = 100;
const int HEIGHT = 40;
}

Value::Value(Display *display, Getter getter, int x, int y, Window parent, const char *prefix, const char *postfix):
    ValueField(display, getter, x, y, WIDTH, HEIGHT, parent),
    _prefix(prefix),
    _postfix(postfix) {
}

std::string Value::getText() const {
    return _prefix + _text + _postfix;
}
