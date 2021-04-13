#include <raylib.h>

//Classe cod�e par Louis Delacour
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

    // M�thodes
    void selection();
    void deselection();

    // Accesseurs
    Color getColor() const;
    const char* getString() const;
    int getPosition(int screenWidth) const;
    bool getSelection() const;

    // Mutateurs
    void setSelection(bool selection);
    void setColor(Color color);
   
    

};