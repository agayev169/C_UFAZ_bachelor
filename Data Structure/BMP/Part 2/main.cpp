#include <iostream>
#include <ctime>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include "tensor.cpp"
#include "bmp.cpp"
#include "conv.cpp"

using namespace std;

vector<float> psf(const string &dirname, unsigned int steps = 10, unsigned int convX = 7, unsigned int convY = 7, unsigned int iterations = 10);
int compar(const void *a, const void *b);
void unwrapImages(const string &origDirname, const vector<float> &psf, const string &unwrapedDirname = "unwraped/");
string getFilename(const string &path);

void flatten(const string &dirname, unsigned int unit);
unsigned char constrain(float c);

int main(int argc, char *argv[]) {
    string imgdir = "imgs/";

    // // vector<float> psf_ = psf(imgdir, 10, 15, 15);
    // vector<float> psf_ = {43.2, 50, 83.6667, 59.6667, 66.8, 69.5333, 74.3333, 76.9333, 79.4667, 80.4};
    // for (auto i = 0u; i < psf_.size(); ++i) {
    //     psf_[i] = 83.667 / psf_[i];
    // }
    // for (auto i = 0u; i < psf_.size(); ++i) {
    //     cout << psf_[i] << endl;
    // }
    // unsigned int unit = psf_.back();
    // psf_.pop_back();
    // unwrapImages(imgdir, psf_);

    flatten("unwraped/", 70);

    return 0;
}

vector<float> psf(const string &dirname, unsigned int steps, unsigned int convX, unsigned int convY,  unsigned int iterations) {
    vector<float> psf(steps);
    vector<string> images;
    DIR *d = opendir(dirname.c_str());
    if (d) {
        struct dirent *ent;
        while ((ent = readdir(d)) != NULL) {
            if (ent->d_name[0] != '.')
                images.push_back(dirname + ent->d_name);
        }
    } 

    qsort(&images[0], images.size(), sizeof(images[0]), compar); // images in ascending order
    cout << "images:" << endl;
    for (auto i = 0u; i < images.size(); ++i) {
        cout << images[i] << endl;
    }
    cout << endl;

    float avgStepTime = 0;

    for (auto i = 0u; i < images.size() - 1 && i < iterations; ++i) {
        auto start = time(NULL);
        BMPImage img1(images[i]);
        BMPImage img2(images[i + 1]);
        Conv conv1(steps, convX, convY, img1.getBytesPerPixel());
        conv1.findMaxSTD(img1);
        auto conv2 = conv1.findSimilar(img2);
        // img1.save(to_string(i * 2) + ".bmp");
        // img2.save(to_string(i * 2 + 1) + ".bmp");
        auto pos1 = conv1.getPos();
        auto pos2 = conv2.getPos();
        for (auto j = 0u; j < steps; ++j) {
            psf[j] += pos1[j].first - pos2[j].first;
        }
        cout << (i + 1) << " steps out of " << images.size() - 1 << 
            " are complete. Time spent for a step: " << time(NULL) - start << endl;
        avgStepTime += time(NULL) - start;
    }
    cout << "Average step time: " << avgStepTime / (min(iterations, (unsigned int) images.size() - 1)) << " seconds" << endl;

    float maxPsf = 0;
    for (auto i = 0u; i < steps; ++i) {
        psf[i] /= min(iterations, (unsigned int) images.size() - 1);
        if (psf[i] > maxPsf) maxPsf = psf[i];
    }

    for (auto i = 0u; i < steps; ++i) {
        cout << psf[i] << endl;
    }

    psf.push_back(maxPsf);

    for (auto i = 0u; i < steps; ++i) {
        psf[i] = maxPsf / psf[i];
    }

    return psf;
}

int compar(const void *a, const void *b) {
    string l = *(const string *)a;
    string r = *(const string *)b;
    return l > r;
}

