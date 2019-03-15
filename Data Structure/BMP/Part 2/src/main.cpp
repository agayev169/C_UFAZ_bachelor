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
void unwrapImages(const string &origDirname, const vector<float> &psf, 
    const string &unwrappedDirname = "unwrapped/", bool verbose = true);

int main(int argc, char *argv[]) {
    bool calcpsf = false;                // Calculate PSF?
    string psfInDir = "imgs/";           // Directory to use to calculate PSF
    string psfInFilename = "psf";        // File to read PSF values from
    string psfOutFilename = "psf";       // File to write PSF values to
    unsigned int steps = 10;             // Number of steps during PSF calculation
    unsigned int convX = 5;              // Size of marker
    unsigned int iterations = 10;        // Number of pair of images to be used to calc. PSF
    unsigned int downscaling = 4;        // Downscaling factor
    bool unwrap = false;                 // Unwrap/resize images?
    bool flatten = false;                // Flatten/glue images?
    string unwrapInDir = "imgs/";        // Directory to use to unwrap/resize images
    string unwrapOutDir = "unwrapped/";  // Directory to save unwrapped/resized images
    string flatInDir = "unwrapped/";     // Directory to use to flatten/glue images
    string flatOutFilename = "out.bmp";  // File to save glued images
    bool verbose = true;                 // Show progres?

    char c;
    while ((c = getopt(argc, argv, "hD:p:s:d:S:i:u:P:o:g:O:v")) != -1) {
        if (c == 'h') {
            cout << "This is a script to find PSF(Pixel Scaling Factor) values, \n" << 
                "to scale an image based on PSF values and to glue unwrapped images" << endl;
            cout << endl;
            cout << "-D dirname: To calculate PSF values using images from dirname directory (imgs/ by default)" << endl;
            cout << "-p filename: To calculate PSF values and write it into filename (psf by default)" << endl;
            cout << "-s n: Number of PSF values to be find (10 by default)" << endl;
            cout << "-d n: Downscaling factor. Images will be reduced by n to calculate PSF values (4 by default)" << endl;
            cout << "-S n: Size of a mask to be used to find PSF values (5 by default)" << endl;
            cout << "-i n: Number of images to be analyzed to calculate PSF values (10 by default)" << endl;
            cout << "-P filename: To use PSF values from filename (psf by default) (is not used if -p is used)" << endl;
            cout << endl;
            cout << "-u dirname: To unwrap images from dirname (imgs/ by default)" << endl;
            cout << "-o dirname: To save unwrapped images to dirname (unwrapped/ by default)" << endl;
            cout << endl;
            cout << "-g dirname: To glue images from dirname (unwrapped/ by default)" << endl;
            cout << "-O filename: To save glued image to filename (out.bmp by default)" << endl;
            cout << endl;
            cout << "-v: To stop showing progress" << endl;
            exit(0);
        } else if (c == 'D') {
            calcpsf = true;
            psfInDir = optarg;
        } else if (c == 'p') {
            calcpsf = true;
            psfOutFilename = optarg;
        } else if (c == 's') {
            calcpsf = true;
            steps = atoi(optarg);
        } else if (c == 'd') {
            calcpsf = true;
            downscaling = atoi(optarg);
        } else if (c == 'S') {
            calcpsf = true;
            convX = atoi(optarg);
        } else if (c == 'i') {
            calcpsf = true;
            iterations = atoi(optarg);
        } else if (c == 'u') {
            unwrap = true;
            unwrapInDir = optarg;
        } else if (c == 'P') {
            psfInFilename = optarg;
        } else if (c == 'o') {
            unwrap = true;
            unwrapOutDir = optarg;
        } else if (c == 'g') {
            flatten = true;
            flatInDir = optarg;
        } else if (c == 'O') {
            flatten = true;
            flatOutFilename = optarg;
        } else if (c == 'v') {
            verbose = false;
        } else if (c == '?') {
            cout << "Try " << argv[0] << " -h for help" << endl;
            exit(6);
        } 
    }

    if (!calcpsf && !unwrap && !flatten) {
        cout << "Try " << argv[0] << " -h for help" << endl;
        exit(5);
    }
    vector<float> psf_;
    if (calcpsf) {
		srand(time(NULL));
        auto start = time(NULL); 
        cout << "Calculating PSF..." << endl;
        psf_ = psf(psfInDir, steps, convX, convX, iterations, downscaling, verbose);
        FILE *psfFile;
        if (!(psfFile = fopen(psfOutFilename.c_str(), "wb"))) {
            cout << "Error occured while openning " << psfOutFilename << " to write PSF values" << endl;
            exit(7);
        }
        for (auto i = 0u; i < psf_.size(); ++i) {
        	fprintf(psfFile, "%f\n", psf_[i]);
        }
        cout << "Calculating PSF complete" << endl;
        cout << "Time spent: " << time(NULL) - start << " second(s)" << endl;
    } else {
        FILE *psfFile;
        if (!(psfFile = fopen(psfInFilename.c_str(), "rb"))) {
            cout << "Error occured while openning " << psfInFilename << " to read PSF values" << endl;
            exit(8);
        }
        while (!feof(psfFile)) {
        	float curpsf = 0;
            fscanf(psfFile, "%f", &curpsf);
            if (curpsf > 0)
            	psf_.push_back(curpsf);
        }
    }

    unsigned int unit = 0; // Max shifting
    if (unwrap) {
        auto start = time(NULL);
        cout << "Unwraping..." << endl;
        unit = psf_.back();
        psf_.pop_back();
        unwrapImages(unwrapInDir, psf_, unwrapOutDir, verbose);
        cout << "Unwraping complete" << endl;
        cout << "Time spent: " << time(NULL) - start << " second(s)" << endl;
    } 

    if (flatten) {
        auto start = time(NULL);
        cout << "Flattening..." << endl;
        if (unit == 0) {
            unit = psf_.back();
            psf_.pop_back();
        }
        BMPImage res = BMPImage::glue(getFilenames(flatInDir), unit, verbose);
        res.save(flatOutFilename);
        cout << "Flattening complete" << endl;
        cout << "Time spent: " << time(NULL) - start << " second(s)" << endl;
    }

    return 0;
}

