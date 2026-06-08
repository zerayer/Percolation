#ifndef PERCOLATION_STATS_H
#define PERCOLATION_STATS_H

#include <cstddef>
#include <vector>

struct PercolationStats
{
    PercolationStats(std::size_t dimension, std::size_t trials);

    double get_mean() const;
    double get_standard_deviation() const;

    double get_confidence_low() const;
    double get_confidence_high() const;

    void execute();

private:
    std::size_t dimension_;
    std::size_t trials_;

    double mean_;
    double standard_deviation_;
    double confidence_low_;
    double confidence_high_;

    std::vector<double> results_;

    double run_one_experiment();
    void calculate_statistics();
};

#endif
