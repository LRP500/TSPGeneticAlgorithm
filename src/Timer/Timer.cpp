//
// Created by Pierre Roy on 02/12/17.
//

#include "Timer.hpp"

System::Timer::Timer() : m_beg(m_clock::now())
{}

void System::Timer::reset()
{
    m_beg = m_clock::now();
}

double System::Timer::elapsed() const
{
    return std::chrono::duration_cast<m_second>(m_clock::now() - m_beg).count();
}