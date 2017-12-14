//
// Created by Pierre Roy on 30/11/17.
//

#include <iostream>
#include <fstream>

#include "TSPManager.hpp"
#include "City.hpp"
#include "Tour.hpp"

#include "utils/utils.h"

using System::randd;

TSP::TSPManager::TSPManager()
{
    std::srand(time(nullptr));
    m_cities.reserve(TSP::CITY_COUNT);
}

void TSP::TSPManager::initialize()
{
    m_greedy = new Tour(this);
    if (TSP::FEED_MODE == TSP::FeedMode::Greedy)
        m_greedy->generateGreedy();
}

int TSP::TSPManager::feed(const std::string& filePath)
{
    std::ifstream file;
    try
    {
        std::cout << "[Reading Input File... ";
        file.open(filePath);
        std::cout << "OK";
    }
    catch (const std::ifstream::failure& e)
    {
        std::cout << e.what() << std::endl;
        return -1;
    }
    std::cout << "]" << std::endl;

    buildMap(file);
    file.close();

    initialize();

    return 0;
}

int TSP::TSPManager::buildMap(std::ifstream& data)
{
    std::cout << "[Building Map... ";

    std::string line;
    int index = 0;
    while (std::getline(data, line))
    {
        m_cities.emplace_back(new City(line, index));
        ++index;
    }
    std::cout << "OK";
    std::cout << "]" << std::endl;
    std::cout << "\nCities Found: " << m_cities.size() << std::endl;

    return 0;
}

int TSP::TSPManager::getCityCount() const
{
    return static_cast<int>(m_cities.size());
}

TSP::City *TSP::TSPManager::getCity(int index) const
{
    return (index < m_cities.size()) ? m_cities[index] : nullptr;
}

TSP::Population *TSP::TSPManager::evolvePopulation(TSP::Population *pop)
{
    auto newPop = new Population(pop->size(), false, this);

    int elitismOffset = 0;
    if (elitism)
    {
        newPop->saveTour(0, pop->getFittest());
        elitismOffset = 1;
    }

    for (int i = elitismOffset; i < newPop->size(); i++)
    {
        Tour* parent1 = tournamentSelection(pop);
        Tour* parent2 = tournamentSelection(pop);
        Tour* child = crossover(parent1, parent2);
        newPop->saveTour(i, child);
    }

    // Mutate the new population a bit to add some new genetic material
    for (int i = elitismOffset; i < newPop->size(); i++)
    {
        mutate(newPop->getTour(i));
    }

    return newPop;
}

TSP::Tour *TSP::TSPManager::crossover(TSP::Tour *first, TSP::Tour *second)
{
    TSP::Tour* child = new Tour(this);

    int startPos = (int) (System::randd() * TSP::CITY_COUNT);
    int endPos = (int) (System::randd() * TSP::CITY_COUNT);

    for (int i = 0; i < TSP::CITY_COUNT; ++i)
    {
        if (startPos < endPos && i > startPos && i < endPos)
        {
            child->setCity(i, first->getCity(i));
        }
        else if (startPos > endPos)
        {
            if (!(i < startPos && i > endPos))
            {
                child->setCity(i, first->getCity(i));
            }
        }
    }

    for (int i = 0; i < TSP::CITY_COUNT; ++i)
    {
        if (!child->contains(second->getCity(i)))
        {
            for (int y = 0; y < TSP::CITY_COUNT; ++y)
            {
                if (child->getCity(y) == nullptr)
                {
                    child->setCity(y, second->getCity(i));
                    break;
                }
            }
        }
    }
    return child;
}

// Mutate a tour using swap
void TSP::TSPManager::mutate(TSP::Tour *tour)
{
    for (int start = 0; start < tour->size(); start++)
    {
        if (randd() < mutationRate)
        {
            // Get a second random position in the tour
            int end = static_cast<int>(tour->size() * randd());

            // Get the cities at target position in tour
            City* city1 = tour->getCity(start);
            City* city2 = tour->getCity(end);

            // Swap them around
            tour->setCity(start, city2);
            tour->setCity(end, city1);
        }
    }
}

TSP::Tour *TSP::TSPManager::tournamentSelection(TSP::Population *pop)
{
    auto tournament = new Population(tournamentSize, false, this);
    for (int index = 0; index < tournamentSize; index++)
    {
        int randomId = static_cast<int>(System::randd() * pop->size());
        tournament->saveTour(index, pop->getTour(randomId));
    }
    Tour* fittest = tournament->getFittest();
    return fittest;
}

const std::vector<TSP::City*> &TSP::TSPManager::getMap() const
{
    return m_cities;
}

TSP::Tour *TSP::TSPManager::getGreedy() const
{
    return m_greedy;
}
