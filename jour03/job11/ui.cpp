#include <iostream>
#include <string>
#include <vector>

void drawBorder()
{
    std::cout << "+--------------------------+\n";
}

void drawHeader(const std::string &title)
{
    drawBorder();
    std::cout << "| " << title << "\n";
    drawBorder();
}

void showStatus(const std::string &name, int hp, int x, int y)
{
    std::cout << name << " - HP: " << hp << " - Pos: (" << x << "," << y << ")\n";
}

int main()
{
    drawHeader("Campus Quest - UI Demo");
    showStatus("Hero", 20, 0, 0);
    showStatus("Goblin", 5, 3, 0);
    std::cout << "Actions: attack | move | switch\n";
    return 0;
}
