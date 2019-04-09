/**
  *   @file DemoWorld.cpp
  *   @author Lauri Westerholm
  *   @brief Source code for DemoWorld
  */

#include "DemoWorld.hpp"

/*  Class DemoWorld */

// set the gravity value
float pe::PhysicsProperties::GravityY = 100.f;
float pe::PhysicsProperties::GravityX = 0.f;

// static funtions, for setting gravity values
void DemoWorld::setGravityX(int gravity){
  pe::PhysicsProperties::GravityX = static_cast<float> (gravity);
}

void DemoWorld::setGravityY(int gravity) {
  pe::PhysicsProperties::GravityY = static_cast<float> (gravity);
}

// Constructor
DemoWorld::DemoWorld(sf::RenderWindow& window): window(window),
removeCollided(false), collisions(true) {}

// Deconstructor
DemoWorld::~DemoWorld() {
  for (auto it = demoObjects.begin(); it != demoObjects.end();) {
    delete *it;
    it = demoObjects.erase(it);
  }
  for (auto it = shapes.begin(); it != shapes.end(); ) {
    delete it->second;
    it = shapes.erase(it);
  }
}

// Init DemoWorld
void DemoWorld::initWorld() {
  loadDemoLevel(DemoLevelLoader::getLevelPath(DemoLevelLoader::StartLevel));
  /*shape = new pe::Shape(40.f, 20.f);
  // create couple DemoObjects
  for (int i = 0; i < 10; i++) {
    DemoObject* obj = new DemoObject(pe::ObjectType::ObjectType::StaticObject, shape, sf::Color::Red);
    obj->setPosition(static_cast<float>(i * 50), static_cast<float>(i * 100));
    // add object to physWorld
    physWorld.addObject(obj->getPhysicsObject());
    demoObjects.push_back(obj);
  }
  for (int i=0; i < 10; i++) {
    DemoObject* obj = new DemoObject(pe::ObjectType::ObjectType::DynamicObject, shape, sf::Color::Green);
    obj->setPosition(static_cast<float>(i * 100), static_cast<float>(i * 50));
    // add object to physWorld
    physWorld.addObject(obj->getPhysicsObject());
    demoObjects.push_back(obj);
  }*/
}

// Handle SFML window events
DemoObject* DemoWorld::handleEvent(sf::Event& event) {
  switch (event.type) {
    case sf::Event::MouseButtonPressed:
      return MousePress(event);
    default:
      return nullptr;
  }
}

// Update DemoWorld periodically
void DemoWorld::update() {
  // update PhysicsWorld
  physWorld.update();
  for (auto& object : demoObjects) {
    object->updatePosition();
  }
  //int num = 0;
  std::list<struct pe::Collided>& collided = physWorld.getCollided();
  for (auto it = collided.begin(); it != collided.end(); it++) {
    //num++;
    // remove collided if removal true
    if (removeCollided) RemoveCollided(*it);
  }
  //std::cout << "Collisions: " << num << std::endl;
}

// Draw DemoWorld
void DemoWorld::draw() {
  // Draw all DemoObjects
  for (auto& object : demoObjects) {
    window.draw(*object);
  }
}

// Try to press DemoObject, private method
DemoObject* DemoWorld::MousePress(sf::Event& event) {
  if (event.mouseButton.button == sf::Mouse::Button::Left) {
    for (DemoObject* object : demoObjects) {
      if ((object->getPhysicsObject()->getObjectType() == pe::ObjectType::ObjectType::DynamicObject) &&
          (object->isInside(pe::Vector2f(event.mouseButton.x, event.mouseButton.y)))) {
        return object;
      }
    }
  }
  return nullptr;
}

// Remove collided objects, private method
void DemoWorld::RemoveCollided(struct pe::Collided& collided) {
  for (auto it = demoObjects.begin(); it != demoObjects.end(); ) {
    if (((*it)->getPhysicsObject() == collided[0]) || ((*it)->getPhysicsObject() == collided[1])) {
      delete *it;
      it = demoObjects.erase(it);
    }
    else it++;
  }
  // now remove PhysicsObjects, demoObject removal should left those untact
  if ((collided[0] != nullptr) && (!physWorld.removeObject(collided[0]))) {
    std::cout << "PhysicsObject removal error" << std::endl;
  }
  if ((collided[1] != nullptr) && (!physWorld.removeObject(collided[1]))) {
    std::cout << "PhysicsObject removal error" << std::endl;
  }
}

