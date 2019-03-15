#pragma once

#include <iostream>
#include <unistd.h>
#include <sys/time.h>

using namespace std;

void printPhase(unsigned int step, unsigned int steps, 
struct timeval start = {}, struct timeval end = {});
string getFilename(const string &path);
int compareStrings(const void *a, const void *b);
int compareFloats(const void *a, const void *b);
float median(vector<float> &v);
vector<string> getFilenames(string dir);

template <class T>
T constrain(T x, T left, T right);

template <class T>
T max(const std::vector<T> &v);