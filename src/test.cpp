#include <gtest/gtest.h>

#include <iostream>

#include "s21_matrix_oop.h"

using namespace std;

TEST(matrixTest, s21MatrixTest1) {
  S21Matrix matrix;

  ASSERT_EQ(matrix.getMatrix(), nullptr);
  ASSERT_EQ(matrix.getRows(), 0);
  ASSERT_EQ(matrix.getCols(), 0);
}

TEST(matrixTest, s21MatrixWithDataTest1) {
  S21Matrix matrix(2, 3);

  ASSERT_EQ(matrix.getRows(), 2);
  ASSERT_EQ(matrix.getCols(), 3);
  for (int i = 0; i < matrix.getRows(); i++) {
    for (int j = 0; j < matrix.getCols(); j++) {
      ASSERT_EQ(matrix.getMatrixElement(i, j), 0);
    }
  }
}

TEST(matrixTest, s21MatrixWithDataTest2) {
  EXPECT_THROW(S21Matrix matrix(2, -1), length_error);
}

TEST(matrixTest, s21MatrixWithDataTest3) {
  EXPECT_THROW(S21Matrix matrix(2, -1), length_error);
}

TEST(matrixTest, s21MatrixCopyTest1) {
  S21Matrix other(2, 2);
  S21Matrix matrix(other);

  ASSERT_EQ(matrix.getRows(), 2);
  ASSERT_EQ(matrix.getCols(), 2);
  for (int i = 0; i < other.getRows(); i++) {
    for (int j = 0; j < other.getCols(); j++) {
      ASSERT_EQ(matrix.getMatrixElement(i, j), 0);
    }
  }
}

TEST(matrixTest, s21MatrixCopyTest2) {
  S21Matrix other;

  EXPECT_THROW(S21Matrix matrix(other), length_error);
}

TEST(matrixTest, s21MatrixMoveTest1) {
  S21Matrix other(2, 2);
  S21Matrix matrix(std::move(other));

  ASSERT_EQ(matrix.getRows(), 2);
  ASSERT_EQ(matrix.getCols(), 2);
  for (int i = 0; i < matrix.getRows(); i++) {
    for (int j = 0; j < matrix.getCols(); j++) {
      ASSERT_EQ(matrix.getMatrixElement(i, j), 0);
    }
  }
}

TEST(matrixTest, s21MatrixMoveTest2) {
  S21Matrix other;

  EXPECT_THROW(S21Matrix matrix(std::move(other)), length_error);
}

TEST(matrixTest, eqMatrixTest1) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 1;
  matrix1(0, 1) = 1;
  matrix1(1, 0) = 1;
  matrix1(1, 1) = 1;

  matrix2(0, 0) = 1;
  matrix2(0, 1) = 1;
  matrix2(1, 0) = 1;
  matrix2(1, 1) = 1;

  EXPECT_TRUE(matrix1.eqMatrix(matrix2));
}

TEST(matrixTest, eqMatrixTest2) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 2;
  matrix1(0, 1) = 1;
  matrix1(1, 0) = 1;
  matrix1(1, 1) = 1;

  matrix2(0, 0) = 1;
  matrix2(0, 1) = 1;
  matrix2(1, 0) = 1;
  matrix2(1, 1) = 1;

  EXPECT_FALSE(matrix1.eqMatrix(matrix2));
}

TEST(matrixTest, eqMatrixTest3) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  matrix1(0, 0) = -1.24;
  matrix1(0, 1) = 1;
  matrix1(1, 0) = 1;
  matrix1(1, 1) = 1;

  matrix2(0, 0) = -1.24;
  matrix2(0, 1) = 1;
  matrix2(1, 0) = 1;
  matrix2(1, 1) = 1;

  EXPECT_TRUE(matrix1.eqMatrix(matrix2));
}

TEST(matrixTest, eqMatrixTest4) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2;

  EXPECT_THROW(matrix1.eqMatrix(matrix2), length_error);
}

TEST(matrixTest, eqMatrixTest5) {
  S21Matrix matrix1;
  S21Matrix matrix2(2, 2);

  EXPECT_THROW(matrix1.eqMatrix(matrix2), length_error);
}

TEST(matrixTest, eqMatrixTest6) {
  S21Matrix matrix1;
  S21Matrix matrix2;

  EXPECT_THROW(matrix1.eqMatrix(matrix2), length_error);
}

