idf_component_register( SRCS "TM1637Display.cpp"
			            INCLUDE_DIRS "include"
                        REQUIRES freertos log driver esp_timer)