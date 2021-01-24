#include <M5Stack.h>
#include <OSCMessage.h>
#include <SLIPEncodedSerial.h>
#include "splash.h"
#include "indicator.h"
#include "control.h"
#include "colors.h"
#include "metro.h"
#include "nav.h"

SLIPEncodedSerial SLIPSerial(Serial);

enum Mode
{
  control,
  nav
};
Mode mode = control;

void setup()
{
  M5.begin();
  M5.Power.begin();
  Serial.setRxBufferSize(1024);
  SLIPSerial.begin(115200);

  splash(true);
}

boolean isActive(uint8_t pos)
{
  return pos == lastControl && ctrlEvents > 4;
}

void controlMsg(OSCMessage &msg)
{
  if (mode != control)
  {
    return;
  }
  int8_t pos = msg.getInt(0);
  if (pos < 1)
  {
    return;
  }
  pos--;
  msg.getString(2, controls[pos].value);

  const float ctrl = msg.getFloat(1);
  controls[pos].ctrl = ctrl == -1 ? (float)msg.getInt(1) : ctrl;

  if (isActive(pos))
  {
    renderControl(pos, controls[pos], true);
    ctrlEvents = 4;
  }
  else
  {
    renderControl(pos, controls[pos], false);
  }

  if (lastControl != pos && ctrlEvents > 4)
  {
    renderControl(lastControl, controls[lastControl], false);
  }

  lastControl = pos;
  ctrlEvents++;
}

void controlDesc(int pos, OSCMessage &msg)
{
  msg.getString(0, controls[pos].desc);
  if (lastControl != pos && mode == control)
  {
    renderControl(pos, controls[pos], false);
  }
}

void p1DescMsg(OSCMessage &msg)
{
  controlDesc(0, msg);
}

void p2Desc(OSCMessage &msg)
{
  controlDesc(1, msg);
}

void p3DescMsg(OSCMessage &msg)
{
  controlDesc(2, msg);
}

void p4DescMsg(OSCMessage &msg)
{
  controlDesc(3, msg);
}

void headerMsg(OSCMessage &msg)
{
  mode = control;
  msg.getString(0, module);
  msg.getString(1, page);
  title(module, page);
}

void navMsg(OSCMessage &msg)
{
  if (mode != nav)
  {
    clearText();
    renderNav();
    mode = nav;
  }
}

void textMsg(OSCMessage &msg)
{
  int pos = msg.getInt(0) - 1;
  if (pos >= 0)
  {
    msg.getString(1, text[pos]);
    if (mode == nav)
    {
      renderNav();
    }
  }
}

void selectTextMsg(OSCMessage &msg)
{
  int pos = msg.getInt(0) - 1;
  if (pos >= 0)
  {
    selectText(pos);
    if (mode == nav)
    {
      renderNav();
    }
  }
}

void clearTextMsg(OSCMessage &msg)
{
  if (mode == nav)
  {
    clearText();
  }
}

void trackMsg(OSCMessage &msg)
{
  activateTrack(msg.getInt(0));
}

boolean firstBeat = true;

void tickMsg(OSCMessage &msg)
{
  int tick = msg.getInt(0);
  if (firstBeat)
  {
    metroLine(0xFFFF, tick / 32);
    header();
    firstBeat = false;
  }
  renderBeat(0xFFFF, msg.getInt(0));
}

void byeMsg(OSCMessage &msg)
{
  splash(false);
  firstBeat = true;
}

void loop()
{
  OSCMessage msg;
  while (!SLIPSerial.endofPacket())
  {
    int size = SLIPSerial.available();
    if (size > 0)
    {
      while (size--)
      {
        int c = SLIPSerial.read();
        msg.fill(c);
      }
    }
  }

  msg.dispatch("/P1Desc", p1DescMsg);
  msg.dispatch("/P2Desc", p2Desc);
  msg.dispatch("/P3Desc", p3DescMsg);
  msg.dispatch("/P4Desc", p4DescMsg);

  msg.dispatch("/control", controlMsg);
  msg.dispatch("/header", headerMsg);

  msg.dispatch("/nav", navMsg);
  msg.dispatch("/text", textMsg);
  msg.dispatch("/selectText", selectTextMsg);
  msg.dispatch("/clearText", clearTextMsg);

  msg.dispatch("/track", trackMsg);

  msg.dispatch("/tick", tickMsg);
  msg.dispatch("/bye", byeMsg);
}
