

#include "urosHandlers.h"
#include "app.h"
#include "ssid_config.h"
/*===========================================================================*/
/* Benchmark related.                                                        */
/*===========================================================================*/

const int gpio = 2;
static   UrosThreadId ap,cp;
  
static uros_err_t log_thread_info(void*pvParameters) {
  UrosString    ct;
  urosStringObjectInit(&ct);
  ct.datap="a";
while (1){
  gpio_enable(gpio, GPIO_OUTPUT);
  
/* Capture the state with the lowest jitter possible.*/
  urosMutexLock(&mengds.lock);
  ct=mengds.load;
 
  urosMutexUnlock(&mengds.lock);

  /* Log the captured info.*/
  printf("@ %s\n",ct.datap);
   
  printf( "\n");
  if (strcmp(ct.datap, "ab")){
gpio_write(gpio, 1);
}
if (strcmp(ct.datap, "ac")){
gpio_write(gpio,0);
}
 vTaskDelay(1000);
}
}




/*===========================================================================*/
/* Main features.                                                            */
/*===========================================================================*/




/*
 * Application entry point.
 */
void user_init(void) {

  
    uart_set_baud(0, 115200);
    printf("SDK version:%s\n", sdk_system_get_sdk_version());
    struct sdk_station_config config = {
        .ssid = WIFI_SSID,
        .password = WIFI_PASS,
    };

    printf("WiFi: connecting to WiFi\n\r");
    sdk_wifi_set_opmode(STATION_MODE);
    sdk_wifi_station_set_config(&config);
    app_initialize();
    
 
   
   

   urosThreadCreateStatic(&ap, "logprint",2,log_thread_info,NULL,NULL,256);

    
}
