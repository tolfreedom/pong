
#include <stdio.h>
#include "ww.h"
#include "ball.h"
#include "player_one.h"
#include "player_two.h"
#include "countdown.h"
#include "score_one.h"
#include "score_two.h"

int screen_width = 1024;
int screen_height = 576;

int main( int argc, char * argv[] ) {

	
	if(ww_window_create(argc, argv, "Pixarray", 1024, 576)) {
		printf("Closing..\n");
		return 1;
	}
	
	init_ball() ; 
	init_player_one() ; 
	init_player_two() ; 
	init_countdown() ;
	init_score_one();
	init_score_two();
	
	
	int y_dir = -3 ;
	int x_dir = -3;
	
	player_two->pad_x = screen_width - player_two->width ;
		ball->pad_x = (screen_width / 2) - (ball->width /2) ; 
		ball->pad_y = (screen_height / 2) - (ball->height /2);
		
	score_one->pad_x = screen_width / 4 * 2;
	
	
	
	while(!ww_window_received_quit_event()) {
		ww_window_update_events();	
		
		if (keystate.esc == 1){
			printf ("ESC pressed\n") ;
			ww_window_send_quit_event() ; 
			}
		
		//player 1 move up
		if (keystate.w == 1 && player_one->pad_y > 0 ) {
			player_one->pad_y = player_one->pad_y -3 ;
		}
		
		//player 1 move down
		if (keystate.s == 1 && player_one->pad_y < screen_height - 
		player_one->height) { 
			player_one->pad_y = player_one->pad_y +3 ;
		}
	
		//player 2 move up
		if (keystate.up == 1 && player_two->pad_y > 0) {
			player_two->pad_y = player_two->pad_y -3 ;
		}
	
		//player 2 move down
		if (keystate.dn == 1 && player_two->pad_y < screen_height - 
			player_two->height) {
			player_two->pad_y = player_two->pad_y +3 ;
		}	
		
		
		//ball movement
		ball->pad_y = ball->pad_y + y_dir;
		ball->pad_x = ball->pad_x + x_dir;
		
		if (ball->pad_y > screen_height - ball->height || 
		ball->pad_y < 0){
			y_dir = y_dir * -1;
		}
		
		//move ball back to sent if off side
		if (ball->pad_x < 0  || ball->pad_x > screen_width){
			ball->pad_x = (screen_width / 2) - (ball->width /2);
			ball->pad_y = (screen_height /2) - (ball->height /2);
		}
		
		if (player_one->pad_y <= ball->pad_y && ball->pad_x < player_one->width){
			x_dir = x_dir * -1;
		}
		if (player_one->pad_y + player_one->height <= ball->pad_y + ball->height && ball->pad_x < 0 + player_one->width){
			x_dir = x_dir * -1;
		}
		if (player_two->pad_y < ball->pad_y && ball->pad_x  > screen_width - player_two->width *2){
			x_dir = x_dir * -1;
		}	
		if (player_two->pad_y + player_two->height <= ball->pad_y + ball->height && ball->pad_x > screen_width - player_two->width *2){
			x_dir = x_dir * -1;		

		}
		
		//score
		if (ball->pad_x > 0){
			(score_one-> active_animationn = score_one-> active_animation + 1); 
		}
			
		ww_draw_sprite(player_one) ; 
		ww_draw_sprite(player_two) ; 
		ww_draw_sprite(ball) ; 
		ww_draw_sprite(score_one) ; 
		ww_draw_sprite(score_two) ; 
		
			
		
		ww_window_update_buffer();
	}
	
	ww_window_destroy();
	return 0;
}
