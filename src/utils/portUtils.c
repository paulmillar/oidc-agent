#define _XOPEN_SOURCE 500
#include "portUtils.h"

#include "../oidc_error.h"
#include "stringUtils.h"

#include <stdio.h>
#include <stdlib.h>

long random_at_most(long max) {
  // max <= RAND_MAX < ULONG_MAX, so this is okay.
  unsigned long num_bins = (unsigned long)max + 1,
                num_rand = (unsigned long)RAND_MAX + 1,
                bin_size = num_rand / num_bins, defect = num_rand % num_bins;
  long x;
  do { x = random(); } while (num_rand - defect <= (unsigned long)x);

  return x / bin_size;
}

unsigned short getRandomPort() {
  unsigned short maxPort = 49151;
  unsigned short minPort = 1024;
  return random_at_most(maxPort - minPort) + minPort;
}

char* portToUri(unsigned short port) {
  return oidc_sprintf("http://localhost:%hu", port);
}

unsigned short getPortFromUri(const char* uri) {
  unsigned short port;
  if (sscanf(uri, "http://localhost:%hu", &port) != 1) {
    if (sscanf(uri, "http://localhost:%hu/", &port) != 1) {
      oidc_errno = OIDC_EFMT;
      return 0;
    }
  }
  return port;
}
