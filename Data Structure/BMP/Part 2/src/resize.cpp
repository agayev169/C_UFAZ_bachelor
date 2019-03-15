#include <iostream>
#include <ctime>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include "tensor.cpp"
#include "bmp.cpp"
#include "marker.cpp"
#include "utils.cpp"

using namespace std;

void resizeImages(const string &in, const vector<float> &psf, 
    const string &out);

int main(int argc, char *argv[]) {
    string psfFilename = "psf";        // File to read PSF values from
    string inImg = "";                 // Directory to get images to resize
    string outImg = "";                // Directory to save resized images
    bool verbose = true;

    char c;
    while ((c = getopt(argc, argv, "hp:i:o:v")) != -1) {
        if (c == 'h') {
            cout << "This is a program to resize an image based on PSF values" << endl;
            cout << endl;
            cout << "-p filename: To use PSF values from filename (psf by default)" << endl;
            cout << "-i filename: To resize filename image" << endl;
            cout << "-o filename: To save resized image into filename (inputFileResized.bmp by default)" << endl;
            cout << endl;
            cout << "-v: To stop showing progress" << endl;
            exit(0);
        } else if (c == 'p') {
            psfFilename = optarg;
        } else if (c == 'i') {
            inImg = optarg;
        } else if (c == 'o') {
            outImg = optarg;
        } else if (c == 'v') {
            verbose = false;
        } else if (c == '?') {
            cout << "Try " << argv[0] << " -h for help" << endl;
            exit(6);
        } 
    }

    if (inImg.empty()) {
        cout << "Usage: " << argv[0] << " -i filename" << endl;
        cout << "Try " << argv[0] << " -h for help" << endl;
        exit(7);
    }

    vector<float> psf_;
    FILE *psfFile;
    if (!(psfFile = fopen(psfFilename.c_str(), "rb"))) {
        cout << "Error occured while openning " << psfFilename << " to read PSF values" << endl;
        exit(8);
    }
    while (!feof(psfFile)) {
        float curpsf = 0;
        fscanf(psfFile, "%f", &curpsf);
        if (curpsf > 0)
            psf_.push_back(curpsf);
    }
    psf_.pop_back();

    struct timeval start;
    struct timeval end;
    gettimeofday(&start, NULL);
    if (verbose) {
        cout << "Resizing..." << endl;
    }
    resizeImages(inImg, psf_, outImg);
    if (verbose) {
        cout << "Resizing complete" << endl;
        gettimeofday(&end, NULL);
        float dt = end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 10e6;
        cout << "Time spent: " << dt << " second(s)" << endl;
    }

    return 0;
}

void resizeImages(const string &in, const vector<float> &psf, 
    const string &out) {
    string output = out;
    BMPImage img(in);
    auto img2 = img.scaleBasedOnPSF(psf).cropStrip(img.getWidth());
    if (output.empty()) {
        output = in;
        if (output.substr(output.size() - 4, 4) == ".bmp") {
            output = output.substr(0, output.size() - 4);
        }
        output += "Resized.bmp";
    }
    img2.save(output);
}