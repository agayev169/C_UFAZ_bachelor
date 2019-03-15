#include "utils.hpp"
#include <unistd.h>
#include <sys/time.h>

using namespace std;

// Function to print the progress
void printPhase(unsigned int step, unsigned int steps, 
struct timeval start, struct timeval end) {
    unsigned int loadNum = 40;
    std::cout << step << "/" << steps << "|";
    unsigned int complete = step * loadNum / steps;
    for (auto i = 0u; i < complete; ++i) {
        std::cout << ">";
    }
    for (auto i = complete; i < loadNum; ++i) {
        std::cout << "=";
    }
    std::cout << "|";
    float dt = end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 10e6;
    if (dt != 0)
        std::cout << dt;
    std::cout << std::endl;
}


// Function to parse filename from full path
string getFilename(const string &path) {
    string filename = "";
    for (int i = path.size() - 1; i >= 0; --i) {
        if (path[i] == '/') break;
        filename = path[i] + filename;
    }
    return filename;
}

// Function to calculate a median of the set
float median(vector<float> &v) {
    qsort(&v[0], v.size(), sizeof(v[0]), compareFloats);
    if (v.size() % 2 == 0) {
        return (v[v.size() / 2] + v[v.size() / 2 - 1]) / 2;
    }
    return v[v.size() / 2];
}


// Function to compare 2 strings
int compareStrings(const void *a, const void *b) {
    string lstr = *(const string *) a;
    string rstr = *(const string *) b;
    
    // Find an integer in the filename
    int l = 0;
    for (auto i = 0u; i < lstr.size(); ++i) {
    	if (lstr[i] >= '0' && lstr[i] <= '9')
    		l = l * 10 + lstr[i] - '0';
    }
    
    // Find an integer in the filename
    int r = 0;
    for (auto i = 0u; i < rstr.size(); ++i) {
    	if (rstr[i] >= '0' && rstr[i] <= '9')
    		r = r * 10 + rstr[i] - '0';
    }

    // Compare integers
    return l > r;
}

// Function to compare 2 float values
int compareFloats(const void *a, const void *b) {
    float l = *(const float *) a;
    float r = *(const float *) b;
    return l > r;
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
    } else {
        cerr << "Error. Cannot open " << dir << " directory" << endl;
        exit(9);
    }

    qsort(&images[0], images.size(), sizeof(images[0]), compareStrings); // images in ascending order
    return images;
}

// Function to constrain some x between left and right
template <class T>
T constrain(T x, T left, T right) {
    return (x < left) ? left : (x > right) ? right : x;
}

// Function to find the maximum value from the vector
template <class T>
T max(const std::vector<T> &v) {
    if (v.size() == 0) return 0;
    T max_ = v[0];
    for (T val : v) {
        if (max_ < val) {
            max_ = val;
        }
    }
    return max_;
}