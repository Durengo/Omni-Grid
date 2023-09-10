char const *greet()
{
    return "hello, world";
}

#include <boost/python.hpp>

BOOST_PYTHON_MODULE(HelloBoostPythonLib)
{
    using namespace boost::python;
    def("greet", greet);
}