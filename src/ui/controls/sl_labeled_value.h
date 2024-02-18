#include <sl_drawable.h>
#include <sl_red_label.h>
#include <sl_value_field.h>

class LabeledValue: public Ui::DrawableObject {
    public:
        LabeledValue(Display *display, const char *label, ValueField::Getter valueGetter, int x, int y, Window parent, int width = 100);

        void show(bool showFlag) override;

    protected:
        RedLabel _label;
        ValueField _field;

        void paint(GC ctx) const override;

        void updateUi() override;
};
