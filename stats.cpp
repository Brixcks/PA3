/**
 * @file            stats.cpp
 * @author          your CWL
 * @description     Implementation of Stats functions
 *
 * THIS FILE WILL BE SUBMITTED
**/

#include "stats.h"

Stats::Stats(PNG& im) {
    //setup sum and sumsq vectors for all channels
}

//take the bottom right corner of the rectangle at coordinates
//(x + w-1, y + h-1) and subtract areas as necessary
//if x and y are 0, do nothing
//if x is greater than 0, subtract (x-1, y)
//if y is greater than 0, subtract (x, y-1)
//if both are greater than 0, subtract both points and add (x-1, y-1)
//return the value for the appropriate channel
int64_t Stats::GetSum(char channel, pair<int, int> ul, int w, int h) {
    //channel selection
    if (channel == r) {
        sumUp(sumRed, ul, w, h);
    } else if (channel == g) {
        sumUp(sumGreen, ul, w, h);
    } else if (channel == b) {
        sumUp(sumBlue, ul, w, h);
    } else {
        return 0;
    }
}

//same as GetSum but with the sumsq vectors
int64_t Stats::GetSumSq(char channel, pair<int, int> ul, int w, int h) {
    //channel selection
    if (channel == r) {
        sumUp(sumsqRed, ul, w, h);
    } else if (channel == g) {
        sumUp(sumsqGreen, ul, w, h);
    } else if (channel == b) {
        sumUp(sumsqBlue, ul, w, h);
    } else {
        return 0;
    }
}

/**
 * Given a rectangle, compute its sum of squared deviations from mean, over all color channels.
 * See written specification for a description of this function.
**/
double Stats::GetVar(pair<int, int> ul, int w, int h) {
    //return the sum of GetSumSq from each channel
    int64_t rSq = GetSumSq(char r, ul, w, h);
    int64_t gSq = GetSumSq(char g, ul, w, h);
    int64_t bSq = GetSumSq(char b, ul, w, h);
    double varSum = (rSq + gSq + bSq);
	return varSum;
}

//divide the sums for each channel by the w x h
//make a new pixel using the averaged values and return it
RGBAPixel Stats::GetAvg(pair<int, int> ul, int w, int h) {
    //set sum variables for each channel using GetSum
    int64_t rSum = GetSum(char r, ul, w, h);
    int64_t gSum = GetSum(char g, ul, w, h);
    int64_t bSum = GetSum(char b, ul, w, h);
    //divide each sum by w x h
    int ravg = (rSum/(w*h));
    int gavg = (gSum/(w*h));
    int bavg = (bSum/(w*h));
    //make a new pixel with the averaged channels
    RGBAPixel avg = new RGBAPixel(ravg, gavg, bavg);
	return avg;
}

/****************************************************************
* IF YOU HAVE DEFINED ANY PRIVATE FUNCTIONS IN stats-private.h, *
* ADD YOUR IMPLEMENTATIONS BELOW                                *
****************************************************************/

//helper for GetSum and GetSumSq
//outer represents the color channel vector being considered
//ul is the (x, y) coordinates of the upper-left corner of the rectangle 
//w and h are the width and height of the rectangle
int64_t sumUp(vector<vector<int64_t>> outer, pair<int, int> ul, int w, int h) {
    int x = ul.first;
    int y = ul.second;
    //the vector corresponding to the y value of the bottom of the rectangle
    vector<int64_t> bottom = outer[y + (h - 1)];
    //the sum of all color values over the area from (0, 0) 
    //to the bottom right corner of the rectangle
    int64_t overall = bottom[x + (w - 1)];
    if ((x == 0) && (y == 0)) {
        return overall;
    } else if ((x > 0) && (y == 0)) {
        //the sum of all color values to the left of the rectangle's area
        int64_t left = bottom[x - 1];
        return (overall - left);
    } else if ((x == 0) && (y > 0)) {
        //the vector corresponding to y value just above the rectangle
        vector<int64_t> top = outer[y - 1];
        //the sum of all color values above the rectangle's area
        int64_t above = top[x];
        return (overall - above);
    } else {
        //area above the rectangle
        vector<int64_t> top = outer[y - 1];
        int64_t above = top[x];
        //area to the left of the rectangle
        int64_t left = bottom[x - 1];
        //area overlapped by the above two
        int64_t overlap = top[x - 1];
        return (overall - above - left + overlap);
    }
}


//sets up the sum and sumsq vectors for each channel
//works similarly to GetSum when placing values
void Stats::setupVectors(PNG& img) {
    //resize vectors such that the outer vector's size is h
    //resize each inner vector to a size of w
    //loop through every pixel in the image
    //y value is the outer vector's index 
    //x is the inner vector's index
    //for every pixel/index, run a summation helper function
    //similar to sumUp
}
