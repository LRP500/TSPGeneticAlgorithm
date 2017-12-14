//
// Created by Pierre Roy on 30/11/17.
//

#include <iostream>
#include <sstream>

#include "City.hpp"
#include "TSPManager.hpp"

TSP::City::City(const std::string &costs, int pos)
        : m_pos(pos)
{
    m_costs.reserve(TSP::CITY_COUNT);
    storeCosts(costs);
}

TSP::City::~City()
{
    m_costs.clear();
    m_costs.shrink_to_fit();
}

int TSP::City::getMatrixPos() const
{
    return m_pos;
}

void TSP::City::storeCosts(const std::string& costs)
{
    std::stringstream ss(costs);
    std::string item;
    while (std::getline(ss, item, ','))
    {
        m_costs.emplace_back(std::stoi(item));
    }
}

int TSP::City::distanceTo(TSP::City *city) const
{
    return m_costs[city->getMatrixPos()];
}

const std::vector<int> &TSP::City::getCosts() const
{
    return m_costs;
}
