//------------------------------------------------------------------------------
//  Copyright (c) 2018-2019 Michele Morrone
//  All rights reserved.
//
//  https://michelemorrone.eu - https://BrutPitt.com
//
//  twitter: https://twitter.com/BrutPitt - github: https://github.com/BrutPitt
//
//  mailto:brutpitt@gmail.com - mailto:me@michelemorrone.eu
//  
//  This software is distributed under the terms of the BSD 2-Clause license
//------------------------------------------------------------------------------
#include "qJulia.h"

#include "glWindow.h"



///////////////////////////////////////////////////////////////////////////////
// UNCOMMENT for screen manipulato virtualGizmo3D 
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// if you want use also the virtualGizmo3D, screen manipulator, uncomment this:

#define GLAPP_USE_VIRTUALGIZMO

// Global variable or member class
#ifdef GLAPP_USE_VIRTUALGIZMO 
    vfGizmo3DClass gizmo; 
    vfGizmo3DClass &getGizmo() { return gizmo; }

    void setRotation(const glm::quat &q) { getGizmo().setRotation(q); }
    glm::quat& getRotation() { return getGizmo().getRotation(); }
#else
/////////////////////////////////////////////////////////////////////////////
// For imGuIZMO, declare global variable or member class quaternion
    glm::quat qRot = glm::quat(1.f, 0.f, 0.f, 0.f);

/////////////////////////////////////////////////////////////////////////////
// two helper functions, not really necessary (but comfortable)
    void setRotation(const glm::quat &q) { qRot = q; }
    glm::quat& getRotation() { return qRot; }
#endif


using namespace glm;

void setView()
{

    vec3 povVec( 0.f, 0, 7.f);
    vec3 tgtVec( 0.f, 0, 0.f);


    theWnd->projectionMatrix = glm::perspective(glm::radians(30.0f),(float)theApp->GetWidth()/(float)theApp->GetHeight(),0.0f,30.0f);
    theWnd->modelMatrix      = glm::mat4(1.0f);
    theWnd->viewMatrix       = glm::lookAt( povVec,
                                            tgtVec,
                                            vec3(0.0f, 1.0f, 0.0f));
#ifdef GLAPP_USE_VIRTUALGIZMO 
    getGizmo().applyTransform(theWnd->modelMatrix);
#endif

    theWnd->mvMatrix         = theWnd->viewMatrix * theWnd->modelMatrix;
    theWnd->mvpMatrix        = theWnd->projectionMatrix * theWnd->mvMatrix;
   
}


void setViewOrtho()
{

    theWnd->projectionMatrix = glm::ortho(-1.0, 1.0, -1.0, 1.0, -2.0, 2.0);
    theWnd->modelMatrix      = glm::mat4(1.0f);
    theWnd->viewMatrix       = glm::lookAt( vec3(0.f, 0.f, 1.f),
                                            vec3(0.f, 0.f, 0.f),
                                            vec3(0.f, 1.f, 0.f));

    theWnd->mvpMatrix        = theWnd->projectionMatrix * theWnd->viewMatrix * theWnd->modelMatrix;

}



void glWindow::Create(const char *wTitle, int w, int h, int xPos, int yPos)
{

}

glWindow::glWindow()
{
    

}


glWindow::~glWindow()
{

}



