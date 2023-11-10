#include <boost/python.hpp>
#include <iostream>

int main()
{
    Py_Initialize();

    try
    {
        boost::python::object math = boost::python::import("math");

        boost::python::object result = math.attr("sqrt")(25);
        double value = boost::python::extract<double>(result);

        std::cout << "Square root of 25 is: " << value << std::endl;
    }
    catch (boost::python::error_already_set const &)
    {
        PyErr_Print();
    }

    Py_Finalize();

    return 0;
}