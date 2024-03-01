#include "s21_matrix_oop.h"

#include <iostream>

using namespace std;

void S21Matrix::nullAll() {
  this->rows_ = 0;
  this->cols_ = 0;
  this->matrix_ = nullptr;
}

int S21Matrix::getRows() { return this->rows_; }

int S21Matrix::getCols() { return this->cols_; }

double** S21Matrix::getMatrix() { return this->matrix_; }

double S21Matrix::getMatrixElement(int i, int j) { return this->matrix_[i][j]; }

void S21Matrix::setRows(int rows) {
  int tempRows = 0;
  if (rows < 1) {
    throw std::length_error("rows number is less than 1!");
  }
  S21Matrix temp(rows, this->cols_);
  if (this->rows_ < rows) {
    tempRows = this->rows_;
  } else {
    tempRows = rows;
  }
  for (int i = 0; i < tempRows; i++) {
    for (int j = 0; j < this->cols_; j++) {
      temp.matrix_[i][j] = this->matrix_[i][j];
    }
  }
  *this = temp;
}

void S21Matrix::setCols(int cols) {
  int tempCols = 0;
  if (cols < 1) {
    throw std::length_error("cols number is less than 1!");
  }
  S21Matrix temp(this->rows_, cols);
  if (this->cols_ < cols) {
    tempCols = this->cols_;
  } else {
    tempCols = cols;
  }
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < tempCols; j++) {
      temp.matrix_[i][j] = this->matrix_[i][j];
    }
  }
  *this = temp;
}

void S21Matrix::createMatrix(int rows, int cols) {
  if (rows < 1 || cols < 1) {
    throw length_error(
        "You can't create a matrix, rows or columns are less then 1!");
  }
  this->rows_ = rows;
  this->cols_ = cols;
  this->matrix_ = new double*[this->rows_]();
  if (this->matrix_ == nullptr) {
    throw bad_alloc();
  }
  for (int i = 0; i < this->rows_; i++) {
    this->matrix_[i] = new double[this->cols_]();
    if (this->matrix_[i] == nullptr) {
      this->nullAll();
      throw bad_alloc();
    }
  }
}

// конструктор создания
S21Matrix::S21Matrix() { this->nullAll(); }

// параметризированный конструктор создания
S21Matrix::S21Matrix(int rows, int cols) { this->createMatrix(rows, cols); }

void S21Matrix::copyMatrix(const S21Matrix& other) {
  for (int i = 0; i < other.rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

// конструктор копирования
S21Matrix::S21Matrix(const S21Matrix& other) {
  this->createMatrix(other.rows_, other.cols_);
  if (other.matrix_ != nullptr) {
    this->copyMatrix(other);
  } else {
    throw bad_alloc();
  }
}

void S21Matrix::deleteMatrix() {
  for (int i = 0; i < this->rows_; i++) {
    delete[] this->matrix_[i];
  }
  delete[] this->matrix_;
  this->nullAll();
}

// конструктор передвижения
S21Matrix::S21Matrix(S21Matrix&& other) {
  this->createMatrix(other.rows_, other.cols_);
  if (other.matrix_ != nullptr) {
    this->copyMatrix(other);
    other.deleteMatrix();
  } else {
    throw bad_alloc();
  }
}

// деструктор
S21Matrix::~S21Matrix() {
  if (this->matrix_ != nullptr) {
    this->deleteMatrix();
  }
}

bool S21Matrix::eqMatrix(const S21Matrix& other) {
  bool result = true;
  if (this->matrix_ == nullptr || other.matrix_ == nullptr) {
    result = false;
    throw length_error("The memory for the matrix was allocated incorrectly!");
  } else {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        if (this->matrix_[i][j] != other.matrix_[i][j]) {
          result = false;
          break;
        }
      }
    }
  }
  return result;
}

