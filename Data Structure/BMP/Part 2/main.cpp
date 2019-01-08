#include <iostream>
#include <ctime>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include "tensor.cpp"
#include "bmp.cpp"
#include "conv.cpp"
#include "printer.cpp"
#include <unistd.h>

using namespace std;

vector<float> psf(const string &dirname, unsigned int steps = 10, unsigned int convX = 7, 
    unsigned int convY = 7, unsigned int iterations = 10, unsigned int downscaling = 4, bool verbose = true);
void unwrapImages(const string &origDirname, const vector<float> &psf, 
    const string &unwrappedDirname = "unwrapped/", bool verbose = true);
string getFilename(const string &path);
int compareStrings(const void *a, const void *b);

vector<string> getFilenames(string dir);
float median(vector<float> &v);

int main(int argc, char *argv[]) {
    bool calcpsf = false;
    string psfInFilename = "psf";
    string psfOutFilename = "psf";
    unsigned int steps = 10;
    unsigned int convX = 5;
    unsigned int convY = 5;
    unsigned int iterations = 10;
    unsigned int downscaling = 4;
    bool unwrap = false;
    bool flatten = false;
    string psfindir = "imgs/";
    string indir = "imgs/";
    string outdir = "unwrapped/";
    string flatIndir = "unwrapped/";
    string flatOutpath = "out.bmp";
    bool verbose = true;

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
            psfindir = optarg;
        } else if (c == 'p') {
            calcpsf = true;
            psfOutFilename = optarg;
        } else if (c == 's') {
            calcpsf = true;
            steps = atoi(optarg);
        } else if (c == 'S') {
            calcpsf = true;
            convX = convY = atoi(optarg);
        } else if (c == 'i') {
            calcpsf = true;
            iterations = atoi(optarg);
        } else if (c == 'u') {
            unwrap = true;
            indir = optarg;
        } else if (c == 'P') {
            psfInFilename = optarg;
        } else if (c == 'o') {
            unwrap = true;
            outdir = optarg;
        } else if (c == 'g') {
            flatten = true;
            flatIndir = optarg;
        } else if (c == 'O') {
            flatten = true;
            flatOutpath = optarg;
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
        psf_ = psf(indir, steps, convX, convY, iterations, downscaling, verbose);
        FILE *psfFile;
        if (!(psfFile = fopen(psfOutFilename.c_str(), "wb"))) {
            cout << "Error occured while openning " << psfOutFilename << " to write PSF values" << endl;
            exit(7);
        }
        fwrite(&psf_[0], sizeof(psf_[0]), psf_.size(), psfFile);
        cout << "Calculating PSF complete" << endl;
        cout << "Time spent: " << time(NULL) - start << " second(s)" << endl;
    } else {
        FILE *psfFile;
        if (!(psfFile = fopen(psfInFilename.c_str(), "rb"))) {
            cout << "Error occured while openning " << psfInFilename << " to read PSF values" << endl;
            exit(8);
        }
        fseek(psfFile, 0, SEEK_END);
        unsigned int end = ftell(psfFile);
        fseek(psfFile, 0, SEEK_SET);
        for (auto i = 0u; i < end; i += sizeof(float)) {
            float curpsf = 0;
            fread(&curpsf, sizeof(float), 1, psfFile);
            psf_.push_back(curpsf);
        }
    }

    unsigned int unit = 0;
    if (unwrap) {
        auto start = time(NULL);
        cout << "Unwraping..." << endl;
        unit = psf_.back();
        psf_.pop_back();
        unwrapImages(indir, psf_, outdir, verbose);
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
        BMPImage res = BMPImage::glue(getFilenames(flatIndir), psf_, unit, verbose);
        res.save(flatOutpath);
        cout << "Flattening complete" << endl;
        cout << "Time spent: " << time(NULL) - start << " second(s)" << endl;
    }

    return 0;
}

