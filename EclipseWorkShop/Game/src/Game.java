import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

import javax.swing.JFrame;


public class Game extends JFrame implements Runnable{
	int x,y,xDir,yDir;
	private Image dbImage;
	private Graphics dbg;
	Image face;
	static Game game;
	MouseEvent Mouse;
	Thread t1;
	Font font = new Font("Arial",Font.BOLD|Font.ITALIC,30);
	public void run(){
		try{
			while(true){
				move();
				Thread.sleep(5);
			}
		}
		catch(Exception q){
			System.out.println("Error!");
		}
	}
	public void move(){
		x =Mouse.getX();
		y =Mouse.getY();
	}
	public void setXDir(int a){
		xDir =a;
	}
	public void setYDir(int a){
		yDir =a;
	}
	public class ML extends MouseAdapter{
		public void mousePressed(MouseEvent e){
			Mouse = (MouseEvent)e;
			t1 = new Thread(game);
			t1.start();
		}
		@SuppressWarnings("deprecation")
		public void mouseReleased(MouseEvent e){
			t1.stop();
			
		}
	}
	public class AL extends KeyAdapter{
		public void keyPressed(KeyEvent e){
			int keyCode = e.getKeyCode();
			if(keyCode == e.VK_UP){
				setYDir(-1);
			}
			if(keyCode == e.VK_DOWN){
				setYDir(+1);
			}
			if(keyCode == e.VK_LEFT){
				setXDir(-1);
			}
			if(keyCode == e.VK_RIGHT){
				setXDir(+1);
			}
		}
		public void keyReleased(KeyEvent e){
			int keyCode = e.getKeyCode();
			if(keyCode == e.VK_UP){
				setYDir(0);
			}
			if(keyCode == e.VK_DOWN){
				setYDir(0);
			}
			if(keyCode == e.VK_LEFT){
				setXDir(0);
			}
			if(keyCode == e.VK_RIGHT){
				setXDir(0);
			}
		}
	}
	public Game(){
		//Load images
		//ImageIcon i = new ImageIcon("C:/Users/weicheng/Desktop/Game/bin/face.gif");
		//face = i.getImage();
		//game properties
		addKeyListener(new AL());
		addMouseListener(new ML());
		setTitle("MY FIRST GAME");
		setSize(250,250);
		setResizable(false);
		setVisible(true);
		setBackground(Color.CYAN);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		x = 150;
		y = 150;
	}
	public void paint(Graphics g){
		dbImage = createImage(getWidth(),getHeight());
		dbg = dbImage.getGraphics();
		paintComponent(dbg);
		g.drawImage(dbImage, 0, 0, this);
		
	}
	public void paintComponent(Graphics g){
		g.setFont(font);
		g.setColor(Color.GRAY);
		g.drawString("Hello World!", 50, 50);
		g.setColor(Color.red);
		g.fillOval(x, y, 10, 10);
		//g.drawImage(face,x,y,this);
		repaint();
	}
	public static void main(String[] args) {
		game = new Game();


	}

}
