#ifndef __S21MATRIX_H__
#define __S21MATRIX_H__

#include <iostream>

#define ACCURACY 1e-07

class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;
  void nullAll();

 public:
  S21Matrix();                    // default constructor
  S21Matrix(int rows, int cols);  // parameterized constructor
  S21Matrix(const S21Matrix& o);  // copy cnstructor
  S21Matrix(S21Matrix&& o);       // move cnstructor
  ~S21Matrix();                   // destructor

  int getRows();
  int getCols();
  void setRows(int rows);
  void setCols(int cols);
  double** getMatrix();
  double getMatrixElement(int i, int j);
  void createMatrix(int rows, int cols);
  void copyMatrix(const S21Matrix& other);
  void deleteMatrix();

  double& operator()(int row, int col);
  double& operator()(int row, int col) const;
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  bool operator==(const S21Matrix& other);
  S21Matrix operator=(const S21Matrix& other);
  S21Matrix operator+=(const S21Matrix& other);
  S21Matrix operator-=(const S21Matrix& other);
  S21Matrix operator*=(const S21Matrix& other);

  bool eqMatrix(const S21Matrix& other);
  void sumMatrix(const S21Matrix& other);
  void subMatrix(const S21Matrix& other);
  void mulNumber(const double num);
  void mulMatrix(const S21Matrix& other);
  S21Matrix transpose();
  S21Matrix calcComplements();
  double determinant();
  S21Matrix inverseMatrix();

  double gaussMethod();
  int colMax(int rows);
  void swapElements(int i, int imax);
  void algAdd(S21Matrix* result);
  S21Matrix removeRowAndColumn(S21Matrix source, S21Matrix* minor,
                               int move_column, int move_row);
};

#endif  // __S21MATRIX_H__