void S21Matrix::sumMatrix(const S21Matrix& other) {
  if (this->matrix_ == nullptr || other.matrix_ == nullptr) {
    throw length_error("The memory for the matrix was allocated incorrectly!");
  } else if (this->cols_ != other.cols_ || this->rows_ != other.rows_) {
    throw length_error("Your martix has incorrect size!");
  } else {
    for (int i = 0; i < other.rows_; i++) {
      for (int j = 0; j < other.cols_; j++) {
        this->matrix_[i][j] = this->matrix_[i][j] + other.matrix_[i][j];
      }
    }
  }
}

void S21Matrix::subMatrix(const S21Matrix& other) {
  if (this->matrix_ == nullptr || other.matrix_ == nullptr) {
    throw length_error("The memory for the matrix was allocated incorrectly!");
  } else if (this->cols_ != other.cols_ || this->rows_ != other.rows_) {
    throw length_error("Your martix has incorrect size!");
  } else {
    for (int i = 0; i < other.rows_; i++) {
      for (int j = 0; j < other.cols_; j++) {
        this->matrix_[i][j] = this->matrix_[i][j] - other.matrix_[i][j];
      }
    }
  }
}

void S21Matrix::mulNumber(const double num) {
  if (this->matrix_ == nullptr) {
    throw length_error("The memory for the matrix was allocated incorrectly!");
  } else {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        this->matrix_[i][j] = this->matrix_[i][j] * num;
      }
    }
  }
}

void S21Matrix::mulMatrix(const S21Matrix& other) {
  if (this->rows_ != other.cols_ || this->cols_ != other.rows_) {
    throw length_error("You have wrong rows or columns!");
  } else if (this->matrix_ == nullptr || other.matrix_ == nullptr) {
    throw length_error("The memory for the matrix was allocated incorrectly!");
  } else {
    S21Matrix result(this->rows_, other.cols_);
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < other.cols_; j++) {
        for (int k = 0; k < other.rows_; k++) {
          result.matrix_[i][j] += this->matrix_[i][k] * other.matrix_[k][j];
        }
      }
    }
    this->deleteMatrix();
    this->createMatrix(result.rows_, result.cols_);
    this->copyMatrix(result);
    result.deleteMatrix();
  }
}

S21Matrix S21Matrix::transpose() {
  S21Matrix result(this->cols_, this->rows_);
  if (this->matrix_ == nullptr) {
    throw length_error("The memory for the matrix was allocated incorrectly!");
  } else {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        result.matrix_[j][i] = this->matrix_[i][j];
      }
    }
  }
  return result;
}

S21Matrix S21Matrix::removeRowAndColumn(S21Matrix source, S21Matrix* minor,
                                        int move_column, int move_row) {
  int shift_column = 0, shift_row = 0;
  for (int row = 0; row < source.rows_ - 1; row++) {
    shift_column = 0;
    if (row == move_row) {
      shift_row = 1;
    }
    for (int column = 0; column < source.cols_ - 1; column++) {
      if (column == move_column) {
        shift_column = 1;
      }
      minor->matrix_[row][column] =
          source.matrix_[row + shift_row][column + shift_column];
    }
  }
  S21Matrix newMinor(source.rows_ - 1, source.cols_ - 1);
  for (int i = 0; i < newMinor.rows_; i++) {
    for (int j = 0; j < newMinor.cols_; j++) {
      newMinor.matrix_[i][j] = minor->matrix_[i][j];
    }
  }
  return newMinor;
}

void S21Matrix::algAdd(S21Matrix* result) {
  int size = this->cols_;
  int sign = 1;
  S21Matrix minor(size, size);
  if (size == 1) {
    result->matrix_[0][0] = 1;
  }
  if (size > 1) {
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        S21Matrix new_minor = removeRowAndColumn(*this, &minor, j, i);
        if ((i + j) % 2 == 0) {
          sign = 1;
        } else {
          sign = -1;
        }
        result->matrix_[i][j] = sign * new_minor.determinant();
      }
    }
  }
}

S21Matrix S21Matrix::calcComplements() {
  S21Matrix result(this->rows_, this->cols_);
  if (this->matrix_ == nullptr) {
    throw bad_alloc();
  } else if (this->cols_ != this->rows_) {
    throw length_error("Rows not equal columns!");
  } else {
    algAdd(&result);
  }
  return result;
}

