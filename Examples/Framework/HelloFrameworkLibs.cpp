#include <boost/python.hpp>
#include <durlib.h>
#include <thread>
#include <gtkmm-4.0/gtkmm.h>
#include <gtkmm-4.0/gtkmm/button.h>
#include <gtkmm-4.0/gtkmm/window.h>
#include <gtkmm-4.0/gtkmm/drawingarea.h>
#include "raylib.h"

void testRaylib(int argc, char *argv[]);
int testGtk(int argc, char *argv[]);
void testBoostPython(int argc, char *argv[]);
void renderRaylib();

class MyDrawingArea : public Gtk::DrawingArea
{
public:
    MyDrawingArea()
    {
    }
    virtual ~MyDrawingArea()
    {
    }

protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr)
    {
        // Custom drawing code using the Cairo drawing context 'cr'.
        // You can use 'cr' to draw shapes, text, images, etc.
        // Example:
        cr->set_source_rgb(0.0, 0.0, 0.0); // Set the drawing color to black.
        cr->rectangle(10, 10, 100, 100);   // Draw a black rectangle.
        cr->fill();                        // Fill the drawn shape.

        // Return 'true' to indicate that drawing is complete.
        return true;
    }
};

class HelloWorld : public Gtk::Window
{

public:
    HelloWorld();
    ~HelloWorld() override;

protected:
    // Signal handlers:
    void on_button_clicked();

    // Member widgets:
    Gtk::Button m_button;
};

HelloWorld::HelloWorld()
    : m_button("Hello World") // creates a new button with label "Hello World".
{
    // Sets the margin around the button.
    m_button.set_margin(10);

    // When the button receives the "clicked" signal, it will call the
    // on_button_clicked() method defined below.
    m_button.signal_clicked().connect(sigc::mem_fun(*this,
                                                    &HelloWorld::on_button_clicked));

    // This packs the button into the Window (a container).
    set_child(m_button);
}

HelloWorld::~HelloWorld()
{
}

void HelloWorld::on_button_clicked()
{
    std::cout << "Hello World" << std::endl;
}
int main(int argc, char *argv[])
{
    DURLIB::Log::Init();

    CLI_TRACE("Hello Framework!");
    CLI_INFO("Hello Framework!");
    CLI_WARN("Hello Framework!");
    CLI_ERROR("Hello Framework!");
    CLI_FATAL("Hello Framework!");

    DEBUG_TRACE("Hello Framework!");
    DEBUG_INFO("Hello Framework!");
    DEBUG_WARN("Hello Framework!");
    DEBUG_ERROR("Hello Framework!");
    DEBUG_FATAL("Hello Framework!");

    auto app = Gtk::Application::create("org.gtkmm.example");
    return app->make_window_and_run<HelloWorld>(argc, argv);
}
// { // BOOST PYTHON
//     Py_Initialize();

//     DEBUG_TRACE("Boost Python initialized.");

//     // std::this_thread::sleep_for(std::chrono::seconds(2));

//     try
//     {
//         boost::python::exec("print('Hello from Python!')");
//     }
//     catch (boost::python::error_already_set const &)
//     {
//         PyErr_Print();
//     }

//     Py_Finalize();
// END BOOST PYTHON

void renderRaylib()
{
    DEBUG_TRACE("Raylib initialized.");

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();
    DEBUG_TRACE("Raylib closed.");
}

void testBoostPython(int argc, char *argv[])
{
    DEBUG_TRACE("Boost Python initialized.");

    // std::this_thread::sleep_for(std::chrono::seconds(2));

    try
    {
        boost::python::exec("print('Hello from Python!')");
    }
    catch (boost::python::error_already_set const &)
    {
        PyErr_Print();
    }
}