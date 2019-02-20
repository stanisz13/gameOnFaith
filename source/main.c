#include "graphics_FA.h"
#include "maths_FA.h"

int isRunning = 1;

void logFMat4(FMat4 m)
{
    printf("%f %f %f %f\n", m.col1.x, m.col2.x, m.col3.x, m.col4.x);
    printf("%f %f %f %f\n", m.col1.y, m.col2.y, m.col3.y, m.col4.y);
    printf("%f %f %f %f\n", m.col1.z, m.col2.z, m.col3.z, m.col4.z);
    printf("%f %f %f %f\n", m.col1.w, m.col2.w, m.col3.w, m.col4.w);

    newLine();
}

FVec3 mouseDirection(FMat4 proj, FMat4 view)
{
    FVec3 res = {};

#if 0    
    mouseState_FA.posX = 0.182222f;
    mouseState_FA.posY = -0.32f;
    #endif
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


    logFMat4(proj);
    logFMat4(invertedProjection);
    logFMat4(view);
    logFMat4(invertedView);

    
    printf("%f %f %f\n", res.x, res.y, res.z);
    
    
    return res;
}

unsigned rayIntersectsBox(FVec3 origin, FVec3 dir, FMat4 model)
{
    float detModel = detFMat4(model);
    FMat4 modelInverse = inverseFMat4(model, detModel);
    
    FVec4 origin4 = mulFMat4ByFVec4(modelInverse, initFVec4(origin.x, origin.y, origin.z, 1.0f));
    FVec4 dir4 = mulFMat4ByFVec4(modelInverse, initFVec4(dir.x, dir.y, dir.z, 1.0f));

    origin = initFVec3(origin4.x, origin4.y, origin4.z);
    dir = initFVec3(dir4.x, dir4.y, dir4.z);


#if 1
    int sign[3];

    FVec3 invDir = {};
    if (fabs(dir.x) > 0.0f)
        invDir.x = 1.0f / dir.x;
    if (fabs(dir.y) > 0.0f)
        invDir.y = 1.0f / dir.y;
    if (fabs(dir.z) > 0.0f)
        invDir.z = 1.0f / dir.z;

    sign[0] = (invDir.x < 0.0f);
    sign[1] = (invDir.y < 0.0f);
    sign[2] = (invDir.z < 0.0f);

    printf("%i %i %i\n", sign[0], sign[1], sign[2]);

    FVec3 bounds[2];
    bounds[0] = initFVec3(-0.5f, -0.5f, -0.5f);
    bounds[1] = initFVec3(0.5f, 0.5f, 0.5f);

        
    float tmin, tmax, tymin, tymax, tzmin, tzmax;

    tmin = (bounds[sign[0]].x - origin.x) * invDir.x;
    tmax = (bounds[1-sign[0]].x - origin.x) * invDir.x;
    tymin = (bounds[sign[1]].y - origin.y) * invDir.y;
    tymax = (bounds[1-sign[1]].y - origin.y) * invDir.y;

    printf("%f %f %f %f\n", tmin, tmax, tymin, tymax);
    
    if ((tmin > tymax) || (tymin > tmax))
        return 0;
    if (tymin > tmin)
        tmin = tymin;
    if (tymax < tmax)
        tmax = tymax;

    tzmin = (bounds[sign[2]].z - origin.z) * invDir.z;
    tzmax = (bounds[1-sign[2]].z - origin.z) * invDir.z;

    printf("%f %f %f %f\n", tmin, tmax, tymin, tymax);
 
    if ((tmin > tzmax) || (tzmin > tmax))
        return 0;
    if (tzmin > tmin)
        tmin = tzmin;
    if (tzmax < tmax)
        tmax = tzmax;

    return 1; 
#endif

#if 0
    float ii, ij, ik;
    ii = 1.0f / dir.x;
    ij = 1.0f / dir.y;
    ik = 1.0f / dir.z;
    
    float sxy, syx, szy, syz, sxz, szx;
    
    syx = dir.x * ij;
    sxy = dir.y * ii;
    szy = dir.y * ik;
    syz = dir.z * ij;
    sxz = dir.x * ik;
    szx = dir.z * ii;

    float cxy, cyx, czy, cyz, cxz, czx;
    
    cxy = origin.y - sxy * origin.x;
    cyx = origin.x - syx * origin.y;
    czy = origin.y - szy * origin.z;
    cyz = origin.z - syz * origin.y;
    cxz = origin.z - sxz * origin.x;
    czx = origin.x - szx * origin.z;

    FVec3 bounds[2];
    bounds[0] = initFVec3(-0.5f, -0.5f, -0.5f);
    bounds[1] = initFVec3(0.5f, 0.5f, 0.5f);

    if ((origin.x > bounds[1].x) || (origin.y > bounds[1].y) || (origin.z > bounds[1].y)
        || (sxy * bounds[1].x - bounds[0].y + cxy < 0)
        || (syx * bounds[1].y - bounds[0].x + cyx < 0)
        || (szy * bounds[1].z - bounds[0].y + czy < 0)
        || (syz * bounds[1].y - bounds[0].z + cyz < 0)
        || (sxz * bounds[1].x - bounds[0].z + cxz < 0)
        || (szx * bounds[1].z - bounds[0].x + czx < 0))
    {
        return 0;
    }
        
    return 1;

#endif
#if 0
    float infinity = 100000.0f;
    double tmin = -infinity, tmax = infinity;

    FVec3 bounds[2];
    bounds[0] = initFVec3(-0.5f, -0.5f, -0.5f);
    bounds[1] = initFVec3(0.5f, 0.5f, 0.5f);

    FVec3 invDir = {};
    if (absFloat(dir.x) > 0.0f)
        invDir.x = 1.0f / dir.x;
    if (absFloat(dir.y) > 0.0f)
        invDir.y = 1.0f / dir.y;
    if (absFloat(dir.z) > 0.0f)
        invDir.z = 1.0f / dir.z;

    
    for (int i = 0; i < 3; ++i)
    {
        double t1 = (bounds[0].mem[i] - origin.mem[i])*invDir.mem[i];
        double t2 = (bounds[1].mem[i] - origin.mem[i])*invDir.mem[i];

        tmin = fmax(tmin, fmin(fmin(t1, t2), tmax));
        tmax = fmin(tmax, fmax(fmax(t1, t2), tmin));
    }

    return ((int)tmax > maxFloat(tmin, 0.0f));

#endif
#if 0
    FVec3 bounds[2];
    bounds[0] = initFVec3(-0.5f, -0.5f, -0.5f);
    bounds[1] = initFVec3(0.5f, 0.5f, 0.5f);

    FVec3 invDir = {};
    if (fabs(dir.x) > 0.0f)
        invDir.x = 1.0f / dir.x;
    if (fabs(dir.y) > 0.0f)
        invDir.y = 1.0f / dir.y;
    if (fabs(dir.z) > 0.0f)
        invDir.z = 1.0f / dir.z;

    
    float t[10];
    t[1] = (bounds[0].x - origin.x) * invDir.x;
    t[2] = (bounds[1].x - origin.x) * invDir.x;
    t[3] = (bounds[0].y - origin.y) * invDir.y;
    t[4] = (bounds[1].y - origin.y) * invDir.y;
    t[5] = (bounds[0].z - origin.z) * invDir.z;
    t[6] = (bounds[1].z - origin.z) * invDir.z;
    t[7] = fmax(fmax(fmin(t[1], t[2]), fmin(t[3], t[4])), fmin(t[5], t[6]));
    t[8] = fmin(fmin(fmax(t[1], t[2]), fmax(t[3], t[4])), fmax(t[5], t[6]));
    t[9] = (t[8] < 0 || t[7] > t[8]) ? 100000.0f : t[7];
    return t[9];

#endif
#if 0
    FVec3 bounds[2];
    bounds[0] = initFVec3(-0.5f, -0.5f, -0.5f);
    bounds[1] = initFVec3(0.5f, 0.5f, 0.5f);

    FVec3 invDir = {};
    invDir.x = 1.0f / dir.x;
    invDir.y = 1.0f / dir.y;
    invDir.z = 1.0f / dir.z;

    double t1 = (bounds[0].x - origin.x)*invDir.x;
    double t2 = (bounds[1].x - origin.x)*invDir.x;
 
    double tmin = fmin(t1, t2);
    double tmax = fmax(t1, t2);
 
    for (int i = 1; i < 3; ++i) {
        t1 = (bounds[0].mem[i] - origin.mem[i])*invDir.mem[i];
        t2 = (bounds[1].mem[i] - origin.mem[i])*invDir.mem[i];
 
        tmin = fmax(tmin, fmin(t1, t2));
        tmax = fmin(tmax, fmax(t1, t2));
    }
 
    return (tmax > fmax(tmin, 0.0));

#endif
#if 0
    float tmin, tmax, tymin, tymax, tzmin, tzmax;

    FVec3 parameters[2];
    parameters[0] = initFVec3(-0.5f, -0.5f, -0.5f);
    parameters[1] = initFVec3(0.5f, 0.5f, 0.5f);

    float t0 = 0.01f;
    float t1 = 1000.0f;

    FVec3 inv_direction = initFVec3(1.0f/dir.x, 1.0f/dir.y, 1.0f/dir.z);
    int sign[3];
    sign[0] = (inv_direction.x < 0);
    sign[1] = (inv_direction.y < 0);
    sign[2] = (inv_direction.z < 0);
    
    tmin = (parameters[sign[0]].x - origin.x) * inv_direction.x;
    tmax = (parameters[1-sign[0]].x - origin.x) * inv_direction.x;
    tymin = (parameters[sign[1]].y - origin.y) * inv_direction.y;
    tymax = (parameters[1-sign[1]].y - origin.y) * inv_direction.y;
    if ( (tmin > tymax) || (tymin > tmax) ) 
        return 0;
    if (tymin > tmin)
        tmin = tymin;
    if (tymax < tmax)
        tmax = tymax;
    tzmin = (parameters[sign[2]].z - origin.z) * inv_direction.z;
    tzmax = (parameters[1-sign[2]].z - origin.z) * inv_direction.z;
    if ( (tmin > tzmax) || (tzmin > tmax) ) 
        return 0;
    if (tzmin > tmin)
        tmin = tzmin;
    if (tzmax < tmax)
        tmax = tzmax;
    return ( (tmin < t1) && (tmax > t0) );    
#endif
#if 0
    float tmin, tmax, tymin, tymax, tzmin, tzmax;
    FVec3 bounds[2];
    bounds[0] = initFVec3(-0.5f, -0.5f, -0.5f);
    bounds[1] = initFVec3(0.5f, 0.5f, 0.5f);

    FVec3 invdir = initFVec3(1.0f/dir.x, 1.0f/dir.y, 1.0f/dir.z);
    IVec3 sign;
    sign.x = (invdir.x < 0);
    sign.y = (invdir.y < 0);
    sign.z = (invdir.z < 0);

    tmin = (bounds[sign.x].x - origin.x) * invdir.x;
    tmax = (bounds[1 - sign.x].x - origin.x) * invdir.x;
    tymin = (bounds[sign.y].y - origin.y) * invdir.y;
    tymax = (bounds[1 - sign.y].y - origin.y) * invdir.y;

    if ((tmin > tymax) || (tymin > tmax))
        return 0;
    if (tymin > tmin)
        tmin = tymin;
    if (tymax < tmax)
        tmax = tymax;

    tzmin = (bounds[sign.z].z - origin.z) * invdir.z;
    tzmax = (bounds[1 - sign.z].z - origin.z) * invdir.z;

    if ((tmin > tzmax) || (tzmin > tmax))
        return 0;
    if (tzmin > tmin)
        tmin = tzmin;
    if (tzmax < tmax)
        tmax = tzmax;

    return 1;
#endif
}

