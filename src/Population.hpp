//
// Created by Pierre Roy on 01/12/17.
//

#ifndef TSPGENETICALGORITHM_POPULATION_HPP
#define TSPGENETICALGORITHM_POPULATION_HPP

#include <vector>

// Forward Declarations
namespace TSP
{
    class Tour;
    class TSPManager;
}

namespace TSP
{

    class Population {
    private:
        std::vector<TSP::Tour*> m_tours;

    public:
        Population(int size,
                   bool initialize,
                   TSPManager* manager);
        ~Population() = default;

        void saveTour(int index, Tour* tour);
        Tour* getTour(int index) const;

        int size() const;

        Tour* getFittest() const;
    };

}

#endif //TSPGENETICALGORITHM_POPULATION_HPP
