// Project UID af1f95f547e44c8ea88730dfb185559d

#include <cassert>
#include "Image.h"

using namespace std;

// REQUIRES: img points to an Image
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *img
// EFFECTS:  Initializes the Image with the given width and height.
// NOTE:     Do NOT use new or delete here.
void Image_init(Image* img, int width, int height) {

	img->height = height;
	img->width = width;
	Matrix_init(&(img->red_channel), width, height);
	Matrix_init(&(img->green_channel), width, height);
	Matrix_init(&(img->blue_channel), width, height);

}

// REQUIRES: img points to an Image
//           is contains an image in PPM format without comments
//           (any kind of whitespace is ok)
// MODIFIES: *img
// EFFECTS:  Initializes the Image by reading in an image in PPM format
//           from the given input stream.
// NOTE:     See the project spec for a discussion of PPM format.
// NOTE:     Do NOT use new or delete here.
void Image_init(Image* img, std::istream& is) {

	//string p = "P3";
		//= img->width;
	// = img->height;
	int maxInten = MAX_INTENSITY;
	string p;
	int height, width;
	is >> p;
	is >> width >> height;
	img->height = height;
	img->width = width;
	is >> maxInten;
	Matrix_init(&(img->red_channel), width, height);
	Matrix_init(&(img->green_channel), width, height);
	Matrix_init(&(img->blue_channel), width, height);
	
	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			/*int* red, * blue, * green;
			red = Matrix_at(&img->red_channel, i, k);
			green = Matrix_at(&img->green_channel, i, k);
			blue = Matrix_at(&img->blue_channel, i, k);
			
			is >> *red;
			is >> *green;
			is >> *blue;*/

			is >> *Matrix_at(&img->red_channel, i, k);
			is >> *Matrix_at(&img->green_channel, i, k);
			is >> *Matrix_at(&img->blue_channel, i, k);

			//Matrix test = { width,height,MAX_MATRIX_HEIGHT * MAX_MATRIX_WIDTH };
			//cout << endl << endl;
			//cout << red1 << " " << green1 << " " << blue1 << endl;
			
			//*red = red1;
			//*green = green1;
			//*blue = blue1;
			
		}
	}
	//Image_print(img, cout);
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Writes the image to the given output stream in PPM format.
//           You must use the kind of whitespace specified here.
//           First, prints out the header for the image like this:
//             P3 [newline]
//             WIDTH [space] HEIGHT [newline]
//             255 [newline]
//           Next, prints out the rows of the image, each followed by a
//           newline. Each pixel in a row is printed as three ints
//           for its red, green, and blue components, in that order. Each
//           int is followed by a space. This means that there will be an
//           "extra" space at the end of each line. See the project spec
//           for an example.
void Image_print(const Image* img, std::ostream& os) {

	os << "P3" << endl;
	os << img->width << " " << img->height << endl;
	os << "255" << endl;

	for (int i = 0; i < Image_height(img); i++) {
		for (int j = 0; j < Image_width(img); j++) {
			
			Pixel pie;

			pie.r = *Matrix_at(&img->red_channel, i, j);
			pie.g = *Matrix_at(&img->green_channel, i, j);
			pie.b = *Matrix_at(&img->blue_channel, i, j);

			os << pie.r << " " << pie.g << " " << pie.b << " ";

			//Pixel p = (Image_get_pixel(img, i, j));
			//os << p.r << " " << p.g << " " << p.b << " ";

		}
		os << endl;
	}
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the width of the Image.
int Image_width(const Image* img) {

	int width = img->width;
	return width;
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the height of the Image.
int Image_height(const Image* img) {

	int height = img->height;
	return height;

}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// EFFECTS:  Returns the pixel in the Image at the given row and column.
Pixel Image_get_pixel(const Image* img, int row, int column) {


	Pixel pie;

	pie.r = *Matrix_at(&img->red_channel, row, column);
	pie.g = *Matrix_at(&img->green_channel, row, column);
	pie.b = *Matrix_at(&img->blue_channel, row, column);

	return pie;
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Sets the pixel in the Image at the given row and column
//           to the given color.
void Image_set_pixel(Image* img, int row, int column, Pixel color) {
	//Matrix_at(img->red_channel, row, column);
	//Matrix *holderred = &img->red_channel;
	
	//Matrix_init(&(img->red_channel), img->width, img->height);
	//Matrix_init(&(img->green_channel), img->width, img->height);
	//Matrix_init(&(img->blue_channel), img->width, img->height);
	

	*Matrix_at(&img->red_channel, row, column) = color.r;
	*Matrix_at(&img->green_channel, row, column) = color.g;
	*Matrix_at(&img->blue_channel, row, column) = color.b;
	/*int* redM = Matrix_at(&img->red_channel, row, column);
	*redM = color.r;
	//img->red_channel
	int* greenM = Matrix_at(&img->green_channel, row, column); 
	*greenM = color.g;
	int* blueM = Matrix_at(&img->blue_channel, row, column);
	*blueM = color.b;*/

	/*for (int i = 0; i < Image_height(img); i++) {
		for (int j = 0; j < Image_width(img); i++) {
			Image_get_pixel(img, row, column) = color;
		}
	}*/
}

// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  Sets each pixel in the image to the given color.
void Image_fill(Image* img, Pixel color) {
	
	for (int i = 0; i < Image_height(img); i++) {
		for (int j = 0; j < Image_width(img); j++) {
			Image_set_pixel(img, i, j, color);
		}
	}
}