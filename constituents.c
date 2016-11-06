/*
 * Copyright (c) 2009 Institute of Geological & Nuclear Sciences Ltd.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <math.h>
#include <time.h>

/* local includes */
#include "libtidal.h"

static struct _libtidal_constituent constituents[LIBTIDAL_CONSTITUENTS] = {
  {"Z0", { 0,  0,  0,  0,  0,  0},  0.00, {
    {{ 0,  0,  0,  0,  0,  0}, 0.00, 0.0000, -1},
  }},
  {"SA", { 0,  0,  1,  0,  0, -1},  0.00, {
    {{ 0,  0,  0,  0,  0,  0}, 0.00, 0.0000, -1},
  }},
  {"SSA", { 0,  0,  2,  0,  0,  0},  0.00, {
    {{ 0,  0,  0,  0,  0,  0}, 0.00, 0.0000, -1},
  }},
  {"MSM", { 0,  1, -2,  1,  0,  0},  0.00, {
    {{ 0,  0,  0,  0,  0,  0}, 0.00, 0.0000, -1},
  }},
  {"MM", { 0,  1,  0, -1,  0,  0},  0.00, {
    {{ 0,  0,  0,  0,  0,  0}, 0.00, 0.0000, -1},
  }},
  {"MSF", { 0,  2, -2,  0,  0,  0},  0.00, {
    {{ 0,  0,  0,  0,  0,  0}, 0.00, 0.0000, -1},
  }},
  {"MF", { 0,  2,  0,  0,  0,  0},  0.00, {
    {{ 0,  0,  0,  0,  0,  0}, 0.00, 0.0000, -1},
  }},
  {"ALP1", { 1, -4,  2,  1,  0,  0}, -0.25, {
    {{ 0,  0,  0, -1,  0,  0}, 0.75, 0.0360,  1},
    {{ 0,  0,  0,  0, -1,  0}, 0.00, 0.1906,  0},
    {{ 0,  0,  0,  0,  0,  0}, 0.00, 0.0000, -1},
  }},
  {"2Q1", { 1, -3,  0,  2,  0,  0}, -0.25, {
    {{ 0,  0,  0, -2, -2,  0}, 0.50, 0.0063,  0},
    {{ 0,  0,  0, -1, -1,  0}, 0.75, 0.0241,  1},
    {{ 0,  0,  0, -1,  0,  0}, 0.75, 0.0607,  1},
    {{ 0,  0,  0,  0, -2,  0}, 0.50, 0.0063,  0},
    {{ 0,  0,  0,  0, -1,  0}, 0.00, 0.1885,  0},
    {{ 0,  0,  0,  0,  0,  0}, 0.00, 0.0000, -1},
  }},
  {"SIG1", { 1, -3,  2,  0,  0,  0}, -0.25, {
    {{ 0,  0,  0, -1,  0,  0}, 0.75, 0.0095,  1},
    {{ 0,  0,  0,  0, -2,  0}, 0.50, 0.0061,  0},
    {{ 0,  0,  0,  0, -1,  0}, 0.00, 0.1884,  0},
    {{ 0,  0,  0,  2,  0,  0}, 0.50, 0.0087,  0},
    {{ 0,  0,  0,  0,  0,  0}, 0.00, 0.0000, -1},
  }},
  {"Q1", { 1, -2,  0,  1,  0,  0}, -0.25, {
    {{ 0,  0,  0, -2, -3,  0}, 0.50, 0.0007,  0},
    {{ 0,  0,  0, -2, -2,  0}, 0.50, 0.0039,  0},
    {{ 0,  0,  0, -1, -2,  0}, 0.75, 0.0010,  1},
    {{ 0,  0,  0, -1, -1,  0}, 0.75, 0.0115,  1},
    {{ 0,  0,  0, -1,  0,  0}, 0.75, 0.0292,  1},
    {{ 0,  0,  0,  0, -2,  0}, 0.50, 0.0057,  0},
    {{ 0,  0,  0, -1,  0,  1}, 0.00, 0.0008,  0},
    {{ 0,  0,  0,  0, -1,  0}, 0.00, 0.1884,  0},
    {{ 0,  0,  0,  1,  0,  0}, 0.75, 0.0018,  1},
    {{ 0,  0,  0,  2,  0,  0}, 0.50, 0.0028,  0},
    {{ 0,  0,  0,  0,  0,  0}, 0.00, 0.0000, -1},
  }},
  {"RHO1", { 1, -2,  2, -1,  0,  0}, -0.25, {
    {{ 0,  0,  0,  0, -2,  0}, 0.50, 0.0058,  0},
    {{ 0,  0,  0,  0, -1,  0}, 0.00, 0.1882,  0},
    {{ 0,  0,  0,  1,  0,  0}, 0.75, 0.0131,  1},
    {{ 0,  0,  0,  2,  0,  0}, 0.50, 0.0576,  0},
    {{ 0,  0,  0,  2,  1,  0}, 0.00, 0.0175,  0},
    {{ 0,  0,  0,  0,  0,  0}, 0.00, 0.0000, -1},
  }},
  {"O1", { 1, -1,  0,  0,  0,  0}, -0.25, {
    {{ 0,  0,  0, -1,  0,  0}, 0.25, 0.0003,  1},
    {{ 0,  0,  0,  0, -2,  0}, 0.50, 0.0058,  0},
    {{ 0,  0,  0,  0, -1,  0}, 0.00, 0.1885,  0},
    {{ 0,  0,  0,  1, -1,  0}, 0.25, 0.0004,  1},
    {{ 0,  0,  0,  1,  0,  0}, 0.75, 0.0029,  1},
    {{ 0,  0,  0,  1,  1,  0}, 0.25, 0.0004,  1},
    {{ 0,  0,  0,  2,  0,  0}, 0.50, 0.0064,  0},
    {{ 0,  0,  0,  2,  1,  0}, 0.50, 0.0010,  0},
    {{ 0,  0,  0,  0,  0,  0}, 0.00, 0.0000, -1},
  }},
  {"TAU1", { 1, -1,  2,  0,  0,  0}, -0.75, {
    {{ 0,  0,  0, -2,  0,  0}, 0.00, 0.0446,  0},
    {{ 0,  0,  0, -1,  0,  0}, 0.25, 0.0426,  1},
    {{ 0,  0,  0,  0, -1,  0}, 0.50, 0.0284,  0},
    {{ 0,  0,  0,  0,  1,  0}, 0.50, 0.2170,  0},
    {{ 0,  0,  0,  0,  2,  0}, 0.50, 0.0142,  0},
    {{ 0,  0,  0,  0,  0,  0}, 0.00, 0.0000, -1},
  }},
  {"BET1", { 1,  0, -2,  1,  0,  0}, -0.75, {
    {{ 0,  0,  0,  0, -1,  0}, 0.00, 0.2266,  0},
    {{ 0,  0,  0,  0,  0,  0}, 0.00, 0.0000, -1},
  }},
  {"NO1", { 1,  0,  0,  1,  0,  0}, -0.75, {
    {{ 0,  0,  0, -2, -2,  0}, 0.50, 0.0057,  0},
    {{ 0,  0,  0, -2, -1,  0}, 0.00, 0.0665,  0},
    {{ 0,  0,  0, -2,  0,  0}, 0.00, 0.3596,  0},
    {{ 0,  0,  0, -1, -1,  0}, 0.75, 0.0331,  1},
    {{ 0,  0,  0, -1,  0,  0}, 0.25, 0.2227,  1},
    {{ 0,  0,  0, -1,  1,  0}, 0.75, 0.0290,  1},
    {{ 0,  0,  0,  0, -1,  0}, 0.50, 0.0290,  0},
    {{ 0,  0,  0,  0,  1,  0}, 0.00, 0.2004,  0},
    {{ 0,  0,  0,  0,  2,  0}, 0.50, 0.0054,  0},
    {{ 0,  0,  0,  0,  0,  0}, 0.00, 0.0000, -1},
  }},
  {"CHI1", { 1,  0,  2, -1,  0,  0}, -0.75, {
    {{ 0,  0,  0,  0, -1,  0}, 0.50, 0.0282,  0},
    {{ 0,  0,  0,  0,  1,  0}, 0.00, 0.2187,  0},
    {{ 0,  0,  0,  0,  0,  0}, 0.00, 0.0000, -1},
  }},
  {"PI1", { 1,  1, -3,  0,  0,  1}, -0.25, {
    {{ 0,  0,  0,  0, -1,  0}, 0.50, 0.0078,  0},
    {{ 0,  0,  0,  0,  0,  0}, 0.00, 0.0000, -1},
  }},
  {"P1", { 1,  1, -2,  0,  0,  0}, -0.25, {
    {{ 0,  0,  0,  0, -2,  0}, 0.00, 0.0008,  0},
    {{ 0,  0,  0,  0, -1,  0}, 0.50, 0.0112,  0},
    {{ 0,  0,  0,  0,  0,  2}, 0.50, 0.0004,  0},
    {{ 0,  0,  0,  1,  0,  0}, 0.75, 0.0004,  1},
    {{ 0,  0,  0,  2,  0,  0}, 0.50, 0.0015,  0},
    {{ 0,  0,  0,  2,  1,  0}, 0.50, 0.0003,  0},
    {{ 0,  0,  0,  0,  0,  0}, 0.00, 0.0000, -1},
  }},
  {"S1", { 1,  1, -1,  0,  0,  1}, -0.75, {
    {{ 0,  0,  0,  0,  0, -2}, 0.00, 0.3534,  0},
    {{ 0,  0,  0,  0,  1,  0}, 0.50, 0.0264,  0},
    {{ 0,  0,  0,  0,  0,  0}, 0.00, 0.0000, -1},
  }},
  {"K1", { 1,  1,  0,  0,  0,  0}, -0.75, {
    {{ 0,  0,  0, -2, -1,  0}, 0.00, 0.0002,  0},
    {{ 0,  0,  0, -1, -1,  0}, 0.75, 0.0001,  1},
    {{ 0,  0,  0, -1,  0,  0}, 0.25, 0.0007,  1},
    {{ 0,  0,  0, -1,  1,  0}, 0.75, 0.0001,  1},
    {{ 0,  0,  0,  0, -2,  0}, 0.00, 0.0001,  0},
    {{ 0,  0,  0,  0, -1,  0}, 0.50, 0.0198,  0},
    {{ 0,  0,  0,  0,  1,  0}, 0.00, 0.1356,  0},
    {{ 0,  0,  0,  0,  2,  0}, 0.50, 0.0029,  0},
    {{ 0,  0,  0,  1,  0,  0}, 0.25, 0.0002,  1},
    {{ 0,  0,  0,  1,  1,  0}, 0.25, 0.0001,  1},
    {{ 0,  0,  0,  0,  0,  0}, 0.00, 0.0000, -1},
  }},
  {"PSI1", { 1,  1,  1,  0,  0, -1}, -0.75, {
    {{ 0,  0,  0,  0,  1,  0}, 0.00, 0.0190,  0},
    {{ 0,  0,  0,  0,  0,  0}, 0.00, 0.0000, -1},
  }},
  {"PHI1", { 1,  1,  2,  0,  0,  0}, -0.75, {
    {{ 0,  0,  0, -2,  0,  0}, 0.00, 0.0344,  0},
    {{ 0,  0,  0, -2,  1,  0}, 0.00, 0.0106,  0},
    {{ 0,  0,  0,  0,  0, -2}, 0.00, 0.0132,  0},
    {{ 0,  0,  0,  0,  1,  0}, 0.50, 0.0384,  0},
    {{ 0,  0,  0,  0,  2,  0}, 0.50, 0.0185,  0},
    {{ 0,  0,  0,  0,  0,  0}, 0.00, 0.0000, -1},
  }},
  {"THE1", { 1,  2, -2,  1,  0,  0}, -0.75, {
    {{ 0,  0,  0, -2, -1,  0}, 0.00, 0.0300,  0},
    {{ 0,  0,  0, -1,  0,  0}, 0.25, 0.0141,  1},
    {{ 0,  0,  0,  0, -1,  0}, 0.50, 0.0317,  0},
    {{ 0,  0,  0,  0,  1,  0}, 0.00, 0.1993,  0},
    {{ 0,  0,  0,  0,  0,  0}, 0.00, 0.0000, -1},
  }},
  {"J1", { 1,  2,  0, -1,  0,  0}, -0.75, {
    {{ 0,  0,  0,  0, -1,  0}, 0.50, 0.0294,  0},
    {{ 0,  0,  0,  0,  1,  0}, 0.00, 0.1980,  0},
    {{ 0,  0,  0,  0,  2,  0}, 0.50, 0.0047,  0},
    {{ 0,  0,  0,  1, -1,  0}, 0.75, 0.0027,  1},
    {{ 0,  0,  0,  1,  0,  0}, 0.25, 0.0816,  1},
    {{ 0,  0,  0,  1,  1,  0}, 0.25, 0.0331,  1},
    {{ 0,  0,  0,  1,  2,  0}, 0.25, 0.0027,  1},
    {{ 0,  0,  0,  2,  0,  0}, 0.50, 0.0152,  0},
    {{ 0,  0,  0,  2,  1,  0}, 0.50, 0.0098,  0},
    {{ 0,  0,  0,  2,  2,  0}, 0.50, 0.0057,  0},
    {{ 0,  0,  0,  0,  0,  0}, 0.00, 0.0000, -1},
  }},
  {"OO1", { 1,  3,  0,  0,  0,  0}, -0.75, {
    {{ 0,  0,  0, -2, -1,  0}, 0.50, 0.0037,  0},
    {{ 0,  0,  0, -2,  0,  0}, 0.00, 0.1496,  0},
    {{ 0,  0,  0, -2,  1,  0}, 0.00, 0.0296,  0},
    {{ 0,  0,  0, -1,  0,  0}, 0.25, 0.0240,  1},
    {{ 0,  0,  0, -1,  1,  0}, 0.25, 0.0099,  1},
    {{ 0,  0,  0,  0,  1,  0}, 0.00, 0.6398,  0},
    {{ 0,  0,  0,  0,  2,  0}, 0.00, 0.1342,  0},
    {{ 0,  0,  0,  0,  3,  0}, 0.00, 0.0086,  0},
    {{ 0,  0,  0,  0,  0,  0}, 0.00, 0.0000, -1},
  }},
  {"UPS1", { 1,  4,  0, -1,  0,  0}, -0.75, {
    {{ 0,  0,  0, -2,  0,  0}, 0.00, 0.0611,  0},
    {{ 0,  0,  0,  0,  1,  0}, 0.00, 0.6399,  0},
    {{ 0,  0,  0,  0,  2,  0}, 0.00, 0.1318,  0},
    {{ 0,  0,  0,  1,  0,  0}, 0.25, 0.0289,  1},
    {{ 0,  0,  0,  1,  1,  0}, 0.25, 0.0257,  1},
    {{ 0,  0,  0,  0,  0,  0}, 0.00, 0.0000, -1},
  }},
  {"OQ2", { 2, -3,  0,  3,  0,  0},  0.00, {
    {{ 0,  0,  0, -1,  0,  0}, 0.25, 0.1042,  2},
    {{ 0,  0,  0,  0, -1,  0}, 0.50, 0.0386,  0},
    {{ 0,  0,  0,  0,  0,  0}, 0.00, 0.0000, -1},
  }},
  {"EPS2", { 2, -3,  2,  1,  0,  0},  0.00, {
    {{ 0,  0,  0, -1, -1,  0}, 0.25, 0.0075,  2},
    {{ 0,  0,  0, -1,  0,  0}, 0.25, 0.0402,  2},
    {{ 0,  0,  0,  0, -1,  0}, 0.50, 0.0373,  0},
    {{ 0,  0,  0,  0,  0,  0}, 0.00, 0.0000, -1},
  }},
  {"2N2", { 2, -2,  0,  2,  0,  0},  0.00, {
    {{ 0,  0,  0, -2, -2,  0}, 0.50, 0.0061,  0},
    {{ 0,  0,  0, -1, -1,  0}, 0.25, 0.0117,  2},
    {{ 0,  0,  0, -1,  0,  0}, 0.25, 0.0678,  2},
    {{ 0,  0,  0,  0, -1,  0}, 0.50, 0.0374,  0},
    {{ 0,  0,  0,  0,  0,  0}, 0.00, 0.0000, -1},
  }},
  {"MU2", { 2, -2,  2,  0,  0,  0},  0.00, {
    {{ 0,  0,  0, -1, -1,  0}, 0.25, 0.0018,  2},
    {{ 0,  0,  0, -1,  0,  0}, 0.25, 0.0104,  2},
    {{ 0,  0,  0,  0, -1,  0}, 0.50, 0.0375,  0},
    {{ 0,  0,  0,  0,  0,  0}, 0.00, 0.0000, -1},
  }},
  {"N2", { 2, -1,  0,  1,  0,  0},  0.00, {
    {{ 0,  0,  0, -2, -2,  0}, 0.50, 0.0039,  0},
    {{ 0,  0,  0, -1,  0,  1}, 0.00, 0.0008,  0},
    {{ 0,  0,  0,  0, -2,  0}, 0.00, 0.0005,  0},
    {{ 0,  0,  0,  0, -1,  0}, 0.50, 0.0373,  0},
    {{ 0,  0,  0,  0,  0,  0}, 0.00, 0.0000, -1},
  }},
  {"NU2", { 2, -1,  2, -1,  0,  0},  0.00, {
    {{ 0,  0,  0,  0, -1,  0}, 0.50, 0.0373,  0},
    {{ 0,  0,  0,  1,  0,  0}, 0.75, 0.0042,  2},
    {{ 0,  0,  0,  2,  0,  0}, 0.00, 0.0042,  0},
    {{ 0,  0,  0,  2,  1,  0}, 0.50, 0.0036,  0},
    {{ 0,  0,  0,  0,  0,  0}, 0.00, 0.0000, -1},
  }},
  {"GAM2", { 2,  0, -2,  2,  0,  0}, -0.50, {
    {{ 0,  0,  0, -2, -2,  0}, 0.00, 0.1429,  0},
    {{ 0,  0,  0, -1,  0,  0}, 0.25, 0.0293,  2},
    {{ 0,  0,  0,  0, -1,  0}, 0.50, 0.0330,  0},
    {{ 0,  0,  0,  0,  0,  0}, 0.00, 0.0000, -1},
  }},
  {"H1", { 2,  0, -1,  0,  0,  1}, -0.50, {
    {{ 0,  0,  0,  0, -1,  0}, 0.50, 0.0224,  0},
    {{ 0,  0,  0,  1,  0, -1}, 0.50, 0.0447,  0},
    {{ 0,  0,  0,  0,  0,  0}, 0.00, 0.0000, -1},
  }},
  {"M2", { 2,  0,  0,  0,  0,  0},  0.00, {
    {{ 0,  0,  0, -1, -1,  0}, 0.75, 0.0001,  2},
    {{ 0,  0,  0, -1,  0,  0}, 0.75, 0.0004,  2},
    {{ 0,  0,  0,  0, -2,  0}, 0.00, 0.0005,  0},
    {{ 0,  0,  0,  0, -1,  0}, 0.50, 0.0373,  0},
    {{ 0,  0,  0,  1, -1,  0}, 0.25, 0.0001,  2},
    {{ 0,  0,  0,  1,  0,  0}, 0.75, 0.0009,  2},
    {{ 0,  0,  0,  1,  1,  0}, 0.75, 0.0002,  2},
    {{ 0,  0,  0,  2,  0,  0}, 0.00, 0.0006,  0},
    {{ 0,  0,  0,  2,  1,  0}, 0.00, 0.0002,  0},
    {{ 0,  0,  0,  0,  0,  0}, 0.00, 0.0000, -1},
  }},
  {"H2", { 2,  0,  1,  0,  0, -1},  0.00, {
    {{ 0,  0,  0,  0, -1,  0}, 0.50, 0.0217,  0},
    {{ 0,  0,  0,  0,  0,  0}, 0.00, 0.0000, -1},
  }},
  {"LDA2", { 2,  1, -2,  1,  0,  0}, -0.50, {
    {{ 0,  0,  0,  0, -1,  0}, 0.50, 0.0448,  0},
    {{ 0,  0,  0,  0,  0,  0}, 0.00, 0.0000, -1},
  }},
  {"L2", { 2,  1,  0, -1,  0,  0}, -0.50, {
    {{ 0,  0,  0,  0, -1,  0}, 0.50, 0.0366,  0},
    {{ 0,  0,  0,  2, -1,  0}, 0.00, 0.0047,  0},
    {{ 0,  0,  0,  2,  0,  0}, 0.50, 0.2505,  0},
    {{ 0,  0,  0,  2,  1,  0}, 0.50, 0.1102,  0},
    {{ 0,  0,  0,  2,  2,  0}, 0.50, 0.0156,  0},
    {{ 0,  0,  0,  0,  0,  0}, 0.00, 0.0000, -1},
  }},
  {"T2", { 2,  2, -3,  0,  0,  1},  0.00, {
    {{ 0,  0,  0,  0,  0,  0}, 0.00, 0.0000, -1},
  }},
  {"S2", { 2,  2, -2,  0,  0,  0},  0.00, {
    {{ 0,  0,  0,  0, -1,  0}, 0.00, 0.0022,  0},
    {{ 0,  0,  0,  1,  0,  0}, 0.75, 0.0001,  2},
    {{ 0,  0,  0,  2,  0,  0}, 0.00, 0.0001,  0},
    {{ 0,  0,  0,  0,  0,  0}, 0.00, 0.0000, -1},
  }},
  {"R2", { 2,  2, -1,  0,  0, -1}, -0.50, {
    {{ 0,  0,  0,  0,  0,  2}, 0.50, 0.2535,  0},
    {{ 0,  0,  0,  0,  1,  2}, 0.00, 0.0141,  0},
    {{ 0,  0,  0,  0,  0,  0}, 0.00, 0.0000, -1},
  }},
  {"K2", { 2,  2,  0,  0,  0,  0},  0.00, {
    {{ 0,  0,  0, -1,  0,  0}, 0.75, 0.0024,  2},
    {{ 0,  0,  0, -1,  1,  0}, 0.75, 0.0004,  2},
    {{ 0,  0,  0,  0, -1,  0}, 0.50, 0.0128,  0},
    {{ 0,  0,  0,  0,  1,  0}, 0.00, 0.2980,  0},
    {{ 0,  0,  0,  0,  2,  0}, 0.00, 0.0324,  0},
    {{ 0,  0,  0,  0,  0,  0}, 0.00, 0.0000, -1},
  }},
  {"ETA2", { 2,  3,  0, -1,  0,  0},  0.00, {
    {{ 0,  0,  0,  0, -1,  0}, 0.50, 0.0187,  0},
    {{ 0,  0,  0,  0,  1,  0}, 0.00, 0.4355,  0},
    {{ 0,  0,  0,  0,  2,  0}, 0.00, 0.0467,  0},
    {{ 0,  0,  0,  1,  0,  0}, 0.75, 0.0747,  2},
    {{ 0,  0,  0,  1,  1,  0}, 0.75, 0.0482,  2},
    {{ 0,  0,  0,  1,  2,  0}, 0.75, 0.0093,  2},
    {{ 0,  0,  0,  2,  0,  0}, 0.50, 0.0078,  0},
    {{ 0,  0,  0,  0,  0,  0}, 0.00, 0.0000, -1},
  }},
  {"M3", { 3,  0,  0,  0,  0,  0}, -0.50, {
    {{ 0,  0,  0,  0, -1,  0}, 0.50, 0.0564,  0},
    {{ 0,  0,  0,  0,  0,  0}, 0.00, 0.0000, -1},
  }},
};

