
#ifndef LCD_H_
#define LCD_H_

#include "stm32f10x.h"
#include "stm32f10x_GPIO.h"

/* APIS */
void lcd_init(void);
void lcd_send_command(uint8_t cmd);
void lcd_print_char(uint8_t data);
void lcd_display_clear(void);
void lcd_display_return_home(void);
void lcd_print_string(char*);
void lcd_set_cursor(uint8_t row, uint8_t column);
void mdelay(uint32_t cnt);
//void lcd_print_time(RTC_Time *time);

/*Application configurable items */

#define GPIO_PIN_NO_13 13
#define GPIO_PIN_NO_14 14
#define GPIO_PIN_NO_15 15
#define GPIO_PIN_NO_3  3
#define GPIO_PIN_NO_2  2
#define GPIO_PIN_NO_1	 1
#define GPIO_PIN_NO_0  0

#define LCD_GPIO_PORT_CONF  GPIOC
#define LCD_GPIO_PORT_DATA  GPIOA
#define LCD_GPIO_RS	   			GPIO_PIN_NO_13
#define LCD_GPIO_RW	   			GPIO_PIN_NO_14
#define LCD_GPIO_EN	   			GPIO_PIN_NO_15
#define LCD_GPIO_D4	   			GPIO_PIN_NO_3
#define LCD_GPIO_D5	   			GPIO_PIN_NO_2
#define LCD_GPIO_D6	   			GPIO_PIN_NO_1
#define LCD_GPIO_D7	   			GPIO_PIN_NO_0


/*LCD commands */
#define LCD_CMD_4DL_2N_5X8F  			0x28
#define LCD_CMD_DON_CURON    			0x0E
#define LCD_CMD_INCADD       			0x06
#define LCD_CMD_DIS_CLEAR    			0X01
#define LCD_CMD_DIS_RETURN_HOME  	0x02

/* LCD Macros for DATA Pattern*/

/* Numbers */
#define DATA_1_L  	0x1
#define DATA_2_L  	0x2
#define DATA_3_L  	0x3
#define DATA_4_L  	0x4
#define DATA_5_L  	0x5
#define DATA_6_L  	0x6
#define DATA_7_L  	0x7
#define DATA_8_L  	0x8
#define DATA_9_L  	0x9

#define DATA_1_H  	0x3
#define DATA_2_H  	0x3
#define DATA_3_H  	0x3
#define DATA_4_H  	0x3
#define DATA_5_H  	0x3
#define DATA_6_H  	0x3
#define DATA_7_H  	0x3
#define DATA_8_H	  0x3
#define DATA_9_H   	0x3

/* CHARACTERS */

#define DATA_A_L		0x1
#define DATA_B_L		0x1
#define DATA_C_L		0x1
#define DATA_D_L		0x1
#define DATA_E_L		0x1
#define DATA_F_L		0x1
#define DATA_G_L		0x1
#define DATA_H_L		0x1
#define DATA_I_L		0x1
#define DATA_J_L		0x1
#define DATA_K_L		0x1
#define DATA_L_L		0x1
#define DATA_M_L		0x1
#define DATA_N_L		0x1
#define DATA_O_L		0x1
#define DATA_P_L		0x1
#define DATA_Q_L		0x1
#define DATA_R_L		0x1
#define DATA_S_L		0x1
#define DATA_T_L		0x1
#define DATA_U_L		0x1
#define DATA_V_L		0x1
#define DATA_W_L		0x1
#define DATA_X_L		0x1
#define DATA_Y_L		0x1
#define DATA_Z_L		0x1
#define DATA_a_L		0x1
#define DATA_b_L		0x1
#define DATA_c_L		0x1
#define DATA_d_L		0x1
#define DATA_e_L		0x1
#define DATA_f_L		0x1
#define DATA_g_L		0x1
#define DATA_h_L		0x1
#define DATA_i_L		0x1
#define DATA_j_L		0x1
#define DATA_k_L		0x1
#define DATA_l_L		0x1
#define DATA_m_L		0x1
#define DATA_n_L		0x1
#define DATA_o_L		0x1
#define DATA_p_L		0x1
#define DATA_q_L		0x1
#define DATA_r_L		0x1
#define DATA_s_L		0x1
#define DATA_t_L		0x1
#define DATA_u_L		0x1
#define DATA_v_L		0x1
#define DATA_w_L		0x1
#define DATA_x_L		0x1
#define DATA_y_L		0x1
#define DATA_z_L		0x1


#define DATA_A_H		0x4
#define DATA_B_H		0x4
#define DATA_C_H		0x4
#define DATA_D_H		0x4
#define DATA_E_H		0x4
#define DATA_F_H		0x4
#define DATA_G_H		0x4
#define DATA_H_H		0x4
#define DATA_I_H		0x4
#define DATA_J_H		0x4
#define DATA_K_H		0x4
#define DATA_L_H		0x4
#define DATA_M_H		0x4
#define DATA_N_H		0x4
#define DATA_O_H		0x4
#define DATA_P_H		0x5
#define DATA_Q_H		0x5
#define DATA_R_H		0x5
#define DATA_S_H		0x5
#define DATA_T_H		0x5
#define DATA_U_H		0x5
#define DATA_V_H		0x5
#define DATA_W_H		0x5
#define DATA_X_H		0x5
#define DATA_Y_H		0x5
#define DATA_Z_H		0x5
#define DATA_a_H		0x6
#define DATA_b_H		0x6
#define DATA_c_H		0x6
#define DATA_d_H		0x6
#define DATA_e_H		0x6
#define DATA_f_H		0x6
#define DATA_g_H		0x6
#define DATA_h_H		0x6
#define DATA_i_H		0x6
#define DATA_j_H		0x6
#define DATA_k_H		0x6
#define DATA_l_H		0x6
#define DATA_m_H		0x6
#define DATA_n_H		0x6
#define DATA_o_H		0x6
#define DATA_p_H		0x7
#define DATA_q_H		0x7
#define DATA_r_H		0x7
#define DATA_s_H		0x7
#define DATA_t_H		0x7
#define DATA_u_H		0x7
#define DATA_v_H		0x7
#define DATA_w_H		0x7
#define DATA_x_H		0x7
#define DATA_y_H		0x7
#define DATA_z_H		0x7

/* Special Characters */
#define DATA_BELL_L		0x8
#define DATA_BELL_H		0X9


#endif /* LCD_H_ */
