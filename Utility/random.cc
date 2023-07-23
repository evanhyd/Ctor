#include "random.h"
#include <chrono>

const std::default_random_engine Random::engine(std::chrono::system_clock::now().time_since_epoch().count());
