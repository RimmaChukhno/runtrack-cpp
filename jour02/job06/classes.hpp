#ifndef CLASSES_HPP
#define CLASSES_HPP

#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

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
    std::map<std::string, int> competences;
    std::vector<std::weak_ptr<Pingouin>> amis;
    std::unordered_map<std::string, std::string> journal;
    std::multiset<double> tempsGlisse;
    std::unordered_set<std::string> lieuxPeche;

protected:
    double vitesseGlisse;

public:
    static std::vector<std::shared_ptr<Pingouin>> colony;
    static std::list<std::string> lieuxRencontre;
    static std::unordered_map<std::string, std::vector<std::string>> lieuxPecheMeetup;

    Pingouin(const std::string &nom, double vNage = 8.0, double vMarche = 2.0)
        : Aquatique(vNage), Terrestre(vMarche), nom(nom), vitesseGlisse(5.0)
    {
        auto ptr = std::shared_ptr<Pingouin>(this);
        colony.push_back(ptr);
        // Tri automatique de la colonie par temps de parcours
        std::sort(colony.begin(), colony.end(),
                  [](const std::shared_ptr<Pingouin> &a, const std::shared_ptr<Pingouin> &b)
                  {
                      return a->tempsParcours() < b->tempsParcours();
                  });
    }

    // Copy constructor
    Pingouin(const Pingouin &other)
        : Aquatique(other.vitesseNage),
          Terrestre(other.vitesseMarche),
          nom(other.nom + "_copy"),
          vitesseGlisse(other.vitesseGlisse),
          competences(other.competences),
          journal(other.journal),
          tempsGlisse(other.tempsGlisse),
          lieuxPeche(other.lieuxPeche)
    {
        auto ptr = std::shared_ptr<Pingouin>(this);
        colony.push_back(ptr);
        // Tri automatique
        std::sort(colony.begin(), colony.end(),
                  [](const std::shared_ptr<Pingouin> &a, const std::shared_ptr<Pingouin> &b)
                  {
                      return a->tempsParcours() < b->tempsParcours();
                  });
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

    // Méthodes de base
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

    // Getters et setters
    void setVitesseGlisse(double vitesse) { vitesseGlisse = vitesse; }
    double getVitesseGlisse() const { return vitesseGlisse; }
    std::string getNom() const { return nom; }

    // Méthodes pour les lieux de rencontre
    static void ajouterLieuRencontre(const std::string &lieu)
    {
        lieuxRencontre.push_back(lieu);
    }

    static void retirerLieuRencontre(const std::string &lieu)
    {
        lieuxRencontre.remove(lieu);
    }

    static void afficherLieuxRencontre()
    {
        std::cout << "Lieux de rencontre disponibles :" << std::endl;
        for (const auto &lieu : lieuxRencontre)
        {
            std::cout << "- " << lieu << std::endl;
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
    }

    void supprimerCompetence(const std::string &nom)
    {
        competences.erase(nom);
    }

    void listerCompetences() const
    {
        std::cout << "Compétences de " << nom << ":" << std::endl;
        for (const auto &[comp, niveau] : competences)
        {
            std::cout << "- " << comp << ": niveau " << niveau << std::endl;
        }
    }

    // Gestion des amis
    void ajouterAmi(std::shared_ptr<Pingouin> ami)
    {
        // Vérifier si l'ami n'existe pas déjà
        auto it = std::find_if(amis.begin(), amis.end(),
                               [&ami](const std::weak_ptr<Pingouin> &wp)
                               {
                                   if (auto locked = wp.lock())
                                   {
                                       return locked == ami;
                                   }
                                   return false;
                               });
        if (it == amis.end())
        {
            amis.push_back(std::weak_ptr<Pingouin>(ami));
        }
    }

    void retirerAmi(const std::shared_ptr<Pingouin> &ami)
    {
        amis.erase(
            std::remove_if(amis.begin(), amis.end(),
                           [&ami](const std::weak_ptr<Pingouin> &wp)
                           {
                               if (auto locked = wp.lock())
                               {
                                   return locked == ami;
                               }
                               return true; // Supprimer aussi les weak_ptr expirés
                           }),
            amis.end());
    }

    // Gestion du journal
    void ajouterEvenement(const std::string &date, const std::string &description)
    {
        journal[date] = description;
    }

    void listerEvenements() const
    {
        std::cout << "Journal de " << nom << ":" << std::endl;
        for (const auto &[date, desc] : journal)
        {
            std::cout << "- " << date << ": " << desc << std::endl;
        }
    }

    // Gestion des temps de glisse
    void ajouterTempsGlisse(double temps)
    {
        tempsGlisse.insert(temps);
    }

    void afficherTempsGlisse() const
    {
        std::cout << "Temps de glisse de " << nom << ":" << std::endl;
        for (double temps : tempsGlisse)
        {
            std::cout << "- " << temps << " secondes" << std::endl;
        }
    }

    // Gestion des lieux de pêche
    void ajouterLieuPeche(const std::string &lieu)
    {
        lieuxPeche.insert(lieu);
    }

    void retirerLieuPeche(const std::string &lieu)
    {
        lieuxPeche.erase(lieu);
    }

    // Treasure Hunt
    static void ajouterLieuPecheMeetup(const std::string &meetup, const std::string &lieuPeche)
    {
        lieuxPecheMeetup[meetup].push_back(lieuPeche);
    }

    bool chercherPoisson(const std::string &meetup)
    {
        auto it = lieuxPecheMeetup.find(meetup);
        if (it != lieuxPecheMeetup.end() && !it->second.empty())
        {
            // Simulation d'une chance sur deux de trouver un poisson
            bool trouve = (rand() % 2) == 0;
            if (trouve)
            {
                std::cout << nom << " a trouvé un poisson à " << meetup << "!" << std::endl;
            }
            else
            {
                std::cout << nom << " n'a pas trouvé de poisson à " << meetup << "." << std::endl;
            }
            return trouve;
        }
        std::cout << "Pas de lieu de pêche connu à " << meetup << std::endl;
        return false;
    }

    double tempsParcours() const
    {
        // 15m glisse + 20m marche + 50m nage + 15m marche
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
};

// Initialisation des membres statiques
std::vector<std::shared_ptr<Pingouin>> Pingouin::colony;

#endif // CLASSES_HPP
std::list<std::string> Pingouin::lieuxRencontre;
std::unordered_map<std::string, std::vector<std::string>> Pingouin::lieuxPecheMeetup;