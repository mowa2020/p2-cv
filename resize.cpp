// Project UID af1f95f547e44c8ea88730dfb185559d
#include "processing.h"
#include <string>
#include <cstring>
#include <fstream>
using namespace std;

int main(int argc, char* argv[]) {
	if (argc != 4 && argc != 5) {
		cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n";
		cout << "WIDTH and HEIGHT must be less than or equal to original";
		cout << endl;
		return 1;
	}
	ifstream fin;
	string file_name = argv[1];
	fin.open(file_name.c_str());
	cout << file_name << endl;
	if (!fin.is_open()) {
		cout << "Error opening file: " << argv[0] << endl;
		return 1;
	}
	Image* img = new Image;
	Image_init(img, fin);
	if (argc == 5) {
		int dWidth = atoi(argv[3]);
		int dheight = atoi(argv[4]);
		if (dWidth <= 0 || dWidth > Image_width(img)) {
			cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n";
			cout << "WIDTH and HEIGHT must be less than or equal to original";
			cout << endl;
			return 1;
		}
		if (dheight <= 0 || dheight > Image_height(img)) {
			cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n";
			cout << "WIDTH and HEIGHT must be less than or equal to original";
			cout << endl;
			return 1;
		}
		seam_carve(img, dWidth, dheight);
	}
	else if (argc == 4) {
		int dWidth = atoi(argv[3]);
		int dheight = Image_height(img);
		if (dWidth <= 0 || dWidth > Image_width(img)) {
			cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n";
			cout << "WIDTH and HEIGHT must be less than or equal to original";
			cout << endl;
			return 1;
		}
		seam_carve(img, dWidth, dheight);
	}
	string outputName = argv[2];
	ofstream fout(outputName.c_str());
	Image_print(img, fout);
	delete img;
}