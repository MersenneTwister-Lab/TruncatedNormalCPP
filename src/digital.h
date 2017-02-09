#pragma once
#ifndef DIGITAL_H
#define DIGITAL_H
/**
 * @file digital.h
 *
 * @brief digital net binary file format
 *
 * @author Shinsuke Mori (Hiroshima University)
 * @author Makoto Matsumoto (Hiroshima University)
 * @author Mutsuo Saito (Hiroshima University)
 *
 * Copyright (C) 2017 Shinsuke Mori, Makoto Matsumoto, Mutsuo Saito
 * and Hiroshima University.
 * All rights reserved.
 *
 * The GPL ver.3 is applied to this software, see
 * COPYING
 */
#include <inttypes.h>

#define DIGITAL_MAGIC UINT64_C(0x36b5951d82b67241)

struct DIGITAL_NET_HEADER_T {
    uint32_t s;
    uint32_t m;
    uint32_t pos;
};

struct DIGITAL_NET_DATA_T {
    uint32_t bit;
    uint32_t s;
    uint32_t m;
    uint32_t tvalue;
    double wafom;
    uint64_t data[0];
};


//extern const digital_net_name digital_net_name_data[];
//extern const int digital_net_name_data_size;

typedef struct DIGITAL_NET_HEADER_T digital_net_header_t;
typedef struct DIGITAL_NET_DATA_T digital_net_data_t;

#endif // DIGITAL_H
