#include "bmp.hpp"

// Constructors
BMPImage::BMPImage(const std::string &fileName) {
    if (fileName.empty()) { // Check if any argument is passed 
        std::cerr << "Error! Cannot open the file " << fileName << std::endl;
        exit(1);
    }

    FILE *file = fopen(fileName.c_str(), "rb");

    if (!file) { //Check if file is opened
        std::cerr << "Error! Cannot open the file " << fileName << std::endl;
        exit(2);
    }

    // BMP Header

    // First 2 bytes (BM)
    char ch[2];
    fread(ch, 1, 2, file);
    if (!(ch[0] == 'B' && ch[1] == 'M')) { // Check if a file is of BMP format
        std::cerr << "Error!" << fileName << " is not a BMP file" << std::endl;
        exit(3);
    }

    // Size of file
    int size = 0;
    fread(&size, 1, 4, file);
    size = abs(size);

    // 4 bytes reserved for application
    fseek(file, 4, SEEK_CUR);

    // pixels' start
    fread(&sizeOfHeader_, 4, 1, file);

    // DIB Header

    fseek(file, 0, SEEK_SET);
    header_ = (char*) calloc(sizeOfHeader_, sizeof(char));
    fread(header_, 1, sizeOfHeader_, file);
    // file >> header;
    fseek(file, 18, SEEK_SET);

    // Width of image
    int width = 0;
    fread(&width, 4, 1, file);
    width_ = abs(width);

    // Height of image
    int height = 0;
    fread(&height, 4, 1, file);
    height_ = (unsigned int) abs(height);

    // Number of color panels
    fseek(file, 2, SEEK_CUR);

    // Nubmer of bits for pixel
    int bytesPerPixel = 0;
    fread(&bytesPerPixel, 2, 1, file);
    bytesPerPixel_ = abs(bytesPerPixel / 8);

    // Finally pixels!
    fseek(file, sizeOfHeader_, SEEK_SET);
    
    // Reading the whole image
    int padding = (4 - (width_ * bytesPerPixel_) % 4) % 4;

    pixels_ = (unsigned char*) 
        calloc(width_ * height_ * bytesPerPixel_, sizeof(unsigned char));
    for (auto i = 0u; i < height_; ++i) {
        auto size_ = fread(&(pixels_[i * width_ * bytesPerPixel_]), 1, width_ * bytesPerPixel_, file);
        if (size_ != width_ * bytesPerPixel_) {
            std::cout << "Read: " << size_ << "\t supposed to read: " << width_ * bytesPerPixel_ << std::endl;
            std::cout << "Problem with " << fileName << std::endl;
            std::cout << "i: " << i << std::endl;
            std::cout << "height_: " << height_ << std::endl;
            exit(4);
        }
        fseek(file, padding, SEEK_CUR);
    }


    fclose(file);
}

BMPImage::BMPImage() {} // Default constructor to create an empty BMPImage

// Copy constructor - used in case of creating a new BMPImage and assigning an old BMPImage object to it
BMPImage::BMPImage(const BMPImage &original) {
    width_ = original.width_;
    height_ = original.height_;
    bytesPerPixel_ = original.bytesPerPixel_;
    sizeOfHeader_ = original.sizeOfHeader_;
    
    header_ = (char*) calloc(sizeOfHeader_, sizeof(char));
    for (auto i = 0u; i < sizeOfHeader_; ++i) {
        header_[i] = original.header_[i];
    }
    
    pixels_ = (unsigned char*) calloc(height_ * width_ * bytesPerPixel_, sizeof(unsigned char));
    for (auto i = 0u; i < height_ * width_ * bytesPerPixel_; ++i) {
        pixels_[i] = original.pixels_[i];
    }
}

