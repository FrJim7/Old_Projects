#include "game_text.h"

#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_internal.h"
#include "tinyfiledialogs.h"

#include "game_defs.h"

Text::Text() {
  transform_.setPosition(kDefaultPosition);
  transform_.setRotation(kDefaultRotation);
  transform_.setScale(kDefaultScale);

  transform_.setFillColor(kDefaultColor);
  transform_.setOutlineColor(kDefaultColor);

  transform_.setString("abcd");
  snprintf(text_, kBufferSize, "abcd");
  
  handle_.loadFromFile(kDefaultFont);
  transform_.setFont(handle_);

  snprintf(path_, kBufferSize, "%s", kDefaultFont);
  type_ = kText;
}

Text::Text(const Text& other) {
  transform_ = other.transform_;
}

Text::~Text() {
}

void Text::init() {
  transform_.setPosition(kDefaultPosition);
  transform_.setRotation(kDefaultRotation);
  transform_.setScale(kDefaultScale);

  transform_.setFillColor(kDefaultColor);
  transform_.setOutlineColor(kDefaultColor);

  transform_.setString("abcd");
  snprintf(text_, kBufferSize, "abcd");
  
  handle_.loadFromFile(kDefaultFont);
  transform_.setFont(handle_);

  snprintf(path_, kBufferSize, "%s", kDefaultFont);
  type_ = kText;
}

void Text::parsePath(const char *path) {
  if (NULL == path) {
    return;
  }

  int aux_index = 0;
  int start_index = 0;
  int path_length = strlen(path);

  memset(parsed_path_, 0, kBufferSize);
  parsed_path_[0] = '.';
  parsed_path_[1] = '.';

  for(int x = 0; x < path_length; ++x) {
    if(path[x] == kGameRoot[aux_index]) {
      aux_index++;
    } else {
      aux_index = 0;
    }
    if(aux_index == kGameRootSize) {
      start_index = x + 1;
    }
  }

  aux_index = 2;

  for (int x = start_index; x < path_length; ++x) {
    parsed_path_[aux_index] = path[x];
    aux_index++;
  }
}

void Text::imgui() {
  ImGui::Text("Object id: %d", id_);
  ImGui::Text("Type: Text");

  ImGui::Separator();

  float data[2] = {transform_.getPosition().x, transform_.getPosition().y};
  if (ImGui::InputFloat2("Position", data)) {
    set_position(data[0], data[1]);
  }
  float rotation = transform_.getRotation();
  if (ImGui::InputFloat("Rotation", &rotation)) {
    set_rotation(rotation);
  }
  data[0] = transform_.getScale().x;
  data[1] = transform_.getScale().y;
  if (ImGui::InputFloat2("Scale", data)) {
    set_scale(data[0], data[1]);
  }
  data[0] = size().x;
  if (ImGui::InputFloat("Size", data)) {
    set_size(data[0], 0.0f);
  }

  int color_data[4] = {transform_.getFillColor().r, 
    transform_.getFillColor().g, 
    transform_.getFillColor().b, 
    transform_.getFillColor().a};
  if (ImGui::InputInt4("Fill Color", color_data)) {
    set_color(sf::Color(color_data[0], color_data[1], 
      color_data[2], color_data[3]));
  }

  color_data[0] = transform_.getOutlineColor().r;
  color_data[1] = transform_.getOutlineColor().g;
  color_data[2] = transform_.getOutlineColor().b;
  color_data[3] = transform_.getOutlineColor().a;
  if (ImGui::InputInt4("Outline Color", color_data)) {
    set_color(sf::Color(color_data[0], color_data[1], 
      color_data[2], color_data[3]));
  }

  if (ImGui::InputText("String", text_, kBufferSize)) {
    set_text(text_);
  }

  const char *kFilterPatterns[2] = { "*.ttf" };
  char const *path = nullptr;

  if (ImGui::Button("...")){
    path = tinyfd_openFileDialog(NULL, NULL, 1, kFilterPatterns, NULL, 0);
    parsePath(path);
    snprintf(path_, kBufferSize, "%s", parsed_path_);
  }
  ImGui::Text("Path: %s", path_);
}

void Text::update(float dt) {
}

void Text::draw(sf::RenderTexture& texture) {
  texture.draw(transform_);
}

void Text::set_position(float px, float py) {
  transform_.setPosition(px, py);
}

void Text::set_rotation(float rotation) {
  transform_.setRotation(rotation);
}

void Text::set_scale(float scx, float scy) {
  transform_.setScale(scx, scy);
}

void Text::set_size(float sx, float sy) {
  transform_.setCharacterSize((unsigned int)sx);
}

void Text::set_color(sf::Color color) {
  transform_.setFillColor(color);
}

void Text::set_outlinecolor(sf::Color o_color) {
  transform_.setOutlineColor(o_color);
}

void Text::set_text(char *text) {
  if (NULL == text) {
    return;
  }
  transform_.setString(text);
  snprintf(text_, kBufferSize, "%s", text);
}

void Text::set_font(char *path) {
  if (NULL == path) {
    return;
  }
  handle_.loadFromFile(path);
  snprintf(path_, kBufferSize, "%s", path);
}

void Text::set_texture_id(int texture_id) {
}

void Text::set_velocity(float vx, float vy) {
}

float Text::rotation() {
  return transform_.getRotation();
}

sf::Vector2f Text::position() {
  return transform_.getPosition();
}

sf::Vector2f Text::scale() {
  return transform_.getScale();
}

sf::Vector2f Text::size() {
  return sf::Vector2f((float)transform_.getCharacterSize(), 0.0f);
}

sf::Color Text::color() {
  return transform_.getFillColor();
}

sf::Color Text::o_color() {
  return transform_.getOutlineColor();
}

char* Text::text() {
  return text_;
}

char* Text::font() {
  return path_;
}

int Text::texture_id() {
  return -1;
}

sf::Vector2f Text::velocity() {
  return sf::Vector2f(0, 0);
}