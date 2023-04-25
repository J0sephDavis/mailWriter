#include <exception>
#include <iostream>
#include <memory>
#include <gtkmm.h>

using namespace std;

class MyWindow : public Gtk::Window {
public:
    MyWindow() {
        try {
            cout << "In MyWindow!" << endl;
            auto builder = Gtk::Builder::create_from_file("gui.glade");
            cout << "Builder created!" << endl;

            Gtk::Window* main_window = nullptr;
            builder->get_widget("LogIn_Window", main_window);
            cout << "Window retrieved!" << endl;

            add(*main_window);
        } catch (Glib::FileError e) {
            cout << e.what() << endl;
        }
        
    }
};

int main(int argc, char** argv) {
    cout << "Starting!" << endl;
    auto app = Gtk::Application::create("com.glade.example");
    cout << "App created!" << endl;
    MyWindow window;
    cout << "Window created!" << endl;
    return app->run(window);
}