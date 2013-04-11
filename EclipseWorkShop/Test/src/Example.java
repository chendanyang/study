import static org.lwjgl.opengl.GL11.GL_COLOR_BUFFER_BIT;
import static org.lwjgl.opengl.GL11.GL_DEPTH_BUFFER_BIT;
import static org.lwjgl.opengl.GL11.GL_QUADS;
import static org.lwjgl.opengl.GL11.glBegin;
import static org.lwjgl.opengl.GL11.glClear;
import static org.lwjgl.opengl.GL11.glColor3f;
import static org.lwjgl.opengl.GL11.glEnd;
import static org.lwjgl.opengl.GL11.glVertex2f;

import org.lwjgl.opengl.Display;
import org.lwjgl.opengl.DisplayMode;


public class Example {
	float x =400;
	float y =350;
	float rotation =0.0f;
	
	long last_frame;
	int fps;
	long last_fps;
	
	public void start(){
		try{
			Display.setDisplayMode(new DisplayMode(800,600));
			Display.create();
		}catch(Exception e){
			System.out.println("Damn it!");
		}
		
		initGL();
		getDelta();
		last_fps = getTime();
		
		while(!Display.isCloseRequested()){
			glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
			glColor3f(1.0f,1.0f,0.0f);
			glBegin(GL_QUADS);
			{
				glVertex2f(100,100);
				glVertex2f(100+200,100);
				glVertex2f(100+200,100+200);
				glVertex2f(100,100+200);

			}
			glEnd();
			Display.update();
		}
		Display.destroy();
		System.exit(0);
	}
	
}
