#include "graphics_FA.h"
#include "maths_FA.h"

int isRunning = 1;


FVec3 mouseDirection(FMat4 proj, FMat4 view)
{
    FVec3 res = {};
    
    FVec4 clipCoords = initFVec4(mouseState_FA.posX, mouseState_FA.posY, -1.0f, 1.0f);

    float projDet = detFMat4(proj);
    FMat4 invertedProjection = inverseFMat4(proj, projDet);
    FVec4 eyeCoords = mulFMat4ByFVec4(invertedProjection, clipCoords);
    eyeCoords.z = -1.0f;
    eyeCoords.w = 0.0f;

    float viewDet = detFMat4(view);
    FMat4 invertedView = inverseFMat4(view, viewDet);
    FVec4 worldCoords = mulFMat4ByFVec4(invertedView, eyeCoords);

    res = initFVec3(worldCoords.x, worldCoords.y, worldCoords.z);

    res = normalizeFVec3(res);


    //NOTE(Stanisz13): noticed that the sign of Y is wrong, dont know
    // if maybe this should be that way!
    res.y *= -1.0f;
    
    return res;
}

unsigned rayIntersectsBox(FVec3 origin, FVec3 dir, FMat4 model)
{
    model.col4.y *= -1.0f;

    float det = detFMat4(model);
    FMat4 modelInverse = inverseFMat4(model, det);
    
    FVec4 origin4 = mulFMat4ByFVec4(modelInverse, initFVec4(origin.x, origin.y, origin.z, 1.0f));
    FVec4 dir4 = mulFMat4ByFVec4(modelInverse, initFVec4(dir.x, dir.y, dir.z, 0.0f));

    
    origin = initFVec3(origin4.x, origin4.y, origin4.z);
    dir = initFVec3(dir4.x, dir4.y, dir4.z);

    int sign[3];
    FVec3 invDir = initFVec3(1.0f / dir.x, 1.0f / dir.y, 1.0f / dir.z);
    sign[0] = (invDir.x < 0);
    sign[1] = (invDir.y < 0);
    sign[2] = (invDir.z < 0);

    FVec3 bounds[2];
    bounds[0] = initFVec3(-0.5f, -0.5f, -0.5f);
    bounds[1] = initFVec3(0.5f, 0.5f, 0.5f);

        
    float tmin, tmax, tymin, tymax, tzmin, tzmax;

    tmin = (bounds[sign[0]].x - origin.x) * invDir.x;
    tmax = (bounds[1-sign[0]].x - origin.x) * invDir.x;
    tymin = (bounds[sign[1]].y - origin.y) * invDir.y;
    tymax = (bounds[1-sign[1]].y - origin.y) * invDir.y;

    if ((tmin > tymax) || (tymin > tmax))
        return 0;
    if (tymin > tmin)
        tmin = tymin;
    if (tymax < tmax)
        tmax = tymax;

    tzmin = (bounds[sign[2]].z - origin.z) * invDir.z;
    tzmax = (bounds[1-sign[2]].z - origin.z) * invDir.z;

    if ((tmin > tzmax) || (tzmin > tmax))
        return 0;
    if (tzmin > tmin)
        tmin = tzmin;
    if (tzmax < tmax)
        tmax = tzmax;

    return 1; 
}

FVec2 screenSpaceToNDC(FVec2 v)
{
    v.x *= 2;
    v.x -= contextData_FA.windowWidth;

    v.y *= 2;
    v.y -= contextData_FA.windowHeight;
    mouseState_FA.posY *= -1.0f;

    v.x /= contextData_FA.windowWidth;
    v.y /= contextData_FA.windowHeight;

    return v;
}

FVec2 NDCtoScreenSpace(FVec2 v)
{
    v.x *= contextData_FA.windowWidth / 2;
    v.x += contextData_FA.windowWidth / 2;
    v.y *= contextData_FA.windowHeight / 2;
    v.y += contextData_FA.windowHeight / 2;
    
    return v;
}

//NOTE(Stanisz13): Assumes, that v is in NDC.
FVec3 NDCtoHemisphere(FVec2 v)
{
    v = NDCtoScreenSpace(v);
    
    float R = 0.5f * minUnsigned(contextData_FA.windowWidth, contextData_FA.windowHeight);
    float RSquared = R * R;
    
    FVec2 o = initFVec2(0.5f * contextData_FA.windowWidth, 0.5f * contextData_FA.windowHeight); 
    float dTerm1 = v.x - o.x;
    float dTerm2 = v.y - o.y;
    float DSquared = dTerm1 * dTerm1 + dTerm2 * dTerm2;

    float z = 0.0f;

    if (DSquared < RSquared)
        z = sqrt(RSquared - DSquared);

    FVec3 res = initFVec3(v.x, v.y, z);
    return res;
}

