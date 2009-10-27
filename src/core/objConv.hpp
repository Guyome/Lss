#ifndef H_OBJCONV_H
#define H_OBJCONV_H

#include <boost/python.hpp>
#include <blitz/array.h>
#include <vector>

/**
 * @brief This librairy contains functions
 * to interfacing coreLSS to Python
 * @author Guillaume Lanquepin <guillaume@himolde.no>
 * @version 0.1
 */

/** Convert an blitzz array to python list*/
template < class data> data ArrayToObj(const blitz::Array<double,2>& array);
/** Convert an python list(vector) to blitz array*/
blitz::Array<double,1>* ObjToVector(const boost::python::list& list);
/**< Convert an python list(2D) to blitz array*/
blitz::Array<double,2>* ObjToArray(const boost::python::list& list);
/** Convert an blitzz array to c++ std::vector<double>(2D)*/
/*std::vector<std::vector<double>> ArrayToObj(const blitz::Array<double,2>& array);*/
/** Convert c++ std::vector<double>* to blitz array*/
blitz::Array<double,1>* ObjToVector(const std::vector<double>& list);
/**< Convert an c++ std::vector<double>(2D) to blitz tab*/
blitz::Array<double,2>* ObjToArray(const std::vector<std::vector<double> >& list);

#endif
