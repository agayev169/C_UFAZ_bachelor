#include <iostream>
#include <ctime>
#include <dirent.h>
#include <unistd.h>
#include <sys/time.h>
#include "tensor.cpp"
#include "bmp.cpp"
#include "marker.cpp"
#include "utils.cpp"

using namespace std;

vector<float> psf(const string &dirname, unsigned int steps = 10, unsigned int convX = 7, 
    unsigned int convY = 7, unsigned int iterations = 10, unsigned int downscaling = 4, bool verbose = true);

int main(int argc, char *argv[]) {
    unsigned int stripSize = 0;               // Size of strip to be croped from original images
    string psfInFilename = "psf";             // File to read PSF values from
    string inDir = "imgs/";                   // Directory to use to flatten/glue images
    string out = "glued.bmp";                 // File to save glued images
    bool verbose = true;                      // Show progres?

    char c;
    while ((c = getopt(argc, argv, "hs:p:i:o:v")) != -1) {
        if (c == 'h') {
            cout << "This is a program to glue several images into one" << endl;
            cout << endl;
            cout << "-s n: Size of a strip to be croped from images before glueing" << endl;
            cout << "-p filename: To use PSF values from filename (psf by default)" << endl;
            cout << "-i dirname: To glue images from dirname (imgs/ by default)" << endl;
            cout << "-o filename: To save glued image to filename (glued.bmp by default)" << endl;
            cout << endl;
            cout << "-v: To stop showing progress" << endl;
            exit(0);
        } else if (c == 's') {
            stripSize = atoi(optarg);
        } else if (c == 'p') {
            psfInFilename = optarg;
        } else if (c == 'i') {
            inDir = optarg;
        } else if (c == 'o') {
            out = optarg;
        } else if (c == 'v') {
            verbose = false;
        } else if (c == '?') {
            cout << "Try " << argv[0] << " -h for help" << endl;
            exit(6);
        } 
    }

    if (psfInFilename != "psf" && stripSize != 0) {
        cout << "Not allowed to use -s and -p together" << endl;
        cout << "Try " << argv[0] << " -h for help" << endl;
        exit(5);
    }

    if (stripSize == 0) {        
        FILE *psfFile;
        if (!(psfFile = fopen(psfInFilename.c_str(), "rb"))) {
            cout << "Error occured while openning " << psfInFilename << " to read PSF values" << endl;
            exit(8);
        }
        while (!feof(psfFile)) {
            float curpsf = 0;
            fscanf(psfFile, "%f", &curpsf);
            if (curpsf > 0)
                stripSize = curpsf;
        }
    }

    struct timeval start;
    struct timeval end;
    gettimeofday(&start, NULL);
    if (verbose)
        cout << "Gluing..." << endl;
    BMPImage res = BMPImage::glue(getFilenames(inDir), stripSize, verbose);
    res.save(out);
    if (verbose) {
        cout << "Gluing complete" << endl;
        gettimeofday(&end, NULL);
        float dt = end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 10e6;
        cout << "Time spent: " << dt << " second(s)" << endl;
    }

    return 0;
}