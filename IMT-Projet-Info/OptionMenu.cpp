#include "optionMenu.h"

// Constructeur
OptionMenu::OptionMenu(const char* s, bool selection) {
    this->s = s;
    this->estSelectionne = selection;
    this->taille = MeasureText(s, 40);
    if (selection) {
        setColor(RED);
    }
    else setColor(WHITE);
}

// Méthodes
void OptionMenu::selection() {
    setColor(RED);
    setSelection(true);
}
void OptionMenu::deselection() {
    setColor(WHITE);
    setSelection(false);
}

// Accesseurs
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

// Mutateurs
void OptionMenu::setColor(Color color) {
    this->color = color;
}

void OptionMenu::setSelection(bool selection) {
    this->estSelectionne = selection;
}