// Assignment operator - used in case of assigning one BMPImage object to another one
BMPImage& BMPImage::operator=(const BMPImage &original) {
    width_ = original.width_;
    height_ = original.height_;
    bytesPerPixel_ = original.bytesPerPixel_;
    sizeOfHeader_ = original.sizeOfHeader_;
    
    if (header_) free(header_);
    header_ = (char*) calloc(sizeOfHeader_, sizeof(char));
    for (auto i = 0u; i < sizeOfHeader_; ++i) {
        header_[i] = original.header_[i];
    }
    
    if (pixels_) free(pixels_);
    pixels_ = (unsigned char*) calloc(height_ * width_ * bytesPerPixel_, sizeof(unsigned char));
    for (auto i = 0u; i < height_ * width_ * bytesPerPixel_; ++i) {
        pixels_[i] = original.pixels_[i];
    }

    return *this;
}

// Destructor
BMPImage::~BMPImage() {
    free(pixels_);
    free(header_);
}

void BMPImage::save(const std::string &fileName) const {
    int padding = (4 - (width_ * bytesPerPixel_) % 4) % 4;

    FILE *file = fopen(fileName.c_str(), "wr");
    
    // Writing a header of original file
    fwrite(header_, 1, sizeOfHeader_, file);

    // Changing size of file
    fseek(file, 2, SEEK_SET);
    int size = sizeOfHeader_ + bytesPerPixel_ * width_ * height_;
    fwrite(&size, 1, 4, file);
    
    // Changing width of image
    fseek(file, 18, SEEK_SET);
    fwrite(&width_, 1, 4, file);
    int h = -height_; // Negative height used to flip image vertically
    fwrite(&h, 1, 4, file);
    fseek(file, sizeOfHeader_, SEEK_SET);

    int zero = 0;
    for (auto y = 0u; y < height_; ++y) {
        fwrite(&(pixels_[y * width_ * bytesPerPixel_]), 1, width_ * bytesPerPixel_, file);
        if (padding)
            fwrite(&zero, 1, padding, file);
    }

    fclose(file);
}

void BMPImage::cropAndSave(const std::string &fileName, int stripSize) const {
    int padding = (4 - (stripSize * bytesPerPixel_) % 4) % 4;

    // New width
    int width = stripSize;

    int start = width_ / 2 - stripSize / 2;

    FILE *file = fopen(fileName.c_str(), "wr");
    
    // Writing a header of original file
    fwrite(header_, 1, sizeOfHeader_, file);

    // Changing size of file
    fseek(file, 2, SEEK_SET);
    int size = sizeOfHeader_ + bytesPerPixel_ * width * height_;
    fwrite(&size, 1, 4, file);
    
    // Changing width of image
    fseek(file, 18, SEEK_SET);
    fwrite(&width, 1, 4, file);
    fseek(file, sizeOfHeader_, SEEK_SET);

    int zero = 0;
    for (auto y = 0u; y < height_; ++y) {
        fwrite(&(pixels_[(y * width_ + start) * bytesPerPixel_]), 1, width * bytesPerPixel_, file);
        if (padding)
            fwrite(&zero, 1, padding, file);
    }

    fclose(file);
}

// Function to crop a strip of size stripSize from an image
BMPImage BMPImage::cropStrip(unsigned int stripSize) const {
    BMPImage result = BMPImage();
    
    result.sizeOfHeader_ = sizeOfHeader_;
    result.header_ = (char*) calloc(sizeOfHeader_, sizeof(char));
    for (auto i = 0u; i < sizeOfHeader_; ++i) {
        result.header_[i] = header_[i];
    }

    result.width_ = stripSize; 
    result.height_ = height_;
    result.bytesPerPixel_ = bytesPerPixel_;
    result.pixels_ = (unsigned char*) calloc(height_ * stripSize * bytesPerPixel_, sizeof(unsigned char));

    unsigned int start = (width_ - stripSize) / 2;
    for (auto y = 0u; y < height_; ++y) {
        for (auto x = 0u; x < stripSize; ++x) {
            for (auto z = 0u; z < bytesPerPixel_; ++z) {
                result.pixels_[(y * stripSize + x) * bytesPerPixel_ + z] = 
                    pixels_[(y * width_ + x + start) * bytesPerPixel_ + z];
            }
        }
    }


    return result;
}