FVec2 screenSpaceToNDC(FVec2 v)
{
    v.x *= 2;
    v.x -= contextData_FA.windowWidth;

    v.y *= 2;
    v.y -= contextData_FA.windowHeight;
    v.y *= -1.0f;
    
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

    camera_FA.pos = initFVec3(1.0f, 2.0f, 5.0f);
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
    FMat4 model = identityFMat4();//rotationFMat4(degreesToRadians(45.0f), initFVec3(1.0f, 1.0f, 1.0f));
    FMat4 proj = perspectiveFMat4(0.1f, 100.0f, aRatio, degreesToRadians(45.0f));
    
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
    float totalElapsedTime = 0.0f;
    
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
        int win_x, win_y, root_x, root_y = 0;
        unsigned int mask = 0;
        Window child_win, root_win;

        printf("ASDbASJBDKA %i %i | %i %i \n\n\n", root_x, root_y, win_x, win_y);

        FVec2 poss = screenSpaceToNDC(initFVec2(win_x, win_y));
//        if (mouseState_FA.posY > 0)
        //         mouseState_FA.posY *= -1.0f;
        printf("ASDbASJBDKA %f %f \n\n\n", mouseState_FA.posX, mouseState_FA.posY);
        
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

                float angle = 0.01f;//acos(argument);
                
                logS("Angle:");
                logF(angle);
                newLine();
            
                FVec3 axisOfRot = crossProductFVec3(prevHemisphere, nowHemisphere);

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
                    logS("cameraDist:");
                    logF(lengthFVec3(camera_FA.pos));
                    newLine();
                    
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
        }
        
        //model = mulFMat4(model, rotationFMat4(0.0001f * dt, initFVec3(0.0f, 0.0f, 1.0f)));
        view = lookAt();
        
        
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
        totalElapsedTime += dt;
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