TEST(matrixTest, sumMatrixTest1) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 1;
  matrix1(0, 1) = 1;
  matrix1(1, 0) = 1;
  matrix1(1, 1) = 1;
  matrix2(0, 0) = 1;
  matrix2(0, 1) = 1;
  matrix2(1, 0) = 1;
  matrix2(1, 1) = 1;

  matrix1.sumMatrix(matrix2);

  for (int i = 0; i < matrix1.getRows(); i++) {
    for (int j = 0; j < matrix1.getCols(); j++) {
      ASSERT_EQ(matrix1.getMatrixElement(i, j), 2);
    }
  }
}

TEST(matrixTest, sumMatrixTest2) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 1;
  matrix1(0, 1) = 1;
  matrix1(1, 0) = 1;
  matrix1(1, 1) = 1;
  matrix2(0, 0) = 1;
  matrix2(0, 1) = 1;
  matrix2(1, 0) = 1;
  matrix2(1, 1) = 1;

  EXPECT_THROW(matrix1.sumMatrix(matrix2), length_error);
}

TEST(matrixTest, sumMatrixTest3) {
  S21Matrix matrix1;
  S21Matrix matrix2(2, 2);

  matrix2(0, 0) = 1;
  matrix2(0, 1) = 1;
  matrix2(1, 0) = 1;
  matrix2(1, 1) = 1;

  EXPECT_THROW(matrix1.sumMatrix(matrix2), length_error);
}

TEST(matrixTest, subMatrixTest1) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 3;
  matrix1(0, 1) = 3;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 3;
  matrix2(0, 0) = 1;
  matrix2(0, 1) = 1;
  matrix2(1, 0) = 1;
  matrix2(1, 1) = 1;

  matrix1.subMatrix(matrix2);

  for (int i = 0; i < matrix1.getRows(); i++) {
    for (int j = 0; j < matrix1.getCols(); j++) {
      ASSERT_EQ(matrix1.getMatrixElement(i, j), 2);
    }
  }
}

TEST(matrixTest, subMatrixTest2) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 1;
  matrix1(0, 1) = 1;
  matrix1(1, 0) = 1;
  matrix1(1, 1) = 1;
  matrix2(0, 0) = 1;
  matrix2(0, 1) = 1;
  matrix2(1, 0) = 1;
  matrix2(1, 1) = 1;

  EXPECT_THROW(matrix1.subMatrix(matrix2), length_error);
}

TEST(matrixTest, subMatrixTest3) {
  S21Matrix matrix1;
  S21Matrix matrix2(2, 2);

  matrix2(0, 0) = 1;
  matrix2(0, 1) = 1;
  matrix2(1, 0) = 1;
  matrix2(1, 1) = 1;

  EXPECT_THROW(matrix1.subMatrix(matrix2), length_error);
}

TEST(matrixTest, mulNumberTest1) {
  double number = 2.3;
  S21Matrix matrix(2, 3);

  matrix(0, 0) = 1;
  matrix(0, 1) = 1;
  matrix(0, 2) = 1;
  matrix(1, 0) = 1;
  matrix(1, 1) = 1;
  matrix(1, 2) = 1;

  matrix.mulNumber(number);

  for (int i = 0; i < matrix.getRows(); i++) {
    for (int j = 0; j < matrix.getCols(); j++) {
      ASSERT_EQ(matrix.getMatrixElement(i, j), number);
    }
  }
}

TEST(matrixTest, mulNumberTest2) {
  double number = 2.3;
  S21Matrix matrix;

  EXPECT_THROW(matrix.mulNumber(number), length_error);
}

TEST(matrixTest, mulMatrixTest1) {
  int rows = 2, cols = 3;
  S21Matrix matrix1(rows, cols);
  S21Matrix matrix2(cols, rows);
  S21Matrix result(matrix1.getRows(), matrix2.getCols());

  matrix1(0, 0) = 1.5;
  matrix1(0, 1) = -2.5;
  matrix1(0, 2) = 0.3;
  matrix1(1, 0) = 47;
  matrix1(1, 1) = -0.001;
  matrix1(1, 2) = 6;

  matrix2(0, 0) = -1;
  matrix2(0, 1) = 8.5;
  matrix2(1, 0) = 3.321321;
  matrix2(1, 1) = 4.1;
  matrix2(2, 0) = 5;
  matrix2(2, 1) = 6;

  result(0, 0) = -8.303303;
  result(0, 1) = 4.3;
  result(1, 0) = -17.003321;
  result(1, 1) = 435.4959;

  matrix1.mulMatrix(matrix2);

  for (int i = 0; i < result.getRows(); i++) {
    for (int j = 0; j < result.getCols(); j++) {
      EXPECT_NEAR(result.getMatrixElement(i, j), matrix1.getMatrixElement(i, j),
                  0.000001);
    }
  }
}

