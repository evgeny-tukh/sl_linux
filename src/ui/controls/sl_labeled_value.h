#include <sl_drawable.h>
#include <sl_red_label.h>
#include <sl_value_field.h>

class LabeledValue: public Ui::DrawableObject {
    public:
        LabeledValue(Display *display, const char *label, ValueField::Getter valueGetter, int x, int y, Window parent, int width);
        LabeledValue(Display *display, const char *label, ValueField::Getter valueGetter, int x, int y, Window parent);

        void show(bool showFlag) override;

        void setupLayout(int xOffset, int yOffset) override;

    protected:
        RedLabel _label;
        ValueField _field;

        void paint(GC ctx) override;

        void updateUi() override;
};
