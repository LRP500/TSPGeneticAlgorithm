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
        _isatty(_fileno(stdout)) == 1 ? [](const size_t& i) { std::cout << "\rProgress ... " << i << "s" << std::flush; }
                                      : [](const size_t& i)
        {
            static std::ios::off_type last(-1);
            if (last != -1)
                std::cout.seekp(last, std::ios::beg);
            last = std::cout.tellp();
            std::cout << "Number " << i << std::endl;
        }
);

static void writeToFile(TSP::Tour* result, const std::string& filePath)
{
    std::ofstream file;
    try
    {
        file.open(filePath);
    }
    catch (const std::ofstream::failure& e)
    {
        std::cout << e.what() << std::endl;
        return ;
    }

    file << "1\n";
    for (int i = 1; i < result->size(); ++i)
    {
        file << result->getDestinations()[i - 1]->distanceTo(result->getDestinations()[i]) << std::endl;
    }
    file << "1\n";
    file.close();
}

static int usage()
{
    std::cout << "USAGE: ./TSPGeneticAlgorithm FILEPATH" << std::endl;
    return EXIT_FAILURE;
}

int main()
{
    TSP::TSPManager manager;

    if (manager.feed("../tsp_exp.txt"))
        return EXIT_FAILURE;

    auto pop = new TSP::Population(10, true, &manager);

    int initial = pop->getFittest()->getDistance();
    std::cout << "Initial distance: " << initial << std::endl;

    System::Timer timer;

    int generations = 1;
    pop = manager.evolvePopulation(pop);
    for (int i = 0; timer.elapsed() < 29.0; i++)
    {
        pop = manager.evolvePopulation(pop);
        progress_printer(static_cast<const size_t &>(timer.elapsed()));
        ++generations;
    }
    std::cout << std::endl;

    int final = pop->getFittest()->getDistance();
    std::cout << "Final distance: " << final << std::endl;

    auto decreased = (float)(initial - final);
    auto percentage = static_cast<float>(decreased / (float)(initial) * 100.0);
    std::cout << "Distance decreased by " << percentage << "% over " << generations << " generations" << std::endl;
    std::cout << "Time elapsed " << timer.elapsed() << std::endl;

    writeToFile(pop->getFittest(), "../output");

    return EXIT_SUCCESS;
}