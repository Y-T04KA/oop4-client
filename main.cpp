#include "TInterface.h"
#include <application.h>

int main(int argc, char *argv[])
{
    TClientApp a(argc, argv);
    return a.exec();
}
