#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <cmath>


class GameObject;
class Character;
class Enemy;
class Decor;
class Projectile;
class Weapon;
class Player;
class Bow;
class Spear;
class Sword;

// Simple 2D vector
class Vector2d
{
public:
    double x{0}, y{0};
    Vector2d(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
    Vector2d operator+(const Vector2d &o) const { return {x + o.x, y + o.y}; }
    Vector2d operator-(const Vector2d &o) const { return {x - o.x, y - o.y}; }
    double distance(const Vector2d &o) const
    {
        double dx = x - o.x;
        double dy = y - o.y;
        return std::sqrt(dx * dx + dy * dy);
    }
};

// Base GameObject
class GameObject
{
public:
    Vector2d pos;
    virtual ~GameObject() = default;
    virtual void update() = 0;
    // return a 2-character representation used by the map renderer (e.g. "P ", "E ", "# ")
    virtual std::string repr() const = 0;
    virtual bool isAlive() const { return true; }
    virtual bool blocks() const { return false; }
    virtual void damage(int) {}
};

// Character base
class Character : public GameObject
{
public:
    Character(std::string n, int h, Vector2d p) : name(std::move(n)), hp(h) { pos = p; }
    void damage(int d) override { hp = std::max(0, hp - d); }
    bool isAlive() const override { return hp > 0; }
    const std::string &getName() const { return name; }
    int getHp() const { return hp; }
    bool blocks() const override { return isAlive(); }

protected:
    std::string name;
    int hp;
};

// Weapon base: now accepts an optional direction (for ranged weapons)
class Weapon
{
public:
    virtual ~Weapon() = default;
    // dir: normalized direction vector. For melee weapons this can be ignored.
    virtual void attack(std::vector<std::unique_ptr<GameObject>> &world, const GameObject *attacker, const Vector2d &dir = Vector2d{1, 0}) = 0;
    virtual int getRange() const = 0;
    virtual int getDamage() const = 0;
    virtual const char *getName() const = 0;
};

// Projectile
class Projectile : public GameObject
{
public:
    Projectile(Vector2d p, Vector2d d, int dmg) : dmg_(dmg), dir(d)
    {
        pos = p;
        double len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        if (len > 0)
        {
            dir.x /= len;
            dir.y /= len;
        }
    }
    void update() override
    {
        pos.x += dir.x;
        pos.y += dir.y;
        lifetime--;
    }
    std::string repr() const override { return "↟ "; }
    bool isAlive() const override { return lifetime > 0; }
    int getDamage() const { return dmg_; }
    void damage(int) override { lifetime = 0; }

private:
    Vector2d dir;
    int dmg_;
    int lifetime{10};
};

// Forward weapon classes
class Bow : public Weapon
{
public:
    void attack(std::vector<std::unique_ptr<GameObject>> &world, const GameObject *attacker, const Vector2d &dir = Vector2d{1, 0}) override;
    int getRange() const override { return 4; }
    int getDamage() const override { return 1; }
    const char *getName() const override { return "Bow"; }
};
class Spear : public Weapon
{
public:
    void attack(std::vector<std::unique_ptr<GameObject>> &world, const GameObject *attacker, const Vector2d &dir = Vector2d{1, 0}) override;
    int getRange() const override { return 2; }
    int getDamage() const override { return 2; }
    const char *getName() const override { return "Spear"; }
};
class Sword : public Weapon
{
public:
    void attack(std::vector<std::unique_ptr<GameObject>> &world, const GameObject *attacker, const Vector2d &dir = Vector2d{1, 0}) override;
    int getRange() const override { return 1; }
    int getDamage() const override { return 4; }
    const char *getName() const override { return "Sword"; }
};

// Decor (walls) — now destructible
class Decor : public GameObject
{
public:
    Decor(Vector2d p, const std::string &d = "Wall", int hp_ = 3) : desc(d), hp(hp_) { pos = p; }
    void update() override {}
    std::string repr() const override { return (hp > 0 ? std::string("# ") : std::string("  ")); }
    bool blocks() const override { return hp > 0; }
    void damage(int d) override { hp = std::max(0, hp - d); }
    bool isAlive() const override { return hp > 0; }

private:
    std::string desc;
    int hp{3};
};

// Enemy
class Enemy : public Character
{
public:
    Enemy(const std::string &n, int hp_, Vector2d p) : Character(n, hp_, p) {}
    void update() override
    {
        if (!target)
            return;
        Vector2d dir{target->pos.x - pos.x, target->pos.y - pos.y};
        double dist = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        if (dist > 1.0)
        {
            dir.x = dir.x / dist * 0.5;
            dir.y = dir.y / dist * 0.5;
            pos.x += dir.x;
            pos.y += dir.y;
        }
    }
    std::string repr() const override { return "E "; }
    void setTarget(GameObject *t) { target = t; }

private:
    GameObject *target{nullptr};
};

// Player
class Player : public Character
{
public:
    Player(const std::string &n, int hp_, Vector2d p) : Character(n, hp_, p)
    {
        weapons.push_back(std::make_unique<Bow>());
        weapons.push_back(std::make_unique<Spear>());
        weapons.push_back(std::make_unique<Sword>());
    }
    void update() override {}
    std::string repr() const override { return "P "; }

