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
    std::unordered_set<std::string> lieuxPeche; // Nouveau: unordered_set pour les lieux de pêche

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
          tempsGlisse(other.tempsGlisse),
          lieuxPeche(other.lieuxPeche)
    {
        auto ptr = std::shared_ptr<Pingouin>(this);
        colony.push_back(ptr);
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

    bool connaitLieuPeche(const std::string &lieu) const
    {
        return lieuxPeche.find(lieu) != lieuxPeche.end();
    }

    void afficherLieuxPeche() const
    {
        std::cout << "Lieux de pêche connus par " << nom << ":" << std::endl;
        for (const auto &lieu : lieuxPeche)
        {
            std::cout << "- " << lieu << std::endl;
        }
    }

    size_t getNombreLieuxPeche() const
    {
        return lieuxPeche.size();
    }

    // Autres méthodes existantes...
    void ajouterTempsGlisse(double temps)
    {
        tempsGlisse.insert(temps);
    }

    void afficherTempsGlisse() const
    {
        std::cout << "Temps de glisse de " << nom << " (en secondes):" << std::endl;
        for (double temps : tempsGlisse)
        {
            std::cout << "- " << temps << std::endl;
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