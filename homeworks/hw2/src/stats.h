//
// File: stats.h
// stats.h is the interface for functions in a simple statistics module.
//
// @author csci243: Mechanics Course Account
// @author tss2344: Thomas Schollenberger
//
// @date 01/03/2022
//
// // // // // // // // // // // // // // // // // // // // // // //

#ifndef _STATS_H_
#define _STATS_H_

/**
 * @brief Computes the average of a set of scores in an int array
 * 
 * @param count number of scores in the scores array
 * @param scores int array containing the scores to be averaged
 * @return double
 */
double average( int count, const int scores[] );

/**
 * @brief Computes the standard deviation of a set of scores
 * 
 * @param count number of scores in the scores array
 * @param scores int array containing the scores to generate the standard deviation of
 * @param mean the average of the scores
 * @return double 
 */
double std_dev( int count, const int scores[], double mean );

/**
 * @brief Outputs a visible histogram of the scores
 * 
 * @param count number of scores in the scores array
 * @param scores int array containing the scores to generate the histogram of
 */
void histogram(int count, const int scores[]);

#endif
