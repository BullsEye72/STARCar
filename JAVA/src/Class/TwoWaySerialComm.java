package Class;

import gnu.io.CommPort;
import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Administrateur
 */
public class TwoWaySerialComm {
    
    public static SerialPort serial; 
    
    public TwoWaySerialComm() {
        super();
    }

    void connect(SerialPort serialPort) {        

        serial = serialPort;
        
        InputStream in;
        try {
            in = serialPort.getInputStream();
            (new Thread(new SerialReader(in))).start();
        } catch (IOException ex) {
            Logger.getLogger(TwoWaySerialComm.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    /**
     *      */
    public static class SerialReader implements Runnable {

        InputStream in;

        public SerialReader(InputStream in) {
            this.in = in;
        }

        public void run() {
            byte[] buffer = new byte[1024];
            int len = -1;
            try {
                while ((len = this.in.read(buffer)) > -1) {
                                        
                    OutputStream out = serial.getOutputStream();                                                            
                    out.write("rpm".getBytes());
                    out.close();                    
                    
                    String response = new String(buffer, 0, len);
                   
                    
                    if(!response.equals("")){
                        LiaisonJavaC.majCompteTour(Integer.parseInt(response));
                    }
                    
                    try {
                        Thread.sleep(64);
                    } catch (InterruptedException ex) {
                        Logger.getLogger(TwoWaySerialComm.class.getName()).log(Level.SEVERE, null, ex);
                    }
                    
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    /**
     *      */
    public static class SerialWriter implements Runnable {

        OutputStream out;

        public SerialWriter(OutputStream out) {
            this.out = out;
        }

        public void run() {
            try {
                int c = 0;
                while ((c = System.in.read()) > -1) {
                    this.out.write(c);
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
