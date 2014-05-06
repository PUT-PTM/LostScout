#include <wtypes.h>
    extern "C" {
    #include "setupapi.h"
    #include "hidsdi.h"
    }
bool FindTheHID(void);
void GetDeviceCapabilities(void);
void PrepareForOverlappedTransfer(void);
void WriteOutputReport(char * outbuffer);
void DisplayInputReport(char * buffer);
void ReadInputReport( char * inbuffer);

void WriteOutputReportEdit(int i);

bool FindTheHID2(void);
void GetDeviceCapabilities2(void);
void PrepareForOverlappedTransfer2(void);
void WriteOutputReport2(char * outbuffer);
void DisplayInputReport2(char * buffer);
void ReadInputReport2( char * inbuffer);

void WriteOutputReportEdit2(int i);

#pragma once

#include <tchar.h>
