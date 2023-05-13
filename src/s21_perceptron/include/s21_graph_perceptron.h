//
// Created by Anton Ivanov on 01.05.2023.
//

#ifndef CPP7_MLP_1_SRC_S21_PERCEPTRON_INCLUDE_S21_GRAPH_PERCEPTRON_H_
#define CPP7_MLP_1_SRC_S21_PERCEPTRON_INCLUDE_S21_GRAPH_PERCEPTRON_H_

#include "s21_perceptron.h"

namespace s21 {

class GraphPerceptron : public s21::Perceptron {
 public:

  GraphPerceptron(const s21::Perceptron::Parameters &);
  GraphPerceptron(const std::string &name, const std::string &path = "./");
  GraphPerceptron(const GraphPerceptron &);

  Matrix ForwardPropagation(const Matrix &input) override;

  void BackPropagation(const Matrix &x, const Matrix &t) override;

  void ExportPerceptronToFile(const std::string &name, const std::string &path = "./") override;

  Parameters GetParameters() const override;

 private:

  class Neuron;

  class Layer {
   public:

    Neuron *neurons;

    int size;

    Layer *next = nullptr;
    Layer *previous = nullptr;

    inline Layer(const Matrix &weight, const Matrix &bias) {

      auto m = weight.m();
      auto n = weight.n();

      size = n;
      neurons = new Neuron[n];

      for (auto i(0); i < n; i += 1) {

        neurons[i].weight = new float[n];
        neurons[i].bias = new float[n];

        for (auto j(0); j < m; j += 1) {

          neurons[i].weight[j] = weight[i][j];
          neurons[i].bias[j] = bias[0][j];
        }
      }
    }

    inline ~Layer() {
      delete[] neurons;
    }

    inline Layer* get_last_layer() {

      Layer* layer = this;

      if (layer == nullptr) {

        return nullptr;
      }

      while (layer->next != nullptr) {

        layer = layer->next;
      }

      return layer;
    }
  };

  class Neuron {
   public:

    float *weight;
    float *bias;

    float t;
    float h;

    float _dE_dw;
    float _dE_db;

    inline Neuron() {
      weight = nullptr;
      bias = nullptr;
    }

    inline ~Neuron() {
      delete[] weight;
      delete[] bias;
    }
  };

  int _number_of_layers;
  int _number_of_hidden_layers;
  int *_number_of_neurons_in_layers;

  float _alpha;

  std::string _activation_name;
  Matrix (*_activation)(const Matrix &);
  Matrix (*_derivedActivation)(const Matrix &);

  Matrix *_W;
  Matrix *_b;

  Layer *layers_ = nullptr;

  void input_layer(const Matrix& x);
  void parse_info(const std::string &bundle);
  void parse_layer(const std::string &bundle);
  [[nodiscard]] Matrix *parse_layer(const std::string &bundle,
                                    const std::string &filename) const;

  void export_info(const std::string &bundle) const;
  void export_layer(const std::string &bundle,
                    const std::string &filename,
                    const Matrix *matrix) const;
  void update();
};

}

#endif //CPP7_MLP_1_SRC_S21_PERCEPTRON_INCLUDE_S21_GRAPH_PERCEPTRON_H_
