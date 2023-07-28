#include "random.h"
#include <chrono>

std::default_random_engine Random::engine(std::chrono::system_clock::now().time_since_epoch().count());
