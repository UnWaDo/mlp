//
// Created by Anton Ivanov on 27.04.2023.
//

#include "s21_matrix.h"

Matrix Matrix::parse(std::string data) {

  if (data.empty()) {
    throw "empty";
  }

  for (auto i(0); data[i] != '\0'; i += 1) {

    auto c = data[i];
    if (std::isdigit(c) || c == ' ' || c == ',' || c == '[' || c == ']' || c == '\n' || c == '-') {

      continue;
    }

    throw "is not digit";
  }

  auto numberOfM = -1;
  auto numberOfN = 1;

  auto i = 0;
  while (data[i] != '\0') {
    if (data[i] == ']') {
      numberOfM += 1;
    }
    i += 1;
  }

  i = 0;
  while (data[i] != ']') {
    if (data[i] == ',') {
      numberOfN += 1;
    }
    i += 1;
  }

  auto m = numberOfM;
  auto n = numberOfN;
  auto dataMatrix = new float[m * n];

  data.erase(0, data.find_first_not_of(" [\n"));
  data.erase(data.find_last_not_of(" ]\n") + 1);

  i = 0;
  auto j = 0;
  size_t pos = 0;
  size_t npos = 0;
  std::string string;
  std::string strinONE;
  while ((npos = data.find('[')) != std::string::npos) {
    string = data.substr(0, npos);

    j = 0;
    while ((pos = string.find(',')) != std::string::npos) {
      strinONE = string.substr(0, pos);

      strinONE.erase(0, strinONE.find_first_not_of(", [\n"));
      strinONE.erase(strinONE.find_last_not_of(", ]\n") + 1);

      dataMatrix[i * n + j] = std::stof(strinONE);

      string.erase(0, pos + 1);
      j += 1;
    }

    string.erase(0, string.find_first_not_of(" [\n"));
    string.erase(string.find_last_not_of(" ]\n") + 1);

    data.erase(0, npos + 1);
    i += 1;
  }

  string = data.substr(0, npos);
  j = 0;
  while ((pos = string.find(',')) != std::string::npos) {
    strinONE = string.substr(0, pos);

    strinONE.erase(0, strinONE.find_first_not_of(", [\n"));
    strinONE.erase(strinONE.find_last_not_of(", ]\n") + 1);

    dataMatrix[i * n + j] = std::stof(strinONE);

    string.erase(0, pos + 1);
    j += 1;
  }

  strinONE = string.substr(0, pos);

  strinONE.erase(0, strinONE.find_first_not_of(", [\n"));
  strinONE.erase(strinONE.find_last_not_of(", ]\n") + 1);

  dataMatrix[i * n + j] = std::stof(strinONE);

  return {m, n, dataMatrix};
}
