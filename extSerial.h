#ifndef extSerial_h
#define extSerial_h

// Alright, why do I want this? What this? How do I use it?
//
// If you have issues with larger chunks of data coming into your Serial buffer and
// overrunning it's fixed 65 byte buffer, causing all sorts of headaches, then this is for
// you!
//
// This glues a buffer extension to the original input buffer. Allowing larger chunks of
// data to be buffered, while your program gets around to reading it. Think of it like an
// employee with a shovel. They spend all their time shoveling data out of the serial
// buffer, for you to read at your leisure.
//
// This doesn't actually change your Serial port in any way. It just keeps it cleared out
// as much as possible. Setting up and Writing to your Serial port is unaffected. Do this
// like you always do. Just when it comes to reading you're serial port, use these calls.
//

/*

#include  <extSerial.h>						// Including the library.

extSerial mySerial(&Serial);				// Create by choosing your port.

void setup(void) {

	Serial.begin(9600);						// Start up as usual.
	if (!Serial) {
		//wait, or not..
	}
	mySerial.begin();							// Don't need to wait or ask. Just call it.
	Serial.println("We have Serial!");	// Output is unaffected.
}


// We'll do a simple "echo what was typed" exa.mple here.
void loop(void) {

	char	aChar;
	
	idle();								// IMPORTANT!! idle() runs all the magic behind the scenes.
	if (mySerial.available()) {	// Use extSerial for available().
		aChar = mySerial.read();	// And read().
		Serial.print(aChar);			// Original calls for output.
	}
}

*/

// NOTE: DO NOT USE delay() IN YOUR CODE! THIS WILL STOP EVERYTHING. BUT, NO FEAR! WE
// SUPPLY YOU WITH A sleep() call that acts just like delay for you, but does NOT stop
// everything. Try it, you'll love it! 
//
// Remember : When people demand code without using delay(), because it causes blocking,
// our sleep() call does NOT cause blocking. What a hack!


#include <textBuff.h>
#include <idlers.h>

#define DEF_BYTES_ADDED	100


class extSerial :	public textBuff,
						public idler {
						
	public:
				extSerial(Stream* inStream,int inBytes=DEF_BYTES_ADDED);
	virtual	~extSerial(void);
	
	virtual	void	begin(void);
	virtual	int	available(void);
	virtual	int	read(void);
	
	virtual	void	grabData(void);
	virtual	void	idle(void);

				Stream*	ourPort;
};
	
				
				
#endif