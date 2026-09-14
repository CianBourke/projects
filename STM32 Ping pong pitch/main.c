#include <stm32f031x6.h>
#include "display.h"
#include "sound.h"
#include "musical_notes.h"


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 160

void initClock(void);
void initSysTick(void);
void SysTick_Handler(void);
void delay(volatile uint32_t dly);
void setupIO();
int isInside(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint16_t px, uint16_t py);
void enablePullUp(GPIO_TypeDef *Port, uint32_t BitNumber);
void pinMode(GPIO_TypeDef *Port, uint32_t BitNumber, uint32_t Mode);

void displayMenu() //code added to display menu(piano room)
{
    fillRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, RGBToWord(0, 0, 0)); // Clear screen
    printTextX2("Welcome to", 6, 10, RGBToWord(255, 255, 255), 0); // Display title
    printTextX2("PING PONG", 12, 30, RGBToWord(255, 0, 0), 0); // Instructions
	printTextX2("PITCH!", 33, 50, RGBToWord(255, 0, 0), 0); // Instructions
    printText("Press any button", 8, 80, RGBToWord(255, 255, 255), 0); // Instructions
	printText("to start!", 35, 92, RGBToWord(255, 255, 255), 0); // Instructions
}

int isStartButtonPressed()
{
    if (((GPIOB->IDR & (1 << 4)) == 0) || 
        ((GPIOB->IDR & (1 << 5)) == 0) || 
        ((GPIOA->IDR & (1 << 8)) == 0) || 
        ((GPIOA->IDR & (1 << 11)) == 0)) 
    { 
        // Any button pressed (Piano room)
        return 1;
    }
    return 0;
}

uint32_t my_tune_notes[]={E4, D4, FS4_Gb4, G4, C5, B4, D4, C5, B4, A4};
uint32_t my_tune_times[]={400, 200, 400, 200, 400, 200, 400, 200, 400, 800};

void playTune()
{
    int count = sizeof(my_tune_notes) / sizeof(my_tune_notes[0]);
    int index = 0;
    const uint32_t bpm = 180;
    const uint32_t beat_duration_ms = 60000 / bpm;

    while(index < count)
    {
        playNote(my_tune_notes[index]);
        delay(my_tune_times[index] * beat_duration_ms / 400);
        playNote(0);
        delay(100);  // Reduced delay to make it faster
        index++;
    }
}

void clearScreen()
{
    fillRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, RGBToWord(1, 82, 9)); // Set background to green
}

void drawWhiteLine(void)
{
    // Draw a white line in the middle of the screen
    fillRectangle(0, 80, 128, 2, RGBToWord(255, 255, 255)); // White line in the middle of the green background
}

void drawWhiteCircle(void)
{
    int x = 64, y = 81;  // Center of the circle
    int radius = 17;      // Slightly larger radius
    int thickness = 2;    // Thickness of the circle (number of concentric circles)

    // Draw multiple concentric circles to create a thicker effect
    for (int i = 0; i < thickness; i++)
    {
        drawCircle(x, y, radius + i, RGBToWord(255, 255, 255));
    }
}

