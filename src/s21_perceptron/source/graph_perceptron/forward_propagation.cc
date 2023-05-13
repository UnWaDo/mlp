//
// Created by Anton Ivanov on 29.04.2023.
//

#include "s21_graph_perceptron.h"
#include "s21_utils.h"
#include <cmath>

Matrix GraphPerceptron::ForwardPropagation(const Matrix& x) {

  input_layer(x);

  for (auto index(0); index < _number_of_hidden_layers - 1; index += 1) {

    auto m = layers_[index].size;
    auto n = layers_[index + 1].size;

    for (auto i(0); i < m; i += 1) {

      for (auto j(0); j < n; j += 1) {

        auto weight = layers_[index].neurons[i].weight[i];
        auto bias = layers_[index].neurons[i].bias[i];
        layers_[index + 1].neurons[n].t = layers_[index].neurons[i].h * weight + bias;
      }
    }

    for (auto i(0); i < n; i += 1) {

      auto t = layers_[index + 1].neurons[i].t;
      layers_[index + 1].neurons[i].h = 1 / (1 + exp(-t));
    }
  }

  auto layer = layers_->get_last_layer();
  auto m = layer->size;
  auto last_layer = _number_of_layers - 1;
  auto n = _number_of_neurons_in_layers[last_layer];
  auto z_data = new float[n];

  for (auto i(0); i < m; i += 1) {
    for (auto j(0); j < n; j += 1) {
      auto weight = layer->neurons[i].weight[i];
      auto bias = layer->neurons[i].bias[i];
      z_data[j] = layer->neurons[j].h * weight + bias;
    }
  }

  for (auto i(0); i < n; i += 1) {
    auto t = layers_[last_layer - 1].neurons[i].t;
    layers_[last_layer - 1].neurons[i].h = 1 / (1 + exp(-t));
  }

  return {1, n, z_data};
}

void GraphPerceptron::input_layer(const Matrix& x) {

  auto x_data = x.data();

  auto m = layers_->size;
  auto n = layers_->next->size;

  for (auto i(0); i < m; i += 1) {
    for (auto j(0); j < n; j += 1) {
      auto weight = layers_->neurons[i].weight[i];
      auto bias = layers_->neurons[j].bias[i];
      layers_->next->neurons[j].t = x_data[i] * weight + bias;
    }
  }

  for (auto i(0); i < n; i += 1) {
    auto t = layers_->next->neurons[i].t;
    layers_->next->neurons[i].h = 1 / (1 + exp(-t));
  }
}
