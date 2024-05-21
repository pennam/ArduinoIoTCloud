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

#include <AIoTC_Config.h>
#ifdef BOARD_HAS_ECCX08

/******************************************************************************
 * CONSTANTS
 ******************************************************************************/

// The following was created by running the BearSSL "brssl" tool in the
// extras/TrustAnchors directory:
//
//   brssl ta *.cer

extern const unsigned char TA0_DN[];

extern const unsigned char TA0_EC_Q[];

extern const br_x509_trust_anchor ArduinoIoTCloudTrustAnchor[];

#define ArduinoIoTCloudTrustAnchor_NUM (1)

#endif /* #ifdef BOARD_HAS_ECCX08 */

#endif /* _BEAR_SSL_TRUST_ANCHOR_H_ */