void drawGoals(void) {
    // Draw a 1-pixel thin white line at the top edge of the screen
    fillRectangle(0, 0, SCREEN_WIDTH, 2, RGBToWord(255, 255, 255));  // Top edge

    // Draw a 1-pixel thin white line at the bottom edge of the screen
    fillRectangle(0, SCREEN_HEIGHT - 2, SCREEN_WIDTH, 2, RGBToWord(255, 255, 255));  // Bottom edge

    // Top-left corner line (vertical line, 2 pixels wide, 10 pixels long)
    fillRectangle(0, 0, 2, 10, RGBToWord(255, 255, 255));  // Top-left corner

    // Top-right corner line (vertical line, 2 pixels wide, 10 pixels long)
    fillRectangle(SCREEN_WIDTH - 2, 0, 2, 10, RGBToWord(255, 255, 255));  // Top-right corner

    // Bottom-left corner line (vertical line, 2 pixels wide, 10 pixels long)
    fillRectangle(0, SCREEN_HEIGHT - 10, 2, 10, RGBToWord(255, 255, 255));  // Bottom-left corner

    // Bottom-right corner line (vertical line, 2 pixels wide, 10 pixels long)
    fillRectangle(SCREEN_WIDTH - 2, SCREEN_HEIGHT - 10, 2, 10, RGBToWord(255, 255, 255));  // Bottom-right corner



    int topStartY = 3;  // 3 pixels from the top
    int bottomStartY = SCREEN_HEIGHT - 3;  // 3 pixels from the bottom
    int lineWidth = 1;  // Width of the lines
    int lineGap = 1;    // Gap between each line
    //int stopDistance = 10;  // 10 pixels from the top/bottom to stop drawing lines

    // Draw 4 horizontal lines near the top
    for (int i = 0; i < 4; i++) {
        int y = topStartY + (i * (lineWidth + lineGap));  // Calculate the Y position for each line
        fillRectangle(0, y, SCREEN_WIDTH, lineWidth, RGBToWord(255, 255, 255));  // Full width of screen
    }

    // Draw 4 horizontal lines near the bottom
    for (int i = 0; i < 4; i++) {
        int y = bottomStartY - (i * (lineWidth + lineGap));  // Calculate the Y position for each line
        fillRectangle(0, y, SCREEN_WIDTH, lineWidth, RGBToWord(255, 255, 255));  // Full width of screen
    }

    int topPadding = 10;  // 10 pixels from the top
    int bottomPadding = 10;  // 10 pixels from the bottom
    int gap = 1;  // Gap between each vertical line
    int yStart = 0;  // Start drawing from the top
    int yEnd = topPadding;  // Stop drawing at the top padding (10 pixels from the top)

    // Calculate the number of vertical lines
    int availableWidth = SCREEN_WIDTH - (2 * lineWidth);  // Total width minus the line width
    int numLines = availableWidth / (lineWidth + gap);  // Calculate the number of vertical lines we can fit

    // Draw vertical lines from top to bottom with a 1px gap
    for (int i = 0; i < numLines; i++) {
        int xPos = i * (lineWidth + gap);  // Position of the current vertical line
        
        // Draw the vertical line from yStart to yEnd (starting from top and stopping 10 pixels from the top)
        fillRectangle(xPos, yStart, lineWidth, yEnd - yStart, RGBToWord(255, 255, 255));  // White vertical line
    }

    
    int yStartTop = 0;  // Start drawing from the top
    int yEndTop = topPadding;  // Stop drawing at the top padding (10 pixels from the top)
    int yStartBottom = SCREEN_HEIGHT - bottomPadding;  // Start drawing from the bottom padding
    int yEndBottom = SCREEN_HEIGHT;  // End at the very bottom of the screen

    // Calculate the number of vertical lines for the top and bottom parts

    // Draw vertical lines from top to bottom (stopping at topPadding)
    for (int i = 0; i < numLines; i++) {
        int xPos = i * (lineWidth + gap);  // Position of the current vertical line
        
        // Draw the vertical line from yStartTop to yEndTop (from top to top padding)
        fillRectangle(xPos, yStartTop, lineWidth, yEndTop - yStartTop, RGBToWord(255, 255, 255));  // White vertical line
        
        // Draw the vertical line from yStartBottom to yEndBottom (from bottom to bottom padding)
        fillRectangle(xPos, yStartBottom, lineWidth, yEndBottom - yStartBottom, RGBToWord(255, 255, 255));  // White vertical line
    }
}

// Added in lab
volatile uint32_t milliseconds;