// Toggle object collisions on/off, that is done by adjusting PhysicsObjects collision_masks
void DemoWorld::toggleCollisions() {
  uint8_t mask;
  if (collisions) {
    collisions = false;
    mask = 0xFF; // no collisions
  }
  else {
    collisions = true;
    mask = 0x00; // all collisions
  }
  // update masks
  for (auto& object : demoObjects) {
    object->getPhysicsObject()->setCollisionMask(mask);
  }
}

// Clear all objects
void DemoWorld::clearWorld() {
  physWorld = pe::PhysicsWorld(); // assign new PhysicsWorld which effectively clears the old one
  for (auto it = demoObjects.begin(); it != demoObjects.end(); ) {
    delete *it;
    it = demoObjects.erase(it);
  }
}

// Load demo level: create demoObjecs and physicsWorld
void DemoWorld::loadDemoLevel(const char* path) {
  // clear previous objects
  clearWorld();

  std::string line;
  std::ifstream file(path);
  if (file.is_open()) {
    while (getline(file, line)) {
      // convert to string stream to separate values based on , -delimiter
      float x, y, width, height;
      pe::ObjectType::ObjectType object_type;
      std::istringstream stream(line);
      int i = 0;
      std::string content;
      while (getline(stream, content, ',')) {
        try {
          switch (i) {
            case 0:
              object_type = StrToObjectType(content);
              break;
            case 1:
              x = std::stof(content);
              break;
            case 2:
              y = std::stof(content);
              break;
            case 3:
              width = std::stof(content);
              break;
            case 4:
              height = std::stof(content);
              break;
            default:
              std::cout << "Unexpected file read" << std::endl;
          }
          i++;
          content = "";
        } catch (std::invalid_argument& e) {
          std::cout << "File load failed: " << e.what() << ", return" << std::endl;
          return;
        }
      }
      if (i > 4) {
        // everything went right, we should now have one object to be added to world
        DemoObject* obj;
        if (object_type == pe::ObjectType::ObjectType::StaticObject) {
          obj = new DemoObject(object_type, GetShape(width, height), sf::Color::Red);
        } else obj = new DemoObject(object_type, GetShape(width, height), sf::Color::Green);

        obj->setPosition(x, y);
        // add object to physWorld
        physWorld.addObject(obj->getPhysicsObject());
        demoObjects.push_back(obj);

      } else {
        std::cout << "Cannot construct object, file " << path << " missing details" << std::endl;
      }

    }
    file.close();
  }
  else {
    std::cout << "file opening error: " << path << std::endl;
  }
}

// Convert str to pe::ObjectType
pe::ObjectType::ObjectType DemoWorld::StrToObjectType(std::string& str) const {
  if (str == "DynamicObject") return pe::ObjectType::ObjectType::DynamicObject;
  return pe::ObjectType::ObjectType::StaticObject;
}

// Get correct Shape
pe::Shape* DemoWorld::GetShape(float width, float height) {
  auto it = shapes.find(pe::Vector2f(width, height));
  if (it == shapes.end()) {
    // inset new Shape
    pe::Shape* new_shape = new pe::Shape(width, height);
    shapes.emplace(pe::Vector2f(width, height), new_shape);
    return new_shape;
  }
  return it->second;
}

// Set density for all objects
void DemoWorld::setObjectDensity(int density) {
  if (density < 0) density = 0;
  else if (density > 50) density = 50;
  float densityf = density * 0.1f;
  for (auto& object : demoObjects) {
    object->getPhysicsObject()->setDensity(static_cast<float> (densityf));
  }
}

// Set elasticity for all objects
void DemoWorld::setObjectElasticity(int elasticity) {
  if (elasticity < 0) elasticity = 0;
  else if (elasticity > 20) elasticity = 20;
  float elasticityf = 0.05f * elasticity;
  for (auto& object : demoObjects) {
    object->getPhysicsObject()->setElasticity(elasticityf);
  }
}
