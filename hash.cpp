#include "hash.hpp"

namespace Hasher {

unsigned long hash(unsigned char *str) {
  unsigned long hash = 5381;

  int c;

  while (c = *str++) {
    hash = ((hash << 5) + hash) + c;
  }
  return hash;
}

} // namespace Hasher