// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Image_test_helpers.h"
#include "unit_test_framework.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  cout << "Test Print Basic"; 
  cout << endl;
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());
  cout << "PASS";
  cout << endl;
  delete img; // delete the Image
}

// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.h as needed.

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() 

TEST(Test_width) {
  cout << "Test width"; 
  cout << endl;
    Image* img1 = new Image;
    Image_init(img1, 3, 4);
    cout << Image_width(img1);
    ASSERT_TRUE(Image_width(img1) == 3);
    cout << "PASS";
    cout << endl;

    delete img1;
	}

TEST(Test_height) {
    cout << "Test height";
    cout << endl;
    Image* img1 = new Image;
      Image_init(img1, 3, 4);
    ASSERT_TRUE(Image_height(img1) == 4);
    cout << "PASS";
    cout << endl;

    delete img1;
}

TEST(Test_imagePrint) {
Image *img = new Image;
   Image_init(img, 2, 2);
   const Pixel red = {255, 0, 0};
   ostringstream image;
   Image_fill(img, red);
   Image_print(img, image);

  ostringstream correct;
  correct << "P3" << endl;
  correct << "2 2" << endl;
  correct << "255" << endl;
  correct << "255 0 0 255 0 0 " << endl;
  correct << "255 0 0 255 0 0 " << endl;
  ASSERT_EQUAL(image.str(), correct.str());

  delete img;
}

TEST(Test_getPixel) {
Image *img = new Image;
   Image_init(img, 5, 5);
   const Pixel red = {255, 0, 0};
   Image_fill(img, red);

   ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 2, 2), red));
  
  delete img;
}

TEST(Test_setPixel) {
Image *img = new Image;
   Image_init(img, 5, 5);
   const Pixel red = {255, 0, 0};
   Pixel green = {0, 255, 0};
   Image_fill(img, red);
   
   Image_set_pixel(img, 1, 1, green);
   ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 1, 1), green));
  delete img;
}

TEST(test_imgfill) {
 Image *img = new Image;
   Image_init(img, 5, 5);
   const Pixel red = {255, 0, 0};
   Image_fill(img, red);

  for(int r = 0; r < 5; ++r){
    for(int c = 0; c < 5; ++c){
       ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, r, c), red));;
    }
  }

  delete img; 
}

