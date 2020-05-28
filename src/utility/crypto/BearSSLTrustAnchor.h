/*
   This file is part of ArduinoIoTBearSSL.

   Copyright 2019 ARDUINO SA (http://www.arduino.cc/)

   This software is released under the GNU General Public License version 3,
   which covers the main part of ArduinoIoTBearSSL.
   The terms of this license can be found at:
   https://www.gnu.org/licenses/gpl-3.0.en.html

   You can be released from the requirements of the above licenses by purchasing
   a commercial license. Buying such a license is mandatory if you want to modify or
   otherwise use the software for commercial activities involving the Arduino
   software without disclosing the source code of your own applications. To purchase
   a commercial license, send an email to license@arduino.cc.

*/

#ifndef _BEAR_SSL_TRUST_ANCHOR_H_
#define _BEAR_SSL_TRUST_ANCHOR_H_

/******************************************************************************
 * INCLUDE
 ******************************************************************************/

#include <ArduinoIoTCloud_Config.h>

#ifdef BOARD_HAS_ECCX08

#include "bearssl/bearssl_ssl.h"

/******************************************************************************
 * CONSTANTS
 ******************************************************************************/

// The following was created by running the BearSSL "brssl" tool in the
// extras/TrustAnchors directory:
//
//   brssl ta *.cer

static const unsigned char TA0_DN[] = {
  0x30, 0x45, 0x31, 0x0B, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13,
  0x02, 0x55, 0x53, 0x31, 0x17, 0x30, 0x15, 0x06, 0x03, 0x55, 0x04, 0x0A,
  0x13, 0x0E, 0x41, 0x72, 0x64, 0x75, 0x69, 0x6E, 0x6F, 0x20, 0x4C, 0x4C,
  0x43, 0x20, 0x55, 0x53, 0x31, 0x0B, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04,
  0x0B, 0x13, 0x02, 0x49, 0x54, 0x31, 0x10, 0x30, 0x0E, 0x06, 0x03, 0x55,
  0x04, 0x03, 0x13, 0x07, 0x41, 0x72, 0x64, 0x75, 0x69, 0x6E, 0x6F
};

static const unsigned char TA0_EC_Q[] = {
  0x04, 0x6D, 0x77, 0x6C, 0x5A, 0xCF, 0x61, 0x1C, 0x7D, 0x44, 0x98, 0x51,
  0xF2, 0x5E, 0xE1, 0x02, 0x40, 0x77, 0xB7, 0x9C, 0xBD, 0x49, 0xA2, 0xA3,
  0x8C, 0x4E, 0xAB, 0x5E, 0x98, 0xAC, 0x82, 0xFC, 0x69, 0x5B, 0x44, 0x22,
  0x77, 0xB4, 0x4D, 0x2E, 0x8E, 0xDF, 0x2A, 0x71, 0xC1, 0x39, 0x6C, 0xD6,
  0x39, 0x14, 0xBD, 0xD9, 0x6B, 0x18, 0x4B, 0x4B, 0xEC, 0xB3, 0xD5, 0xEE,
  0x42, 0x89, 0x89, 0x55, 0x22
};

static const unsigned char TA1_DN[] = {
  0x30, 0x50, 0x31, 0x0B, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13,
  0x02, 0x55, 0x53, 0x31, 0x17, 0x30, 0x15, 0x06, 0x03, 0x55, 0x04, 0x0A,
  0x13, 0x0E, 0x41, 0x72, 0x64, 0x75, 0x69, 0x6E, 0x6F, 0x20, 0x4C, 0x4C,
  0x43, 0x20, 0x55, 0x53, 0x31, 0x0B, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04,
  0x0B, 0x13, 0x02, 0x49, 0x54, 0x31, 0x1B, 0x30, 0x19, 0x06, 0x03, 0x55,
  0x04, 0x03, 0x13, 0x12, 0x63, 0x65, 0x73, 0x2E, 0x69, 0x6F, 0x74, 0x2E,
  0x61, 0x72, 0x64, 0x75, 0x69, 0x6E, 0x6F, 0x2E, 0x63, 0x63
};

static const unsigned char TA1_EC_Q[] = {
  0x04, 0x57, 0x4A, 0xF7, 0xFB, 0x20, 0x2A, 0x1E, 0xBD, 0x98, 0xD5, 0xA8,
  0xFF, 0xD4, 0xEF, 0x7B, 0x90, 0xB9, 0x37, 0xA0, 0xB7, 0x00, 0x16, 0x09,
  0x57, 0x3C, 0xD5, 0x92, 0x42, 0xAA, 0x9F, 0x78, 0xCF, 0xD5, 0x54, 0x21,
  0xE6, 0x28, 0x89, 0x73, 0x2A, 0x4E, 0xC3, 0x9D, 0xBC, 0x10, 0x57, 0x79,
  0x91, 0x87, 0x93, 0xD8, 0xAE, 0x15, 0xA7, 0xDB, 0x79, 0x56, 0x4D, 0x5F,
  0x96, 0x8D, 0xE3, 0xDC, 0x51
};

static const br_x509_trust_anchor ArduinoIoTCloudTrustAnchor[2] = {
  {
    { (unsigned char *)TA0_DN, sizeof TA0_DN },
    BR_X509_TA_CA,
    {
      BR_KEYTYPE_EC,
      {
        .ec = {
          BR_EC_secp256r1,
          (unsigned char *)TA0_EC_Q, sizeof TA0_EC_Q,
        }
      }
    }
  },
  {
    { (unsigned char *)TA1_DN, sizeof TA1_DN },
    0,
    {
      BR_KEYTYPE_EC,
      {
        .ec = {
          BR_EC_secp256r1,
          (unsigned char *)TA1_EC_Q, sizeof TA1_EC_Q,
        }
      }
    }
  }
};

#define ArduinoIoTCloudTrustAnchor_NUM (2)

#endif /* BOARD_HAS_ECCX08 */

#endif /* _BEAR_SSL_TRUST_ANCHOR_H_ */
