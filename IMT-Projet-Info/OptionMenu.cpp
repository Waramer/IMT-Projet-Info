#include "optionMenu.h"

OptionMenu::OptionMenu(const char* s, bool selection) {
    this->s = s;
    this->estSelectionne = selection;
    this->taille = MeasureText(s, 20);
    if (selection) {
        setColor(RED);
    }
    else setColor(WHITE);
}

Color OptionMenu::getColor() const{
    return color;
}

const char* OptionMenu::getString() const {
    return s;
}

int OptionMenu::getPosition(int screenWidth) const{
    return screenWidth / 2 - taille / 2;
}

bool OptionMenu::getSelection() const {
    return estSelectionne;
}

void OptionMenu::setColor(Color color) {
    this->color = color;
}

void OptionMenu::setSelection(bool selection) {
    this->estSelectionne = selection;
}

void OptionMenu::selection() {
    setColor(RED);
    setSelection(true);
}
void OptionMenu::deselection() {
    setColor(WHITE);
    setSelection(false);
}