    // move with bounds checking done by caller
    bool move(const std::string &dir, const std::vector<std::unique_ptr<GameObject>> &world, int width, int height)
    {
        Vector2d newPos = pos;
        if (dir == "up")
            newPos.y -= 1;
        else if (dir == "down")
            newPos.y += 1;
        else if (dir == "left")
            newPos.x -= 1;
        else if (dir == "right")
            newPos.x += 1;
        else
            return false; // unknown direction

        // bounds
        if (newPos.x < 0 || newPos.x >= width || newPos.y < 0 || newPos.y >= height)
            return false;

        for (const auto &obj : world)
        {
            if (obj.get() != this && obj->blocks() && obj->pos.distance(newPos) < 0.5)
            {
                return false;
            }
        }
        pos = newPos;
        return true;
    }

    // player attack: forwards the direction to the weapon
    void attack(std::vector<std::unique_ptr<GameObject>> &world, const Vector2d &dir)
    {
        if (!weapons.empty())
        {
            weapons[currentWeapon]->attack(world, this, dir);
        }
    }

    void switchWeapon()
    {
        currentWeapon = (currentWeapon + 1) % weapons.size();
        std::cout << "Switched to " << weapons[currentWeapon]->getName() << "\n";
    }

    const char *getCurrentWeaponName() const { return weapons[currentWeapon]->getName(); }

private:
    std::vector<std::unique_ptr<Weapon>> weapons;
    size_t currentWeapon{0};
};

// UI namespace — improved drawMap that prints a grid
namespace UI
{
    void drawBorder(int width = 40) { std::cout << std::string(width, '=') << '\n'; }
    void drawHeader(const std::string &title)
    {
        drawBorder();
        std::cout << title << '\n';
        drawBorder();
    }

    void drawMap(const std::vector<std::unique_ptr<GameObject>> &objects, int width = 20, int height = 10)
    {
        // each tile occupies 2 characters
        std::vector<std::string> grid(height, std::string(width * 2, ' '));
        auto put = [&](int x, int y, const std::string &s)
        {
            if (x >= 0 && x < width && y >= 0 && y < height)
            {
                int idx = x * 2;
                for (size_t k = 0; k < s.size() && idx + (int)k < (int)grid[y].size(); ++k)
                    grid[y][idx + k] = s[k];
            }
        };

        for (const auto &obj : objects)
        {
            int x = static_cast<int>(std::floor(obj->pos.x + 0.0001));
            int y = static_cast<int>(std::floor(obj->pos.y + 0.0001));
            if (x < 0 || x >= width || y < 0 || y >= height)
                continue;
            put(x, y, obj->repr());
        }

        // print grid with coordinates (y increasing downward)
        std::cout << "   ";
        for (int x = 0; x < width; ++x)
        {
            if (x < 10)
                std::cout << " " << x;
            else
                std::cout << x;
        }
        std::cout << "\n";
        for (int y = 0; y < height; ++y)
        {
            if (y < 10)
                std::cout << " " << y << " ";
            else
                std::cout << y << " ";
            std::cout << grid[y] << "\n";
        }
    }

    void showHelp()
    {
        std::cout << "\nCommandes:\n"
                  << "  move up/down/left/right - Se déplacer\n"
                  << "  attack - Attaquer (pour Bow indiquez direction: up/down/left/right)\n"
                  << "  switch - Changer d'arme\n"
                  << "  help - Afficher l'aide\n"
                  << "  quit - Quitter\n";
    }
}

// Game class — holds world and main loop
class Game
{
public:
    Game()
    {
        // map size
        mapWidth = 20;
        mapHeight = 10;

        // Player
        world.push_back(std::make_unique<Player>("Hero", 20, Vector2d{2, 2}));

        // Add walls
        for (int i = 0; i < 5; ++i)
        {
            world.push_back(std::make_unique<Decor>(Vector2d{5.0 + i, 5.0}));
        }

        // Add enemies
        spawnEnemy("Goblin", 5, Vector2d{8, 8});
        spawnEnemy("Orc", 8, Vector2d{12, 3});
    }

