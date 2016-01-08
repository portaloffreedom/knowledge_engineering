#include <iostream>
#include <src/controller/Controller.h>

using namespace std;

int main(int argc, char** argv) {
    Controller controller(argc, argv);
    return controller.exec();
}
