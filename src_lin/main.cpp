#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "cudaRaytracer.h"
#include "SceneDesc.h"
#include "FileParser.h"
#include "ColorImage.h"
#include "glRoutine.h"
#include "variables.h"

using namespace std;



const char* IOFILES[6][2] = {
    "scene4-ambient.test", "scene4-ambient.ppm",
    "scene4-specular.test", "scene4-specular.ppm",
    "scene4-emission.test", "scene4-emission.ppm",
    "scene4-diffuse.test", "scene4-diffuse.ppm",
    "scene-diffuse-boxlight.test", "scene-diffuse-boxlight.ppm" ,
    "scene7.test","scene7.test" 
};

RayTracer* cudaRayTracer = NULL;
unsigned int win_w, win_h;

int main( int argc, char* argv[] )
{
    SceneDesc theScene;
    ColorImage outputImage;
    FileParser::parse( IOFILES[4][0], theScene );

    outputImage.init( theScene.width, theScene.height );
    win_w = theScene.width;
    win_h = theScene.height;

    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL );

    glutInitContextVersion( 4, 0 );
    glutInitContextFlags( GLUT_FORWARD_COMPATIBLE );
    glutInitContextProfile( GLUT_CORE_PROFILE );

    glutInitWindowSize( theScene.width, theScene.height );
    glutCreateWindow( "GPU RayTracer" );

    GLenum errCode = glewInit();
    if( errCode != GLEW_OK )
    {
        cerr<<"Error: "<<glewGetErrorString(errCode)<<endl;
        return 1;
    }

    glutDisplayFunc( glut_display );
    glutReshapeFunc( glut_reshape );
    glutKeyboardFunc( glut_keyboard );
    glutIdleFunc( glut_idle );
    glutMainLoop();
    //cudaRayTracer = new CudaRayTracer();

    //
    //cudaRayTracer->renderImage( theScene, outputImage );

    //outputImage.outputPPM( IOFILES[4][1] );

    //delete cudaRayTracer;
    return 0;
}

