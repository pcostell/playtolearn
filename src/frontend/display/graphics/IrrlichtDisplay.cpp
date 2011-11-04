
#include "IrrlichtDisplay.hpp"

#include <string>
#include <iostream>
#include <fstream>



using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

using namespace std;

using namespace PlayToLearn::Frontend;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

IrrlichtDisplay::IrrlichtDisplay() {
  device =
    createDevice( video::EDT_OPENGL, dimension2d<u32>(640, 480), 16,
      false, false, false, 0);

  if (!device) throw Error("Could not open device.");

  device->setWindowCaption(L"Hello World! - Irrlicht Engine Demo");
  driver = device->getVideoDriver();
  smgr = device->getSceneManager();
  guienv = device->getGUIEnvironment();



  guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
    rect<s32>(10,10,260,22), true);

  IAnimatedMesh* mesh = smgr->getMesh("media/sydney.md2");
  if (!mesh)
  {
    device->drop();
    throw Error("Could not load mesh.");
  }
  IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh );

  if (node)
  {
    node->setMaterialFlag(EMF_LIGHTING, false);
    node->setMD2Animation(scene::EMAT_STAND);
    node->setMaterialTexture( 0, driver->getTexture("media/sydney.bmp") );
  }

  smgr->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));
}

IrrlichtDisplay::~IrrlichtDisplay() {
  device->drop();
}

void IrrlichtDisplay::main_display_loop() {
  while(device->run())
  {
    driver->beginScene(true, true, SColor(255,100,101,140));

    smgr->drawAll();
    guienv->drawAll();

    driver->endScene();
  }
}