const uint16_t antony[]=
{
	16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,24327,65535,24327,24327,24327,24327,24327,16394,16394,47651,47651,47651,16394,40224,65535,65535,24327,65535,24327,24327,24327,24327,24327,22355,22355,22355,22355,47651,16394,40224,65535,65535,24327,65535,24327,24327,24327,24327,24327,22355,22355,22355,22355,26649,16394,40224,16394,16394,24327,65535,24327,24327,22355,24327,22355,22355,22355,0,22355,26649,16394,40224,16394,16394,16394,16394,16394,16394,22355,16394,22355,16394,22355,22355,22355,26649,16394,16394,16394,16394,16394,16394,16394,16394,22355,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,
};
const uint16_t nunez[]=
{
	16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,40375,16394,16394,16394,16394,16394,16394,16394,16394,26649,40375,40375,40375,16394,40375,16394,40375,16394,16394,16394,16394,16394,16394,13474,16394,26649,40375,0,40375,40375,40375,40224,40375,40224,40224,65535,40224,16394,16394,13474,16394,26649,40375,40375,40375,40375,40224,40224,40224,40224,40224,65535,40224,65535,65535,13474,16394,26649,40375,40375,40375,40375,40224,40224,40224,40224,40224,65535,40224,65535,65535,13474,16394,26649,26649,26649,26649,16394,40224,40224,40224,40224,40224,65535,40224,16394,16394,16394,16394,16394,26649,26649,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,16394,
};
int antony_score= 0;
int nunez_score= 0;
int target_score = 3;

uint16_t ball_x = SCREEN_WIDTH / 2;
uint16_t ball_y = SCREEN_HEIGHT / 2;
int ball_dx = 2, ball_dy = 2;

uint16_t xa = 50, ya = 10;  // Antony initial position
uint16_t xn = 50, yn = 130; // Nunez initial position


void moveBall()
{
    // Erase old ball position
    fillRectangle(ball_x, ball_y, 5, 5, RGBToWord(1, 82, 9));

    // Update position
    ball_x += ball_dx;
    ball_y += ball_dy;

    // Bounce off walls
    if (ball_x <= 0 || ball_x >= SCREEN_WIDTH - 5) {
        ball_dx = -ball_dx;
    }
    if (ball_y <= 0 || ball_y >= SCREEN_HEIGHT - 5) {
        ball_dy = -ball_dy;
    }

    // Bounce off Antony (top paddle)
    if (isInside(xa, ya, 16, 16, ball_x, ball_y)) {
        ball_dy = 2;  // You can also adjust this if needed
    }

    // Bounce off Nunez (bottom paddle)
    if (isInside(xn, yn, 16, 16, ball_x, ball_y)) {
        ball_dy = -2;  // You can also adjust this if needed
    }

    // Make ball move faster by increasing the speed
    ball_dx *= 1.49;  // Increase horizontal speed  (1.4 before)
    ball_dy *= 1.49;  // Increase vertical speed 
    // Draw ball at new position
    fillRectangle(ball_x, ball_y, 5, 5, RGBToWord(255, 255, 255));
}