// Function to crop the image (Not used)
BMPImage BMPImage::crop(unsigned int x0, unsigned int x1, unsigned int y0, unsigned int y1) const {
    // Constrain the x and y values to be inside the image
    x0 = constrain(x0, 0u, width_);
    x1 = constrain(x1, 0u, width_);
    y0 = constrain(y0, 0u, height_);
    y1 = constrain(y1, 0u, height_);

    // x0 should be less than x1
    if (x0 > x1) {
        unsigned int tmp = x0;
        x0 = x1;
        x1 = tmp;
    }

    // y0 should be less than y1
    if (y0 > y1) {
        unsigned int tmp = y0;
        y0 = y1;
        y1 = tmp;
    }

    BMPImage result;
    result.height_ = y1 - y0;
    result.width_ = x1 - x0;
    result.bytesPerPixel_ = bytesPerPixel_;

    result.pixels_ = (unsigned char*) calloc(result.height_ * result.width_ * bytesPerPixel_, 
        sizeof(unsigned char));
    result.sizeOfHeader_ = sizeOfHeader_;
    result.header_ = (char*) calloc(sizeOfHeader_, sizeof(char));
    for (auto i = 0u; i < sizeOfHeader_; ++i) {
        result.header_[i] = header_[i];
    }

    for (auto y = 0u; y < result.height_; ++y) {
        for (auto x = 0u; x < result.width_; ++x) {
            for (auto z = 0u; z < bytesPerPixel_; ++z) {
                result.pixels_[(y * result.width_ + x) * bytesPerPixel_ + z] = 
                    pixels_[((y + y0) * width_ + x + x0) * bytesPerPixel_ + z];
            }
        }
    }

    return result;
}

// Function to resize images using givn PSF values
BMPImage BMPImage::scaleBasedOnPSF(const std::vector<float> &psf) const {
    BMPImage result; 

    result.height_ = height_;
    result.width_ = max(psf) * width_;
    result.bytesPerPixel_ = bytesPerPixel_;
    result.pixels_ = (unsigned char*) calloc(height_ * result.width_ * bytesPerPixel_, 
        sizeof(unsigned char));
    
    result.sizeOfHeader_ = sizeOfHeader_;
    result.header_ = (char*) calloc(sizeOfHeader_, sizeof(char));
    for (auto i = 0u; i < sizeOfHeader_; ++i) {
        result.header_[i] = header_[i];
    }
    
    for (auto i = 0u; i < psf.size(); ++i) {
        unsigned int yStart = height_ / psf.size() * i; // Starting y position
        float factor = psf[i]; // PSF value to be used on i-th step
        unsigned int curWidth = width_ * psf[i]; // Width of the i-th step
        unsigned int xStart = (result.width_ - curWidth) / 2; // Starting x position (img should be centered)
        for (auto y = 0u; y < height_ / psf.size(); ++y) {
            unsigned int xRes = 0; // x-counter for resulting image
            unsigned int xOrig = 0; // x-counter for original image
            float written = 0; // Number of pixels written on the last iteration

            while (xOrig < width_ && xRes < result.width_) {
                if (factor >= 1 - written) { // Case when we can fully insert the data from old image to new
                    float curFactor = 1 - written; // How many to write?
                    for (auto z = 0u; z < bytesPerPixel_; ++z) {
                        result.pixels_[((yStart + y) * 
                            result.width_ + xRes + xStart) * bytesPerPixel_ + z] += curFactor *
                            pixels_[((yStart + y) * width_ + xOrig) * bytesPerPixel_ + z];
                    }
                    written = 0; // Everythin is written, reset variable
                    ++xRes; // New pixel on the resulting image
                    if (factor == 0) { // If all the data from the current pixel is written
                        ++xOrig; // Go to new pixel
                        factor = psf[i]; // Reset the factor
                    } else
                        factor -= curFactor; // Else factor is now less by the written amount
                } else { // Case when we cannot fully insert the data from old image to new
                    for (auto z = 0u; z < bytesPerPixel_; ++z) {
                        result.pixels_[((yStart + y) * 
                            result.width_ + xRes + xStart) * bytesPerPixel_ + z] += factor *
                            pixels_[((yStart + y) * width_ + xOrig) * bytesPerPixel_ + z];
                    }
                    written = factor; // factor < 1 - written => written = factor
                    factor = psf[i]; // Reset the factor
                    ++xOrig; // Go to new pixel
                }
            }
        }
    }

    return result;
}

