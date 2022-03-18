#include "App/sandbox.h"
#include<memory>

int main()
{
    sandBox* phoenixSandbox = sandBox::getSandBox();
    phoenixSandbox->init();
    phoenixSandbox->run();
    delete phoenixSandbox;
}