int main()
{
    int hn_moved = 0, vn_moved = 0, ha_moved = 0, va_moved = 0;
    int hn_inverted = 0, vn_inverted = 0, ha_inverted = 0, va_inverted = 0;

    uint16_t oldxn = xn, oldyn = yn;
    uint16_t oldxa = xa, oldya = ya;

    initClock();
    initSysTick();
    setupIO();
	initSound();
	

    displayMenu(); // Display the menu

    while (!isStartButtonPressed()) {
        delay(50);
    }

    clearScreen();
  

    putImage(xn, yn, 16, 16, nunez, 0, 0);
    putImage(xa, ya, 16, 16, antony, 0, 0);

    while (1)
    {
		displayScore();
		drawWhiteLine();
		drawWhiteCircle();
		drawGoals();

        hn_moved = vn_moved = ha_moved = va_moved = 0;
        hn_inverted = vn_inverted = ha_inverted = va_inverted = 0;

        // --- Movement for Nunez (with screen boundaries) ---
        if ((GPIOB->IDR & (1 << 4)) == 0) { // right1 (Nunez)
            if (xn < 110) { xn += 4; hn_moved = 1; hn_inverted = 0; }
        }
        if ((GPIOB->IDR & (1 << 5)) == 0) { // left1 (Nunez)
            if (xn > 3) { xn -= 4; hn_moved = 1; hn_inverted = 1; }
        }

        // --- Movement for Antony (with screen boundaries) ---
        if ((GPIOA->IDR & (1 << 8)) == 0) { // Move right (Antony)
            if (xa < 110) { xa += 4; ha_moved = 1; ha_inverted = 1; } // Correct direction
        }
        if ((GPIOA->IDR & (1 << 11)) == 0) { // Move left (Antony)
            if (xa > 3) { xa -= 4; ha_moved = 1; ha_inverted = 0; } // Correct direction
        }

        // --- Redraw only when necessary ---
        if (hn_moved) {
            fillRectangle(oldxn, oldyn, 16, 16, RGBToWord(1, 82, 9)); // Clear old Nunez position
            putImage(xn, yn, 16, 16, nunez, hn_inverted, 0); // Draw Nunez at new position
            oldxn = xn; oldyn = yn;
        }
        if (ha_moved) {
            fillRectangle(oldxa, oldya, 16, 16, RGBToWord(1, 82, 9)); // Clear old Antony position
            putImage(xa, ya, 16, 16, antony, ha_inverted, 0); // Draw Antony at new position
            oldxa = xa; oldya = ya;
        }

        // Check ball boundaries for scoring and reset ball position
        if (ball_y <= 0) {  // If the ball reaches the top, Nunez scores
            nunez_score++;   // Increment Nunez's score
            displayScore();   // Display updated score
			//playTune(my_tune_notes,my_tune_times, sizeof(my_tune_notes) / sizeof(my_tune_notes[0]));
			red_on();
            resetGame();      // Reset game (restarts after a score)
        } 
        else if (ball_y >= SCREEN_HEIGHT - 5) {  // If the ball reaches the bottom, Antony scores
            antony_score++;   // Increment Antony's score
            displayScore();   // Display updated score
			red_on();
            resetGame();      // Reset game (restarts after a score)
			//playTune(my_tune_notes,my_tune_times, sizeof(my_tune_notes) / sizeof(my_tune_notes[0]));
        }
		if (nunez_score >= target_score) {
			fillRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, RGBToWord(0, 0, 0)); // Clear screen
			printTextX2("Red Wins!", 15, 70, RGBToWord(255, 0, 0), 0); // Display winner
			delay(2000); // Show winner message for 2 seconds
			nunez_score = 0; // Reset scores
			antony_score = 0;
			displayMenu(); // Display the menu

            while (!isStartButtonPressed()) {
                delay(50);
            } // Resete the gam
            resetGame();
		} 
		else if (antony_score >= target_score) {
			fillRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, RGBToWord(0, 0, 0)); // Clear screen
			printTextX2("Yellow", 30, 60, RGBToWord(255, 255, 0), 0); // Display winner
            printTextX2("Wins!", 40, 80, RGBToWord(255, 255, 0), 0); // Display winner
			delay(2000); // Show winner message for 2 seconds
			nunez_score = 0; // Reset scores
			antony_score = 0;
			displayMenu(); // Display the menu

            while (!isStartButtonPressed()) {
                delay(50);
            }
            resetGame();
		}

        // Move the ball and update screen
        moveBall();
        delay(50); // Small delay for smoother movement
    }
    return 0;
}

void initSysTick(void)
{
	SysTick->LOAD = 48000;
	SysTick->CTRL = 7;
	SysTick->VAL = 10;
	__asm(" cpsie i "); // enable interrupts
}

void SysTick_Handler(void)
{
	milliseconds++;
}