int S21Matrix::colMax(int column) {
  int maxElement = abs(this->matrix_[column][column]);
  int maxPos = column;
  for (int i = column + 1; i < this->rows_; ++i) {
    double element = abs(this->matrix_[i][this->cols_]);
    if (element > maxElement) {
      maxElement = element;
      maxPos = i;
    }
  }
  return maxPos;
}

void S21Matrix::swapElements(int row, int maxRow) {
  for (int i = 0; i < this->rows_; i++) {
    double temp = this->matrix_[row][i];
    this->matrix_[row][i] = this->matrix_[maxRow][i];
    this->matrix_[maxRow][i] = temp;
  }
}

double S21Matrix::gaussMethod() {
  int swapCount = 0;
  for (int row = 0; row < this->cols_ - 1; row++) {
    int maxRow = colMax(row);
    if (row != maxRow && row < this->rows_) {
      swapElements(row, maxRow);
      swapCount++;
    }
    if (row < this->rows_) {
      for (int j = row + 1; j < this->rows_; j++) {
        double mulRow = -this->matrix_[j][row] / this->matrix_[row][row];
        for (int k = row; k < this->rows_; k++) {
          this->matrix_[j][k] += this->matrix_[row][k] * mulRow;
        }
      }
    }
  }
  return swapCount;
}

double S21Matrix::determinant() {
  double result = 1;
  int sign = 0;
  if (this->matrix_ == nullptr) {
    throw bad_alloc();
  } else if (this->rows_ != this->cols_) {
    throw length_error("Rows not equal columns!");
  } else if (this->rows_ < 1 || this->cols_ < 1) {
    throw length_error("Rows or columns are less then 1");
  } else if (this->rows_ == 1) {
    result = this->matrix_[0][0];
  } else if (this->rows_ == 2) {
    result = this->matrix_[0][0] * this->matrix_[1][1] -
             this->matrix_[1][0] * this->matrix_[0][1];
  } else {
    sign = this->gaussMethod();
    for (int i = 0; i < this->rows_; i++) {
      result *= this->matrix_[i][i];
    }
    if (sign % 2 != 0) {
      result *= -1;
    }
  }
  return result;
}

S21Matrix S21Matrix::inverseMatrix() {
  S21Matrix result(this->rows_, this->rows_);
  S21Matrix tempForDet(this->rows_, this->cols_);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      tempForDet.matrix_[i][j] = this->matrix_[i][j];
    }
  }
  if (this->cols_ != this->rows_) {
    throw length_error("Rows not equal columns!");
  } else {
    double result_det = tempForDet.determinant();
    if (fabs(result_det) < ACCURACY) {
      throw length_error("determinant equal 0!");
    }
    S21Matrix temp = this->calcComplements();
    S21Matrix transpose = temp.transpose();
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->rows_; j++) {
        result.matrix_[i][j] = transpose.matrix_[i][j] / result_det;
      }
    }
  }
  return result;
}

double& S21Matrix::operator()(int row, int col) {
  if (row > this->rows_ || col > this->cols_ || row < 0 || col < 0) {
    throw length_error("Problem with rows and columns!");
  }
  return this->matrix_[row][col];
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix result(this->rows_, this->cols_);
  result = *this;
  result.sumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix result(this->rows_, this->cols_);
  result = *this;
  result.subMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix result(this->rows_, this->cols_);
  result = *this;
  result.mulMatrix(other);
  return result;
}

bool S21Matrix::operator==(const S21Matrix& other) {
  bool result = this->eqMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator=(const S21Matrix& other) {
  this->deleteMatrix();
  this->createMatrix(other.rows_, other.cols_);
  this->copyMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator+=(const S21Matrix& other) {
  this->sumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-=(const S21Matrix& other) {
  this->subMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(const S21Matrix& other) {
  this->mulMatrix(other);
  return *this;
}
