#include <reg51.h>
#include <string.h>

#define LCD P2 /* Attached Lcd on Port */
sbit rs = P3^5; /* Configure RS Pin */
sbit rw = P3^6; /* Configure R/W pin */
sbit e = P3^7; /* Configure Enable pin */

sbit R1 = P1^0;     // Connecting keypad to Port 1
sbit R2 = P1^1;
sbit R3 = P1^2;
sbit R4 = P1^3;
sbit C1 = P1^4;
sbit C2 = P1^5;
sbit C3 = P1^6;
/* Function to send a string through UART */
void UART_SendString(const char *str) {
    while (*str != '\0') {
        SBUF = *str;     // Load data into the serial buffer
        while (TI == 0); // Wait until TX buffer is empty
        TI = 0;          // Clear transmit interrupt flag
        str++;
    }
}


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

/* Function to initialize UART */
void UART_Init() {
    TMOD = 0x20; // Timer 1 in mode 2, 8-bit auto-reload
    TH1 = 0xFD;  // Baud rate = 9600 bps (for 11.0592 MHz crystal)
    SCON = 0x50; // 8-bit UART, enable reception
    TR1 = 1;     // Start timer
}

/* Function to send a character through UART */
void UART_SendChar(char c) {
    SBUF = c;
    while (TI == 0); // Wait until TX buffer is empty
    TI = 0;          // Clear transmit interrupt flag
}


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
		UART_Init(); // Initialize UART
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

/* Function to Display message on Lcd and PC */
void DisplayMessage(const char *pszMessage) {
    while (*pszMessage != '\0') {
        rs = 1;
        rw = 0;
        e = 1;
        LCD = *pszMessage;
        msdelay(1);
        e = 0;

        // Send the character to PC through UART
        UART_SendChar(*pszMessage);

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

	C1=C2=C3=1;

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
	return key;
}

/* Function to move message on LCD */
void MoveMessage(const char *pszMessage)
{
    
        lcd_cmd(0x18); /* Shift Display Left */
        msdelay(30);       /* Adjust the delay as needed */

}

int row_finder1() //Function for finding the row for column 1

{

R1=R2=R3=R4=1;

C1=C2=C3=0;


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

C1=C2=C3=0;


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

C1=C2=C3=0;


if(R1==0)
return 3;

if(R2==0)

return 6;

if(R3==0)

return 9;

if(R4==0)

return 14;

}
