#include <pebble.h>
#include "Meetup.h"

static Window *window;
static TextLayer *s_timeLayer;

static void window_load(Window *window){
	Layer *window_layer = window_get_root_layer(window);
	
	s_timeLayer = text_layer_create(GRect(20,65,100,100));
	layer_add_child(window_layer,text_layer_get_layer(s_timeLayer));
	
	text_layer_set_text_alignment(s_timeLayer, GTextAlignmentCenter);
	text_layer_set_font(s_timeLayer, fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21));
	
	text_layer_set_text_color(s_timeLayer, GColorOrange);
}

static void window_unload(Window *window){
	text_layer_destroy(s_timeLayer);
}

void handle_tick(struct tm *tick_time, TimeUnits unit_changed){
	static char time_text[] = "12:34:56";
	strftime(time_text,sizeof(time_text),"%H-%M-%S",tick_time);
	text_layer_set_text(s_timeLayer,time_text);
}

void handle_init(void){
	printf("Handle Init...");
	window = window_create();
	
	window_set_window_handlers(window, (WindowHandlers){
		.load = window_load,
		.unload = window_unload
	});
	
	window_stack_push(window,true);
	tick_timer_service_subscribe(SECOND_UNIT,handle_tick);
}

void handle_deinit(void){
	printf("Handle Deinit...");
	tick_timer_service_unsubscribe();
	window_destroy(window);
}

int main(void) {
	handle_init();
	app_event_loop();
	handle_deinit();
}