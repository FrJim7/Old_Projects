/**
 * @defgroup   APP_MANAGER application manager
 *
 * @brief      This file implements application manager.
 *
 * @author     jimenezga
 * @date       2019
 */
#ifndef __APP_MANAGER_H__
#define __APP_MANAGER_H__ 1

const float kAgentSpeed = 5.0f;

/**
 * @brief      App Manager class
 */
class AppManager {
 public:

  /**
   * @brief      Get an instance of the class
   *
   * @return     { reference to the class }
   */
  static AppManager& instance();

  /**
   * @brief      Update the input of the app
   */
  void update();

  bool exit_request_;
  bool app_end_;

  float mouse_x_;
  float mouse_y_;

 private:
  AppManager();

};

#endif//__APP_MANAGER_H__