#include <extSerial.h>


extSerial::extSerial(Stream* inStream,int inBytes)
	: textBuff(inBytes),
	idler() { ourPort = inStream; }


extSerial::~extSerial(void) {  }


void extSerial::begin(void) { hookup(); }


int extSerial::available(void) {

	int	numbytes;
	
	numbytes = 0;													// We start at zero bytes. Make sense.
	if (ourPort) {													// Sanity! They could pass you a NULL then blame you for a crash. They're like that.
		grabData();													// Any time we can, shovel out data first!
		numbytes = numChars() + ourPort->available();	// Let's give them the total amount.
	}																	//
	return numbytes;												// There you go.
}


int extSerial::read(void) {

	int	outByte;
	
	outByte = -1;								// From the Arduino doc. No Byte gets -1.
	if (ourPort) {								// Again, keep an eye on these guys, they're nuts!
		grabData();								// As always shovel shovel shovel.
		if (numChars()) {						// If we have any data.
			outByte = (int)readChar();		// Give them a byte.
		}											//
	}												//
	return(outByte);							// Here is your result sir.
}



// These next two guys? You shouldn't mess with 'em. It would be like sticking your hand
// into a running engine.


// Shovel out all the data we can get.
void extSerial::grabData(void) {

	char	aChar;
	
	if (ourPort) {											// Sanity..
		while(!full()&&ourPort->available()) {		// If our buffer is NOT full and there are bytes to read?..
			aChar = ourPort->read();					// Read one.
			addChar(aChar);								// Store it away.
		}														// Repeat.
	}															//
}


// The magic that runs the machine in the background. It's like having our own private
// piece of the user's loop() function.
void extSerial::idle(void) { grabData(); }
