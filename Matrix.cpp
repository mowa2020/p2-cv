// Project UID af1f95f547e44c8ea88730dfb185559d

#include <cassert>
#include "Matrix.h"
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

// REQUIRES: mat points to a Matrix
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *mat
// EFFECTS:  Initializes *mat as a Matrix with the given width and height.
// NOTE:     Do NOT use new or delete here.
void Matrix_init(Matrix* mat, int width, int height) {
  
  mat->width = width;
  mat->height = height;
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: os
// EFFECTS:  First, prints the width and height for the Matrix to os:
//             WIDTH [space] HEIGHT [newline]
//           Then prints the rows of the Matrix to os with one row per line.
//           Each element is followed by a space and each row is followed
//           by a newline. This means there will be an "extra" space at
//           the end of each line.
void Matrix_print(const Matrix* mat, std::ostream& os) {
  

  os << mat->width << " ";
  os << mat->height << endl;
  for (int i = 0; i < Matrix_height(mat); i++)  {
	  for (int j = 0; j < Matrix_width(mat); j++) {
		  os << *(Matrix_at(mat, i, j)) << " ";

	  }
	  os << endl;
  }
}

// REQUIRES: mat points to an valid Matrix
// EFFECTS:  Returns the width of the Matrix.
int Matrix_width(const Matrix* mat) {
  
  int width = mat->width;
  return width;
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the height of the Matrix.
int Matrix_height(const Matrix* mat) {
  
  int height = mat->height;
  return height;
}

// REQUIRES: mat points to a valid Matrix
//           ptr points to an element in the Matrix
// EFFECTS:  Returns the row of the element pointed to by ptr.
int Matrix_row(const Matrix* mat, const int* ptr) {
  
  int row = (ptr - mat->data) / Matrix_width(mat);
  
  return row;

}

// REQUIRES: mat points to a valid Matrix
//           ptr point to an element in the Matrix
// EFFECTS:  Returns the column of the element pointed to by ptr.
int Matrix_column(const Matrix* mat, const int* ptr) {
  
  int column = (ptr - mat->data) % mat->width;
  
  return column;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// MODIFIES: (The returned pointer may be used to modify an
//            element in the Matrix.)
// EFFECTS:  Returns a pointer to the element in the Matrix
//           at the given row and column.
int* Matrix_at(Matrix* mat, int row, int column) {
	/*int* element = mat->data;
	
	if (row >= 1 && column >= 1) {
		element += 1000;
		element += (row * mat->width) + column;
	}
	else if (row == 0) {
		element += 500;
		element += column;
	}
	else if (column == 0) {
		element += row;
	}*/
	
  int *element = mat->data + (row * mat->width) + column;

  return element;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// EFFECTS:  Returns a pointer-to-const to the element in
//           the Matrix at the given row and column.
const int* Matrix_at(const Matrix* mat, int row, int column) {
	
	const int* element = mat->data + (row * mat->width) + column;
	return element;
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix_fill(Matrix* mat, int value) {
	Matrix_init(mat, mat->width, mat->height);
	for (int i = 0; i < Matrix_height(mat); i++) {
		for (int j = 0; j < Matrix_width(mat); j++) {
			*Matrix_at(mat, i, j) = value;
			
		}
	}
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element on the border of the Matrix to
//           the given value. These are all elements in the first/last
//           row or the first/last column.
void Matrix_fill_border(Matrix* mat, int value) {
	Matrix_init(mat, mat->width, mat->height);

	for (int col = 0; col < Matrix_width(mat); col++) {
		*Matrix_at(mat, 0, col) = value;
		*Matrix_at(mat, mat->height - 1, col) = value;

	}

	for (int row = 0; row < Matrix_height(mat); row++) {
		*Matrix_at(mat, row, 0) = value;
		*Matrix_at(mat, row, mat->width - 1) = value;
	}
	
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the value of the maximum element in the Matrix
int Matrix_max(const Matrix* mat) {
  
  int max = *Matrix_at(mat, 0, 0);
  int tempMax = 0;
  for (int i = 0; i < Matrix_height(mat); i++) {
	  for (int j = 0; j < Matrix_width(mat); j++) {
		 tempMax = *Matrix_at(mat, i, j);
		 if (tempMax > max) {
			 max = tempMax;
		 }
	  }
  }
  return max;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the column of the element with the minimal value
//           in a particular region. The region is defined as elements
//           in the given row and between column_start (inclusive) and
//           column_end (exclusive).
//           If multiple elements are minimal, returns the column of
//           the leftmost one.
int Matrix_column_of_min_value_in_row(const Matrix* mat, int row,
                                      int column_start, int column_end) {
	int min = *(Matrix_at(mat, row, column_start));
	int minColumn = column_start;
	//const int* ptr = Matrix_at(mat, row, column_start);
	for (int j = column_start; j >= column_start && j < column_end; j++) {
		if (*Matrix_at(mat, row, j) < min) {
			min = *Matrix_at(mat, row, j);
			minColumn = j;
			//ptr = Matrix_at(mat, row, j);
		}
	}
	const int* ptr = Matrix_at(mat, row, minColumn);
	return Matrix_column(mat, ptr);
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the minimal value in a particular region. The region
//           is defined as elements in the given row and between
//           column_start (inclusive) and column_end (exclusive).
int Matrix_min_value_in_row(const Matrix* mat, int row,
                            int column_start, int column_end) {
   int minRow = *(Matrix_at(mat, row, column_start));
	//const int *ptr = Matrix_at(mat, row, 0);
		for (int j = column_start; j < column_end; j++) {
			if(*Matrix_at(mat, row, j) < minRow ) {
			minRow = *Matrix_at(mat, row, j);
			//ptr = Matrix_at(mat, row, j);
		}
	}	
	//return *ptr;
		return minRow;
  
}
double averageBeatsPerMinute(const int *album, int numSongs) {
const int *end = album + numSongs;
double mean = 0;
double sum = 0;
	for (const int *ptr = album; ptr < end; ptr++) {
		sum += *ptr;
	}
	mean = sum / numSongs;

	return mean;  
}
void classifyAlbum(const vector<int*> albumList, int numSongs) {
const int * end = albumList + numSongs;
for (int i = 0; i < albumList.size(); i++) {
	if (averageBeatsPerMinute((albumList[i]), numSongs) >= 130) {
		cout << "HIGH ENERGY" << endl;
	}
	else {
		cout << "LOW ENERGY" << endl;
	}
	
}

}

double totalBeats(const int * arr, int length) {
  double total = 0;
  for (const int * start = arr; start < arr + length; start++) {
      total += *start;
  }
  cout << "total: " << total << endl;
  return total;
}

// EFFECTS: Iterates through menu to find the first
//          Sandwich with name matching sandwich_name
//          and returns the price of that sandwich.
//          Returns 0 if no matching Sandwich is found.
double order_sandwich(const string &sandwich_name,
                       vector<int> &menu) {

for (int i = 0; i < menu.size();) {
	if (*(menu[i]) == &sandwich_name) {
		
		*(menu[i]).calculate_price();
	}
	i++;
}
}


					   
					   
}