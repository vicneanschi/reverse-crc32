#include "stdafx.h"
#include <stdio.h>
#include "Crc32.h"
#include <string.h>

const char* testOneAscii(UInt32 startCrc, UInt32 wantedCrc)
{
    Crc32 crc;
    
    crc.set(startCrc);

    const char* patch = crc.findReverseAscii(wantedCrc);
    crc.append(patch, 6);

    printf("    initial: 0x%.8x %s -  string to add: %s\n",  
           startCrc, (wantedCrc == crc.get() ? "OK  " : "FAIL"), patch);
	return patch;
}

int main(void)
{
	Crc32 crc{};
	const char * message = "Hello world!";
	UInt32 initialCrc = crc.crc32_tabledriven((unsigned char *)message, strlen(message));
	
	printf("initial crc32: 0x%.8x\n", initialCrc);
	UInt32 wantedCrc = 0xbbd1264f; // http://slides.com/ivanvoras/blockchain1#/11
	const char *result = testOneAscii(initialCrc, wantedCrc);  // Hello world!1Naxuh
	printf("Solution: %s%s", message, result);
    return 0;
}
