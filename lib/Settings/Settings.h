/* Settings.h
 * 30.06.2022
 * 
 * Enables to set an read settings
 * 
 * Author: Lukas Beck
 * Email: Lukas.beck@ditf.de
 */

class Settings {
  public:

  int id; // id of the controller, displayed in name of controller
  int send_freq; // send frequency of new values in ms

  void setup(void);
};