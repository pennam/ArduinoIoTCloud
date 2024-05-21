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

#ifndef _AIOTC_SS_CERT_H_
#define _AIOTC_SS_CERT_H_

/******************************************************************************
 * INCLUDE
 ******************************************************************************/

#include <AIoTC_Config.h>
#if defined(BOARD_HAS_SE050) || defined(BOARD_HAS_SOFTSE)

/******************************************************************************
 * CONSTANTS
 ******************************************************************************/
extern const char AIoTSSCert[];

#endif /* #if defined(BOARD_HAS_SE050) || defined(BOARD_HAS_SOFTSE) */

#endif /* _AIOTC_SS_CERT_H_ */
