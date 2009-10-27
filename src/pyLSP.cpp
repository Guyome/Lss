#include "core/coreLSS.hpp"
#include <boost/python.hpp>

using namespace boost::python;

/** Python wrapper for coreLSS class based on boost.python */
BOOST_PYTHON_MODULE(pylss)
{
    scope().attr("__doc__") =
        "This library implements dynamic programming\n"
        "solver (see Wagner and Whitin Algo.) for lot-size problem\n";
    class_<coreLSS<list> >("pylss",init<list, list, list, list, list, list, int, int>())
        .def_readonly("product",&coreLSS<list>::getProduct)
        .def_readonly("period",&coreLSS<list>::getPeriod)
        .def_readonly("price",&coreLSS<list>::getPrice)
        .def_readonly("hold",&coreLSS<list>::getHold)
        .def_readonly("prod",&coreLSS<list>::getProd)
        .def_readonly("setup",&coreLSS<list>::getSetup)
        .def("Objective", &coreLSS<list>::objective)
        .def("solve", &coreLSS<list>::solve, "Solser based on dynamic programming\n"
            "Solve lot-size problem\nSee Wagner and Within(1958)\n")
    ;
}
