//
// Created by Pierre Roy on 30/11/17.
//

#include <iostream>
#include <random>

#include "Tour.hpp"
#include "City.hpp"
#include "TSPManager.hpp"

TSP::Tour::Tour(TSP::TSPManager* manager) : m_manager(manager), m_fitness(0), m_distance(0)
{
    m_destinations.reserve(TSP::CITY_COUNT);
    m_destinations = std::vector<City*>(TSP::CITY_COUNT, nullptr);
}

TSP::Tour::Tour(const std::vector<TSP::City *>& cities, TSP::TSPManager* manager)
        : m_destinations(cities), m_fitness(0), m_distance(0)
{}

TSP::Tour::~Tour()
{
    m_destinations.clear();
    m_destinations.shrink_to_fit();
    delete m_manager;
}

int TSP::Tour::size() const
{
    return static_cast<int>(m_destinations.size());
}

TSP::City *TSP::Tour::getCity(int position) const
{
    return (position < m_destinations.size()) ? m_destinations[position] : nullptr;
}

void TSP::Tour::setCity(int position, TSP::City *city)
{
    m_destinations[position] = city;
    m_fitness = 0;
    m_distance = 0;
}

double TSP::Tour::getFitness()
{
    if (!m_fitness)
        m_fitness = 1 / (double) getDistance();
    return m_fitness;
}

int TSP::Tour::getDistance()
{
    if (!m_distance)
    {
        int tourDistance = 0;
        for (int i = 0; i < m_destinations.size(); ++i)
        {
            City *from = getCity(i);
            City *dest = (i + 1 < m_destinations.size()) ? getCity(i + 1) : getCity(0);
            tourDistance += from->distanceTo(dest);
        }
        m_distance = tourDistance;
    }
    return m_distance;
}

bool TSP::Tour::contains(TSP::City *city) const
{
    return (std::find(m_destinations.begin(), m_destinations.end(), city) != m_destinations.end());
}

void TSP::Tour::generateShuffle()
{
    for (int i = 0; i < TSP::CITY_COUNT; ++i)
    {
        setCity(i, m_manager->getCity(i));
    }
    unsigned int seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
    std::shuffle(m_destinations.begin(), m_destinations.end(), std::default_random_engine(seed));
}

TSP::City* TSP::Tour::findClosest(TSP::City* current) const
{
    int smallest = INT_MAX;
    TSP::City* closest = nullptr;
    for (int i = 1; i < current->getCosts().size(); ++i)
    {
        if ((current->getCosts()[i] == 0))
            continue ;
        if (current->getCosts()[i] <= smallest)
        {
            if (!this->contains(m_manager->getCity(i)))
            {
                closest = m_manager->getCity(i);
                smallest = current->getCosts()[i];
            }
        }
    }
    return closest;
}

void TSP::Tour::generateGreedy()
{
    this->setCity(0, m_manager->getCity(0));
    for (int i = 1; i < TSP::CITY_COUNT; ++i)
    {
        TSP::City* closest = findClosest(this->getCity(i - 1));
        this->setCity(i, closest);
    }
}

void TSP::Tour::print() const
{
    std::cout << 0 << std::endl;
    for (int i = 0; i < m_destinations.size(); ++i)
    {
        City* a = getCity(i);
        City *b = (i + 1 < m_destinations.size()) ? getCity(i + 1) : getCity(0);
        std::cout << a->getMatrixPos() << " - " << a->distanceTo(b) << std::endl;
    }
    std::cout << 0 << std::endl;
}

const std::vector<TSP::City *>& TSP::Tour::getDestinations() const
{
    return m_destinations;
}
