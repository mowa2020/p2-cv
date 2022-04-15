// Project UID af1f95f547e44c8ea88730dfb185559d

#include <cassert>
#include "processing.h"

using namespace std;



// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_left is provided for you.
// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the left (counterclockwise).
void rotate_left(Image* img) {

    // for convenience
    int width = Image_width(img);
    int height = Image_height(img);

    // auxiliary image to temporarily store rotated image
    Image* aux = new Image;
    Image_init(aux, height, width); // width and height switched

    // iterate through pixels and place each where it goes in temp
    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
            Image_set_pixel(aux, width - 1 - c, r, Image_get_pixel(img, r, c));
        }
    }

    // Copy data back into original
    *img = *aux;
    delete aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_right is provided for you.
// REQUIRES: img points to a valid Image.
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the right (clockwise).
void rotate_right(Image* img) {

    // for convenience
    int width = Image_width(img);
    int height = Image_height(img);

    // auxiliary image to temporarily store rotated image
    Image* aux = new Image;
    Image_init(aux, height, width); // width and height switched

    // iterate through pixels and place each where it goes in temp
    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
            Image_set_pixel(aux, c, height - 1 - r, Image_get_pixel(img, r, c));
        }
    }

    // Copy data back into original
    *img = *aux;
    delete aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------


