/* Do not edit this file. It was automatically generated. */

#ifndef HEADER_ColumnsPanel
#define HEADER_ColumnsPanel
/*
htop - ColumnsPanel.h
(C) 2004-2011 Hisham H. Muhammad
Released under the GNU GPL, see the COPYING file
in the source distribution for its full text.
*/

#include "Panel.h"
#include "Settings.h"

typedef struct ColumnsPanel_ {
   Panel super;
   ScreenSettings* ss;
   bool* changed;

   bool moving;
} ColumnsPanel;


extern PanelClass ColumnsPanel_class;

void ColumnsPanel_fill(ColumnsPanel* this, ScreenSettings* ss);

ColumnsPanel* ColumnsPanel_new(ScreenSettings* ss, bool* changed);

int ColumnsPanel_fieldNameToIndex(const char* name);

void ColumnsPanel_update(Panel* super);


#endif