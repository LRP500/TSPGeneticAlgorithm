//
// Created by Pierre Roy on 01/12/17.
//

#include <iostream>

#include "Tour.hpp"
#include "Population.hpp"
#include "TSPManager.hpp"

TSP::Population::Population(int size, bool initialize, TSPManager* manager)
{
    m_tours.reserve(size);
    m_tours = std::vector<Tour*>(size, nullptr);

    if (initialize)
    {
        for (int index = 0; index < m_tours.size(); ++index)
        {
            Tour* t;
            if (TSP::FEED_MODE == TSP::FeedMode::Greedy)
            {
                t = new TSP::Tour(manager->getGreedy()->getDestinations(), manager);
            }
            else
            {
                t = new TSP::Tour(manager);
                t->generateShuffle();
            }
            saveTour(index, t);
        }
    }
}

void TSP::Population::saveTour(int index, TSP::Tour *tour)
{
    m_tours[index] = tour;
}

TSP::Tour* TSP::Population::getTour(int index) const
{
    return (index < m_tours.size()) ? m_tours[index] : nullptr;
}

int TSP::Population::size() const
{
    return static_cast<int>(m_tours.size());
}

TSP::Tour *TSP::Population::getFittest() const
{
    Tour* fittest = m_tours[0];

    for (int index = 0; index < m_tours.size() ; ++index)
    {
        if (fittest->getFitness() <= getTour(index)->getFitness())
            fittest = getTour(index);
    }
    return fittest;
}
