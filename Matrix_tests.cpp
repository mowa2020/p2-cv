// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"
#include <ostream>
#include <iostream>
#include <sstream>
#include <cassert>
using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat; // delete the Matrix
}

TEST(test_print) {
    Matrix *mat = new Matrix;
   
   Matrix_init(mat, 5, 4);

   ostringstream matrix;
   Matrix_fill(mat, 50);


  Matrix_print(mat, matrix);

  ostringstream correct;
  correct << "5 4" << endl;
  correct << "50 50 50 50 50 " << endl;
  correct << "50 50 50 50 50 " << endl;
  correct << "50 50 50 50 50 " << endl;
  correct << "50 50 50 50 50 " << endl;
  ASSERT_EQUAL(matrix.str(), correct.str());

  delete mat;
}

TEST(test_width) {
    Matrix* mat = new Matrix;
    int width = 3;
    int height = 4;
    Matrix_init(mat, width, height);
    
    ASSERT_TRUE(Matrix_width(mat) == 3);

    delete mat;
}
TEST(test_height) {
    Matrix* mat = new Matrix;
    int width = 3;
    int height = 4;
    Matrix_init(mat, width, height);

    ASSERT_TRUE(Matrix_height(mat) == 4);

    delete mat;
}
TEST(test_columnMin) {
    Matrix* mat = new Matrix;
    int width = 3;
    int height = 4;
    Matrix_init(mat, width, height);
    Matrix_fill(mat, 10);
    *Matrix_at(mat, 0, 0) = 12;
    *Matrix_at(mat, 0, 1) = 13;
     *Matrix_at(mat, 0, 2) = 5;
     
    int col = Matrix_column_of_min_value_in_row(mat, 0, 0, 3);
   
   ASSERT_TRUE(col == 2);

    delete mat;
}
TEST(test_minVal) {
    Matrix* mat = new Matrix;
    int width = 3;
    int height = 4;
    Matrix_init(mat, width, height);
    Matrix_fill(mat, 20);
    *Matrix_at(mat, 0, 0) = 12;
    *Matrix_at(mat, 0, 1) = 13;
     *Matrix_at(mat, 0, 2) = 5;
     
    int min = Matrix_min_value_in_row(mat, 0, 0, 3);
    ASSERT_TRUE(min == 5);

    delete mat;
}
TEST(test_matColumn) {
    Matrix* mat = new Matrix;
    int width = 3;
    int height = 4;
    Matrix_init(mat, width, height);
    Matrix_fill(mat, 0);
    *Matrix_at(mat, 0, 0) = 12;
    *Matrix_at(mat, 0, 1) = 13;
    const int *ptr = Matrix_at(mat, 0, 2);
    int col = Matrix_column(mat, ptr);
    ASSERT_TRUE(col == 2);
    int N = 0;
    ASSERT_TRUE(N >= 0);

    delete mat;
}
TEST(test_matRow) {
    Matrix* mat = new Matrix;
    int width = 3;
    int height = 4;
    Matrix_init(mat, width, height);
    Matrix_fill(mat, 0);
    *Matrix_at(mat, 0, 0) = 12;
    *Matrix_at(mat, 0, 1) = 13;
    const int *ptr = Matrix_at(mat, 0, 2);
    int row = Matrix_row(mat, ptr);
    ASSERT_TRUE(row == 0);

    delete mat;
}
TEST(test_fillBorder) {
  Matrix *mat = new Matrix;
   
   Matrix_init(mat, 5, 4);
    Matrix_fill(mat, 0);
   ostringstream matrix;
   Matrix_fill_border(mat, 50);


  Matrix_print(mat, matrix);

  ostringstream correct;
  correct << "5 4" << endl;
  correct << "50 50 50 50 50 " << endl;
  correct << "50 0 0 0 50 " << endl;
  correct << "50 0 0 0 50 " << endl;
  correct << "50 50 50 50 50 " << endl;
  ASSERT_EQUAL(matrix.str(), correct.str());

  delete mat;
}
TEST(test_maxVal) {
    Matrix* mat = new Matrix;
    int width = 3;
    int height = 4;
    Matrix_init(mat, width, height);
    Matrix_fill(mat, 0);
    *Matrix_at(mat, 0, 0) = 12;
    *Matrix_at(mat, 0, 1) = 13;
    *Matrix_at(mat, 0, 2) = 5;
    int max = Matrix_max(mat);
   ASSERT_TRUE(max == 13);

delete mat;
    Matrix* mat1 = new Matrix;
    int width1 = 3;
    int height1 = 4;
    Matrix_init(mat1, width1, height1);
    Matrix_fill(mat1, 20);
    *Matrix_at(mat1, 0, 0) = 12;
    *Matrix_at(mat1, 0, 1) = 50;
    *Matrix_at(mat1, 0, 2) = 5;
    int max2 = Matrix_max(mat1);
   ASSERT_TRUE(max2 == 50);
   
   delete mat1;
   Matrix* mat2 = new Matrix;
    int width2 = 3;
    int height2 = 4;
    Matrix_init(mat2, width2, height2);
    Matrix_fill(mat2, 30);
    *Matrix_at(mat2, 0, 0) = 30;
    *Matrix_at(mat2, 0, 1) = 30;
    *Matrix_at(mat2, 0, 2) = 30;
    int max3 = Matrix_max(mat2);
   ASSERT_TRUE(max3 == 30);

    delete mat2;
}

TEST(test_matAt) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, 0);
  ASSERT_EQUAL(*Matrix_at(mat, 0, 0) = 30, 30);
   // *Matrix_at(mat, 0, 1) = 30;
   // *Matrix_at(mat, 0, 2) = 30;
    

  delete mat; // delete the Matrix
}


// You are encouraged to use any functions from Matrix_test_helpers.h as needed.


// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here

