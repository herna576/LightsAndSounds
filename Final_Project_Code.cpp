    #include "mbed.h"
     
    AnalogIn leftChannel(A0); // left channel  
    AnalogIn rightChannel(A1); // right channel   

	BusOut LeftLED(D2, D3, D4);	
	BusOut RightLED(D5, D6, D7);
	
	Serial myPC(D1,D0);
	
	//Clear Screen
	void clrscr()
	{
		char clrscr[] = {0x1B, '[', '2', 'J', 0};
		myPC.printf(clrscr);
	}

	//Home Cursor
	void homescr()
	{
		char homescr[] = {0x1B, '[', 'H', 0};
		myPC.printf(homescr);
	}

    int main() 
	{
     
		float leftChannelSignal;
		float rightChannelSignal;
		float lowCutoff = 10;
		float mediumCutoff = 1000;
		float highCutoff = 2000;
		
		myPC.baud(9600);
		clrscr();
		homescr();
		
		myPC.printf("\n\rTurn Sound Into Light");
     
		while(1) 
		{
			leftChannelSignal = leftChannel.read(); // Converts and read the analog input value (value from 0.0 to 1.0)     
			rightChannelSignal = rightChannel.read(); // Converts and read the analog input value (value from 0.0 to 1.0)
     
			leftChannelSignal = leftChannelSignal * 3300; // Change the value to be in the 0 to 3300 range    
			rightChannelSignal = rightChannelSignal * 3300; // Change the value to be in the 0 to 3300 range
     
			myPC.printf("\n\rL Channel = %.0f mVn", leftChannelSignal);     
			myPC.printf("\n\rR Channel = %.0f mVn", rightChannelSignal);
     
			//LEFT CHANNEL     
			if (leftChannelSignal <= lowCutoff) 
			{ 				
				LeftLED = 0x000;
			}
			else if(leftChannelSignal <= mediumCutoff) 
			{ 				
				LeftLED = 0x001;
			}
			else if(leftChannelSignal <= highCutoff) 
			{ 
				LeftLED = 0x011;
			}
			else 
			{	
				LeftLED = 0x111;
			}
     
			//RIGHT CHANNEL     
			if (rightChannelSignal <= lowCutoff) 
			{ 
				RightLED = 0x000;
			}              
			else if(rightChannelSignal <= mediumCutoff) 
			{      
				RightLED = 0x001;
			}		              
			else if(rightChannelSignal <= highCutoff)
			{ 
				RightLED = 0x011;
			}
			else 
			{
				RightLED = 0x111;
			} 
			wait(0.2); // 200 ms
		}
    }