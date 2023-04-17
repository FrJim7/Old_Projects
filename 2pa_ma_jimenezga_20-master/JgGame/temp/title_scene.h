#ifndef __TITLE_SCENE_H__
#define __TITLE_SCENE_H__ 1

#include "scene.h"

class TitleScene : public Scene {
 public:
  TitleScene();
  virtual ~TitleScene();

  void init(int id) override;
  void input() override;
  void update() override;
};

#endif//__TITLE_SCENE_H__