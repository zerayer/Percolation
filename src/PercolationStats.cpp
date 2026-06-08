#include "PercolationStats.h"

#include "Percolation.h"

#include <algorithm>
#include <cmath>
#include <numeric>
#include <random>
#include <stdexcept>
#include <vector>

PercolationStats::PercolationStats(std::size_t dimension, std::size_t trials)
    : dimension_(dimension),
      trials_(trials),
      mean_(0.0),
      standard_deviation_(0.0),
      confidence_low_(0.0),
      confidence_high_(0.0)
{
    if (dimension == 0)
    {
        throw std::invalid_argument("Dimension must be positive");
    }

    if (trials == 0)
    {
        throw std::invalid_argument("Amount of trials must be positive");
    }
}

double PercolationStats::get_mean() const
{
    return mean_;
}

double PercolationStats::get_standard_deviation() const
{
    return standard_deviation_;
}

double PercolationStats::get_confidence_low() const
{
    return confidence_low_;
}

double PercolationStats::get_confidence_high() const
{
    return confidence_high_;
}

void PercolationStats::execute()
{
    results_.clear();
    results_.reserve(trials_);

    for (std::size_t trial = 0; trial < trials_; ++trial)
    {
        results_.push_back(run_one_experiment());
    }

    calculate_statistics();
}

double PercolationStats::run_one_experiment()
{
    Percolation percolation(dimension_);

    std::vector<std::size_t> cells(dimension_ * dimension_);
    std::iota(cells.begin(), cells.end(), 0);

    static std::mt19937 generator(std::random_device{}());
    std::shuffle(cells.begin(), cells.end(), generator);

    std::size_t index = 0;

    while (!percolation.percolates() && index < cells.size())
    {
        const std::size_t cell_number = cells[index];
        const std::size_t row = cell_number / dimension_;
        const std::size_t column = cell_number % dimension_;

        percolation.open(row, column);
        ++index;
    }

    return static_cast<double>(percolation.get_open_count()) /
           static_cast<double>(dimension_ * dimension_);
}

void PercolationStats::calculate_statistics()
{
    const double sum = std::accumulate(results_.begin(), results_.end(), 0.0);
    mean_ = sum / static_cast<double>(trials_);

    if (trials_ == 1)
    {
        standard_deviation_ = 0.0;
    }
    else
    {
        double squared_sum = 0.0;

        for (double value : results_)
        {
            squared_sum += (value - mean_) * (value - mean_);
        }

        standard_deviation_ = std::sqrt(squared_sum / static_cast<double>(trials_ - 1));
    }

    const double delta = 1.96 * standard_deviation_ / std::sqrt(static_cast<double>(trials_));
    confidence_low_ = mean_ - delta;
    confidence_high_ = mean_ + delta;
}
