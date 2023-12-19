#include <reg51.h>
#include <string.h>

#define LCD P2 /* Attached Lcd on Port */
sbit rs = P3^0; /* Configure RS Pin */
sbit rw = P3^1; /* Configure R/W pin */
sbit e = P3^2; /* Configure Enable pin */

sbit C4 = P1^0;     // Connecting keypad to Port 1
sbit C3 = P1^1;
sbit C2 = P1^2;
sbit C1 = P1^3;
sbit R4 = P1^4;
sbit R1 = P1^5;
sbit R2 = P1^6;
sbit R3 = P1^7;


/* Function to write command on Lcd */
void lcd_cmd(const char cCommand);

/* Function to display message on Lcd */
void DisplayMessage(const char *pszMessage);

/* Function To Initialize Lcd */
void LcdInit(void);

/* Function to Provide delay */
void msdelay(unsigned int);

/* Function to read keypad */
int ReadKey(void);

int row_finder1();
int row_finder2();
int row_finder3(); 
int row_finder4();

/* Function to move message on LCD */
void MoveMessage(const char *pszMessage);



int main()
{
    short siLoop = 0;
    short siLen = 0;
    int key;
    const char *pszMessages[9] = {
        "Message 1",
        "Message 2",
        "Message 3",
        "Message 4",
        "Message 5",
        "Message 6",
        "Message 7",
        "Message 8",
        "Message 9"};

    LcdInit(); /* Lcd Initialize */

    while (1)
    {
        key = ReadKey(); /* Read key from keypad */

        if (key >= 1 && key <= 9)
					
					
        {
					int count1;
					const char *message =pszMessages[key - 1];
					for(count1 = 0; message[count1] != '\0'; count1++) 
    {
								char character = message[count1]; // Access each character in the message
                DisplayMessage(&character);       // Display each character    
								msdelay(30);
    }
		for(count1 = 0; message[count1] != '\0'; count1++) 
    {
								char character = message[count1]; // Access each character in the message
                MoveMessage(&character);       // Display each character    
								msdelay(30);
    }
		
		
        }
    }
}

/* Function to write command on Lcd */
void lcd_cmd(const char cCommand)
{
    rs = 0;
    rw = 0;
    e = 1;
    LCD = cCommand;
    msdelay(1);
    e = 0;
}

/* Function to Display message on Lcd */
void DisplayMessage(const char *pszMessage)
{
    
    while (*pszMessage != '\0')
    {		rs = 1;
				rw = 0;
        e = 1;
        LCD = *pszMessage;
        msdelay(1);
        e = 0;
        pszMessage++;
    }
}

void msdelay(unsigned int time)  // Function for creating delay in milliseconds.

{
    unsigned i,j ;

    for(i=0;i<time;i++)    

    for(j=0;j<1275;j++);
}

/* Initialise the LCD */
void LcdInit()
{
    /*(0x38);  // for using 2 lines and 5X7 matrix of LCD

    msdelay(10);

    lcd_cmd(0x0F);  // turn display ON, cursor blinking

    msdelay(10);

    lcd_cmd(0x01);  //clear screen

    msdelay(10);

    lcd_cmd(0x81);  // bring cursor to position 1 of line 1

    msdelay(10);*/
		lcd_cmd(0x01);
    lcd_cmd(0x38);
    lcd_cmd(0x06);
    lcd_cmd(0x0c);
}

/* Function to read keypad */
int ReadKey()
{
	int key = 0;

	msdelay(30); 

	C1=C2=C3=C4=1;

	R1=R2=R3=R4=0;

	if(C1==0)
		{
	lcd_cmd(0x01);
	key=row_finder1();
}
	else if(C2==0){
	lcd_cmd(0x01);
	key=row_finder2();
}
	else if(C3==0){
	lcd_cmd(0x01);
	key=row_finder3();
}
	else if(C4==0){
	lcd_cmd(0x01);
	key=row_finder4();
	}
	return key;
}

/* Function to move message on LCD */
void MoveMessage(const char *pszMessage)
{
    
        lcd_cmd(0x18); /* Shift Display Left */
        msdelay(30);       /* Adjust the delay as needed */

}
/* Function for serial communication initialization */
/* Function for serial communication initialization 
void SerialInit() {
    // Assuming the microcontroller is operating at a specific frequency (e.g., 11.0592 MHz)
    // Configure the serial communication parameters

    // Set the baud rate to 9600 (assuming 11.0592 MHz crystal frequency)
    // Formula: Baud rate = Crystal frequency / (12 * (256 - TH1))
    // For 9600 baud rate: TH1 = 256 - (Crystal frequency / (12 * 32 * Baud rate))
    // For 11.0592 MHz and 9600 baud rate:
    TH1 = 0xFD; // Load TH1 with 0xFD (253 in decimal)

    // Configure serial mode
    // For 8-bitdata, 1 stopbit, no parity
    TMOD |= 0x20; // Timer1 in Mode 2 (8-bitauto-reload mode)
    SCON = 0x50; // SCON: serial mode 1, 8-bitdata, REN=1 (Enable Receiver)

    // Enable serialinterrupt (if needed)
    // ES = 1; // Uncomment this line ifusing interrupts

    // Start timer
    TR1 = 1; // Start Timer 1 for baud rate generation

    // Additional configuration if needed:
    // - Enable transmit and/or receiveinterrupt
    // - Set UART mode (UART0, UART1, etc.) if available
    // - Enable FIFO (if supported)
    // - Configure pin I/O settings (TX, RX pins)

    // Your hardware-specific configurations may vary
}

/* Function for serial communication
void SerialTransmit(chardata)
{
    SBUF=\data; // Loaddata into serial buffer
    while (!TI); // Wait until transmission is complete
    TI = 0; // Clear the transmit \interrupt flag (TI) for next transmission
    // Optionally, add delay or error handling here
}

*/
int row_finder1() //Function for finding the row for column 1

{

R1=R2=R3=R4=1;

C1=C2=C3=C4=0;


if(R1==0)

return 1;

if(R2==0)

return 4;

if(R3==0)

return 7;

if(R4==0)

return 15;

}


int row_finder2() //Function for finding the row for column 2

{

R1=R2=R3=R4=1;

C1=C2=C3=C4=0;


if(R1==0)

return 2;
if(R2==0)

return 5;

if(R3==0)

return 8;

if(R4==0)

return 0;

}


int row_finder3() //Function for finding the row for column 3

{

R1=R2=R3=R4=1;

C1=C2=C3=C4=0;


if(R1==0)
return 3;

if(R2==0)

return 6;

if(R3==0)

return 9;

if(R4==0)

return 14;

}


int row_finder4() //Function for finding the row for column 4

{

R1=R2=R3=R4=1;

C1=C2=C3=C4=0;


if(R1==0)

return 10;

if(R2==0)

return 11;

if(R3==0)

return 12;

if(R4==0)

return 13;

}