TEST(matrixTest, mulMatrixTest2) {
  int rows = 2, cols = 3;
  S21Matrix matrix1(rows, cols);
  S21Matrix matrix2(rows, rows);

  matrix1(0, 0) = 1.5;
  matrix1(0, 1) = -2.5;
  matrix1(0, 2) = 0.3;
  matrix1(1, 0) = 47;
  matrix1(1, 1) = -0.001;
  matrix1(1, 2) = 6;

  matrix2(0, 0) = -1;
  matrix2(0, 1) = 8.5;
  matrix2(1, 0) = 3.321321;
  matrix2(1, 1) = 4.1;

  EXPECT_THROW(matrix1.mulMatrix(matrix2), length_error);
}

TEST(matrixTest, mulMatrixTest3) {
  int rows = 2, cols = 3;
  S21Matrix matrix1(rows, cols);
  S21Matrix matrix2;

  matrix1(0, 0) = 1.5;
  matrix1(0, 1) = -2.5;
  matrix1(0, 2) = 0.3;
  matrix1(1, 0) = 47;
  matrix1(1, 1) = -0.001;
  matrix1(1, 2) = 6;

  EXPECT_THROW(matrix1.mulMatrix(matrix2), length_error);
}

TEST(matrixTest, transposeTest1) {
  int rows = 2, cols = 3;
  S21Matrix matrix(rows, cols);
  S21Matrix checkMatrix(cols, rows);

  matrix(0, 0) = 1.5;
  matrix(0, 1) = -2.5;
  matrix(0, 2) = 0.3;
  matrix(1, 0) = 47;
  matrix(1, 1) = -0.001;
  matrix(1, 2) = 6;

  checkMatrix(0, 0) = 1.5;
  checkMatrix(0, 1) = 47;
  checkMatrix(1, 0) = -2.5;
  checkMatrix(1, 1) = -0.001;
  checkMatrix(2, 0) = 0.3;
  checkMatrix(2, 1) = 6;

  matrix.transpose();

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      ASSERT_EQ(matrix.getMatrixElement(i, j),
                checkMatrix.getMatrixElement(j, i));
    }
  }
}

TEST(matrixTest, transposeTest2) {
  S21Matrix matrix;

  EXPECT_THROW(matrix.transpose(), length_error);
}

TEST(matrixTest, calcComplementsTest1) {
  int rows = 2, cols = 2;
  S21Matrix matrix(rows, cols);
  S21Matrix checkResult(rows, cols);

  matrix(0, 0) = 57.0;
  matrix(0, 1) = -55.0;
  matrix(1, 0) = 2.0;
  matrix(1, 1) = -79.0;

  checkResult(0, 0) = -79.0;
  checkResult(0, 1) = -2.0;
  checkResult(1, 0) = 55.0;
  checkResult(1, 1) = 57.0;

  S21Matrix result = matrix.calcComplements();

  for (int i = 0; i < result.getRows(); i++) {
    for (int j = 0; j < result.getCols(); j++) {
      EXPECT_NEAR(result.getMatrixElement(i, j),
                  checkResult.getMatrixElement(i, j), 0.000001);
    }
  }
}