static struct _libtidal_shallow shallows[LIBTIDAL_SHALLOWS] = {
  {"2PO1", 2, {{"P1", 2.0},{"O1", -1.0},}},
  {"SO1", 2, {{"S2", 1.0},{"O1", -1.0},}},
  {"ST36", 3, {{"M2", 2.0},{"N2", 1.0},{"S2", -2.0},}},
  {"2NS2", 2, {{"N2", 2.0},{"S2", -1.0},}},
  {"ST37", 2, {{"M2", 3.0},{"S2", -2.0},}},
  {"ST1", 3, {{"N2", 2.0},{"K2", 1.0},{"S2", -2.0},}},
  {"ST2", 4, {{"M2", 1.0},{"N2", 1.0},{"K2", 1.0},{"S2", -2.0},}},
  {"ST3", 3, {{"M2", 2.0},{"S2", 1.0},{"K2", -2.0},}},
  {"O2", 1, {{"O1", 2.0},}},
  {"ST4", 3, {{"K2", 2.0},{"N2", 1.0},{"S2", -2.0},}},
  {"SNK2", 3, {{"S2", 1.0},{"N2", 1.0},{"K2", -1.0},}},
  {"OP2", 2, {{"O1", 1.0},{"P1", 1.0},}},
  {"MKS2", 3, {{"M2", 1.0},{"K2", 1.0},{"S2", -1.0},}},
  {"ST5", 3, {{"M2", 1.0},{"K2", 2.0},{"S2", -2.0},}},
  {"ST6", 4, {{"S2", 2.0},{"N2", 1.0},{"M2", -1.0},{"K2", -1.0},}},
  {"2SK2", 2, {{"S2", 2.0},{"K2", -1.0},}},
  {"MSN2", 3, {{"M2", 1.0},{"S2", 1.0},{"N2", -1.0},}},
  {"ST7", 4, {{"K2", 2.0},{"M2", 1.0},{"S2", -1.0},{"N2", -1.0},}},
  {"2SM2", 2, {{"S2", 2.0},{"M2", -1.0},}},
  {"ST38", 3, {{"M2", 2.0},{"S2", 1.0},{"N2", -2.0},}},
  {"SKM2", 3, {{"S2", 1.0},{"K2", 1.0},{"M2", -1.0},}},
  {"2SN2", 2, {{"S2", 2.0},{"N2", -1.0},}},
  {"NO3", 2, {{"N2", 1.0},{"O1", 1.0},}},
  {"MO3", 2, {{"M2", 1.0},{"O1", 1.0},}},
  {"NK3", 2, {{"N2", 1.0},{"K1", 1.0},}},
  {"SO3", 2, {{"S2", 1.0},{"O1", 1.0},}},
  {"MK3", 2, {{"M2", 1.0},{"K1", 1.0},}},
  {"SP3", 2, {{"S2", 1.0},{"P1", 1.0},}},
  {"SK3", 2, {{"S2", 1.0},{"K1", 1.0},}},
  {"ST8", 3, {{"M2", 2.0},{"N2", 1.0},{"S2", -1.0},}},
  {"N4", 1, {{"N2", 2.0},}},
  {"3MS4", 2, {{"M2", 3.0},{"S2", -1.0},}},
  {"ST39", 4, {{"M2", 1.0},{"S2", 1.0},{"N2", 1.0},{"K2", -1.0},}},
  {"MN4", 2, {{"M2", 1.0},{"N2", 1.0},}},
  {"ST40", 3, {{"M2", 2.0},{"S2", 1.0},{"K2", -1.0},}},
  {"ST9", 4, {{"M2", 1.0},{"N2", 1.0},{"K2", 1.0},{"S2", -1.0},}},
  {"M4", 1, {{"M2", 2.0},}},
  {"ST10", 3, {{"M2", 2.0},{"K2", 1.0},{"S2", -1.0},}},
  {"SN4", 2, {{"S2", 1.0},{"N2", 1.0},}},
  {"KN4", 2, {{"K2", 1.0},{"N2", 1.0},}},
  {"MS4", 2, {{"M2", 1.0},{"S2", 1.0},}},
  {"MK4", 2, {{"M2", 1.0},{"K2", 1.0},}},
  {"SL4", 2, {{"S2", 1.0},{"L2", 1.0},}},
  {"S4", 1, {{"S2", 2.0},}},
  {"SK4", 2, {{"S2", 1.0},{"K2", 1.0},}},
  {"MNO5", 3, {{"M2", 1.0},{"N2", 1.0},{"O1", 1.0},}},
  {"2MO5", 2, {{"M2", 2.0},{"O1", 1.0},}},
  {"3MP5", 2, {{"M2", 3.0},{"P1", -1.0},}},
  {"MNK5", 3, {{"M2", 1.0},{"N2", 1.0},{"K1", 1.0},}},
  {"2MP5", 2, {{"M2", 2.0},{"P1", 1.0},}},
  {"2MK5", 2, {{"M2", 2.0},{"K1", 1.0},}},
  {"MSK5", 3, {{"M2", 1.0},{"S2", 1.0},{"K1", 1.0},}},
  {"3KM5", 3, {{"K2", 1.0},{"K1", 1.0},{"M2", 1.0},}},
  {"2SK5", 2, {{"S2", 2.0},{"K1", 1.0},}},
  {"ST11", 3, {{"N2", 3.0},{"K2", 1.0},{"S2", -1.0},}},
  {"2NM6", 2, {{"N2", 2.0},{"M2", 1.0},}},
  {"ST12", 4, {{"N2", 2.0},{"M2", 1.0},{"K2", 1.0},{"S2", -1.0},}},
  {"ST41", 3, {{"M2", 3.0},{"S2", 1.0},{"K2", -1.0},}},
  {"2MN6", 2, {{"M2", 2.0},{"N2", 1.0},}},
  {"ST13", 4, {{"M2", 2.0},{"N2", 1.0},{"K2", 1.0},{"S2", -1.0},}},
  {"M6", 1, {{"M2", 3.0},}},
  {"MSN6", 3, {{"M2", 1.0},{"S2", 1.0},{"N2", 1.0},}},
  {"MKN6", 3, {{"M2", 1.0},{"K2", 1.0},{"N2", 1.0},}},
  {"2MS6", 2, {{"M2", 2.0},{"S2", 1.0},}},
  {"2MK6", 2, {{"M2", 2.0},{"K2", 1.0},}},
  {"NSK6", 3, {{"N2", 1.0},{"S2", 1.0},{"K2", 1.0},}},
  {"2SM6", 2, {{"S2", 2.0},{"M2", 1.0},}},
  {"MSK6", 3, {{"M2", 1.0},{"S2", 1.0},{"K2", 1.0},}},
  {"ST42", 3, {{"M2", 2.0},{"S2", 2.0},{"K2", -1.0},}},
  {"S6", 1, {{"S2", 3.0},}},
  {"ST14", 3, {{"M2", 2.0},{"N2", 1.0},{"O1", 1.0},}},
  {"ST15", 3, {{"N2", 2.0},{"M2", 1.0},{"K1", 1.0},}},
  {"M7", 1, {{"M2", 3.5},}},
  {"ST16", 3, {{"M2", 2.0},{"S2", 1.0},{"O1", 1.0},}},
  {"3MK7", 2, {{"M2", 3.0},{"K1", 1.0},}},
  {"ST17", 4, {{"M2", 1.0},{"S2", 1.0},{"K2", 1.0},{"O1", 1.0},}},
  {"ST18", 2, {{"M2", 2.0},{"N2", 2.0},}},
  {"3MN8", 2, {{"M2", 3.0},{"N2", 1.0},}},
  {"ST19", 4, {{"M2", 3.0},{"N2", 1.0},{"K2", 1.0},{"S2", -1.0},}},
  {"M8", 1, {{"M2", 4.0},}},
  {"ST20", 3, {{"M2", 2.0},{"S2", 1.0},{"N2", 1.0},}},
  {"ST21", 3, {{"M2", 2.0},{"N2", 1.0},{"K2", 1.0},}},
  {"3MS8", 2, {{"M2", 3.0},{"S2", 1.0},}},
  {"3MK8", 2, {{"M2", 3.0},{"K2", 1.0},}},
  {"ST22", 4, {{"M2", 1.0},{"S2", 1.0},{"N2", 1.0},{"K2", 1.0},}},
  {"ST23", 2, {{"M2", 2.0},{"S2", 2.0},}},
  {"ST24", 3, {{"M2", 2.0},{"S2", 1.0},{"K2", 1.0},}},
  {"ST25", 3, {{"M2", 2.0},{"N2", 2.0},{"K1", 1.0},}},
  {"ST26", 3, {{"M2", 3.0},{"N2", 1.0},{"K1", 1.0},}},
  {"4MK9", 2, {{"M2", 4.0},{"K1", 1.0},}},
  {"ST27", 3, {{"M2", 3.0},{"S2", 1.0},{"K1", 1.0},}},
  {"ST28", 2, {{"M2", 4.0},{"N2", 1.0},}},
  {"M10", 1, {{"M2", 5.0},}},
  {"ST29", 3, {{"M2", 3.0},{"N2", 1.0},{"S2", 1.0},}},
  {"ST30", 2, {{"M2", 4.0},{"S2", 1.0},}},
  {"ST31", 4, {{"M2", 2.0},{"N2", 1.0},{"S2", 1.0},{"K2", 1.0},}},
  {"ST32", 2, {{"M2", 3.0},{"S2", 2.0},}},
  {"ST33", 3, {{"M2", 4.0},{"S2", 1.0},{"K1", 1.0},}},
  {"M12", 1, {{"M2", 6.0},}},
  {"ST34", 2, {{"M2", 5.0},{"S2", 1.0},}},
  {"ST35", 4, {{"M2", 3.0},{"N2", 1.0},{"K2", 1.0},{"S2", 1.0},}},
};

