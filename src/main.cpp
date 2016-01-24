#include <iostream>
#include <src/controller/Controller.h>
//#include <QQmlDebuggingEnabler>

using namespace std;

int main(int argc, char** argv) {
    for (int i=0; i<argc; i++) {
        std::cout<<"argument["<<i<<"]: "<<argv[i]<<std::endl;
    }

    //static QmlJsDebuggingEnabler enableDebuggingHelper;

    Controller controller(argc, argv);
    return controller.exec();
}
