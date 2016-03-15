#ifndef JK_SCENE_H
#define JK_SCENE_H

namespace JK_OPENGL
{
	class JK_Scene
	{
	public:
		Scene() : m_animate(true) { }
	
		/**
		  Load textures, initialize shaders, etc.
		  */
		virtual void initScene() = 0;

		/**
		  This is called prior to every frame.  Use this
		  to update your animation.
		  */
		virtual void update( float t ) = 0;

		/**
		  Draw your scene.
		  */
		virtual void render() = 0;

		/**
		  Called when screen is resized
		  */
		virtual void resize(int, int) = 0;
    
		void animate( bool value ) { m_animate = value; }
		bool animating() { return m_animate; }
    
	protected:
		bool m_animate;
	};

}

#endif // SCENE_H