// v DO NOT CHANGE v ------------------------------------------------
// The implementation of diff2 is provided for you.
static int squared_difference(Pixel p1, Pixel p2) {
    int dr = p2.r - p1.r;
    int dg = p2.g - p1.g;
    int db = p2.b - p1.b;
    // Divide by 100 is to avoid possible overflows
    // later on in the algorithm.
    return (dr * dr + dg * dg + db * db) / 100;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------


// ------------------------------------------------------------------
// You may change code below this line!





// REQUIRES: img points to a valid Image.
//           energy points to a Matrix.
// MODIFIES: *energy
// EFFECTS:  energy serves as an "output parameter".
//           The Matrix pointed to by energy is initialized to be the same
//           size as the given Image, and then the energy matrix for that
//           image is computed and written into it.
//           See the project spec for details on computing the energy matrix.
//energy(X) = squared_difference(N, S) + squared_difference(W, E)
void compute_energy_matrix(const Image* img, Matrix* energy) {
    
    //int width = Image_width(img);
    //int height = Image_height(img);
    
    //int max = 0;


    /*for (int i = 1; i < height - 1; i++) {
        for (int k = 1; k < width - 1; k++) {
            *Matrix_at(energy, i, k)= squared_difference
            (Image_get_pixel(img, i + 1, k),
            Image_get_pixel(img, i - 1, k))
                + squared_difference(Image_get_pixel(img, i, k + 1),
                Image_get_pixel(img, i, k - 1));
            
            if (*Matrix_at(energy, i, k) < max) {
                max = *Matrix_at(energy, i, k);
            }
            cout << *Matrix_at(energy, i, k);
        }
        cout << endl;
    }



    //Matrix_print(energy, cout);

    Matrix_fill_border(energy, max);
    Matrix_init(energy, width, height);
    Matrix_fill(energy, 0);
    int temp = 0;
    int max = 0;
    for (int i = 1; i < height - 1; i++) {
        for (int k = 0; k < width - 1; k++) {
            temp = squared_difference(Image_get_pixel(img, i + 1, k), 
            Image_get_pixel(img, i - 1, k))
                + squared_difference(Image_get_pixel(img, i, k + 1),
                Image_get_pixel(img, i, k - 1));
            *Matrix_at(energy, i, k) = temp;
            //Matrix_at(energy, i, k) = temp;
            if (max < temp) {
                max = temp;
            }
        }
    }
    Matrix_fill_border(energy, max);*/

    Matrix_init(energy, Image_width(img), Image_height(img));
    Matrix_fill(energy, 0);
    int totalRow = Image_height(img);
    int totColumn = Image_width(img);
    int maxEnergy = 0;
    int temp = 0;
    for (int i = 1; i < totalRow - 1; i++) {
        for (int k = 1; k < totColumn - 1; k++) {
            int *changed = Matrix_at(energy, i, k);
            temp = squared_difference(Image_get_pixel(img, i + 1, k), 
                Image_get_pixel(img, i - 1, k))
                + squared_difference(Image_get_pixel(img, i, k + 1), 
                    Image_get_pixel(img, i, k - 1));
            *changed = temp;
            if (maxEnergy < temp) {
                maxEnergy = temp;
            }
        }
    }

    Matrix_fill_border(energy, maxEnergy);

    //int width = Image_width(img);
    //int height = Image_height(img);

    //if statement index 0
    //for (int i = 0; i < Matrix_height(energy); i++){
       // for (int j = 0; j < Matrix_width(energy); j++) {
          //  if (Matrix_at(energy, i, j) != 0) {
                //energy = squared_difference(i, j)
          //  }
        // }
   // } 
    //(squared_difference(Pixel(), Pixel()));
}


// REQUIRES: energy points to a valid Matrix.
//           cost points to a Matrix.
//           energy and cost aren't pointing to the same Matrix
// MODIFIES: *cost
// EFFECTS:  cost serves as an "output parameter".
//           The Matrix pointed to by cost is initialized to be the same
//           size as the given energy Matrix, and then the cost matrix is
//           computed and written into it.
//           See the project spec for details on computing the cost matrix.
void compute_vertical_cost_matrix(const Matrix* energy, Matrix* cost) {
    Matrix_init(cost, Matrix_width(energy), Matrix_height(energy));
    int columns = Matrix_width(energy);
    for (int i = 0; i < columns; i++) {
        *Matrix_at(cost, 0, i) = *Matrix_at(energy, 0, i);

        //not sure if it is with or without the asterict
    }
    int rows = Matrix_height(energy);
    int costValue = 0;
    for (int k = 1; k < rows; k++) {
        for (int a = 0; a < columns; a++) {
            costValue = *Matrix_at(energy, k, a);
            if (a > 0 && a < columns - 1) {
                costValue += Matrix_min_value_in_row(cost, k - 1, a - 1, a + 2);
            }
            else if (a == 0) {
                costValue += Matrix_min_value_in_row(cost, k - 1, a, a + 2);
            }
            else if (a == columns - 1) {
                costValue += Matrix_min_value_in_row(cost, k - 1, a - 1, a+1);
            }
            *Matrix_at(cost, k, a) = costValue;
        }
    }
    // Matrix_init(cost, Image_width(energy), energy->height);
     //for (int i = 0; i < Matrix_at(cost, 0, 3); i++) {
        // Matrix_at(cost, i, 3) = energy;
     //}
}


// REQUIRES: cost points to a valid Matrix
//           seam points to an array
//           the size of seam is >= Matrix_height(cost)
// MODIFIES: seam[0]...seam[Matrix_height(cost)-1]
// EFFECTS:  seam serves as an "output parameter".
//           The vertical seam with the minimal cost according to the given
//           cost matrix is found and the seam array is filled with the column
//           numbers for each pixel along the seam, with the pixel for each
//           row r placed at seam[r]. While determining the seam, if any pixels
//           tie for lowest cost, the leftmost one (i.e. with the lowest
//           column number) is used.
//           See the project spec for details on computing the minimal seam.
// NOTE:     You should compute the seam in reverse order, starting
//           with the bottom of the image and proceeding to the top,
//           as described in the project spec.
void find_minimal_vertical_seam(const Matrix* cost, int seam[]) {
    // TODO Replace with your implementation!

    int height = Matrix_height(cost);
    int width = Matrix_width(cost);

    int minOne = Matrix_column_of_min_value_in_row(cost, height-1, 0, width - 1);
    seam[height - 1] = minOne;

    for (int i = height - 2; i >= 0; i--) {
        int preRow = seam[i + 1];
        if (preRow > 0 && preRow < width - 1) {
            seam[i] = Matrix_column_of_min_value_in_row(cost, i, preRow - 1, preRow + 2);
        }
        else if (preRow == 0) {
            seam[i] = Matrix_column_of_min_value_in_row(cost, i, preRow, preRow + 2);
        }
        else if (preRow == width - 1) {
            seam[i] = Matrix_column_of_min_value_in_row(cost, i, preRow - 1, preRow + 1);
        }
    }
}


// REQUIRES: img points to a valid Image with width >= 2
//           seam points to an array
//           the size of seam is == Image_height(img)
//           each element x in seam satisfies 0 <= x < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Removes the given vertical seam from the Image. That is, one
//           pixel will be removed from every row in the image. The pixel
//           removed from row r will be the one with column equal to seam[r].
//           The width of the image will be one less than before.
//           See the project spec for details on removing a vertical seam.
// NOTE:     Use the new operator here to create the smaller Image,
//           and then use delete when you are done with it.

// does not seem to be issue
void remove_vertical_seam(Image* img, const int seam[]) {
    // TODO Replace with your implementation!

    Image* temp = new Image;
    Image_init(temp, Image_width(img) - 1, Image_height(img));
    for (int i = 0; i < Image_height(img); i++) {
        int counter = 0;
        for (int a = 0; a < Image_width(img); a++) {
            if (seam[i] != a) {
                Image_set_pixel(temp, i, counter, 
                    Image_get_pixel(img, i, a));
                counter++;
            }
        }
    }
    /*for (int i = 0; i < Image_height(temp); i++) {
        for (int a = 0; a < seam[i]; a++) {
            Image_set_pixel(temp, i, a, Image_get_pixel(img, i, a));
        }
        for (int k = seam[i] + 1; k < Image_width(img); k++) {
            Image_set_pixel(temp, i, k-1, Image_get_pixel(img, i, k));
        }
    }


    Image_init(img, Image_width(temp), Image_height(temp));

    for (int j = 0; j < Image_height(img); j++) {
        for (int l = 0; l < Image_width(img); l++) {
            Image_set_pixel(img, j, l, Image_get_pixel(temp, j, l));
        }
    }*/
    *img = *temp;
    delete temp;
}


// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width of the given Image to be newWidth by using
//           the seam carving algorithm. See the spec for details.
// NOTE:     Use the new operator here to create Matrix objects, and
//           then use delete when you are done with them.
void seam_carve_width(Image* img, int newWidth) {
    // TODO Replace with your implementation!
    int seam[MAX_MATRIX_HEIGHT];
    for (int i = Image_width(img); i > newWidth; i--) {
        Matrix* test = new Matrix;
        //Matrix_init(test, Image_width(img), Image_height(img));
        Matrix* cost = new Matrix;
        //Matrix_init(cost, Image_width(img), Image_height(img));
        compute_energy_matrix(img, test);
       
        compute_vertical_cost_matrix(test, cost);

        find_minimal_vertical_seam(cost, seam);
        
        remove_vertical_seam(img, seam);

        delete test;
        delete cost;
    } 
}

// REQUIRES: img points to a valid Image
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the height of the given Image to be newHeight.
// NOTE:     This is equivalent to first rotating the Image 90 degrees left,
//           then applying seam_carve_width(img, newHeight), then rotating
//           90 degrees right.
void seam_carve_height(Image* img, int newHeight) {
    // TODO Replace with your implementation!
    rotate_left(img);
    seam_carve_width(img, newHeight);
    rotate_right(img);
}

// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width and height of the given Image to be newWidth
//           and newHeight, respectively.
// NOTE:     This is equivalent to applying seam_carve_width(img, newWidth)
//           and then applying seam_carve_height(img, newHeight).
void seam_carve(Image* img, int newWidth, int newHeight) {
    // TODO Replace with your implementation!
    seam_carve_width(img, newWidth);
    seam_carve_height(img, newHeight);
}