#ifndef CLASSES_HPP
#define CLASSES_HPP

#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

class Aquatique
{
protected:
    double vitesseNage;

public:
    Aquatique(double vitesse = 0.0) : vitesseNage(vitesse) {}
    virtual void nage() = 0;
    double getVitesseNage() const { return vitesseNage; }
    void setVitesseNage(double vitesse) { vitesseNage = vitesse; }
};

class Terrestre
{
protected:
    double vitesseMarche;

public:
    Terrestre(double vitesse = 0.0) : vitesseMarche(vitesse) {}
    virtual void marche() = 0;
    double getVitesseMarche() const { return vitesseMarche; }
    void setVitesseMarche(double vitesse) { vitesseMarche = vitesse; }
};

class Pingouin : public Aquatique, public Terrestre
{
private:
    std::string nom;
    double vitesseGlisse;

public:
    // Vector statique pour la colonie
    static std::vector<std::shared_ptr<Pingouin>> colony;

    Pingouin(const std::string &nom, double vNage = 8.0, double vMarche = 2.0)
        : Aquatique(vNage), Terrestre(vMarche), nom(nom), vitesseGlisse(5.0)
    {
        auto ptr = std::shared_ptr<Pingouin>(this);
        colony.push_back(ptr);
    }

    // Copy constructor
    Pingouin(const Pingouin &other)
        : Aquatique(other.vitesseNage),
          Terrestre(other.vitesseMarche),
          nom(other.nom + "_copy"),
          vitesseGlisse(other.vitesseGlisse)
    {
        auto ptr = std::shared_ptr<Pingouin>(this);
        colony.push_back(ptr);
    }

    // Destructeur pour retirer le pingouin de la colonie
    ~Pingouin()
    {
        auto it = std::find_if(colony.begin(), colony.end(),
                               [this](const std::shared_ptr<Pingouin> &p)
                               { return p.get() == this; });
        if (it != colony.end())
        {
            colony.erase(it);
        }
    }

    void nage() override
    {
        std::cout << nom << " nage à " << vitesseNage << " m/s" << std::endl;
    }

    void marche() override
    {
        std::cout << nom << " marche à " << vitesseMarche << " m/s" << std::endl;
    }

    void sePresenter() const
    {
        std::cout << "Je suis " << nom << ", un pingouin qui nage à "
                  << vitesseNage << " m/s et marche à "
                  << vitesseMarche << " m/s!" << std::endl;
    }

    void setVitesseGlisse(double vitesse) { vitesseGlisse = vitesse; }
    double getVitesseGlisse() const { return vitesseGlisse; }
    std::string getNom() const { return nom; }

    // Méthode statique pour afficher la colonie
    static void afficherColonie()
    {
        std::cout << "Colonie de pingouins (" << colony.size() << " membres):" << std::endl;
        for (const auto &p : colony)
        {
            p->sePresenter();
        }
    }
};

// Initialisation du vector statique
std::vector<std::shared_ptr<Pingouin>> Pingouin::colony;

#endif