//
// Created by Anton Ivanov on 27.04.2023.
//

#include "s21_matrix.h"

std::string Matrix::description() const {

  return description(" ");
}

std::string Matrix::description(const std::string& separator) const {

  auto description = std::string("[[");
  auto _separator = "]," + separator + "[";
  auto terminator = "]]";

  auto end_m = _m - 1;
  auto end_n = _n - 1;

  for (auto i(0); i < _m; i += 1) {
    for (auto j(0); j < _n; j += 1) {
      
      description += std::to_string(_data[i * _n + j]);
      description += j != end_n ? ", " : "";
    }

    description += i != end_m ? _separator : terminator;
  }

  return description;
}
