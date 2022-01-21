//
// File: stats.h
// stats.h is the interface for functions in a simple statistics module.
//
// @author csci243: Mechanics Course Account
// @author TODO complete with your login and full name
//
// @date 01/03/2022
//
// // // // // // // // // // // // // // // // // // // // // // //

// TODO ADD INCLUDE GUARDS TO THIS FILE


/// TODO write full docstring including @param and @return for average function

double average( int count, const int scores[] );

/// TODO write full docstring including @param and @return for std_dev function

double std_dev( int count, const int scores[], double mean );

/// TODO write full docstring including @param and @return for histogram

void histogram(int count, const int scores[]);