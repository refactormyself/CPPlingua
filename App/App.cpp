#include "stdafx.h"
#include <iostream>
#include <thread>

using namespace System;

void function_1()
{
	std::cout << "Beauty is only skin deep\n";
}

int main(array<System::String ^> ^args)
{
	std::thread thread_1(function_1);
    return 0;
}
