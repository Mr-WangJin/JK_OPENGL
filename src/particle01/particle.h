#ifndef PARTICLE01_H
#define PARTICLE01_H


#include "../common/jk_scene.h"

class Particle : public JK_OPENGL::JK_Scene
{
public:
	Particle();
	~Particle();

	virtual void initScene();
	virtual void update( float t );
	virtual void render();
	virtual void resize(int, int);

protected:


};

#endif
