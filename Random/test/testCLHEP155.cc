
#include "CLHEP/Random/MixMaxRng.h"

int main()
try {
  CLHEP::MixMaxRng eng(0); // Seeding with 0 is not supported; should throw.
  return 1;
}
catch(...) {
  return 0;
}

