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

vector<float> psf(const string &dirname, unsigned int steps = 10, unsigned int convX = 7, 
    unsigned int convY = 7, unsigned int iterations = 10, unsigned int downscaling = 4, bool verbose = true);

int main(int argc, char *argv[]) {
    string inDir = "imgs/";
    string out = "psf";
    unsigned int steps = 10;             // Number of steps during PSF calculation
    unsigned int convX = 5;              // Size of marker
    unsigned int iterations = 10;        // Number of pair of images to be used to calc. PSF
    unsigned int downscaling = 4;        // Downscaling factor
    bool verbose = true;                 // Show progres?

    char c;
    while ((c = getopt(argc, argv, "hD:o:s:d:S:i:v")) != -1) {
        if (c == 'h') {
            cout << "This is a program for calcuating PSF(Pixel Scaling Factor) values" << endl;
            cout << endl;
            cout << "-D dirname: To calculate PSF values using images from dirname directory (imgs/ by default)" << endl;
            cout << "-o filename: To save PSF values into filename (psf by default)" << endl;
            cout << "-s n: Number of PSF values to be find (10 by default)" << endl;
            cout << "-d n: Downscaling factor. Images will be reduced by n to calculate PSF values (4 by default)" << endl;
            cout << "-S n: Size of a marker to be used to find PSF values (5 by default)" << endl;
            cout << "-i n: Number of images to be analyzed to calculate PSF values (10 by default)" << endl;
            cout << endl;
            cout << "-v: To stop showing progress" << endl;
            exit(0);
        } else if (c == 'D') {
            inDir = optarg;
        } else if (c == 'o') {
            out = optarg;
        } else if (c == 's') {
            steps = atoi(optarg);
        } else if (c == 'd') {
            downscaling = atoi(optarg);
        } else if (c == 'S') {
            convX = atoi(optarg);
        } else if (c == 'i') {
            iterations = atoi(optarg);
        } else if (c == 'v') {
            verbose = false;
        } else if (c == '?') {
            cout << "Try " << argv[0] << " -h for help" << endl;
            exit(6);
        } 
    }

    vector<float> psf_;
    srand(time(NULL));
    struct timeval start;
    struct timeval end;
    gettimeofday(&start, NULL);
    if (verbose)
        cout << "Calculating PSF..." << endl;
    psf_ = psf(inDir, steps, convX, convX, iterations, downscaling, verbose);
    FILE *psfFile;
    if (!(psfFile = fopen(out.c_str(), "wb"))) {
        cout << "Error occured while openning " << out << " to write PSF values" << endl;
        exit(7);
    }
    for (auto i = 0u; i < psf_.size(); ++i) {
        fprintf(psfFile, "%f\n", psf_[i]);
    }
    if (verbose) {
        cout << "Calculating PSF complete" << endl;
        gettimeofday(&end, NULL);
        float dt = end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 10e6;
        cout << "Time spent: " << dt << " second(s)" << endl;
    }

    return 0;
}


vector<float> psf(const string &dirname, unsigned int steps, unsigned int convX, 
    unsigned int convY,  unsigned int iterations, unsigned int downscaling, bool verbose) {
    vector<string> images = getFilenames(dirname);
    if (images.size() == 0) {
        std::cerr << "Error. No images to calculate PSF values" << std::endl;
        exit(8);
    }

    vector<pair<string, string>> imagePairs(images.size() - 1); // Pair of the images - candidates to be used in calculation
    for (auto i = 0u; i < images.size() - 1; ++i) {
        imagePairs[i] = make_pair(images[i], images[i + 1]);
    }

    vector<vector<float>> psfs(min((unsigned int) (images.size() - 1), iterations), 
                               vector<float>(steps));

    if (verbose)
        printPhase(0, min(iterations, (unsigned int) images.size() - 1));
    for (auto i = 0u; i < images.size() - 1 && i < iterations; ++i) {
        struct timeval start;
        struct timeval end;
        gettimeofday(&start, NULL);
        BMPImage img1(images[i]);
        BMPImage img2(images[i + 1]);
        if (iterations < images.size() - 1) { 
            // If all the images will not be used in calculation we choose random pairs
            unsigned int index = rand() % imagePairs.size();
            img1 = BMPImage(imagePairs[index].first);
            img2 = BMPImage(imagePairs[index].second);
            imagePairs.erase(imagePairs.begin() + index);
        }
        auto img1_scaled = img1.reduceBy(downscaling);
        auto img2_scaled = img2.reduceBy(downscaling);
        Marker conv1(steps, convX, convY, img1_scaled.getBytesPerPixel()); // Create a marker
        conv1.findMaxSTD(img1_scaled); // Find distinguishable spots on the image
        auto conv2 = conv1.findSimilar(img2_scaled); // Find same spots on the second image
        auto pos1 = conv1.getPos();
        auto pos2 = conv2.getPos();
        for (auto j = 0u; j < psfs[0].size(); ++j) {
            psfs[i][j] = (pos1[j].first - pos2[j].first) * downscaling;
        }
        gettimeofday(&end, NULL);
        if (verbose)
            printPhase(i + 1, min(iterations, (unsigned int) images.size() - 1), start, end);
    }

    // Finding medians
    vector<vector<float>> psfsTranspose(steps, vector<float>(min((unsigned int) (images.size() - 1), iterations)));
    for (auto i = 0u; i < psfs.size(); ++i) {
        for (auto j = 0u; j < psfs[0].size(); ++j) {
            psfsTranspose[j][i] = psfs[i][j];
        }
    }

    vector<float> medians(steps);
    for (auto i = 0u; i < medians.size(); ++i) {
        medians[i] = median(psfsTranspose[i]);
    }

    // Excluding "fake" data points from the population
    vector<unsigned int> psfCount(steps);
    vector<float> psf(steps);
    for (auto i = 0u; i < psfs.size(); ++i) {
        for (auto j = 0u; j < medians.size(); ++j) {
            if (abs(medians[j] - psfs[i][j]) <= medians[j] / 5) {
                psf[j] += psfs[i][j];
                ++psfCount[j];
            }
        }
    }


    for (auto i = 0u; i < psf.size(); ++i) {
        psf[i] /= psfCount[i];
    }

    // Finding maximum shift 
    float maxPSF = psf[0];
    for (auto i = 1u; i < psf.size(); ++i) {
        if (psf[i] > maxPSF) maxPSF = psf[i];
    }
    psf.push_back(maxPSF);
    for (auto i = 0u; i < psf.size() - 1; ++i) {
        psf[i] = maxPSF / psf[i];
    }

    return psf;
}