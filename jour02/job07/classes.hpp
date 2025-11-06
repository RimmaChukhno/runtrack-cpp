#ifndef CLASSES_HPP
#define CLASSES_HPP

#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <map>

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
    std::map<std::string, int> competences; // Map des compétences

public:
    static std::vector<std::shared_ptr<Pingouin>> colony;

    Pingouin(const std::string &nom, double vNage = 8.0, double vMarche = 2.0)
        : Aquatique(vNage), Terrestre(vMarche), nom(nom), vitesseGlisse(5.0)
    {
        auto ptr = std::shared_ptr<Pingouin>(this);
        colony.push_back(ptr);
        // Ajout de compétences par défaut
        competences["Nage"] = static_cast<int>(vNage);
        competences["Marche"] = static_cast<int>(vMarche);
    }

    Pingouin(const Pingouin &other)
        : Aquatique(other.vitesseNage),
          Terrestre(other.vitesseMarche),
          nom(other.nom + "_copy"),
          vitesseGlisse(other.vitesseGlisse),
          competences(other.competences)
    { // Copie des compétences
        auto ptr = std::shared_ptr<Pingouin>(this);
        colony.push_back(ptr);
    }

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

    // Gestion des compétences
    void ajouterCompetence(const std::string &nom, int niveau)
    {
        competences[nom] = niveau;
    }

    void modifierCompetence(const std::string &nom, int nouveauNiveau)
    {
        if (competences.find(nom) != competences.end())
        {
            competences[nom] = nouveauNiveau;
        }
        else
        {
            std::cout << "Compétence " << nom << " non trouvée!" << std::endl;
        }
    }

    void supprimerCompetence(const std::string &nom)
    {
        if (competences.find(nom) != competences.end())
        {
            competences.erase(nom);
        }
        else
        {
            std::cout << "Compétence " << nom << " non trouvée!" << std::endl;
        }
    }

    void listerCompetences() const
    {
        std::cout << "Compétences de " << nom << ":" << std::endl;
        for (const auto &[comp, niveau] : competences)
        {
            std::cout << "- " << comp << ": niveau " << niveau << std::endl;
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

    double tempsParcours() const
    {
        return (15.0 / vitesseGlisse) + (20.0 / vitesseMarche) +
               (50.0 / vitesseNage) + (15.0 / vitesseMarche);
    }

    static void afficherTemps()
    {
        for (const auto &p : colony)
        {
            std::cout << p->getNom() << ": " << p->tempsParcours() << " secondes" << std::endl;
        }
    }

    static void afficherColonie()
    {
        std::cout << "Colonie de pingouins (" << colony.size() << " membres):" << std::endl;
        for (const auto &p : colony)
        {
            p->sePresenter();
        }
    }
};

std::vector<std::shared_ptr<Pingouin>> Pingouin::colony;

#endif