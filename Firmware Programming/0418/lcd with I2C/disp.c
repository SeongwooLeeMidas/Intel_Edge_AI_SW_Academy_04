/*
 * disp.c
 *
 *  Created on: Apr 18, 2024
 *      Author: IOT
 */
#include <stdio.h>
#include <stdarg.h>
#include "disp.h"
#include "cmsis_os.h"
#include "i2c_HD44780.h"

// debug mode, -DEBUG
#ifdef EBUG
#define FNAME() printf("\n%s (%s, line %d)\n", __func__, __FILE__, __LINE__)

// do-while은 optimize도 안되고 항상 실행됨
#define DBG(...) \
do { \
	printf("%s (%s, line %d): ", __func__, __FILE__, __LINE__); \
    printf(__VA_ARGS__); \
    printf("\n");  \
} while (0)
#else
    #define FNAME()  do{}while(0)
    #define DBG(...) do{}while(0)
#endif //EBUG



static osMutexId_t disp_mutex;

static const osMutexAttr_t disp_mutex_attr = {
	"Disp Mutex",
	osMutexPrioInherit,    // attr_bits
	NULL,                  // memory for control block
	0U                     // size for control block
};


#define disp_mutex_acq() {	osMutexAcquire(disp_mutex, osWaitForever);	}
#define disp_mutex_rls() {	osMutexRelease(disp_mutex);	}


void disp_init(void){

	disp_mutex = osMutexNew(&disp_mutex_attr);
	if(disp_mutex != NULL)
		printf("Mutex created");
	else {
		printf("Mutex created fail");
	}

	lcd_init();
}

void disp_on(void)
{
	disp_mutex_acq();
	lcd_disp_on();
	disp_mutex_rls();
}


void disp_off(void)
{
	disp_mutex_acq();
	lcd_disp_off();
	disp_mutex_rls();
}


void disp_home(void)
{
	disp_mutex_acq();
	lcd_home();
	disp_mutex_rls();
}


void disp_clear_display(void)
{
	disp_mutex_acq();
	lcd_clear_display();
	disp_mutex_rls();
}


void disp_locate(uint8_t row, uint8_t column)
{
	disp_mutex_acq();
	lcd_locate(row, column);
	disp_mutex_rls();
}


void disp_printchar(unsigned char ascode)
{
	disp_mutex_acq();
	lcd_printchar(ascode);
	disp_mutex_rls();
}


void disp_print_string (char *str)
{
	disp_mutex_acq();
	lcd_print_string(str);
	disp_mutex_rls();
}

void disp_printf(const char *fmt, ...)
{
  uint32_t i;
  uint32_t text_size, letter;
  static char text_buffer[32];
  va_list args;

  va_start(args, fmt);
  text_size = vsprintf(text_buffer, fmt, args);

  // Process the string
  for (i = 0; i < text_size; i++)
  {
    letter = text_buffer[i];

    if (letter == 10)
      break;
    else
    {
      if ((letter > 0x1F) && (letter < 0x80))
        lcd_printchar(letter);
    }
  }
}


