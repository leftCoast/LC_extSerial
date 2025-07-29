# LC_extSerial

 Alright, why do I want this? What is this? How do I use it?
 
 If you have issues with larger chunks of data coming into your Serial port and
 overrunning it's fixed 65 byte buffer? Then this is for you!

 This glues a buffer extension to the original Serial input buffer. Allowing larger
 chunks of data to be buffered, while your program gets around to reading it. Think
 of it like an employee with a shovel. They spend all their time shoveling data out
 of the serial buffer, for you to read at your leisure.

 This doesn't actually change your Serial port in any way. It just keeps it cleared out
 as much as possible. Setting up and Writing to your Serial port is unaffected. Do this
 like you always do. Just, when it comes to reading, use these calls.

```c++
#include  <extSerial.h>				// Including the library.

extSerial mySerial(&Serial);			// Create by choosing your port.

void setup(void) {

	Serial.begin(9600);			// Start up as usual.
	if (!Serial) {
						// wait, stop or whatever..
	}
	mySerial.begin();			// Don't need to wait or ask. Just call it.
	Serial.println("We have Serial!");	// Output is unaffected.
}


// We'll do a simple "echo what was typed" exa.mple here.
void loop(void) {

	char	aChar;
	
	idle();					// IMPORTANT!! idle() runs all the magic behind the scenes.
	if (mySerial.available()) {		// Use extSerial for available().
		aChar = mySerial.read();	// And read().
		Serial.print(aChar);		// Original calls for output.
	}
}
```

 NOTE: DO NOT USE delay() IN YOUR CODE! THIS WILL STOP EVERYTHING. BUT, NO FEAR! WE
 SUPPLY YOU WITH A sleep() call that acts just like delay for you, but does NOT stop
 everything. Try it, you'll love it! 

 Remember : When people demand code without using delay(), because it causes blocking,
 our sleep() call does NOT cause blocking. What a hack!