vector<string> getFilenames(string dir) {
    vector<string> images;
    if (dir[dir.size() - 1] != '/') dir += '/';
    DIR *d = opendir(dir.c_str());
    if (d) {
        struct dirent *ent;
        while ((ent = readdir(d)) != NULL) {
            if (ent->d_name[0] != '.')
                images.push_back(dir + ent->d_name);
        }
    } 

    qsort(&images[0], images.size(), sizeof(images[0]), compareStrings); // images in ascending order
    return images;
}

vector<float> psf(const string &dirname, unsigned int steps, unsigned int convX, 
    unsigned int convY,  unsigned int iterations, unsigned int downscaling, bool verbose) {
    vector<string> images = getFilenames(dirname);

    vector<pair<string, string>> imagePairs(images.size() - 1);
    for (auto i = 0u; i < images.size() - 1; ++i) {
        imagePairs[i] = make_pair(images[i], images[i + 1]);
    }

    qsort(&images[0], images.size(), sizeof(images[0]), compareStrings); // images in ascending order

    float avgStepTime = 0;
    vector<vector<float>> psfs(min((unsigned int) (images.size() - 1), iterations), vector<float>(steps));

    unsigned int scaleFactor = downscaling;
    if (verbose)
        printPhase(0, min(iterations, (unsigned int) images.size() - 1));
    for (auto i = 0u; i < images.size() - 1 && i < iterations; ++i) {
        BMPImage img1(images[i]);
        BMPImage img2(images[i + 1]);
        if (iterations < images.size() - 1) {
            unsigned int index = rand() % imagePairs.size();
            img1 = BMPImage(imagePairs[index].first);
            img2 = BMPImage(imagePairs[index].second);
            imagePairs.erase(imagePairs.begin() + index);
        }
        auto start = time(NULL);
        auto img1_scaled = img1.reduceBy(scaleFactor);
        auto img2_scaled = img2.reduceBy(scaleFactor);
        Conv conv1(steps, convX, convY, img1_scaled.getBytesPerPixel());
        conv1.findMaxSTD(img1_scaled);
        auto conv2 = conv1.findSimilar(img2_scaled);
        img1_scaled.save(to_string(i * 2) + ".bmp");
        img2_scaled.save(to_string(i * 2 + 1) + ".bmp");
        auto pos1 = conv1.getPos();
        auto pos2 = conv2.getPos();
        for (auto j = 0u; j < psfs[0].size(); ++j) {
            psfs[i][j] = (pos1[j].first - pos2[j].first) * scaleFactor;
        }
        if (verbose)
            printPhase(i + 1, min(iterations, (unsigned int) images.size() - 1), time(NULL) - start);

        avgStepTime += time(NULL) - start;
    }


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

int compareStrings(const void *a, const void *b) {
    string lstr = *(const string *) a;
    string rstr = *(const string *) b;
    
    int l = 0;
    for (auto i = 0u; i < lstr.size(); ++i) {
    	if (lstr[i] >= '0' && lstr[i] <= '9')
    		l = l * 10 + lstr[i] - '0';
    }
    
    int r = 0;
    for (auto i = 0u; i < rstr.size(); ++i) {
    	if (rstr[i] >= '0' && rstr[i] <= '9')
    		r = r * 10 + rstr[i] - '0';
    }
    return l > r;
}

int compareFloats(const void *a, const void *b) {
    float l = *(const float *) a;
    float r = *(const float *) b;
    return l > r;
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

string getFilename(const string &path) {
    string filename = "";
    for (int i = path.size() - 1; i >= 0; --i) {
        if (path[i] == '/') break;
        filename = path[i] + filename;
    }
    return filename;
}

float median(vector<float> &v) {
    qsort(&v[0], v.size(), sizeof(v[0]), compareFloats);
    if (v.size() % 2 == 0) {
        return (v[v.size() / 2] + v[v.size() / 2 - 1]) / 2;
    }
    return v[v.size() / 2];
}
