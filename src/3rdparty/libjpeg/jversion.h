/*
 * jversion.h
 *
 * This file was part of the Independent JPEG Group's software:
 * Copyright (C) 1991-2020, Thomas G. Lane, Guido Vollbeding.
 * libjpeg-turbo Modifications:
 * Copyright (C) 2010, 2012-2024, D. R. Commander.
 * For conditions of distribution and use, see the accompanying README.ijg
 * file.
 *
 * This file contains software version identification.
 */


#if JPEG_LIB_VERSION >= 80

#define JVERSION        "libjpeg-turbo 3.1.4.1 with libjpeg 8 API"

#elif JPEG_LIB_VERSION >= 70

#define JVERSION        "libjpeg-turbo 3.1.4.1 with libjpeg 7 API"

#else

#define JVERSION        "libjpeg-turbo 3.1.4.1 with libjpeg 6b API"

#endif

/*
 * NOTE: It is our convention to place the authors in the following order:
 * - libjpeg-turbo authors (2009-) in descending order of the date of their
 *   most recent contribution to the project, then in ascending order of the
 *   date of their first contribution to the project, then in alphabetical
 *   order
 * - Upstream authors in descending order of the date of the first inclusion of
 *   their code
 */

#define JCOPYRIGHT1 \
  "Copyright (C) 2009-2024 D. R. Commander\n" \
  "Copyright (C) 2015, 2020 Google, Inc.\n" \
  "Copyright (C) 2019-2020 Arm Limited\n" \
  "Copyright (C) 2015-2016, 2018 Matthieu Darbois\n" \
  "Copyright (C) 2011-2016 Siarhei Siamashka\n" \
  "Copyright (C) 2015 Intel Corporation\n"
#define JCOPYRIGHT2 \
  "Copyright (C) 2013-2014 Linaro Limited\n" \
  "Copyright (C) 2013-2014 MIPS Technologies, Inc.\n" \
  "Copyright (C) 2009, 2012 Pierre Ossman for Cendio AB\n" \
  "Copyright (C) 2009-2011 Nokia Corporation and/or its subsidiary(-ies)\n" \
  "Copyright (C) 1999-2006 MIYASAKA Masaru\n" \
  "Copyright (C) 1999 Ken Murchison\n" \
  "Copyright (C) 1991-2020 Thomas G. Lane, Guido Vollbeding\n"

#define JCOPYRIGHT_SHORT \
  "Copyright (C) 2024 The libjpeg-turbo Project and many others"
