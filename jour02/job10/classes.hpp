#ifndef CLASSES_HPP
#define CLASSES_HPP

#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_map>

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
    std::map<std::string, int> competences;
    std::set<std::weak_ptr<Pingouin>, std::owner_less<std::weak_ptr<Pingouin>>> amis;
    std::unordered_map<std::string, std::string> journal;
    std::multiset<double> tempsGlisse; // Nouveau: multiset pour les temps de glisse

public:
    static std::vector<std::shared_ptr<Pingouin>> colony;

    Pingouin(const std::string &nom, double vNage = 8.0, double vMarche = 2.0)
        : Aquatique(vNage), Terrestre(vMarche), nom(nom), vitesseGlisse(5.0)
    {
        auto ptr = std::shared_ptr<Pingouin>(this);
        colony.push_back(ptr);
    }

    Pingouin(const Pingouin &other)
        : Aquatique(other.vitesseNage),
          Terrestre(other.vitesseMarche),
          nom(other.nom + "_copy"),
          vitesseGlisse(other.vitesseGlisse),
          competences(other.competences),
          journal(other.journal),
          tempsGlisse(other.tempsGlisse)
    {
        auto ptr = std::shared_ptr<Pingouin>(this);
        colony.push_back(ptr);
    }

    // Gestion des temps de glisse
    void ajouterTempsGlisse(double temps)
    {
        tempsGlisse.insert(temps);
    }

    void supprimerMeilleurTemps()
    {
        if (!tempsGlisse.empty())
        {
            tempsGlisse.erase(tempsGlisse.begin()); // Supprime le plus petit temps
        }
    }

    void supprimerPireTemps()
    {
        if (!tempsGlisse.empty())
        {
            auto it = tempsGlisse.end();
            --it; // Point vers le dernier élément
            tempsGlisse.erase(it);
        }
    }

    void afficherTempsGlisse() const
    {
        std::cout << "Temps de glisse de " << nom << " (en secondes):" << std::endl;
        for (double temps : tempsGlisse)
        {
            std::cout << "- " << temps << std::endl;
        }
    }

    double getMeilleurTemps() const
    {
        if (!tempsGlisse.empty())
        {
            return *tempsGlisse.begin();
        }
        return 0.0;
    }

    double getPireTemps() const
    {
        if (!tempsGlisse.empty())
        {
            return *tempsGlisse.rbegin();
        }
        return 0.0;
    }

    double getMoyenneTemps() const
    {
        if (tempsGlisse.empty())
            return 0.0;
        double somme = 0.0;
        for (double temps : tempsGlisse)
        {
            somme += temps;
        }
        return somme / tempsGlisse.size();
    }

    // Autres méthodes existantes...
    void ajouterEvenement(const std::string &date, const std::string &description)
    {
        journal[date] = description;
    }

    void afficherJournal() const
    {
        std::cout << "Journal de " << nom << ":" << std::endl;
        for (const auto &[date, description] : journal)
        {
            std::cout << date << ": " << description << std::endl;
        }
    }

    void ajouterAmi(const std::shared_ptr<Pingouin> &ami)
    {
        amis.insert(std::weak_ptr<Pingouin>(ami));
    }

    void listerAmis() const
    {
        std::cout << "Amis de " << nom << ":" << std::endl;
        for (const auto &weak_ami : amis)
        {
            if (auto ami = weak_ami.lock())
            {
                std::cout << "- " << ami->getNom() << std::endl;
            }
        }
    }

    void ajouterCompetence(const std::string &nom, int niveau)
    {
        competences[nom] = niveau;
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
};

std::vector<std::shared_ptr<Pingouin>> Pingouin::colony;

#endif