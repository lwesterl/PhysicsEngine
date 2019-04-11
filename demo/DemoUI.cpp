/**
  *   @file DemoUI.cpp
  *   @author Lauri Westerholm
  *   @brief Source for DemoUI
  */


#include "DemoUI.hpp"

/* Class DemoUI */

// Constructor
DemoUI::DemoUI(sf::RenderWindow& window): paused(true), window(window), demoWorld(window) {
  demoWorld.initWorld();
  CreateUI();
}

// Deconstructor
DemoUI::~DemoUI() {
  for (int i = 0; i < 4; i++) {
    delete multiChoices[i];
  }
  delete levelSelect;
}


// Run DemoUI until window is closed
void DemoUI::run() {
  while(window.isOpen()) {
    sf::Event event;
    while(window.pollEvent(event)) {
      if (! HandleUIEvent(event)) {
        // quit
        window.close();
        return;
      }
      if (! paused) {
        // Handle also DemoWorld events
        DemoObject* object;
        if ((object = demoWorld.handleEvent(event))) {
          mouseApplyForce.setEvent(object, object->getCenterPosition());
        }
      }
    }
    if (paused) HandleMouseHold();
    else HandleForceApply();

    // clear all draw objects
    window.clear(sf::Color::White);
    // update demoWorld if not paused
    if (! paused) demoWorld.update();
    // draw all objects
    demoWorld.draw();
    drawUI();
    // show updated window
    window.display();
  }
}

// Draw all UI related objects
void DemoUI::drawUI() {
  window.setView(bottomToolbarView);
  window.draw(toolbarBackground);
  window.draw(buttons[0]);
  window.draw(buttons[1]);
  window.draw(buttonText[0]);
  window.draw(buttonText[1]);
  window.setView(window.getDefaultView());
  if (paused) {
    // draw also UI-elements for pause menu
    window.draw(pauseBackground);
    window.draw(switches[0]);
    window.draw(switches[1]);
    for (unsigned i = 0; i < DemoUI::MultiChoiceAmount; i++) {
      window.draw(*multiChoices[i]);
    }
    window.draw(*levelSelect);
  }
  else if (mouseApplyForce.leftHold) {
    mouseApplyForce.draw(window);
  }
}

// Update UI related events, private method
bool DemoUI::HandleUIEvent(sf::Event& event) {
  switch (event.type) {
    case sf::Event::Closed:
      return false;
    case sf::Event::KeyPressed:
      return HandleKeyPress(event);
    case sf::Event::MouseButtonPressed:
      return HandleMousePress(event);
    default:
      return true;
  }
}

// Handle key presses, private method
bool DemoUI::HandleKeyPress(sf::Event& event) {
  if (event.key.code == sf::Keyboard::Escape) return false;
  if (event.key.code == sf::Keyboard::Space) pauseSwitch();
  if ((event.key.code == sf::Keyboard::R) && (!mouseApplyForce.leftHold)) restartSwitch();
  return true;
}

// Handle mouse presses, private method
bool DemoUI::HandleMousePress(sf::Event& event) {
  if (event.mouseButton.button == sf::Mouse::Button::Left) {
    if (buttons[0].checkClicked(event.mouseButton.x, event.mouseButton.y - DemoUI::BottomToolStartHeight * DemoUI::WindowHeight)) return true;
    if (buttons[1].checkClicked(event.mouseButton.x, event.mouseButton.y - DemoUI::BottomToolStartHeight * DemoUI::WindowHeight)) return true;
    if (paused) {
      // check if pause menu UI-elements are pressed
      if (switches[0].tryToggle(event.mouseButton.x, event.mouseButton.y)) {
        demoWorld.toggleCollisions();
      }
      else if (switches[1].tryToggle(event.mouseButton.x, event.mouseButton.y)) {
        demoWorld.toggleObjectRemoval();
      }
      else {
        for (unsigned i = 0; i < DemoUI::MultiChoiceAmount; i++) {
          if (multiChoices[i]->tryToggle(event.mouseButton.x, event.mouseButton.y)) {
            // update MousePressDetails
            mousePressDetails.leftHold = true;
            mousePressDetails.prevTime = std::chrono::steady_clock::now();
            mousePressDetails.multiChoice = multiChoices[i];
            return true;
          }
        }
        if (levelSelect->tryToggle(event.mouseButton.x, event.mouseButton.y)) {
          restartSwitch();
        }
      }
    }
  }
  return true;
}

// Handle continous mouse holds, private method
void DemoUI::HandleMouseHold() {
  if (mousePressDetails.leftHold && (sf::Mouse::isButtonPressed(sf::Mouse::Left))) {
    std::chrono::steady_clock::time_point time_now = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds> (time_now - mousePressDetails.prevTime).count() > DemoUI::PressDuration) {
      // trigger a new mouse press
      sf::Vector2i mousePos = sf::Mouse::getPosition(window);
      if (! mousePressDetails.multiChoice->tryToggle(mousePos.x, mousePos.y)) {
        // Mouse not anymore above the Multichoice
        mousePressDetails.leftHold = false;
      }
      mousePressDetails.prevTime = time_now;
    }
  }
  else mousePressDetails.leftHold = false;
}

// Handle changes in mouseApplyForce, private method
void DemoUI::HandleForceApply() {
  if (mouseApplyForce.leftHold) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      // update end and start position
      mouseApplyForce.end.position = static_cast<sf::Vector2f> (sf::Mouse::getPosition(window));
      mouseApplyForce.start.position = mouseApplyForce.demoObject->getCenterPosition();
    }
    else {
      // applyForce and init
      mouseApplyForce.applyForce();
      mouseApplyForce.leftHold = false;
      mouseApplyForce.demoObject = nullptr;
    }
  }
}