void initClock(void)
{
// This is potentially a dangerous function as it could
// result in a system with an invalid clock signal - result: a stuck system
        // Set the PLL up
        // First ensure PLL is disabled
        RCC->CR &= ~(1u<<24);
        while( (RCC->CR & (1 <<25))); // wait for PLL ready to be cleared
        
// Warning here: if system clock is greater than 24MHz then wait-state(s) need to be
// inserted into Flash memory interface
				
        FLASH->ACR |= (1 << 0);
        FLASH->ACR &=~((1u << 2) | (1u<<1));
        // Turn on FLASH prefetch buffer
        FLASH->ACR |= (1 << 4);
        // set PLL multiplier to 12 (yielding 48MHz)
        RCC->CFGR &= ~((1u<<21) | (1u<<20) | (1u<<19) | (1u<<18));
        RCC->CFGR |= ((1<<21) | (1<<19) ); 

        // Need to limit ADC clock to below 14MHz so will change ADC prescaler to 4
        RCC->CFGR |= (1<<14);

        // and turn the PLL back on again
        RCC->CR |= (1<<24);        
        // set PLL as system clock source 
        RCC->CFGR |= (1<<1);
}

void delay(volatile uint32_t dly)
{
	uint32_t end_time = dly + milliseconds;
	while(milliseconds != end_time)
		__asm(" wfi "); // sleep
}

void enablePullUp(GPIO_TypeDef *Port, uint32_t BitNumber)
{
	Port->PUPDR = Port->PUPDR &~(3u << BitNumber*2); // clear pull-up resistor bits
	Port->PUPDR = Port->PUPDR | (1u << BitNumber*2); // set pull-up bit
}

void pinMode(GPIO_TypeDef *Port, uint32_t BitNumber, uint32_t Mode)
{
	/*
	*/
	uint32_t mode_value = Port->MODER;
	Mode = Mode << (2 * BitNumber);
	mode_value = mode_value & ~(3u << (BitNumber * 2));
	mode_value = mode_value | Mode;
	Port->MODER = mode_value;
}

int isInside(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint16_t px, uint16_t py)
{
	// checks to see if point px,py is within the rectange defined by x,y,w,h
	uint16_t x2,y2;
	x2 = x1+w;
	y2 = y1+h;
	int rvalue = 0;
	if ( (px >= x1) && (px <= x2))
	{
		// ok, x constraint met
		if ( (py >= y1) && (py <= y2))
			rvalue = 1;
	}
	return rvalue;
}

void setupIO()
{
	RCC->AHBENR |= (1 << 18) + (1 << 17); // enable Ports A and B
	display_begin();
	pinMode(GPIOB,4,0);
	pinMode(GPIOB,5,0);
	pinMode(GPIOA,8,0);
	pinMode(GPIOA,11,0);
	pinMode(GPIOB,3,1);
	enablePullUp(GPIOB,4);
	enablePullUp(GPIOB,5);
	enablePullUp(GPIOA,11);
	enablePullUp(GPIOA,8);
}

void displayScore() 
{
    char scoreText[10];
    sprintf(scoreText, "Y:%d", antony_score);
    fillRectangle(5, 5, 100, 10, RGBToWord(1, 82, 9)); // Clear old score
    printText(scoreText, 2, 30, RGBToWord(255, 255, 255), RGBToWord(1, 82, 9)); // Print new score
    sprintf(scoreText, "R:%d", nunez_score);
    fillRectangle(5, 5, 100, 10, RGBToWord(1, 82, 9)); // Clear old score
    printText(scoreText, 2, 90, RGBToWord(255, 255, 255), RGBToWord(1, 82, 9)); // Print new score
}

void resetGame() {
    delay(500); // Brief pause after scoring
    xa = 50; ya = 10;  // Reset Antony's position
    xn = 50; yn = 130; // Reset Nunez's position
    clearScreen();
    drawWhiteLine();
    drawWhiteCircle();
    drawGoals();
    displayScore();
    putImage(xn, yn, 16, 16, nunez, 0, 0); // Draw Nunez's paddle
    putImage(xa, ya, 16, 16, antony, 0, 0); // Draw Antony's paddle
	red_off();
}
void red_on(void)
{
	//set bit 0 of GPIOA without changing
	GPIOB->ODR = GPIOB->ODR | (1 << 3);
}
void red_off(void)
{
	//set bit 0 of GPIOA without changing
	//any other bits
	GPIOB->ODR = GPIOB->ODR & ~ (1 << 3);
}