TEST(matrixTest, calcComplementsTest2) {
  int rows = 3, cols = 3;
  S21Matrix matrix(rows, cols);
  S21Matrix checkMatrix(rows, cols);

  matrix(0, 0) = 1;
  matrix(0, 1) = 10;
  matrix(0, 2) = 8.6;
  matrix(1, 0) = -78.4;
  matrix(1, 1) = -0.054;
  matrix(1, 2) = 0.53;
  matrix(2, 0) = 154;
  matrix(2, 1) = 123;
  matrix(2, 2) = 8;

  checkMatrix(0, 0) = -65.622;
  checkMatrix(0, 1) = 708.82;
  checkMatrix(0, 2) = -9634.884;
  checkMatrix(1, 0) = 977.8;
  checkMatrix(1, 1) = -1316.4;
  checkMatrix(1, 2) = 1417;
  checkMatrix(2, 0) = 5.7644;
  checkMatrix(2, 1) = -674.77;
  checkMatrix(2, 2) = 783.946;

  S21Matrix result = matrix.calcComplements();

  for (int i = 0; i < result.getRows(); i++) {
    for (int j = 0; j < result.getCols(); j++) {
      EXPECT_NEAR(result.getMatrixElement(i, j),
                  checkMatrix.getMatrixElement(i, j), 0.000001);
    }
  }
}

TEST(matrixTest, calcComplementsTest3) {
  int rows = 1, cols = 1;
  S21Matrix matrix(rows, cols);
  S21Matrix checkResult(rows, cols);

  matrix(0, 0) = 23464;

  checkResult(0, 0) = 1;

  S21Matrix result = matrix.calcComplements();

  EXPECT_NEAR(result.getMatrixElement(0, 0), checkResult.getMatrixElement(0, 0),
              0.000001);
}

TEST(matrixTest, calcComplementsTest4) {
  S21Matrix matrix;

  EXPECT_THROW(matrix.calcComplements(), length_error);
}

TEST(matrixTest, calcComplementsTest5) {
  int rows = 3, cols = 2;
  S21Matrix matrix(rows, cols);
  EXPECT_THROW(matrix.calcComplements(), length_error);
}

TEST(matrixTest, determinantTest1) {
  int rows = 4, cols = 4;
  S21Matrix matrix(rows, cols);

  matrix(0, 0) = -2;
  matrix(0, 1) = 3;
  matrix(0, 2) = 5;
  matrix(0, 3) = 4;

  matrix(1, 0) = 2;
  matrix(1, 1) = 0;
  matrix(1, 2) = 3;
  matrix(1, 3) = -1;

  matrix(2, 0) = -1;
  matrix(2, 1) = 2;
  matrix(2, 2) = 4;
  matrix(2, 3) = 0;

  matrix(3, 0) = 3;
  matrix(3, 1) = 1;
  matrix(3, 2) = 2;
  matrix(3, 3) = -1;

  double result = matrix.determinant();
  double checkResult = 78;

  EXPECT_NEAR(result, checkResult, 0.000001);
}

TEST(matrixTest, determinantTest2) {
  S21Matrix matrix;

  EXPECT_THROW(matrix.determinant(), bad_alloc);
}

TEST(matrixTest, determinantTest3) {
  int rows = 1, cols = 1;
  S21Matrix matrix(rows, cols);

  matrix(0, 0) = 1;

  double result = matrix.determinant();
  double checkResult = 1;

  ASSERT_EQ(result, checkResult);
}

TEST(matrixTest, determinantTest4) {
  int rows = 2, cols = 2;
  S21Matrix matrix(rows, cols);

  matrix(0, 0) = 1;
  matrix(0, 1) = 2;

  matrix(1, 0) = 3;
  matrix(1, 1) = 4;

  double result = matrix.determinant();
  double checkResult = -2;

  ASSERT_EQ(result, checkResult);
}

TEST(matrixTest, determinantTest5) {
  int rows = 2, cols = 3;
  S21Matrix matrix(rows, cols);

  EXPECT_THROW(matrix.determinant(), length_error);
}

TEST(matrixTest, inverseMatrixTest1) {
  int rows = 2, cols = 2;
  S21Matrix matrix(rows, cols);
  S21Matrix checkResult(rows, cols);

  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = -8;
  matrix(1, 1) = -0.02;

  checkResult(0, 0) = -0.001252;
  checkResult(0, 1) = -0.125156;
  checkResult(1, 0) = 0.500626;
  checkResult(1, 1) = 0.062578;

  S21Matrix result = matrix.inverseMatrix();

  for (int i = 0; i < result.getRows(); i++) {
    for (int j = 0; j < result.getCols(); j++) {
      EXPECT_NEAR(result.getMatrixElement(i, j),
                  checkResult.getMatrixElement(i, j), 0.000001);
    }
  }
}

