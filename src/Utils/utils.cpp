//
// Created by Pierre Roy on 01/12/17.
//

#include <iostream>

#include "utils.h"

double System::randd()
{
    return (double) rand() / (RAND_MAX + 1.0);
}
