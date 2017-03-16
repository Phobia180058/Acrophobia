package ServerSockets;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class Server {

public static void main(String[] args) throws IOException {
	   ServerSocket ss = new ServerSocket(9090);      //创建服务器监听socket
	   System.out.println("ServerSocket create");        
       System.out.println("Server starts");
       while(true){                                   //循环监听端口
           Socket socket = ss.accept();               //收到连接创建socket来实现连接
           Sock sock = new Sock();                    
           sock.setSocket(socket);                    
           sock.start();
           System.out.println("New client connects");
       }
   } 	
}
