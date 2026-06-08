#include "Percolation.h"

#include <queue>
#include <stdexcept>
#include <utility>
#include <vector>

Percolation::Percolation(std::size_t dimension)
    : dimension_(dimension),
      open_count_(0),
      grid_(dimension, std::vector<bool>(dimension, false))
{
    if (dimension == 0)
    {
        throw std::invalid_argument("Dimension must be positive");
    }
}

void Percolation::open(std::size_t row, std::size_t column)
{
    if (!is_correct_cell(row, column))
    {
        throw std::out_of_range("Incorrect cell coordinates");
    }

    if (!grid_[row][column])
    {
        grid_[row][column] = true;
        ++open_count_;
    }
}

bool Percolation::is_open(std::size_t row, std::size_t column) const
{
    if (!is_correct_cell(row, column))
    {
        throw std::out_of_range("Incorrect cell coordinates");
    }

    return grid_[row][column];
}

bool Percolation::is_full(std::size_t row, std::size_t column) const
{
    if (!is_correct_cell(row, column))
    {
        throw std::out_of_range("Incorrect cell coordinates");
    }

    if (!grid_[row][column])
    {
        return false;
    }

    std::vector<std::vector<bool>> visited(dimension_, std::vector<bool>(dimension_, false));
    std::queue<std::pair<std::size_t, std::size_t>> queue;

    for (std::size_t col = 0; col < dimension_; ++col)
    {
        if (grid_[0][col])
        {
            queue.push({0, col});
            visited[0][col] = true;
        }
    }

    const int d_row[4] = {-1, 1, 0, 0};
    const int d_col[4] = {0, 0, -1, 1};

    while (!queue.empty())
    {
        const auto current = queue.front();
        queue.pop();

        if (current.first == row && current.second == column)
        {
            return true;
        }

        for (int direction = 0; direction < 4; ++direction)
        {
            const int next_row = static_cast<int>(current.first) + d_row[direction];
            const int next_col = static_cast<int>(current.second) + d_col[direction];

            if (next_row < 0 || next_col < 0)
            {
                continue;
            }

            const std::size_t next_row_size = static_cast<std::size_t>(next_row);
            const std::size_t next_col_size = static_cast<std::size_t>(next_col);

            if (next_row_size >= dimension_ || next_col_size >= dimension_)
            {
                continue;
            }

            if (grid_[next_row_size][next_col_size] && !visited[next_row_size][next_col_size])
            {
                visited[next_row_size][next_col_size] = true;
                queue.push({next_row_size, next_col_size});
            }
        }
    }

    return false;
}

bool Percolation::percolates() const
{
    for (std::size_t col = 0; col < dimension_; ++col)
    {
        if (is_full(dimension_ - 1, col))
        {
            return true;
        }
    }

    return false;
}

std::size_t Percolation::get_dimension() const
{
    return dimension_;
}

std::size_t Percolation::get_open_count() const
{
    return open_count_;
}

bool Percolation::is_correct_cell(std::size_t row, std::size_t column) const
{
    return row < dimension_ && column < dimension_;
}