static double leftover(double x) {
  return (double) (x - ((x < 0.0) ? ceil(x) : floor(x)));
}

static int compare_constituents(const void *v0, const void *v1) {
  return strcasecmp(((struct _libtidal_constituent *)v0)->name, ((struct _libtidal_constituent *)v1)->name);
}
static int compare_shallows(const void *v0, const void *v1) {
  return strcasecmp(((struct _libtidal_shallow *)v0)->name, ((struct _libtidal_shallow *)v1)->name);
}

static int shallows_unsorted = 1;
static int constituents_unsorted = 1;

static int sort_shallows() {
  qsort(shallows, LIBTIDAL_SHALLOWS, sizeof(struct _libtidal_shallow), compare_shallows); shallows_unsorted = 0;
}
static int sort_constituents() {
  qsort(constituents, LIBTIDAL_CONSTITUENTS, sizeof(struct _libtidal_constituent), compare_constituents); constituents_unsorted = 0;
}

static struct _libtidal_constituent *libtidal_get_constituent(char *name) {
  struct _libtidal_constituent key;

  memset(&key, 0, sizeof(key));
  strncpy(key.name, name, LIBTIDAL_CHARLEN - 1);

  if (constituents_unsorted)
    sort_constituents();

  return bsearch(&key, constituents, LIBTIDAL_CONSTITUENTS, sizeof(struct _libtidal_constituent), compare_constituents);
}

