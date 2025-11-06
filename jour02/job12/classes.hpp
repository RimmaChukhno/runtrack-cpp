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
#include <unordered_set>
#include <random>

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
    std::multiset<double> tempsGlisse;
    std::unordered_set<std::string> lieuxPeche;

    static std::random_device rd;
    static std::mt19937 gen;

public:
    static std::vector<std::shared_ptr<Pingouin>> colony;
    static std::unordered_map<std::string, std::vector<std::string>> lieuxPecheMeetup;

    Pingouin(const std::string &nom, double vNage = 8.0, double vMarche = 2.0)
        : Aquatique(vNage), Terrestre(vMarche), nom(nom), vitesseGlisse(5.0)
    {
        auto ptr = std::shared_ptr<Pingouin>(this);
        colony.push_back(ptr);
    }

    // Méthodes de gestion des lieux de pêche par meetup (statiques)
    static void ajouterLieuPecheMeetup(const std::string &meetup, const std::string &lieuPeche)
    {
        lieuxPecheMeetup[meetup].push_back(lieuPeche);
    }

    static void retirerLieuPecheMeetup(const std::string &meetup, const std::string &lieuPeche)
    {
        auto it = lieuxPecheMeetup.find(meetup);
        if (it != lieuxPecheMeetup.end())
        {
            auto &lieux = it->second;
            lieux.erase(std::remove(lieux.begin(), lieux.end(), lieuPeche), lieux.end());
            if (lieux.empty())
            {
                lieuxPecheMeetup.erase(it);
            }
        }
    }

    static void afficherTousLieuxPecheMeetup()
    {
        std::cout << "Lieux de pêche par point de rencontre:" << std::endl;
        for (const auto &[meetup, lieux] : lieuxPecheMeetup)
        {
            std::cout << meetup << ":" << std::endl;
            for (const auto &lieu : lieux)
            {
                std::cout << "  - " << lieu << std::endl;
            }
        }
    }

    // Méthode pour chercher des poissons à un meetup
    bool chercherPoisson(const std::string &meetup)
    {
        auto it = lieuxPecheMeetup.find(meetup);
        if (it != lieuxPecheMeetup.end() && !it->second.empty())
        {
            std::uniform_int_distribution<> dis(0, it->second.size() - 1);
            int index = dis(gen);
            std::string lieuPeche = it->second[index];

            // 50% de chance de trouver un poisson
            std::uniform_int_distribution<> chance(0, 1);
            bool trouve = chance(gen) == 1;

            // Journaliser l'événement
            std::string resultat = trouve ? "a trouvé" : "n'a pas trouvé";
            ajouterEvenement("Pêche",
                             "Exploration de " + lieuPeche + " depuis " + meetup + ": " + resultat + " de poisson");

            std::cout << nom << " " << resultat << " de poisson à " << lieuPeche
                      << " (depuis " << meetup << ")" << std::endl;

            if (trouve)
            {
                lieuxPeche.insert(lieuPeche); // Mémoriser le lieu de pêche fructueux
            }

            return trouve;
        }

        std::cout << "Aucun lieu de pêche connu à " << meetup << std::endl;
        return false;
    }

    // Méthodes existantes...
    void ajouterLieuPeche(const std::string &lieu)
    {
        lieuxPeche.insert(lieu);
    }

    void afficherLieuxPeche() const
    {
        std::cout << "Lieux de pêche connus par " << nom << ":" << std::endl;
        for (const auto &lieu : lieuxPeche)
        {
            std::cout << "- " << lieu << std::endl;
        }
    }

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

    void nage() override
    {
        std::cout << nom << " nage à " << vitesseNage << " m/s" << std::endl;
    }

    void marche() override
    {
        std::cout << nom << " marche à " << vitesseMarche << " m/s" << std::endl;
    }

    std::string getNom() const { return nom; }
};

// Initialisation des membres statiques
std::vector<std::shared_ptr<Pingouin>> Pingouin::colony;
std::unordered_map<std::string, std::vector<std::string>> Pingouin::lieuxPecheMeetup;
std::random_device Pingouin::rd;
std::mt19937 Pingouin::gen(Pingouin::rd());

#endif