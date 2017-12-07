/*! @file
 * Oled driver file.
 */
#include "general_header.h"
#include "fonts.h"
#include <avr/pgmspace.h>
#include "oled_driver.h"
#include "eeprom.h"
#include <stdlib.h>
#include <string.h>

#define MAX_PAGES 7
#define MAX_COLUMS 127
#define MAX_OLED_COL 60
//#define EEPROM_BRIGHTNESS_ADR 0x70
volatile char *oled_control = (char *) 0x1000; // Start address for the OLED
volatile char *sram_data = (char *) 0x1800; // Start address for SRAM memory
volatile char *oled_data = (char *) 0x1200; // Start address for the OLED data
const char *buffer_range_error = "(!) ERROR: SRAM buffer out of range \r";

uint8_t LINE_POS = 0;
uint8_t COL_POS = 0;

/*!
 * \brief Write to controll register function
 * @param val Value
 */
void write_c(uint8_t val){
	*oled_control = val;	
}

/*!
 * \brief Write to data register function
 * @param data Data
 */
void write_d(uint8_t data){
	*oled_data = data;
}

/*!
 * \brief Initialize Oled.
 */
uint8_t oled_init(void)
{
	write_c(0xae);        //  display  off
	write_c(0xa1);        //segment  remap
	write_c(0xda);        //common  pads  hardware:  alternative
	write_c(0x12);
	write_c(0xc8);        //common output scan direction:com63~com0
	write_c(0xa8);        //multiplex  ration  mode:63
	write_c(0x3f);
	write_c(0xd5);        //display divide ratio/osc. freq. mode
	write_c(0x80);
	write_c(0x81);        //contrast  control
	write_c(0x50);
	write_c(0xd9);        //set  pre-charge  period
	write_c(0x21);
	write_c(0x20);        //Set  Memory  Addressing  Mode
	write_c(0x02);		  //Page mode
	write_c(0xdb);        //VCOM  deselect  level  mode
	write_c(0x30);
	write_c(0xad);        //master  configuration
	write_c(0x00);
	write_c(0xa4);        //out  follows  RAM  content
	write_c(0xa6);        //set  normal  display
	write_c(0xaf);        //  display  on
	return 0;
}

/*!
 * \brief Set cursor on oled screen. To be used with dual-buffer setup.
 * @param line Line (from 0 to MAX_PAGES on screen).
 * @param col  Column (from 0 to MAX_COLUMS )
 */
void set_cursor(int line, int col){
	if (line >= 0 && line <= MAX_PAGES && col >= 0 && col < MAX_COLUMS){  
		//oled_page_select(line);
		//oled_col_start_end(col, MAX_COLUMS);
		LINE_POS = line;
		COL_POS = col;
	}
}

/*!
 * \brief Print small letters to SRAM buffer.
 * @param ch Character
 * @param file File format spesific for FDEV_SETUP_STREAM
 */
int oled_print_small_b(char ch, FILE* file){
	return oled_print_char_small_buffer(ch, LINE_POS,COL_POS);
}

/*!
 * \brief Print medium letters to SRAM buffer.
 * @param ch Character
 * @param file File format spesific for FDEV_SETUP_STREAM
 */
int oled_print_medium_b(char ch, FILE* file){
	return oled_print_char_medium_buffer(ch, LINE_POS,COL_POS);
}

/*!
 * \brief Print large letters to SRAM buffer.
 * @param ch Character
 * @param file File format spesific for FDEV_SETUP_STREAM
 */
int oled_print_large_b(char ch, FILE* file){
	return oled_print_char_large_buffer(ch, LINE_POS,COL_POS);
}

int oled_print_char_small_buffer(char chr, int line, int col_start){
	if(line < 0 || line > MAX_PAGES || col_start < 0 || (col_start+4) > MAX_COLUMS){
		printf(buffer_range_error);
		return 1;
	}
	for (int i = 0; i < 4; i++)
	{
		sram_data[(MAX_COLUMS+1)*line + col_start+i] = pgm_read_byte(&font4[chr - 32][i]);
		COL_POS++;
	}
	//COL_POS++;
	return 0;
}

int oled_print_char_medium_buffer(char chr, int line, int col_start){
	if(line < 0 || line > MAX_PAGES || col_start < 0 || (col_start+5) > MAX_COLUMS){
		printf(buffer_range_error);
		return 1;
	}
	for (int i = 0; i < 5; i++)
	{
		sram_data[(MAX_COLUMS+1)*line + col_start+i] = pgm_read_byte(&font5[chr - 32][i]);
		COL_POS++;
	}
	COL_POS++; //NOT SUPPOSED TO BE HERE; TEST PURPOSES
	return 0;
}

int oled_print_char_large_buffer(char chr, int line, int col_start){
	if(line < 0 || line > MAX_PAGES || col_start < 0 || (col_start+8) > MAX_COLUMS){
		printf(buffer_range_error);
		return 1;
	}
	for (int i = 0; i < 8; i++)
	{
		sram_data[(MAX_COLUMS+1)*line + col_start+i] = pgm_read_byte(&font8[chr - 32][i]);
		COL_POS++;
	}
	return 0;
}