TEST(matrixTest, inverseMatrixTest2) {
  int rows = 3, cols = 3;
  S21Matrix matrix(rows, cols);
  S21Matrix checkResult(rows, cols);

  matrix(0, 0) = 1;
  matrix(0, 1) = 10;
  matrix(0, 2) = 8.6;
  matrix(1, 0) = -78.4;
  matrix(1, 1) = -0.054;
  matrix(1, 2) = 0.53;
  matrix(2, 0) = 154;
  matrix(2, 1) = 123;
  matrix(2, 2) = 8;

  checkResult(0, 0) = 0.000865;
  checkResult(0, 1) = -0.012893;
  checkResult(0, 2) = -0.000076;
  checkResult(1, 0) = -0.009347;
  checkResult(1, 1) = 0.017358;
  checkResult(1, 2) = 0.008898;
  checkResult(2, 0) = 0.127047;
  checkResult(2, 1) = -0.018685;
  checkResult(2, 2) = -0.010337;

  S21Matrix result = matrix.inverseMatrix();

  for (int i = 0; i < result.getRows(); i++) {
    for (int j = 0; j < result.getCols(); j++) {
      EXPECT_NEAR(result.getMatrixElement(i, j),
                  checkResult.getMatrixElement(i, j), 0.000001);
    }
  }
}

TEST(matrixTest, inverseMatrixTest3) {
  S21Matrix matrix;

  EXPECT_THROW(matrix.inverseMatrix(), length_error);
}

TEST(matrixTest, inverseMatrixTest4) {
  int rows = 3, cols = 2;
  S21Matrix matrix(rows, cols);
  S21Matrix result(rows, cols);

  EXPECT_THROW(matrix.inverseMatrix(), length_error);
}

TEST(matrixTest, inverseMatrixTest5) {
  int rows = 2, cols = 2;
  S21Matrix matrix(rows, cols);
  S21Matrix result(rows, cols);

  matrix(0, 0) = 25;
  matrix(0, 1) = 60;
  matrix(1, 0) = 5;
  matrix(1, 1) = 12;

  EXPECT_THROW(matrix.inverseMatrix(), length_error);
}

TEST(matrixTest, operatorPlusTest) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 1;
  matrix1(0, 1) = 1;
  matrix1(1, 0) = 1;
  matrix1(1, 1) = 1;

  matrix2(0, 0) = 1;
  matrix2(0, 1) = 1;
  matrix2(1, 0) = 1;
  matrix2(1, 1) = 1;

  S21Matrix result = matrix1 + matrix2;

  for (int i = 0; i < matrix1.getRows(); i++) {
    for (int j = 0; j < matrix1.getCols(); j++) {
      ASSERT_EQ(result.getMatrixElement(i, j), 2);
    }
  }
}

TEST(matrixTest, operatorMinusTest) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 3;
  matrix1(0, 1) = 3;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 3;
  matrix2(0, 0) = 1;
  matrix2(0, 1) = 1;
  matrix2(1, 0) = 1;
  matrix2(1, 1) = 1;

  S21Matrix result = matrix1 - matrix2;

  for (int i = 0; i < matrix1.getRows(); i++) {
    for (int j = 0; j < matrix1.getCols(); j++) {
      ASSERT_EQ(result.getMatrixElement(i, j), 2);
    }
  }
}

TEST(matrixTest, operatorMulTest) {
  int rows = 2, cols = 3;
  S21Matrix matrix1(rows, cols);
  S21Matrix matrix2(cols, rows);
  S21Matrix checkResult(matrix1.getRows(), matrix2.getCols());

  matrix1(0, 0) = 1.5;
  matrix1(0, 1) = -2.5;
  matrix1(0, 2) = 0.3;
  matrix1(1, 0) = 47;
  matrix1(1, 1) = -0.001;
  matrix1(1, 2) = 6;

  matrix2(0, 0) = -1;
  matrix2(0, 1) = 8.5;
  matrix2(1, 0) = 3.321321;
  matrix2(1, 1) = 4.1;
  matrix2(2, 0) = 5;
  matrix2(2, 1) = 6;

  checkResult(0, 0) = -8.303303;
  checkResult(0, 1) = 4.3;
  checkResult(1, 0) = -17.003321;
  checkResult(1, 1) = 435.4959;

  S21Matrix result = matrix1 * matrix2;

  for (int i = 0; i < checkResult.getRows(); i++) {
    for (int j = 0; j < checkResult.getCols(); j++) {
      EXPECT_NEAR(checkResult.getMatrixElement(i, j),
                  result.getMatrixElement(i, j), 0.000001);
    }
  }
}

