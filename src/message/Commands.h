/*
  This file is part of the ArduinoIoTCloud library.

  Copyright (c) 2024 Arduino SA

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#pragma once

/******************************************************************************
 * INCLUDE
 ******************************************************************************/

#include <stdint.h>
#include <stddef.h>

/******************************************************************************
 * DEFINE
 ******************************************************************************/

#define THING_ID_SIZE        37
#define SHA256_SIZE          32
#define URL_SIZE            256
#define MAX_STATE_SIZE       32
#define ID_SIZE              32
#define MAX_LIB_VERSION_SIZE 10

/******************************************************************************
 * TYPEDEF
 ******************************************************************************/

enum CommandId : uint16_t {
  /* Commands Up */
  OtaBeginUpId,
  ThingGetIdCmdUpId,
  ThingGetLastValueCmdUpId,
  DeviceBeginCmdUpId,
  OtaProgressCmdUpId,
  TimezoneCommandUpId,

  /* Commands Down */
  OtaUpdateCmdDownId,
  ThingGetIdCmdDownId,
  ThingGetLastValueCmdDownId,
  TimezoneCommandDownId,

  /* Device Events */
  SendCapabilities,
  GetThingId,
  ThingId,
  AttachThing,
  DetachThing,

  /* Thing Events */
  GetLastValues,
  LastValues,
  SendProperties,

  /* Ota Events */
  OtaUrl,
  OtaReq,
  OtaConfirm,
  OtaStart,
  OtaError,

  /* Generic Events */
  Disconnect,
  Reset,

  /* Unknown command id */
  UnknownCmdId
};

struct Command {
  CommandId id;
};

typedef Command Message;

struct ThingGetIdCmdUp {
  Command c;
  struct {
    char thing_id[THING_ID_SIZE];
  } params;
};

struct ThingGetLastValueCmdUp {
  Command c;
};

struct OtaBeginUp {
  Command c;
  struct {
    uint8_t sha[SHA256_SIZE];
  } params;
};

struct DeviceBeginCmdUp {
  Command c;
  struct {
    char lib_version[MAX_LIB_VERSION_SIZE];
  } params;
};

struct OtaProgressCmdUp {
  Command c;
  struct {
    char id[ID_SIZE];
    char state[MAX_STATE_SIZE];
    uint32_t time;
    uint32_t count;
  } params;
};

struct TimezoneCommandUp {
  Command c;
};

struct __attribute__((__packed__)) OtaUpdateCmdDown {
  Command c;
  struct {
    char id[ID_SIZE];
    char url[URL_SIZE];
    uint8_t initialSha256[SHA256_SIZE];
    uint8_t finalSha256[SHA256_SIZE];
  } params;
};

struct __attribute__((__packed__)) ThingGetIdCmdDown {
  Command c;
  struct {
    char thing_id[THING_ID_SIZE];
  } params;
};

struct __attribute__((__packed__)) ThingGetLastValueCmdDown {
  Command c;
  struct {
    uint8_t *last_values;
    size_t length;
  } params;
};

struct __attribute__((__packed__)) TimezoneCommandDown {
  Command c;
  struct {
    uint32_t offset;
    uint32_t until;
  } params;
};

union CommandDown {
  struct Command c;
  struct OtaUpdateCmdDown otaUpdateCmdDown;
  struct ThingGetIdCmdDown thingGetIdCmdDown;
  struct ThingGetLastValueCmdDown thingGetLastValueCmdDown;
  struct TimezoneCommandDown timezoneCommandDown;
  uint8_t buf[sizeof(otaUpdateCmdDown)];
};