int oled_update_buffer(void){
	oled_col_start_end(0,MAX_COLUMS); // set start point
	for (int page = 0; page <= MAX_PAGES; page++)
	{
		oled_page_select(page);
		for (int col = 0; col <= MAX_COLUMS; col++)
		{
			write_d(sram_data[(1+MAX_COLUMS)*page + col]);
		}
	}
}

//--------------------------Functions for single buffer -----------------------
// int oled_print_small(char chr,FILE* file) {
// 	for (int i = 0; i < 4; i++)
// 	{
// 		write_d(pgm_read_byte(&font4[chr - 32][i]));
// 	}
// 	return 0;
// }
// int oled_print_medium(char chr, FILE* file) {
// 	for (int i = 0; i < 5; i++)
// 	{
// 		write_d(pgm_read_byte(&font5[chr - 32][i]));
// 	}
// 	return 0;
// }
// int oled_print_large(char chr,FILE* file) {
// 	for (int i = 0; i < 8; i++)
// 	{
// 		write_d(pgm_read_byte(&font8[chr - 32][i]));
// 	}
// 	return 0;
// }
void oled_page_select(int page){ // Should be changed to just an input page only.
	write_c(0xb0 + page);
}
void oled_col_start_end(int start, int end){
	write_c(0x21);
	write_c(start);
	write_c(end);
}
// int oled_home(void) {
// 	//Set the cursor to the start of the screen
// 	oled_page_select(0);
// 	oled_col_start_end(0, MAX_COLUMS);
// 	return 0;
// }
//------------------------------------------------------------------------------

void oled_clear_line(int line){
	char space = ' ';
	for (int col = 0; col < 16; col++){
		for (int i = 0; i < 8; i++){
			sram_data[(MAX_COLUMS+1)*line + 8*col + i] = pgm_read_byte(&font8[space - 32][i]);
		}
	}
	oled_update_buffer();
}

void oled_reset_screen(void){
	for (int i = 0; i <= MAX_PAGES; i++){
		oled_clear_line(i);}
	}
	
void oled_fill_screen(void){
	for (int page = 0; page <= MAX_PAGES; page++){ 
		oled_page_select(page);
		oled_col_start_end(0,127);
		for (int i = 0; i< 128; i++){
			write_d(0xFFFF);
		}
	}
}

// void oled_print_arrow(uint8_t line){
// 	char* a = "->";
// 	for (int chr = 0; a[chr] != '\0'; chr++){
// 		oled_print_char_small_buffer(&a[chr],1,chr*4);
// 	}
// 	oled_update_buffer();
// }

// bool oled_draw_circle_buffer(int line, int col_start, int radius){
// 	int circle;
// 	if (radius < 8) {
// 		circle = radius - 1;
// 		} else {
// 		return false;
// 	}
// 	
// 	if(line < 0 || line > MAX_PAGES || col_start < 0 || (col_start+32) > MAX_COLUMS){
// 		printf(buffer_range_error);
// 		return false;
// 	}
// 	for (int i = 0; i < 16; i++)
// 	{	
// 		sram_data[(MAX_COLUMS)*line + col_start+i] = pgm_read_byte(&circles[circle][i]);
// 	}
//    	for (int i = 16; i < 32; i++)
//    	{
//   		 sram_data[(MAX_COLUMS)*(line+1) + col_start+i-12-line] = pgm_read_byte(&circles[circle][i]);
//    	}
// 	
// 	return true;
// }

// void oled_draw_face(){
// 		oled_draw_circle_buffer(2,50,4);
// 		oled_draw_circle_buffer(2,70,4);
// 		oled_draw_circle_buffer(3,62,3);
// 		oled_draw_circle_buffer(4,55,2);
// 		oled_draw_circle_buffer(4,55,2);
// 		oled_draw_circle_buffer(4,60,2);
// 		oled_draw_circle_buffer(4,65,2);
// 		oled_draw_circle_buffer(4,70,2);
// 		oled_draw_circle_buffer(4,75,2);
// }

// void oled_draw_picture(){
// 	for (int i = 0; i < 1030; i++)
// 	{
// 		write_d(pgm_read_byte(&pingpong[i]));
// 	}
// }

// int oled_draw_man(void){
// 	oled_home();
// 	bool walking = true;
// 	for (int j = 0; j < 8; j++) {
// 		for(int i = 0; i < 24; i++) {
// 			sram_data[j*128 + i] =pgm_read_byte(&man[j][i]);
// 		}
// 	}
// 	oled_update_buffer();
// 	return 0;
// }

void oled_adjust_brightness(uint8_t level){
	write_c(0x81);
	write_c(level);
}

int oled_set_last_brightness(void){
	uint8_t last_value = EEPROM_read(EEPROM_BRIGHTNESS_ADR);
	oled_adjust_brightness(last_value);
	
	return 0;	 
}


