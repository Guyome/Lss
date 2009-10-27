#include <boost/python.hpp>
#include <vector>
#include "coreLSS.hpp"
#include "coreLSS.cpp"

template class coreLSS<boost::python::list>;
//template class coreLSS<std::vector<double> >;