// This function gets a directory name and parses all the ".bmp" format files from it
vector<string> getFilenames(string dir) {
    vector<string> images;
    if (dir[dir.size() - 1] != '/') dir += '/';
    DIR *d = opendir(dir.c_str());
    if (d) {
        struct dirent *ent;
        while ((ent = readdir(d)) != NULL) {
            string filename = ent->d_name;
            if (filename[0] != '.' && filename.size() >= 4 && 
                filename.substr(filename.size() - 4, filename.size()) == ".bmp") {
                images.push_back(dir + ent->d_name);
            }
        }
    } 

    qsort(&images[0], images.size(), sizeof(images[0]), compareStrings); // images in ascending order
    return images;
}


vector<float> psf(const string &dirname, unsigned int steps, unsigned int convX, 
    unsigned int convY,  unsigned int iterations, unsigned int downscaling, bool verbose) {
    vector<string> images = getFilenames(dirname);

    vector<pair<string, string>> imagePairs(images.size() - 1); // Pair of the images - candidates to be used in calculation
    for (auto i = 0u; i < images.size() - 1; ++i) {
        imagePairs[i] = make_pair(images[i], images[i + 1]);
    }

    vector<vector<float>> psfs(min((unsigned int) (images.size() - 1), iterations), 
                               vector<float>(steps));

    if (verbose)
        printPhase(0, min(iterations, (unsigned int) images.size() - 1));
    for (auto i = 0u; i < images.size() - 1 && i < iterations; ++i) {
        auto start = time(NULL);
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
        if (verbose)
            printPhase(i + 1, min(iterations, (unsigned int) images.size() - 1), time(NULL) - start);
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

void unwrapImages(const string &origDirname, const vector<float> &psf, 
    const string &unwrappedDirname, bool verbose) {
    vector<string> images = getFilenames(origDirname);

    mkdir(unwrappedDirname.c_str(), 0777); 
    string dir = unwrappedDirname;
    if (dir[dir.size() - 1] != '/') dir += '/';
    if (verbose)
        printPhase(0, images.size());
    for (auto i = 0u; i < images.size(); ++i) {
        auto start = time(NULL);
        BMPImage img(images[i]);
        auto img2 = img.scaleBasedOnPSF(psf).cropStrip(img.getWidth());
        img2.save(dir + getFilename(images[i]));
        if (verbose)
            printPhase(i + 1, images.size(), time(NULL) - start);
    }
}