static struct _libtidal_shallow *libtidal_get_shallow(char *name) {
  struct _libtidal_shallow key;

  memset(&key, 0, sizeof(key));
  strncpy(key.name, name, LIBTIDAL_CHARLEN - 1);

  if (shallows_unsorted)
    sort_shallows();

  return bsearch(&key, shallows, LIBTIDAL_SHALLOWS, sizeof(struct _libtidal_shallow), compare_shallows);
}

int libtidal_constituents(char *name, struct _libtidal_astronomical *astro, struct _libtidal_factors *factors) {
  int sat;
  double uu;
  double ratio = 0.0;
  double sumc = 1.0;
  double sums = 0.0;

  double slat; /* local latitude */
  struct _libtidal_constituent *constituent = NULL; /* tidal parts */

  // find the shallow water representation
  if ((constituent = libtidal_get_constituent(name)) == NULL)
    return -1;

  // blows up near the equator ...
  slat = sin(M_PI * ((fabs(astro->l) < 5.0) ? copysign(5.0, astro->l) : astro->l) / 180.0);

  // clear the decks ...
  memset(factors, 0, sizeof(struct _libtidal_factors));

  factors->V = constituent->semi;
  factors->V += ((double) constituent->doodson[0] * astro->t);
  factors->V += ((double) constituent->doodson[1] * astro->s);
  factors->V += ((double) constituent->doodson[2] * astro->h);
  factors->V += ((double) constituent->doodson[3] * astro->p);
  factors->V += ((double) constituent->doodson[4] * astro->np);
  factors->V += ((double) constituent->doodson[5] * astro->pp);
  factors->V = leftover(factors->V);

  factors->F = 0.0;
  factors->F += ((double) constituent->doodson[0] * astro->dt);
  factors->F += ((double) constituent->doodson[1] * astro->ds);
  factors->F += ((double) constituent->doodson[2] * astro->dh);
  factors->F += ((double) constituent->doodson[3] * astro->dp);
  factors->F += ((double) constituent->doodson[4] * astro->dnp);
  factors->F += ((double) constituent->doodson[5] * astro->dpp);
  factors->F /= (24.0 * 60.0 * 60.0);

  for (sat = 0; sat < LIBTIDAL_MAXSATS; sat++) {
    if (constituent->satellites[sat].corr < 0) break;

    if (constituent->satellites[sat].corr == 1)
      ratio = constituent->satellites[sat].ratio * 0.36309 * (1.0 - 5.0 * slat * slat) / slat;
    else if (constituent->satellites[sat].corr == 2)
      ratio = constituent->satellites[sat].ratio * 2.59808 * slat;
    else
      ratio = constituent->satellites[sat].ratio;

    uu = constituent->satellites[sat].phase;
    uu += ((double) constituent->satellites[sat].doodson[3] * astro->p);
    uu += ((double) constituent->satellites[sat].doodson[4] * astro->np);
    uu += ((double) constituent->satellites[sat].doodson[5] * astro->pp);
    uu = leftover(uu);

    sumc += ratio * cos(2.0 * M_PI * uu);
    sums += ratio * sin(2.0 * M_PI * uu);
  }

  factors->f = sqrt(sums * sums + sumc * sumc);
  factors->u = 0.5 * atan2(sums, sumc) / M_PI;

  // done ...
  return 0;
}

int libtidal_shallows(char *name, struct _libtidal_astronomical *astro, struct _libtidal_factors *factors) {
  int part = 0;
  struct _libtidal_shallow *shallow = NULL; /* tidal parts */
  struct _libtidal_factors parts;

  /* reset factors */
  memset(factors, 0, sizeof( struct _libtidal_factors));

  // find the shallow water representation
  if ((shallow = libtidal_get_shallow(name)) == NULL)
    return -1;

  // run through each consitituent part ...
  for (part = 0; part < shallow->nparts; part++) {
    // find the contribution ...
    if (libtidal_constituents(shallow->parts[part].name, astro, &parts) < 0)
      return -1;

    // adjustements ...
    factors->V += shallow->parts[part].coef * parts.V;
    factors->F += shallow->parts[part].coef * parts.F;
    factors->u += shallow->parts[part].coef * parts.u;
    factors->f *= pow((part > 0) ? parts.f : 1.0, fabs(shallow->parts[part].coef));
  }

  // done
  return 0;
}