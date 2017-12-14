//
// Created by Pierre Roy on 30/11/17.
//

#ifndef TSPGENETICALGORITHM_CITY_HPP
#define TSPGENETICALGORITHM_CITY_HPP

#include <vector>

namespace TSP
{

    class City {
    private:
        std::vector<int> m_costs;
        int m_pos;

    public:
        explicit City(const std::string& costs, int pos);
        ~City();

        int getMatrixPos() const;
        void storeCosts(const std::string& costs);
        int distanceTo(City* city) const;

        const std::vector<int>& getCosts() const;
    };

}

#endif //TSPGENETICALGORITHM_CITY_HPP
