#include "s21_batch_data.h"

#include <algorithm>
#include <random>

using namespace s21;

void BatchData::ShuffleData() {
    std::random_device r;
    std::mt19937 engine(r());
    std::shuffle(indices_.begin(), indices_.end(), engine);
}
