#pragma once

#include "BoundedBuffer.h"

#include "UdpData.h"

#ifndef QSIZE
QSIZE 100
#endif

typedef BoundedBuffer<UdpData, QSIZE> QueueType;