// Create UI for DemoUI, private method
void DemoUI::CreateUI() {
  // create view
  bottomToolbarView.setViewport(sf::FloatRect(0, DemoUI::BottomToolStartHeight, 1, 1.f - DemoUI::BottomToolStartHeight));
  bottomToolbarView.setSize(DemoUI::WindowWidth, (1.f - DemoUI::BottomToolStartHeight) * DemoUI::WindowHeight);
  bottomToolbarView.setCenter(sf::Vector2f(DemoUI::WindowWidth /2.f, (1.f - DemoUI::BottomToolStartHeight) * DemoUI::WindowHeight * 0.5f));
  // init UI-elements
  buttons[0] = UI::Button(10.f, 10.f, textureLoader.getTexture(UI::TextureName::StartStop), std::bind(&DemoUI::pauseSwitch, this));
  buttons[1] = UI::Button(100.f, 10.f, textureLoader.getTexture(UI::TextureName::Restart), std::bind(&DemoUI::restartSwitch, this));
  toolbarBackground.setSize(bottomToolbarView.getSize());
  toolbarBackground.setFillColor(sf::Color(0, 0, 0, 235));
  pauseBackground.setSize(sf::Vector2f(DemoUI::WindowWidth, DemoUI::BottomToolStartHeight * DemoUI::WindowHeight));
  pauseBackground.setFillColor(sf::Color(0, 0, 0, 235));
  font.loadFromFile(FontPath);
  buttonText[0] = sf::Text("Space", font, 12);
  buttonText[0].setFillColor(sf::Color::Blue);
  pe::Vector2f button_size = buttons[0].getSize();
  buttonText[0].setPosition(15.f, -7.f + button_size.getY());
  buttonText[1] = sf::Text("R", font, 12);
  buttonText[1].setFillColor(sf::Color::Blue);
  buttonText[1].setPosition(105.f, -7.f + button_size.getY());

  switches[0] = UI::Switch(50.f, 200.f, "Collisions");
  switches[1] = UI::Switch(50.f, 300.f, "Remove collided", false);
  multiChoices[0] = new UI::Multichoice("Gravity x-dimension", 0.35 * DemoUI::WindowWidth, 10.f, 80.f, 120.f,
  textureLoader.getTexture(UI::TextureName::UpArrow), textureLoader.getTexture(UI::TextureName::DownArrow), std::bind(&DemoWorld::setGravityX, std::placeholders::_1));
  multiChoices[0]->setScale(pe::PhysicsProperties::GravityX, 2000, -2000, 50);
  multiChoices[1] = new UI::Multichoice("Gravity y-dimension", 0.35 * DemoUI::WindowWidth, 200.f, 80.f, 120.f,
  textureLoader.getTexture(UI::TextureName::UpArrow), textureLoader.getTexture(UI::TextureName::DownArrow), std::bind(&DemoWorld::setGravityY, std::placeholders::_1));
  multiChoices[1]->setScale(pe::PhysicsProperties::GravityY, 2000, -2000, 50);
  multiChoices[2] = new UI::Multichoice("Threads", 0.7 * DemoUI::WindowWidth, 10.f, 80.f, 120.f,
  textureLoader.getTexture(UI::TextureName::UpArrow), textureLoader.getTexture(UI::TextureName::DownArrow), std::bind(&pe::PhysicsWorld::setThreads, std::placeholders::_1));
  multiChoices[2]->setScale(static_cast<int32_t> (pe::PhysicsWorld::getThreads()), static_cast<int32_t> (std::thread::hardware_concurrency()), 1, 1);
  multiChoices[3] = new UI::Multichoice("Update period", 0.7 * DemoUI::WindowWidth, 200.f, 80.f, 120.f,
  textureLoader.getTexture(UI::TextureName::UpArrow), textureLoader.getTexture(UI::TextureName::DownArrow), std::bind(&pe::PhysicsWorld::setIterationAmount, std::placeholders::_1));
  multiChoices[3]->setScale(static_cast<int32_t> (pe::PhysicsWorld::getIterationAmount()), 100, 1, 5);
  multiChoices[4] = new UI::Multichoice("Density",  0.35 * DemoUI::WindowWidth, 390.f, 80.f, 120.f,
  textureLoader.getTexture(UI::TextureName::UpArrow), textureLoader.getTexture(UI::TextureName::DownArrow), std::bind(&DemoWorld::setObjectDensity, &demoWorld, std::placeholders::_1));
  multiChoices[4]->setScale(static_cast<int32_t> (DemoObject::DynamicObjectDensity * 10.f), 50, 0, 2);
  multiChoices[5] = new UI::Multichoice("Elasticity",  0.7 * DemoUI::WindowWidth, 390.f, 80.f, 120.f,
  textureLoader.getTexture(UI::TextureName::UpArrow), textureLoader.getTexture(UI::TextureName::DownArrow), std::bind(&DemoWorld::setObjectElasticity, &demoWorld, std::placeholders::_1));
  multiChoices[5]->setScale(static_cast<int32_t> (20.f * pe::PhysicsProperties::DefaultElasticity), 20, 0, 1);

  levelSelect = new UI::TextChoice(50.f, 10.f, "Demo level", DemoLevelLoader::LevelNames, DemoLevelLoader::StartLevelIndex,
  textureLoader.getTexture(UI::TextureName::UpArrow), textureLoader.getTexture(UI::TextureName::DownArrow));
}

// Restart current demo level
void DemoUI::restartSwitch() {
  demoWorld.loadDemoLevel(DemoLevelLoader::getLevelPath(levelSelect->getCurrentText().c_str()));
  // also elasticity ans density need to be reset (new objects created)
  demoWorld.setObjectElasticity(multiChoices[5]->getValue());
  demoWorld.setObjectDensity(multiChoices[4]->getValue());
}
