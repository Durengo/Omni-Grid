#include <boost/python.hpp>
#include <iostream>

int main(int argc, char *argv[])
{
    // Initialize Python
    Py_Initialize();

    try
    {
        // Execute a Python script
        boost::python::exec("print('Hello from Python!')");
    }
    catch (boost::python::error_already_set const &)
    {
        PyErr_Print();
    }

    // Finalize Python
    Py_Finalize();

    return 0;
}