void unwrapImages(const string &origDirname, const vector<float> &psf, const string &unwrapedDirname) {
    vector<string> images;
    DIR *d = opendir(origDirname.c_str());
    if (d) {
        struct dirent *ent;
        while ((ent = readdir(d)) != NULL) {
            if (ent->d_name[0] != '.')
                images.push_back(origDirname + ent->d_name);
        }
    } 

    qsort(&images[0], images.size(), sizeof(images[0]), compar); // images in ascending order

    mkdir(unwrapedDirname.c_str(), 0777);
    string dir = unwrapedDirname;
    if (dir[dir.size() - 1] != '/') dir += '/';
    for (auto i = 0u; i < images.size(); ++i) {
        BMPImage img(images[i]);
        auto img2 = img.scaleBasedOnPSF(psf).cropStrip(img.getWidth());
        img2.save(dir + getFilename(images[i]));
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

void flatten(const string &dirname, unsigned int unit) {
    vector<string> images;
    DIR *d = opendir(dirname.c_str());
    if (d) {
        struct dirent *ent;
        while ((ent = readdir(d)) != NULL) {
            if (ent->d_name[0] != '.')
                images.push_back(dirname + ent->d_name);
        }
    } 

    qsort(&images[0], images.size(), sizeof(images[0]), compar); // images in ascending order
    if (images.size() == 0) return;

    BMPImage curImg = BMPImage(images[0]);
    BMPImage result(curImg, curImg.getWidth() + (images.size() - 1) * unit, curImg.getHeight());
    // for (auto i = 0u; i < result.getHeight() * result.getWidth() * result.getBytesPerPixel(); ++i) 
    //     result.pixels_[i] = result.pixels_[i] / (curImg.getWidth() / unit);
    // float factor = 1.0 / (curImg.getWidth() / unit + 2);
    for (auto i = 1u; i < images.size(); ++i) {
        auto img = BMPImage(images[i]);
        for (auto y = 0u; y < img.getHeight(); ++y) {
            for (auto x = unit * i; x < img.getWidth() + i * unit && x < result.getWidth(); ++x) {
                bool isBlack = true;
                for (auto z = 0u; z < result.getBytesPerPixel(); ++z) {
                    if (result.pixels_[(y * result.getWidth() + x) * result.getBytesPerPixel() + z] != 0) {
                        isBlack = false;
                        break;
                    }
                }
                for (auto z = 0u; z < result.getBytesPerPixel(); ++z) {
                    if (isBlack)
                        result.pixels_[(y * result.getWidth() + x) * result.getBytesPerPixel() + z] =  
                            img.pixels_[(y * img.getWidth() + x - (unit * i)) * img.getBytesPerPixel() + z];
                    else 
                        result.pixels_[(y * result.getWidth() + x) * result.getBytesPerPixel() + z] =   
                            0.5 * result.pixels_[(y * result.getWidth() + x) * result.getBytesPerPixel() + z] + 
                            0.5 * img.pixels_[(y * img.getWidth() + x - (unit * i)) * img.getBytesPerPixel() + z];
                    // result.pixels_[(y * result.getWidth() + x) * result.getBytesPerPixel() + z] += constrain(factor * 
                    //     img.pixels_[(y * img.getWidth() + x - (unit * i)) * img.getBytesPerPixel() + z]);
                // for (auto x = img.getWidth() + (i - 1) * unit; x < img.getWidth() + i * unit; ++x) {
                        // img.pixels_[(y * img.getWidth() + img.getWidth() - unit + x - (img.getWidth() + (i - 1) * unit))
                            // * img.getBytesPerPixel() + z];
                }
            }
        }
    }

    // for (auto i = 0u; i < result.getHeight() * result.getWidth() * result.getBytesPerPixel(); ++i) {

    // }
            

    result.save(dirname + "flat.bmp");
}

unsigned char constrain(float c) {
    return (c > 255) ? 255 : (c < 0) ? 0 : c;
}