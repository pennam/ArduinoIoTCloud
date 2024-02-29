/*
   This file is part of ArduinoIoTCloud.

   Copyright 2020 ARDUINO SA (http://www.arduino.cc/)

   This software is released under the GNU General Public License version 3,
   which covers the main part of arduino-cli.
   The terms of this license can be found at:
   https://www.gnu.org/licenses/gpl-3.0.en.html

   You can be released from the requirements of the above licenses by purchasing
   a commercial license. Buying such a license is mandatory if you want to modify or
   otherwise use the software for commercial activities involving the Arduino
   software without disclosing the source code of your own applications. To purchase
   a commercial license, send an email to license@arduino.cc.
*/

/******************************************************************************
 * INCLUDE
 ******************************************************************************/

#include "CBOREncoder.h"

#undef max
#undef min
#include <algorithm>
#include <iterator>

#include "lib/tinycbor/cbor-lib.h"
#include "MessageEncoder.h"

/******************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 ******************************************************************************/

CborError MessageEncoder::encode(Message * message, uint8_t * data, size_t const size, int & bytes_encoded)
{
  EncoderState current_state = EncoderState::EncodeTag,
                 next_state  = EncoderState::Error;

  CborEncoder encoder;
  CborEncoder arrayEncoder;

  cbor_encoder_init(&encoder, data, size, 0);

  while (current_state != EncoderState::Complete) {

    switch (current_state) {
      case EncoderState::EncodeTag            : next_state = handle_EncodeTag(&encoder, message); break;
      case EncoderState::EncodeArray          : next_state = handle_EncodeArray(&encoder, &arrayEncoder, message); break;
      case EncoderState::EncodeParam          : next_state = handle_EncodeParam(&arrayEncoder, message); break;
      case EncoderState::CloseArray           : next_state = handle_CloseArray(&encoder, &arrayEncoder); break;
      case EncoderState::MessageNotSupported  : return CborErrorUnsupportedType; break;
      case EncoderState::Complete             : /* Nothing to do */ break;
      case EncoderState::Error                : return CborErrorInternalError; break;
    }

    current_state = next_state;
  }

  bytes_encoded = cbor_encoder_get_buffer_size(&encoder, data);

  return CborNoError;
}

/******************************************************************************
   PRIVATE MEMBER FUNCTIONS
 ******************************************************************************/

MessageEncoder::EncoderState MessageEncoder::handle_EncodeTag(CborEncoder * encoder, Message * message)
{
  CborTag commandTag = (uint64_t) message->id;
  if (cbor_encode_tag(encoder, commandTag) != CborNoError)
    return EncoderState::Error;

  return EncoderState::EncodeArray;
}

MessageEncoder::EncoderState MessageEncoder::handle_EncodeArray(CborEncoder * encoder, CborEncoder * array_encoder, Message * message)
{
  // Set array size based on the message id
  size_t array_size = 0;
  switch (message->id)
  {
  case CommandID::OtaBeginUpId:
    array_size = 1;
    break;
  case CommandID::ThingGetIdCmdUpId:
    array_size = 1;
    break;
  case CommandID::DeviceBeginCmdUpId:
    array_size = 1;
    break;
  case CommandID::ThingGetLastValueCmdUpId:
    break;
  case CommandID::OtaProgressCmdUpId:
    array_size = 4;
    break;
  case CommandID::TimezoneCommandUpId:
    break;
  default:
    return EncoderState::MessageNotSupported;
  }

  // Start an array with fixed width based on message type
  if (cbor_encoder_create_array(encoder, array_encoder, array_size) != CborNoError){
    return EncoderState::Error;
  }

  return EncoderState::EncodeParam;
}

MessageEncoder::EncoderState MessageEncoder::handle_EncodeParam(CborEncoder * array_encoder, Message * message)
{
  CborError error = CborNoError;
  switch (message->id)
  {
  case CommandID::OtaBeginUpId:
    error = MessageEncoder::encodeOtaBeginUp(array_encoder, message);
    break;
  case CommandID::ThingGetIdCmdUpId:
    error = MessageEncoder::encodeThingGetIdCmdUp(array_encoder, message);
    break;
  case CommandID::DeviceBeginCmdUpId:
    error = MessageEncoder::encodeDeviceBeginCmdUp(array_encoder, message);
    break;
  case CommandID::ThingGetLastValueCmdUpId:
    break;
  case CommandID::OtaProgressCmdUpId:
    error = MessageEncoder::encodeOtaProgressCmdUp(array_encoder, message);
    break;
  case CommandID::TimezoneCommandUpId:
    break;
  default:
    return EncoderState::MessageNotSupported;
  }

  if (error != CborNoError) {
    return EncoderState::Error;
  }
    
  return EncoderState::CloseArray;
}

MessageEncoder::EncoderState MessageEncoder::handle_CloseArray(CborEncoder * encoder, CborEncoder * array_encoder)
{

  if (cbor_encoder_close_container(encoder, array_encoder) != CborNoError) {
    return EncoderState::Error;
  }
    
  return EncoderState::Complete;
}

// Message specific encoders
CborError MessageEncoder::encodeOtaBeginUp(CborEncoder * array_encoder, Message * message)
{
  OtaBeginUp * otaBeginUp = (OtaBeginUp *) message;
  CHECK_CBOR(cbor_encode_byte_string(array_encoder, otaBeginUp->fields.params.sha, SHA256_SIZE));
  return CborNoError;
}

CborError MessageEncoder::encodeThingGetIdCmdUp(CborEncoder * array_encoder, Message * message)
{
  ThingGetIdCmdUp * thingGetIdCmdUp = (ThingGetIdCmdUp *) message;
  CHECK_CBOR(cbor_encode_text_stringz(array_encoder, thingGetIdCmdUp->fields.params.thing_id));
  return CborNoError;
}

CborError MessageEncoder::encodeDeviceBeginCmdUp(CborEncoder * array_encoder, Message * message)
{
  DeviceBeginCmdUp * deviceBeginCmdUp = (DeviceBeginCmdUp *) message;
  CHECK_CBOR(cbor_encode_text_stringz(array_encoder, deviceBeginCmdUp->fields.params.lib_version));
  return CborNoError;
}

CborError MessageEncoder::encodeOtaProgressCmdUp(CborEncoder * array_encoder, Message * message)
{
  OtaProgressCmdUp * ota = (OtaProgressCmdUp *)message;
  CHECK_CBOR(cbor_encode_text_stringz(array_encoder, ota->fields.params.id));
  CHECK_CBOR(cbor_encode_text_stringz(array_encoder, ota->fields.params.state));
  CHECK_CBOR(cbor_encode_uint(array_encoder, ota->fields.params.time));
  CHECK_CBOR(cbor_encode_uint(array_encoder, ota->fields.params.count));
  return CborNoError;
}

