//
// This file is part of ArduinoCloudThing
//
// Copyright 2021 ARDUINO SA (http://www.arduino.cc/)
//
// This software is released under the GNU General Public License version 3,
// which covers the main part of ArduinoCloudThing.
// The terms of this license can be found at:
// https://www.gnu.org/licenses/gpl-3.0.en.html
//
// You can be released from the requirements of the above licenses by purchasing
// a commercial license. Buying such a license is mandatory if you want to modify or
// otherwise use the software for commercial activities involving the Arduino
// software without disclosing the source code of your own applications. To purchase
// a commercial license, send an email to license@arduino.cc.
//

#ifndef CLOUDSCHEDULER_H_
#define CLOUDSCHEDULER_H_

/******************************************************************************
   INCLUDE
 ******************************************************************************/

#include <Arduino.h>
#include "../Property.h"

/******************************************************************************
   CLASS DECLARATION
 ******************************************************************************/

class Scheduler {
  public:
    CloudTime start, end, duration;
    int type;
    CloudTime interval;
    Color(float h, float s, float b): hue(h), sat(s), bri(b) {
      setColorHSB(h, s, b);
    }

    bool isActive() {
      if (now > start && now < end) {
        CloudTime delta = getNextSchedule(now);
        while (start + delta < now) {
          if (start + delta + duration > now) {
            return true;
          }
          delta += getNextSchedule();
        }
      }
      return false;
    }

};

class CloudColor : public Property {
  private:
    Color _value,
          _cloud_value;
  public:
    CloudColor() : _value(0, 0, 0), _cloud_value(0, 0, 0) {}
    CloudColor(float hue, float saturation, float brightness) : _value(hue, saturation, brightness), _cloud_value(hue, saturation, brightness) {}

    virtual bool isDifferentFromCloud() {

      return _value != _cloud_value;
    }

    CloudColor& operator=(Color aColor) {
      _value.hue = aColor.hue;
      _value.sat = aColor.sat;
      _value.bri = aColor.bri;
      updateLocalTimestamp();
      return *this;
    }

    Color getCloudValue() {
      return _cloud_value;
    }

    Color getValue() {
      return _value;
    }

    virtual void fromCloudToLocal() {
      _value = _cloud_value;
    }
    virtual void fromLocalToCloud() {
      _cloud_value = _value;
    }
    virtual CborError appendAttributesToCloud() {
      CHECK_CBOR(appendAttribute(_value.hue));
      CHECK_CBOR(appendAttribute(_value.sat));
      CHECK_CBOR(appendAttribute(_value.bri));
      return CborNoError;
    }
    virtual void setAttributesFromCloud() {
      setAttribute(_cloud_value.hue);
      setAttribute(_cloud_value.sat);
      setAttribute(_cloud_value.bri);
    }
};

#endif /* CLOUDSCHEDULER_H_ */