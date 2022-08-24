/*
 * tft_screen.c
 *
 *  Created on: 18 de ago de 2022
 *      Author: rinal
 */

#include "tft_screen.h"
#include "../lvgl/lvgl.h"

void update_screen_cb(lv_timer_t * timer);
void print_debug_iron(void);
void print_debug_air(void);
void print_debug_max6675(void);

extern float termocouple;

uint32_t teste_task_screen  = 0;

static lv_obj_t* Tela_Principal;
static lv_obj_t* frame1;
static lv_obj_t* frame2;
static lv_obj_t* txt_header1;
static lv_obj_t* txt_header2;
static lv_obj_t* txt_iron;
static lv_obj_t* txt_air;
static lv_obj_t* txt_pwm_iron;
static lv_obj_t* txt_adc_iron;
static lv_obj_t* txt_pwm_air;
static lv_obj_t* txt_adc_air;
static lv_obj_t* txt_fluxo_air;
static lv_obj_t* txt_temp;
static lv_obj_t* txt_target_air;
static lv_obj_t* txt_target_iron;
static lv_timer_t* update_screen;

 void main_screen(void)
 {
	   Tela_Principal = lv_obj_create(NULL);
	    lv_obj_clear_flag(Tela_Principal, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	    lv_obj_set_style_bg_color(Tela_Principal, lv_color_hex(0x808080), 0);
	    lv_obj_set_style_bg_grad_color(Tela_Principal, lv_color_hex(0x000000), 0);

	    // Frame 1 Temperature Air
	    frame1 = lv_obj_create(Tela_Principal);
	    lv_obj_set_size(frame1, 120, 60);
	    lv_obj_set_style_radius(frame1, 4, 0);
	    lv_obj_set_style_bg_color(frame1, lv_color_hex(0x000000), 0);
	    lv_obj_set_style_bg_grad_color(frame1, lv_color_hex(0x000000), 0);
	    lv_obj_set_style_border_color(frame1, lv_color_hex(0xAAA9AD), 0);
	    lv_obj_set_style_bg_opa(frame1, LV_OPA_50, 0);
	    lv_obj_clear_flag(frame1, LV_OBJ_FLAG_SCROLLABLE);
	    lv_obj_set_pos(frame1, 60, 20);
	    // Header
	    txt_header1 = lv_label_create(Tela_Principal);
	    lv_obj_set_style_text_font(txt_header1, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
	    lv_obj_set_style_text_color(txt_header1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	    lv_obj_set_style_text_opa(txt_header1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	    lv_obj_set_style_text_letter_space(txt_header1, 1, 0);
	    lv_obj_set_style_text_line_space(txt_header1, 1, 0);

	    lv_label_set_long_mode(txt_header1, LV_LABEL_LONG_WRAP);                // Break the long lines
	    lv_label_set_recolor(txt_header1, true);								// Enable re-coloring by commands in the text
	    lv_label_set_text(txt_header1, "AIR");
	    lv_obj_set_pos(txt_header1, 100, 6);

	    txt_air = lv_label_create(frame1);
	    lv_obj_set_style_text_font(txt_air, &lv_7seg_64, LV_PART_MAIN | LV_STATE_DEFAULT);
	    lv_obj_set_style_text_color(txt_air, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	    lv_obj_set_style_text_opa(txt_air, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	    lv_obj_set_style_text_letter_space(txt_air, 1, 0);
	    lv_obj_set_style_text_line_space(txt_air, 1, 0);

	    lv_label_set_long_mode(txt_air, LV_LABEL_LONG_WRAP);                // Break the long lines
	    lv_label_set_recolor(txt_air, true);								// Enable re-coloring by commands in the text
	    lv_label_set_text(txt_air, "125°C");
	    lv_obj_align_to(txt_air, frame1, LV_ALIGN_CENTER, 0, 0);            // Align to center

	    // Frame 2 Temperature Iron
	    frame2 = lv_obj_create(Tela_Principal);
	    lv_obj_set_size(frame2, 120, 60);
	    lv_obj_set_style_radius(frame2, 4, 0);
	    lv_obj_set_style_bg_color(frame2, lv_color_hex(0x000000), 0);
	    lv_obj_set_style_bg_grad_color(frame2, lv_color_hex(0x000000), 0);
	    lv_obj_set_style_border_color(frame2, lv_color_hex(0xAAA9AD), 0);
	    lv_obj_set_style_bg_opa(frame2, LV_OPA_50, 0);
	    lv_obj_clear_flag(frame2, LV_OBJ_FLAG_SCROLLABLE);
	    lv_obj_set_pos(frame2, 60, 140);
	    //
	    // Header
	    txt_header2 = lv_label_create(Tela_Principal);
	    lv_obj_set_style_text_font(txt_header2, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
	    lv_obj_set_style_text_color(txt_header2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	    lv_obj_set_style_text_opa(txt_header2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	    lv_obj_set_style_text_letter_space(txt_header2, 1, 0);
	    lv_obj_set_style_text_line_space(txt_header2, 1, 0);

	    lv_label_set_long_mode(txt_header2, LV_LABEL_LONG_WRAP);                // Break the long lines
	    lv_label_set_recolor(txt_header2, true);								// Enable re-coloring by commands in the text
	    lv_label_set_text(txt_header2, "IRON");
	    lv_obj_set_pos(txt_header2, 100, 124);
	    // IRON
	    txt_iron = lv_label_create(frame2);
	    lv_obj_set_style_text_font(txt_iron, &lv_7seg_40, LV_PART_MAIN | LV_STATE_DEFAULT);
	    lv_obj_set_style_text_color(txt_iron, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	    lv_obj_set_style_text_opa(txt_iron, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	    lv_obj_set_style_text_letter_space(txt_iron, 1, 0);
	    lv_obj_set_style_text_line_space(txt_iron, 1, 0);

	    lv_label_set_long_mode(txt_iron, LV_LABEL_LONG_WRAP);               // Break the long lines
	    lv_label_set_recolor(txt_iron, true);								// Enable re-coloring by commands in the text
	    lv_label_set_text(txt_iron, "300°C");
	    lv_obj_align_to(txt_iron, frame2, LV_ALIGN_CENTER, 0, 0);			// Align to center

	    print_debug_air();
	    print_debug_iron();
	    print_debug_max6675();

	    static uint32_t user_data = 10;
	    update_screen = lv_timer_create(update_screen_cb, 200, &user_data);

	    lv_scr_load(Tela_Principal);
 }

 void update_screen_cb(lv_timer_t * timer)
 {
 	if(timer->last_run - teste_task_screen >= 50) {
 		teste_task_screen = timer->last_run;
 	}

 	lv_label_set_text_fmt(txt_air, "125°C");
 	lv_label_set_text_fmt(txt_iron, "300°C");

 	lv_label_set_text_fmt(txt_pwm_iron, "PWM: 4095");
 	lv_label_set_text_fmt(txt_adc_iron, "ADC: 1000.00mV");
 	lv_label_set_text_fmt(txt_target_iron, "T: 350°C");

 	lv_label_set_text_fmt(txt_pwm_air, "PWM: 4095");
 	lv_label_set_text_fmt(txt_adc_air, "ADC: 1000.00mV");
 	lv_label_set_text_fmt(txt_fluxo_air, "Air: 4095");
 	lv_label_set_text_fmt(txt_target_air, "T: 400°C");

 	lv_label_set_text_fmt(txt_temp, "Temp: %3.2f°C", termocouple);
 }

 void print_debug_iron(void)
 {
     txt_pwm_iron = lv_label_create(Tela_Principal);
     lv_obj_set_style_text_font(txt_pwm_iron, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
     lv_obj_set_style_text_color(txt_pwm_iron, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
     lv_obj_set_style_text_opa(txt_pwm_iron, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
     lv_obj_set_style_text_letter_space(txt_pwm_iron, 1, 0);
     lv_obj_set_style_text_line_space(txt_pwm_iron, 1, 0);

     lv_label_set_long_mode(txt_pwm_iron, LV_LABEL_LONG_WRAP);                // Break the long lines
     lv_label_set_recolor(txt_pwm_iron, true);								// Enable re-coloring by commands in the text
     lv_label_set_text(txt_pwm_iron, "PWM: 4095");
     lv_obj_set_pos(txt_pwm_iron, 8, 208);

     txt_adc_iron = lv_label_create(Tela_Principal);
     lv_obj_set_style_text_font(txt_adc_iron, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
     lv_obj_set_style_text_color(txt_adc_iron, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
     lv_obj_set_style_text_opa(txt_adc_iron, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
     lv_obj_set_style_text_letter_space(txt_adc_iron, 1, 0);
     lv_obj_set_style_text_line_space(txt_adc_iron, 1, 0);

     lv_label_set_long_mode(txt_adc_iron, LV_LABEL_LONG_WRAP);                // Break the long lines
     lv_label_set_recolor(txt_adc_iron, true);								// Enable re-coloring by commands in the text
     lv_label_set_text(txt_adc_iron, "ADC: 1000.00mV");
     lv_obj_set_pos(txt_adc_iron, 8, 224);

     txt_target_iron = lv_label_create(Tela_Principal);
     lv_obj_set_style_text_font(txt_target_iron, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
     lv_obj_set_style_text_color(txt_target_iron, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
     lv_obj_set_style_text_opa(txt_target_iron, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
     lv_obj_set_style_text_letter_space(txt_target_iron, 1, 0);
     lv_obj_set_style_text_line_space(txt_target_iron, 1, 0);

     lv_label_set_long_mode(txt_target_iron, LV_LABEL_LONG_WRAP);                // Break the long lines
     lv_label_set_recolor(txt_target_iron, true);								// Enable re-coloring by commands in the text
     lv_label_set_text(txt_target_iron, "T: 350°C");
     lv_obj_set_pos(txt_target_iron, 8, 240);
 }

 void print_debug_air(void)
 {
     txt_pwm_air = lv_label_create(Tela_Principal);
     lv_obj_set_style_text_font(txt_pwm_air, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
     lv_obj_set_style_text_color(txt_pwm_air, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
     lv_obj_set_style_text_opa(txt_pwm_air, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
     lv_obj_set_style_text_letter_space(txt_pwm_air, 1, 0);
     lv_obj_set_style_text_line_space(txt_pwm_air, 1, 0);

     lv_label_set_long_mode(txt_pwm_air, LV_LABEL_LONG_WRAP);                // Break the long lines
     lv_label_set_recolor(txt_pwm_air, true);								// Enable re-coloring by commands in the text
     lv_label_set_text(txt_pwm_air, "PWM: 4095");
     lv_obj_set_pos(txt_pwm_air, 8, 84);

     txt_adc_air = lv_label_create(Tela_Principal);
     lv_obj_set_style_text_font(txt_adc_air, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
     lv_obj_set_style_text_color(txt_adc_air, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
     lv_obj_set_style_text_opa(txt_adc_air, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
     lv_obj_set_style_text_letter_space(txt_adc_air, 1, 0);
     lv_obj_set_style_text_line_space(txt_adc_air, 1, 0);

     lv_label_set_long_mode(txt_adc_air, LV_LABEL_LONG_WRAP);                // Break the long lines
     lv_label_set_recolor(txt_adc_air, true);								// Enable re-coloring by commands in the text
     lv_label_set_text(txt_adc_air, "ADC: 1000.00mV");
     lv_obj_set_pos(txt_adc_air, 8, 100);

     txt_fluxo_air = lv_label_create(Tela_Principal);
     lv_obj_set_style_text_font(txt_fluxo_air, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
     lv_obj_set_style_text_color(txt_fluxo_air, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
     lv_obj_set_style_text_opa(txt_fluxo_air, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
     lv_obj_set_style_text_letter_space(txt_fluxo_air, 1, 0);
     lv_obj_set_style_text_line_space(txt_fluxo_air, 1, 0);

     lv_label_set_long_mode(txt_fluxo_air, LV_LABEL_LONG_WRAP);                // Break the long lines
     lv_label_set_recolor(txt_fluxo_air, true);								// Enable re-coloring by commands in the text
     lv_label_set_text(txt_fluxo_air, "Air: 4095");
     lv_obj_set_pos(txt_fluxo_air, 156, 84);

     txt_target_air = lv_label_create(Tela_Principal);
     lv_obj_set_style_text_font(txt_target_air, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
     lv_obj_set_style_text_color(txt_target_air, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
     lv_obj_set_style_text_opa(txt_target_air, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
     lv_obj_set_style_text_letter_space(txt_target_air, 1, 0);
     lv_obj_set_style_text_line_space(txt_target_air, 1, 0);

     lv_label_set_long_mode(txt_target_air, LV_LABEL_LONG_WRAP);                // Break the long lines
     lv_label_set_recolor(txt_target_air, true);								// Enable re-coloring by commands in the text
     lv_label_set_text(txt_target_air, "T: 400°C");
     lv_obj_set_pos(txt_target_air, 8, 116);
 }

 void print_debug_max6675(void)
 {
     txt_temp = lv_label_create(Tela_Principal);
     lv_obj_set_style_text_font(txt_temp, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
     lv_obj_set_style_text_color(txt_temp, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
     lv_obj_set_style_text_opa(txt_temp, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
     lv_obj_set_style_text_letter_space(txt_temp, 1, 0);
     lv_obj_set_style_text_line_space(txt_temp, 1, 0);

     lv_label_set_long_mode(txt_temp, LV_LABEL_LONG_WRAP);                // Break the long lines
     lv_label_set_recolor(txt_temp, true);								// Enable re-coloring by commands in the text
     lv_label_set_text(txt_temp, "Temp: 0000.00°C");
     lv_obj_set_pos(txt_temp, 8, 290);
 }