// Function to downscale the image by given factor
BMPImage BMPImage::reduceBy(unsigned int factor) const {
    BMPImage result;
    result.sizeOfHeader_ = sizeOfHeader_;
    result.header_ = (char*) calloc(sizeOfHeader_, sizeof(char));
    for (auto i = 0u; i < sizeOfHeader_; ++i) {
        result.header_[i] = header_[i];
    }

    result.width_ = width_ / (float) factor; 
    result.height_ = height_ / (float) factor; 
    result.bytesPerPixel_ = bytesPerPixel_;
    result.pixels_ = (unsigned char*) calloc(result.height_ * result.width_ * result.bytesPerPixel_, sizeof(unsigned char));

    for (auto i = 0u; i < result.height_; ++i) {
        for (auto y = i * factor; y < height_ && y < (i + 1) * factor; ++y) {
            for (auto j = 0u; j < result.width_; ++j) {
                for (auto x = j * factor; x < width_ && x < (j + 1) * factor; ++x) {
                    for (auto z = 0u; z < bytesPerPixel_; ++z) {
                        result.pixels_[(i * result.width_ + j) * bytesPerPixel_ + z] +=
                            pixels_[(y * width_ + x) * bytesPerPixel_ + z] / (factor * factor);
                    }
                }
            }
        }
    }

    return result;
}

// Function to glue given images based on the diffMax = shift of the images 
BMPImage BMPImage::glue(const std::vector<std::string> &images, 
    float diffMax, bool verbose) {
    if (images.size() == 0) {
        std::cerr << "Error. No images to glue" << std::endl;
        exit(8);
    }
    
    BMPImage first(images[0]);

    BMPImage result;
    result.sizeOfHeader_ = first.sizeOfHeader_;
    result.header_ = (char*) calloc(result.sizeOfHeader_, sizeof(char));
    for (auto i = 0u; i < result.sizeOfHeader_; ++i) {
        result.header_[i] = first.header_[i];
    }


    result.width_ = diffMax * images.size(); // New width
    result.height_ = first.height_; 
    result.bytesPerPixel_ = first.bytesPerPixel_;
    result.pixels_ = (unsigned char*) calloc(result.height_ * result.width_ * result.bytesPerPixel_, sizeof(unsigned char));

    if (verbose)
        printPhase(0, images.size());
    for (auto i = 0u; i < images.size(); ++i) {
        struct timeval start;
        struct timeval end;
        gettimeofday(&start, NULL);
        BMPImage curImg(images[i]); // Get an image
        curImg = curImg.cropStrip(diffMax); // Crop a strip from it and add it to a new image
        for (auto y = 0u; y < result.height_; ++y) {
            for (auto x = 0u; x < curImg.width_; ++x) {
                for (auto z = 0u; z < first.bytesPerPixel_; ++z) {
                    result.pixels_[(y * result.width_ + i * curImg.width_ + x) * first.bytesPerPixel_ + z] =
                        curImg.pixels_[(y * curImg.width_ + x) * first.bytesPerPixel_ + z];
                }
            }
        }
        gettimeofday(&end, NULL);
        if (verbose)
            printPhase(i + 1, images.size(), start, end);
    }

    return result;
}

unsigned int BMPImage::getWidth() const {
    return width_;
}

unsigned int BMPImage::getHeight() const {
    return height_;
}

unsigned int BMPImage::getBytesPerPixel() const {
    return bytesPerPixel_;
}