

import org.lwjgl.opengl.*;
import static org.lwjgl.opengl.GL11.*;

public class R {


	public static void main(String[] args) {
		
		try{
			LibraryLoader.load();
		}catch(Exception e){
			System.out.println("Damn it!");
		}
		
		Display.setTitle("Hello");
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0,800,0,600,-1,1);
		glMatrixMode(GL_MODELVIEW);

	}
}