TEST(matrixTest, operatorEqTest) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 1;
  matrix1(0, 1) = 1;
  matrix1(1, 0) = 1;
  matrix1(1, 1) = 1;

  matrix2(0, 0) = 1;
  matrix2(0, 1) = 1;
  matrix2(1, 0) = 1;
  matrix2(1, 1) = 1;

  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(matrixTest, operatorAssignTest) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 1;
  matrix1(0, 1) = 1;
  matrix1(1, 0) = 1;
  matrix1(1, 1) = 1;

  matrix2(0, 0) = 2;
  matrix2(0, 1) = 2;
  matrix2(1, 0) = 2;
  matrix2(1, 1) = 2;

  matrix1 = matrix2;

  for (int i = 0; i < matrix1.getRows(); i++) {
    for (int j = 0; j < matrix1.getCols(); j++) {
      ASSERT_EQ(matrix1.getMatrixElement(i, j), 2);
    }
  }
}

TEST(matrixTest, operatorPlusEqTest) {
  S21Matrix matrix(2, 2);
  S21Matrix result(2, 2);

  matrix(0, 0) = 1;
  matrix(0, 1) = 1;
  matrix(1, 0) = 1;
  matrix(1, 1) = 1;

  result(0, 0) = 1;
  result(0, 1) = 1;
  result(1, 0) = 1;
  result(1, 1) = 1;

  result += matrix;

  for (int i = 0; i < matrix.getRows(); i++) {
    for (int j = 0; j < matrix.getCols(); j++) {
      ASSERT_EQ(result.getMatrixElement(i, j), 2);
    }
  }
}

TEST(matrixTest, operatorMinusEqTest) {
  S21Matrix result(2, 2);
  S21Matrix matrix(2, 2);

  result(0, 0) = 3;
  result(0, 1) = 3;
  result(1, 0) = 3;
  result(1, 1) = 3;

  matrix(0, 0) = 1;
  matrix(0, 1) = 1;
  matrix(1, 0) = 1;
  matrix(1, 1) = 1;

  result -= matrix;

  for (int i = 0; i < matrix.getRows(); i++) {
    for (int j = 0; j < matrix.getCols(); j++) {
      ASSERT_EQ(result.getMatrixElement(i, j), 2);
    }
  }
}

TEST(matrixTest, operatorMulEqTest) {
  int rows = 2, cols = 3;
  S21Matrix result(rows, cols);
  S21Matrix matrix(cols, rows);
  S21Matrix checkResult(result.getRows(), matrix.getCols());

  result(0, 0) = 1.5;
  result(0, 1) = -2.5;
  result(0, 2) = 0.3;
  result(1, 0) = 47;
  result(1, 1) = -0.001;
  result(1, 2) = 6;

  matrix(0, 0) = -1;
  matrix(0, 1) = 8.5;
  matrix(1, 0) = 3.321321;
  matrix(1, 1) = 4.1;
  matrix(2, 0) = 5;
  matrix(2, 1) = 6;

  checkResult(0, 0) = -8.303303;
  checkResult(0, 1) = 4.3;
  checkResult(1, 0) = -17.003321;
  checkResult(1, 1) = 435.4959;

  result *= matrix;

  for (int i = 0; i < checkResult.getRows(); i++) {
    for (int j = 0; j < checkResult.getCols(); j++) {
      EXPECT_NEAR(checkResult.getMatrixElement(i, j),
                  result.getMatrixElement(i, j), 0.000001);
    }
  }
}

TEST(matrixTest, setRowsErr) {
  S21Matrix matrix;
  EXPECT_THROW(matrix.setRows(0), std::length_error);
}

TEST(matrixTest, setCols) {
  S21Matrix matrix1(1, 1);
  S21Matrix result(1, 2);
  matrix1.setCols(2);
  EXPECT_EQ(matrix1.getCols(), result.getCols());
}

TEST(matrixTest, setRows) {
  S21Matrix matrix1(1, 1);
  S21Matrix result(2, 1);
  matrix1.setRows(2);
  EXPECT_EQ(matrix1.getRows(), result.getRows());
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}