#include "PercolationStats.h"

#include <cstdlib>
#include <iomanip>
#include <iostream>

int main(int argc, char* argv[])
{
    std::size_t dimension = 20;
    std::size_t trials = 50;

    if (argc >= 3)
    {
        dimension = static_cast<std::size_t>(std::stoul(argv[1]));
        trials = static_cast<std::size_t>(std::stoul(argv[2]));
    }

    try
    {
        PercolationStats stats(dimension, trials);
        stats.execute();

        std::cout << std::fixed << std::setprecision(6);
        std::cout << "dimension = " << dimension << '\n';
        std::cout << "trials = " << trials << '\n';
        std::cout << "mean = " << stats.get_mean() << '\n';
        std::cout << "standard deviation = " << stats.get_standard_deviation() << '\n';
        std::cout << "95% confidence interval = ["
                  << stats.get_confidence_low() << ", "
                  << stats.get_confidence_high() << "]\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