//
/////////////////////////////////////////////////
void glWindow::onInit()
{

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Black Background

    glViewport(0,0,theApp->GetWidth(), theApp->GetHeight());

#ifdef GLAPP_USE_VIRTUALGIZMO 
#ifdef GLAPP_USE_SDL
    getGizmo().setGizmoRotControl( (vgButtons) SDL_BUTTON_LEFT, (vgModifiers) 0 /* evNoModifier */ );

    getGizmo().setGizmoRotXControl((vgButtons) SDL_BUTTON_LEFT, (vgModifiers) KMOD_SHIFT);
    getGizmo().setGizmoRotYControl((vgButtons) SDL_BUTTON_LEFT, (vgModifiers) KMOD_CTRL);
    getGizmo().setGizmoRotZControl((vgButtons) SDL_BUTTON_LEFT, (vgModifiers) KMOD_ALT);

    getGizmo().setDollyControl((vgButtons) SDL_BUTTON_RIGHT, (vgModifiers) 0);
    getGizmo().setPanControl(  (vgButtons) SDL_BUTTON_RIGHT, (vgModifiers) KMOD_CTRL|KMOD_SHIFT);
#else
    getGizmo().setGizmoRotControl( (vgButtons) GLFW_MOUSE_BUTTON_LEFT, (vgModifiers) 0 /* evNoModifier */ );

    getGizmo().setGizmoRotXControl((vgButtons) GLFW_MOUSE_BUTTON_LEFT, (vgModifiers) GLFW_MOD_SHIFT);
    getGizmo().setGizmoRotYControl((vgButtons) GLFW_MOUSE_BUTTON_LEFT, (vgModifiers) GLFW_MOD_CONTROL);
    getGizmo().setGizmoRotZControl((vgButtons) GLFW_MOUSE_BUTTON_LEFT, (vgModifiers) GLFW_MOD_ALT | GLFW_MOD_SUPER);

    getGizmo().setDollyControl((vgButtons) GLFW_MOUSE_BUTTON_RIGHT, (vgModifiers) 0);
    getGizmo().setPanControl(  (vgButtons) GLFW_MOUSE_BUTTON_RIGHT, (vgModifiers) GLFW_MOD_CONTROL|GLFW_MOD_SHIFT);
#endif
    //getGizmo().setPanControls(  (vgButtons) GLFW_MOUSE_BUTTON_RIGHT, (vgModifiers) GLFW_MOD_SHIFT);

    // viewportSize  is need to set mouse sensitivity for rotation
    // You nedd to call it in your "reshape" function: when resize the window
    // look below
    getGizmo().viewportSize(theApp->GetWidth(), theApp->GetHeight());

    // If you need to more feeling with the mouse use:
    // getGizmo().setGizmoFeeling(1.0);
    // 1.0 default,  > 1.0 more sensible, < 1.0 less sensible
    

    // other settings if you need it
    /////////////////////////////////////////////
    getGizmo().setDollyScale(.001f);
    getGizmo().setDollyPosition(1.0f);
    //getGizmo().setRotationCenter(vec3(0.0));
#endif
    qjSet = new qJulia;

}



//
/////////////////////////////////////////////////
void glWindow::onExit()
{
    delete qjSet;
    
}

//
/////////////////////////////////////////////////
void glWindow::onRender()
{
    glViewport(0,0,theApp->GetWidth(), theApp->GetHeight());
    glClear(GL_COLOR_BUFFER_BIT);

#ifdef GLAPP_USE_VIRTUALGIZMO 
    float zoom = getGizmo().getDollyPosition().z;
/*
    if(zoom < .9)       { zoom =.9;   getGizmo().setDollyPosition(zoom); }
    else if (zoom>1.5)  { zoom = 1.5; getGizmo().setDollyPosition(zoom); }
*/
    qjSet->matOrientation = getGizmo().getTransform() * zoom;
#else
////////////////////////////////////////////////////////////////////
// imGuIZMO: get quaternion in to orientation Matrix

    glm::mat4 modelMatrix = glm::mat4_cast(qRot);
    qjSet->matOrientation = modelMatrix;

#endif
    qjSet->render(); 
}



//
/////////////////////////////////////////////////
void glWindow::onIdle()
{
#ifdef GLAPP_USE_VIRTUALGIZMO 
    getGizmo().idle();
#endif
}


//
/////////////////////////////////////////////////
void glWindow::onReshape(GLint w, GLint h)
{
    glViewport(0,0,w,h);
    theApp->SetWidth(w); theApp->SetHeight(h);
    printf("w: %d, h: %d\n", w,h);

#ifdef GLAPP_USE_VIRTUALGIZMO 
    getGizmo().viewportSize(w, h);
#endif
}

//
/////////////////////////////////////////////////
void glWindow::onKeyUp(unsigned char key, int x, int y)
{

}


//
/////////////////////////////////////////////////
void glWindow::onSpecialKeyDown(int key, int x, int y)
{


}


//
/////////////////////////////////////////////////
void glWindow::onKeyDown(unsigned char key, int x, int y)
{



}



//
/////////////////////////////////////////////////
void glWindow::onSpecialKeyUp(int key, int x, int y)
{



}


//
/////////////////////////////////////////////////
void glWindow::onMouseButton(int button, int upOrDown, int x, int y)
{

#ifdef GLAPP_USE_VIRTUALGIZMO 
    getGizmo().mouse((vgButtons) (button),
                    (vgModifiers) theApp->getModifier(),
#ifdef GLAPP_USE_SDL
                    upOrDown==SDL_MOUSEBUTTONDOWN, x, y);
#else
                    upOrDown==GLFW_PRESS, x, y);
#endif
#endif

}

//
/////////////////////////////////////////////////
void glWindow::onMouseWheel(int wheel, int direction, int x, int y)
{

}

//
/////////////////////////////////////////////////
void glWindow::onMotion(int x, int y)
{
#ifdef GLAPP_USE_VIRTUALGIZMO 
    getGizmo().motion(x, y);
#endif

    //qjSet->matOrientation *= trackball.getDollyPosition();
    
}

//
/////////////////////////////////////////////////
void glWindow::onPassiveMotion(int x, int y)
{

}
