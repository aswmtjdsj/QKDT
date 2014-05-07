#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <random>

/*#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <sys/stat.h>

#define SQUARE(x) ((x) * (x))

#define MAX_FILE_NAME 100

#define LEVEL_RELEASE 0
#define LEVEL_DEBUG 3

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL LEVEL_DEBUG
#endif*/

#ifndef FILE_READ_MODE
#define FILE_READ_MODE 0
#endif

#ifndef INTERACTIVE_READ_MODE
#define INTERACTIVE_READ_MODE 1
#endif

#ifndef CMD_READ_MODE
#define CMD_READ_MODE 2
#endif

#ifndef READ_MODE
#define READ_MODE FILE_READ_MODE
#endif

#ifndef EPSILON
#define EPSILON 1e-6
#endif

#endif
