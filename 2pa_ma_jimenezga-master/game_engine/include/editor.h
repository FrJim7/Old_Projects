/**
* @file editor.h
* @author Francisco Jimenez Garcia
* jimenezga@esat-alumni.com
*/

#ifndef __EDITOR_H__
#define __EDITOR_H__ 1

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 
#include <vector>
#include "label.h"
#include "sprite.h"
#include "shape.h"
#include "background.h"

class Editor {
public:
  Editor();
   
   /**
    * @brief      Loads a hierachy.
    *             
    *             This function shows all the objects in the scene
    *             
    * @param[in]  objects  The objects
    */
  void loadHierachy(std::vector<GameObject*> objects, GameObject *ship_, GameObject *enemy_, GameObject *bullet_);

    /**
     * @brief      Loads an editor.
     * 
     *              This function shows and allows the user to see
     *              all the parameters and change them
     */ 
  void loadEditor();

  /**
   * @brief      Creates a data base.
   * 
   *              This function creates the database at the start of the  program
   */ 
  void createDB();
  /**
   * @brief      Saves de data in db.
   *  
   *              Store all the data related to the scene objects. The data 
   *              should be destryo before saving again.
   *  
   * @param[in]  objects  The objects
   */
  void saveDB(std::vector<GameObject*> objects);
  /**
   * @brief      Loads de data of db.
   *
   *             Loads all the stored data in the scene 
   *
   * @param[in]  objects  The objects
   */
  void loadDB(std::vector<GameObject*> objects);

  /**
   * @brief      Creates the window
   * 
   *              Create a special window to add object to the scene.
   *
   * @return     { description_of_the_return_value }
   */
  GameObject* editCreate();

  /**
   * auxiliar path to load and save data
   */
  char path_[255];
  /**
   * auxiliar path to load and save data
   */
  char text_[255];
  /**
   * auxiliar vector to load and save data
   */
  std::vector<GameObject *> v;
  /**
   * auxiliar bool to load and save data
   */
  bool to_load;
  /**
   * auxiliar object to modify the data of other objects
   */
  GameObject* selected_;
  /**
   * data base reference
   */
  sqlite3 *db;
  ~Editor(){};
};

#endif//__EDITOR_H__