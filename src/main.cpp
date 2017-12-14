#include <iostream>
#include <unistd.h>
#include <fstream>

#include "TSPManager.hpp"
#include "Tour.hpp"
#include "City.hpp"
#include "Timer/Timer.hpp"

#define _isatty isatty
#define _fileno fileno

static const std::function<void(const size_t&)> progress_printer(
        _isatty(_fileno(stdout)) == 1 ? [](const size_t& i) { std::cout << "\rProgress ... " << i << "%" << std::flush; }
                                      : [](const size_t& i)
        {
            static std::ios::off_type last(-1);
            if (last != -1)
                std::cout.seekp(last, std::ios::beg);
            last = std::cout.tellp();
            std::cout << "Number " << i << std::endl;
        }
);

static int usage()
{
    std::cout << "USAGE: ./TSPGeneticAlgorithm FILEPATH" << std::endl;
    return EXIT_FAILURE;
}

int main(int argc, char *argv[])
{
    if (argc < 1)
        return usage();

    TSP::TSPManager manager;

    if (manager.feed(argv[1]))
        return EXIT_FAILURE;

    auto pop = new TSP::Population(10, true, &manager);

    int initial = pop->getFittest()->getDistance();
    std::cout << "Initial distance: " << initial << std::endl;

    System::Timer timer;

    int generations = 1000;
    pop = manager.evolvePopulation(pop);
    for (int i = 0; i < generations; i++)
    {
        pop = manager.evolvePopulation(pop);
        progress_printer(static_cast<const size_t &>((float)(i) / (float)generations * 100));
    }
    std::cout << std::endl;

    int final = pop->getFittest()->getDistance();
    std::cout << "Final distance: " << final << std::endl;

    auto decreased = (float)(initial - final);
    auto percentage = static_cast<float>(decreased / (float)(initial) * 100.0);
    std::cout << "Distance decreased by " << percentage << "% over " << generations << " generations" << std::endl;
    std::cout << "Time elapsed " << timer.elapsed() << std::endl;

    return EXIT_SUCCESS;
}