int main(int argc, char* argv[])
{
    newLine();
    newLine();

    contextData_FA.minimalGLXVersionMajor = 1;
    contextData_FA.minimalGLXVersionMinor = 3;
    contextData_FA.minimalGLVersionMajor = 3;
    contextData_FA.minimalGLVersionMinor = 3;
    contextData_FA.windowWidth = 900;
    contextData_FA.windowHeight = 900;
    contextData_FA.name = "Faith";

    configureOpenGL();
    loadFunctionPointers();

    camera_FA.pos = initFVec3(0.0f, 0.0f, 4.0f);
    camera_FA.target = initFVec3(0.0f, 0.0f, 0.0f);
    camera_FA.zoomRangeMin = 0.0f;
    camera_FA.zoomRangeMax = 100.0f;

    mouseState_FA.sensitivity = 0.1f;
    
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    
    unsigned int VBO, VAO;
    glGenVertexArrays_FA(1, &VAO);
    glGenBuffers_FA(1, &VBO);

    glBindVertexArray_FA(VAO);

    glBindBuffer_FA(GL_ARRAY_BUFFER, VBO);
    glBufferData_FA(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer_FA(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray_FA(0);
    // texture coord attribute
    glVertexAttribPointer_FA(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray_FA(1);

    float aRatio = (float)contextData_FA.windowWidth / contextData_FA.windowHeight;


    unsigned tex;
    loadBMPtexture("img.bmp", &tex);

    int basic = createShaderProgram("shaders/basic.vs", "shaders/basic.fs");
    glUseProgram_FA(basic);

    glEnable(GL_DEPTH_TEST);


    unsigned modelLoc = glGetUniformLocation_FA(basic, "model");
    unsigned projLoc = glGetUniformLocation_FA(basic, "proj");
    unsigned viewLoc = glGetUniformLocation_FA(basic, "view");
    unsigned pickedLoc = glGetUniformLocation_FA(basic, "picked");

    FMat4 view = lookAt();
    FMat4 model = rotationFMat4(degreesToRadians(45.0f), initFVec3(1.0f, 1.0f, 1.0f));
    FMat4 proj = perspectiveFMat4(0.01f, 100.0f, aRatio, degreesToRadians(45.0f));
    

    glUniformMatrix4fv_FA(projLoc, 1, GL_FALSE, proj.mem);

#if 0
    disableVSyncIfPossible();
#else
    enableVSyncIfPossible();
#endif

    struct timespec prevTime;
    clock_gettime(CLOCK_MONOTONIC_RAW, &prevTime);
    float dt = 0.0f;
    float elapsed = 0.0f;
    float maxFrameTimeNoticed = 0.0f;

    unsigned mouseMovedAtLeastOnce = 0;
    unsigned mouseMovedThisFrame = 0;

    FVec3 prevHemisphere = {};
    
    while(1)
    {
        XEvent event;
        mouseState_FA.wheel = 0;

        while (XPending(contextData_FA.display))
        {
            XNextEvent(contextData_FA.display, &event);
            
            switch (event.type)
            {
                case ClientMessage:
                    if (event.xclient.data.l[0] == contextData_FA.deleteMessage)
                        isRunning = 0;
                    break;

                case KeymapNotify:
                    XRefreshKeyboardMapping(&event.xmapping);
                    break;
                    
                case ButtonPress:
                    switch(event.xbutton.button)
                    {
                        case Button1:
                            mouseState_FA.left = 1;
                            break;
                        case Button2:
                            mouseState_FA.middle = 1;
                            break;
                        case Button3:
                            mouseState_FA.right = 1;
                            break;
                        case Button4:
                            mouseState_FA.wheel = 1;
                            break;
                        case Button5:
                            mouseState_FA.wheel = -1;
                            break;
                    }
                    break;

                case ButtonRelease:
                    switch(event.xbutton.button)
                    {
                        case Button1:
                            mouseState_FA.left = 0;
                            break;
                        case Button2:
                            mouseState_FA.middle = 0;
                            break;
                        case Button3:
                            mouseState_FA.right = 0;
                            break;
                    }
                    break;

                case MotionNotify:
                    mouseState_FA.posX = event.xmotion.x;
                    mouseState_FA.posY = event.xmotion.y;
                    FVec2 pos = screenSpaceToNDC(initFVec2(mouseState_FA.posX, mouseState_FA.posY));
                    mouseState_FA.posX = pos.x;
                    mouseState_FA.posY = pos.y;
                    
                    if (mouseMovedAtLeastOnce == 0)
                        mouseMovedAtLeastOnce = 1;

                    mouseMovedThisFrame = 1;
                    
                    break;

                case KeyPress:
                    keysPressed_FA[event.xkey.keycode] = 1;
                    //logU(event.xkey.keycode);
                    break;
                    
                case KeyRelease:
                    keysPressed_FA[event.xkey.keycode] = 0;
                    break;
            }
        }

        if (keysPressed_FA[9] == 1 || isRunning == 0)
        {
            break;
        }


        FVec2 currentMousePos = initFVec2(mouseState_FA.posX, mouseState_FA.posY);
        FVec3 nowHemisphere = NDCtoHemisphere(currentMousePos);
        
        if (mouseState_FA.left == 1 && mouseMovedThisFrame == 1)
        {
            logS("nowHemi:");
            logF(nowHemisphere.x);
            logF(nowHemisphere.y);
            logF(nowHemisphere.z);
            newLine();

            logS("prevHemi:");
            logF(prevHemisphere.x);
            logF(prevHemisphere.y);
            logF(prevHemisphere.z);
            newLine();
                    
            float lengthProd = lengthFVec3(nowHemisphere) * lengthFVec3(prevHemisphere);
            if (lengthProd >= EPSILON)
            {
                float argument = dotProductFVec3(nowHemisphere, prevHemisphere) / lengthProd;
                logS("argument:");
                logF(argument);
                
                float angle = acos(argument);

                logS("Angle:");
                logF(angle);
                newLine();
            
                FVec3 axisOfRot = crossProductFVec3(nowHemisphere, prevHemisphere);

                if (lengthSquaredFVec3(axisOfRot) >= EPSILON)
                {
                    axisOfRot = normalizeFVec3(axisOfRot);
            
                    logS("axisOfRot:");
                    logF(axisOfRot.x);
                    logF(axisOfRot.y);
                    logF(axisOfRot.z);
                    newLine();
            
            
                    FMat4 rotationMat = rotationFMat4(angle * dt * mouseState_FA.sensitivity,
                                                      axisOfRot);

                    FVec4 cameraPos4 = initFVec4(camera_FA.pos.x, camera_FA.pos.y, camera_FA.pos.z, 0.0f);
                    cameraPos4 = mulFMat4ByFVec4(rotationMat, cameraPos4);
            
                    camera_FA.pos = initFVec3(cameraPos4.x, cameraPos4.y, cameraPos4.z);

                    view = lookAt();
                }

            }
        }
        
        prevHemisphere = nowHemisphere;
        
        if (mouseState_FA.wheel != 0)
        {
            if (mouseState_FA.wheel > 0)
            {
                if (camera_FA.pos.z > camera_FA.zoomRangeMin)
                {
                    camera_FA.pos.z -= (float)mouseState_FA.wheel/ 2.0f;
                }
            }
            else
            {
                if (camera_FA.pos.z < camera_FA.zoomRangeMax)
                {
                    camera_FA.pos.z -= (float)mouseState_FA.wheel/ 2.0f;
                }
            }
            
            view = lookAt();
        }
        
        model = mulFMat4(model, rotationFMat4(0.0001f * dt, initFVec3(0.0f, 0.0f, 1.0f)));

        if (mouseMovedAtLeastOnce == 1)
        {
            FVec3 mouseDir = mouseDirection(proj, view);
            unsigned intersects = rayIntersectsBox(camera_FA.pos, mouseDir, model);
            glUniform1i_FA(pickedLoc, (int)intersects);
        }
        
        glUniformMatrix4fv_FA(viewLoc, 1, GL_FALSE, view.mem);
        glUniformMatrix4fv_FA(modelLoc, 1, GL_FALSE, model.mem);    
        
        glClearColor(0, 0.5, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glXSwapBuffers(contextData_FA.display, contextData_FA.window);



        
        struct timespec nowTime;
        clock_gettime(CLOCK_MONOTONIC_RAW, &nowTime);
        dt = (nowTime.tv_sec - prevTime.tv_sec) * 1000000
            + (nowTime.tv_nsec - prevTime.tv_nsec) / 1000;
        dt /= 1000.0f;

        prevTime = nowTime;

        elapsed += dt;
        if (dt - maxFrameTimeNoticed > EPSILON)
        {
            maxFrameTimeNoticed = dt;
        }

#if 1
        if (elapsed > 2.0f * 1000)
        {
            printf("Longest frame: %f [%f FPS]\n", maxFrameTimeNoticed, 1000.0f / maxFrameTimeNoticed);
            elapsed = 0.0f;
            maxFrameTimeNoticed = 0.0f;
        }
#else
        printf("dt = %f [%f FPS]\n", dt, 1.0f/dt);
#endif
    }

    freeContextData();
    glDeleteBuffers_FA(1, &VBO);
    glDeleteVertexArrays_FA(1, &VAO);

    return 0;
}
