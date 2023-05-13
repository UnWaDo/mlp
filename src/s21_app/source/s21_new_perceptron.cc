#include <QLineEdit>
#include <QRegularExpressionValidator>
#include <QErrorMessage>

#include "s21_new_perceptron.h"
#include "s21_matrix_perceptron.h"
#include "s21_graph_perceptron.h"
#include "ui_new_perceptron.h"

s21::NewPerceptronWindow::NewPerceptronWindow(QWidget *parent)
    : QDialog(parent)
    , re_field_("^([1-9][0-9]{1,3} *)+$")
    , re_token_("([1-9][0-9]{1,3})") {

  ui_ = new s21::Ui::NewPerceptronWindow;
  ui_->setupUi(this);

  QObject::connect(ui_->ButtonBoxSubmit, &QDialogButtonBox::accepted,
                   this, &s21::NewPerceptronWindow::accept);

  QObject::connect(ui_->ButtonBoxSubmit, &QDialogButtonBox::rejected,
                   this, &s21::NewPerceptronWindow::reject);

  auto v = new QRegularExpressionValidator(this);

  v->setRegularExpression(re_field_);
  ui_->LineEditLayers->setValidator(v);

}

s21::NewPerceptronWindow::~NewPerceptronWindow() { }

void s21::NewPerceptronWindow::accept() {

  if (!ui_->LineEditLayers->hasAcceptableInput()) {

    QErrorMessage msg(this);
    msg.showMessage("Ах, какие данные");
    return ;
  }

  std::string type;
  if (ui_->RadioButtonMatrix->isChecked())
    type = "Matrix";
  else
    type = "Graph";
  
  Perceptron::Parameters params;
  params.activation_name = "Sigmoid";
  params.alpha = ui_->SpinBoxAlpha->value();
  
  params.number_of_layers = 2;
  for (auto w : re_token_.globalMatch(ui_->LineEditLayers->text()))
    params.number_of_layers++;

  params.number_of_neurons_in_layer = new int[params.number_of_layers];

  params.number_of_neurons_in_layer[0] = 784;
  int i = 1;
  for (auto w : re_token_.globalMatch(ui_->LineEditLayers->text())) {

    params.number_of_neurons_in_layer[i] = w.captured().toInt();
    i++;
  }
  params.number_of_neurons_in_layer[params.number_of_layers - 1] = 26;

  emit ModificationFinished(params, type);
  QDialog::accept();
}
