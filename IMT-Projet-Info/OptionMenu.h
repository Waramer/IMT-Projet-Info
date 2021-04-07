#include <raylib.h>

class OptionMenu
{
private:
    Color color;
    const char* s;
    int taille = MeasureText(s, 20);
    bool estSelectionne;
public:
    // Constructeur
    OptionMenu(const char* s, bool selection);

    // Accesseurs
    Color getColor() const;
    const char* getString() const;
    int getPosition(int screenWidth) const;
    bool getSelection() const;

    // Mutateurs
    void setSelection(bool selection);
    void setColor(Color color);
   
    // Autres M�thodes
    void selection();
    void deselection();

};