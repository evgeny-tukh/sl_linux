#pragma once

#include <string>

#include "sl_value_field.h"

class Value: public ValueField {
    public:
        Value(Display *display, Getter getter, int x, int y, Window parent, const char *prefix = "", const char *postfix = "");

    protected:
        std::string _prefix;
        std::string _postfix;
        std::string _compoundText;

        std::string getText() const override;
};