/**
 * @file            stats.cpp
 * @author          your CWL
 * @description     Implementation of Stats functions
 *
 * THIS FILE WILL BE SUBMITTED
**/

#include "stats.h"

Stats::Stats(PNG& im) {
    //maybe set up a local variable for the image for easy access
    //setup sum and sumsq vectors for all channels using GetSum and GetSumSq
}


int64_t Stats::GetSum(char channel, pair<int, int> ul, int w, int h) {
    //create a local int64_t variable
    //repeat the below process depending on the channel
    //find the proper position for x and y by subtracting the ul x and y from
    //the current x and y (vector[0] = vector[currx - ulx], etc.)
    //resize the outer vector to h
    //loop through y values in the associated sum vector (0 to h - 1)
        //resize the inner vector to w
        //loop through x values in the inner vector (0 to w - 1)
        //add the specified channel value to the local variable 
        //and place them in the vector
    //return the local variable

	return 0;
}

int64_t Stats::GetSumSq(char channel, pair<int, int> ul, int w, int h) {
    //same as GetSum but instead, setting each vector to the squared 
    //difference between the channel and GetAvg's channel
    //return the sum of squared differences
	return 0;
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
	return RGBAPixel();
}

/****************************************************************
* IF YOU HAVE DEFINED ANY PRIVATE FUNCTIONS IN stats-private.h, *
* ADD YOUR IMPLEMENTATIONS BELOW                                *
****************************************************************/