    void run()
    {
        std::string cmd;
        Player *player = getPlayer();
        if (!player)
            return;

        UI::drawHeader("Campus Quest");
        UI::showHelp();

        while (player->isAlive())
        {
            std::cout << "\nHP: " << player->getHp() << " | Weapon: " << player->getCurrentWeaponName() << "\n\n";
            UI::drawMap(world, mapWidth, mapHeight);

            std::cout << "\n> ";
            if (!(std::cin >> cmd))
                break;

            if (cmd == "move")
            {
                std::string dir;
                std::cin >> dir;
                if (!player->move(dir, world, mapWidth, mapHeight))
                {
                    std::cout << "Impossible d'aller par là!\n";
                }
            }
            else if (cmd == "attack")
            {
                // determine direction for ranged weapons
                Vector2d dir{1, 0};
                if (std::string(player->getCurrentWeaponName()) == "Bow")
                {
                    std::string aim;
                    std::cout << "Direction (up/down/left/right): ";
                    std::cin >> aim;
                    if (aim == "up")
                        dir = Vector2d{0, -1};
                    else if (aim == "down")
                        dir = Vector2d{0, 1};
                    else if (aim == "left")
                        dir = Vector2d{-1, 0};
                    else
                        dir = Vector2d{1, 0};
                }
                player->attack(world, dir);
                std::cout << "Attaque avec " << player->getCurrentWeaponName() << "!\n";
            }
            else if (cmd == "switch")
            {
                player->switchWeapon();
            }
            else if (cmd == "help")
            {
                UI::showHelp();
                continue;
            }
            else if (cmd == "quit")
            {
                break;
            }
            else
            {
                std::cout << "Commande inconnue. Tapez 'help' pour l'aide.\n";
            }

            updateWorld();
            cleanupDead();

            if (countEnemies() == 0)
            {
                UI::drawHeader("Victoire!");
                break;
            }
        }

        if (!player->isAlive())
        {
            UI::drawHeader("Game Over!");
        }
    }

private:
    std::vector<std::unique_ptr<GameObject>> world;
    int mapWidth{20}, mapHeight{10};

    Player *getPlayer()
    {
        for (auto &obj : world)
            if (auto *p = dynamic_cast<Player *>(obj.get()))
                return p;
        return nullptr;
    }

    void spawnEnemy(const std::string &name, int hp, Vector2d pos)
    {
        auto enemy = std::make_unique<Enemy>(name, hp, pos);
        if (auto *player = getPlayer())
            enemy->setTarget(player);
        world.push_back(std::move(enemy));
    }

    void updateWorld()
    {
        // update all
        for (auto &obj : world)
            obj->update();

        // handle projectile collisions
        for (auto &obj : world)
        {
            if (auto *proj = dynamic_cast<Projectile *>(obj.get()))
            {
                for (auto &target : world)
                {
                    if (target.get() != proj && target->blocks())
                    {
                        if (target->pos.distance(proj->pos) < 0.8)
                        {
                            // We have a hit
                            // If target is enemy or decor, apply damage and print messages
                            if (auto *enemy = dynamic_cast<Enemy *>(target.get()))
                            {
                                enemy->damage(proj->getDamage());
                                std::cout << "Projectile touche " << enemy->getName() << "! HP=" << enemy->getHp() << "\n";
                            }
                            else if (auto *decor = dynamic_cast<Decor *>(target.get()))
                            {
                                decor->damage(proj->getDamage());
                                std::cout << "Projectile touche un mur!\n";
                            }
                            obj->damage(1); // destroy projectile
                            break;
                        }
                    }
                }
            }
        }

        // handle enemy melee attacks
        if (auto *player = getPlayer())
        {
            for (auto &obj : world)
            {
                if (auto *enemy = dynamic_cast<Enemy *>(obj.get()))
                {
                    if (enemy->pos.distance(player->pos) <= 1.0)
                    {
                        player->damage(1);
                        std::cout << enemy->getName() << " vous attaque! HP=" << player->getHp() << "\n";
                    }
                }
            }
        }
    }

    void cleanupDead()
    {
        world.erase(std::remove_if(world.begin(), world.end(), [](const auto &obj)
                                   { return !obj->isAlive(); }),
                    world.end());
    }

    int countEnemies()
    {
        return std::count_if(world.begin(), world.end(), [](const auto &obj)
                             { return dynamic_cast<Enemy *>(obj.get()) != nullptr; });
    }
};

// Weapon implementations
void Bow::attack(std::vector<std::unique_ptr<GameObject>> &world, const GameObject *attacker, const Vector2d &dir)
{
    auto proj = std::make_unique<Projectile>(attacker->pos, dir, getDamage());
    world.push_back(std::move(proj));
}

void Spear::attack(std::vector<std::unique_ptr<GameObject>> &world, const GameObject *attacker, const Vector2d &dir)
{
    for (auto &obj : world)
    {
        if (auto *enemy = dynamic_cast<Enemy *>(obj.get()))
        {
            if (enemy->pos.distance(attacker->pos) <= getRange())
            {
                enemy->damage(getDamage());
                std::cout << "Spear frappe " << enemy->getName() << "! HP=" << enemy->getHp() << "\n";
            }
        }
    }
}

void Sword::attack(std::vector<std::unique_ptr<GameObject>> &world, const GameObject *attacker, const Vector2d &dir)
{
    for (auto &obj : world)
    {
        if (auto *enemy = dynamic_cast<Enemy *>(obj.get()))
        {
            if (enemy->pos.distance(attacker->pos) <= getRange())
            {
                enemy->damage(getDamage());
                std::cout << "Sword frappe " << enemy->getName() << "! HP=" << enemy->getHp() << "\n";
            }
        }
    }
}

int main()
{
    Game game;
    game.run();
    return 0;
}
