//
// Created by Pierre Roy on 02/12/17.
//

#ifndef TSPGENETICALGORITHM_TIMER_HPP
#define TSPGENETICALGORITHM_TIMER_HPP

#include <iostream>
#include <chrono>

namespace System
{

    class Timer {
    private:
        typedef std::chrono::high_resolution_clock m_clock;
        typedef std::chrono::duration<double, std::ratio<1>> m_second;
        std::chrono::time_point<m_clock> m_beg;

    public:
        Timer();

        void reset();

        double elapsed() const;
    };

}


#endif //TSPGENETICALGORITHM_TIMER_HPP
