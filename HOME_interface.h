/*
 * HOME_interface.h
 *
 * Created: 06-Oct-24 6:38:20 PM
 *  Author: 
 */ 


#ifndef HOME_INTERFACE_H_
#define HOME_INTERFACE_H_

#define ROOM1            1
#define ROOM2            2
#define LIVING_ROOM      3
#define KITCHEN          4
#define BATHROOM         5



void ADMIN_HOME_Cntrl(); 
void USER_HOME_Cntrl_lcd();//DISPLAY OPTIONS VIA LCD AND EXECUTE SELECTED COMMAND
void USER_HOME_Cntrl_remotely(); //DISPLAY OPTIONS VIA BL AND EXECUTE SELECTED COMMAND
void HOME_Start();
void HOME_INIT();
void OPEN_DOOR();
void CLOSE_DOOR();
void AC_STATE ();
void LIGHT_SYSTEM (u8 room);
void DIMMING_LAMP (u8 intensity);
void FIRE_ALARM();

#endif /* HOME_INTERFACE_H_ */