#ifndef PERCOLATION_H
#define PERCOLATION_H

#include <cstddef>
#include <vector>

class Percolation
{
public:
    explicit Percolation(std::size_t dimension);

    void open(std::size_t row, std::size_t column);

    bool is_open(std::size_t row, std::size_t column) const;
    bool is_full(std::size_t row, std::size_t column) const;
    bool percolates() const;

    std::size_t get_dimension() const;
    std::size_t get_open_count() const;

private:
    std::size_t dimension_;
    std::size_t open_count_;
    std::vector<std::vector<bool>> grid_;

    bool is_correct_cell(std::size_t row, std::size_t column) const;
};

#endif
