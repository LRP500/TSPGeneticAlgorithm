//
// Created by Pierre Roy on 30/11/17.
//

#ifndef TSPGENETICALGORITHM_TSPMANAGER_HPP
#define TSPGENETICALGORITHM_TSPMANAGER_HPP

#include <vector>
#include <string>
#include "Population.hpp"

// Forward Declarations
namespace TSP
{
    class City;
}

namespace TSP
{
    auto const CITY_COUNT = 1000;

    enum FeedMode {
        Random = 0,
        Greedy
    };
    auto const FEED_MODE = FeedMode::Random;

    class TSPManager {
    private:
        std::vector<TSP::City*> m_cities;
        TSP::Tour* m_greedy;

        static constexpr double mutationRate = 0.005; // default = 0.015
        static const int tournamentSize = 4; // default = 5
        static const bool elitism = true;

    public:
        TSPManager();

        int feed(const std::string& filePath);
        int buildMap(std::ifstream& data);
        int getCityCount() const;
        City* getCity(int index) const;
        const std::vector<TSP::City*>& getMap() const;
        TSP::Tour* getGreedy() const;

        TSP::Population* evolvePopulation(TSP::Population* pop);
        TSP::Tour* crossover(TSP::Tour* a, TSP::Tour* b);
        void mutate(TSP::Tour* tour);
        TSP::Tour* tournamentSelection(TSP::Population* pop);

    private:
        void initialize();
    };

}

#endif //TSPGENETICALGORITHM_TSPMANAGER_HPP
