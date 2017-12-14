//
// Created by Pierre Roy on 30/11/17.
//

#ifndef TSPGENETICALGORITHM_TOUR_HPP
#define TSPGENETICALGORITHM_TOUR_HPP

#include <vector>

namespace TSP
{
    class TSPManager;
    class City;
}

namespace TSP
{

    class Tour {
    private:
        TSPManager* m_manager;
        std::vector<City*> m_destinations;
        double m_fitness;
        int m_distance;

    public:
        explicit Tour(TSPManager* manager);
         Tour(const std::vector<City*>& cities, TSPManager* manager);
        ~Tour();

        int size() const;
        bool contains(City* city) const;

        City* getCity(int position) const;
        void setCity(int position, City* city);

        double getFitness();
        int getDistance();

        City* findClosest(City* current) const;

        void generateShuffle();
        void generateGreedy();

        void print() const;

        const std::vector<City*>& getDestinations() const;
    };

}


#endif //TSPGENETICALGORITHM_TOUR_HPP
