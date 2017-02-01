package Class;

import java.io.*;
import java.util.*;

import gnu.io.*;

public class SerialCommunicationCodeurQuantic implements SerialPortEventListener {

    static CommPortIdentifier portId;
    static CommPortIdentifier saveportId;
    static Enumeration portList;
    InputStream inputStream;
    SerialPort serialPort;

    private OutputStream outputStream;
    private boolean outputBufferEmptyFlag = false;

    SerialCommunicationCodeurQuantic() {
       
        boolean portFound = false;
        String defaultPort;
        
        // determine the name of the serial port on several operating systems
        String osname = System.getProperty("os.name", "").toLowerCase();
        if (osname.startsWith("windows")) {
            // windows
            defaultPort = "COM4"; // TODO
        } else {
            System.out.println("Sorry, your operating system is not supported");
            return;
        }
        
        System.out.println("Set default port to " + defaultPort);

        // parse ports and if the default port is found, initialized the reader
        portList = CommPortIdentifier.getPortIdentifiers();
        while (portList.hasMoreElements()) {
            portId = (CommPortIdentifier) portList.nextElement();
            if (portId.getPortType() == CommPortIdentifier.PORT_SERIAL) {
                if (portId.getName().equals(defaultPort)) {
                    System.out.println("Found port: " + defaultPort);
                    portFound = true;
                    // init reader thread
                }
            }
        }
        if (!portFound) {
            System.out.println("port " + defaultPort + " not found.");
        }
    }

    public void initwritetoport() {
        // initwritetoport() assumes that the port has already been opened and
        //    initialized by "public SerialCommunicationCodeurQuantic()"

        try {
            // get the outputstream
            outputStream = serialPort.getOutputStream();
        } catch (IOException e) {
        }

        try {
            // activate the OUTPUT_BUFFER_EMPTY notifier
            serialPort.notifyOnOutputEmpty(true);
        } catch (Exception e) {
            System.out.println("Error setting event notification");
            System.out.println(e.toString());
            System.exit(-1);
        }

    }

    public void writetoport(String message) {
        //System.out.println("Writing \"" + messageString + "\" to " + serialPort.getName());
        try {
            // write string to serial port
            outputStream.write(message.getBytes());
            outputStream.close();

        } catch (IOException e) {
        }
    }

    public void initSerialPort() throws Exception {
        // initalize serial port
        try {
            serialPort = (SerialPort) portId.open("SimpleReadApp", 2000);
        } catch (PortInUseException e) {
        }

        try {
            inputStream = serialPort.getInputStream();
        } catch (IOException e) {
        }

        try {
            serialPort.addEventListener(this);
        } catch (TooManyListenersException e) {
        }

        // activate the DATA_AVAILABLE notifier
        serialPort.notifyOnDataAvailable(true);

        try {
            // set port parameters
            serialPort.setSerialPortParams(9600, SerialPort.DATABITS_8,
                    SerialPort.STOPBITS_1,
                    SerialPort.PARITY_NONE);
        } catch (UnsupportedCommOperationException e) {
        }
        
        TwoWaySerialComm read = new TwoWaySerialComm();
        
        read.connect(serialPort);
    }

    public void serialEvent(SerialPortEvent event) {
        
        System.out.println(".............." + event.getEventType());
        
        switch (event.getEventType()) {
            case SerialPortEvent.BI:
                System.out.println("BI");
            case SerialPortEvent.OE:
                System.out.println("OE");
            case SerialPortEvent.FE:
                System.out.println("FE");
            case SerialPortEvent.PE:
                System.out.println("PE");
            case SerialPortEvent.CD:
                System.out.println("CD");
            case SerialPortEvent.CTS:
                System.out.println("CTS");
            case SerialPortEvent.DSR:
                System.out.println("DSR");
            case SerialPortEvent.RI:
                System.out.println("RI");
            case SerialPortEvent.OUTPUT_BUFFER_EMPTY:
                System.out.println("OUTPUT_BUFFER_EMPTY");
                break;
            case SerialPortEvent.DATA_AVAILABLE:
                // we get here if data has been received
                byte[] readBuffer = new byte[20];
                try {
                    // read data
                    while (inputStream.available() > 0) {
                        int numBytes = inputStream.read(readBuffer);
                    }
                    // print data
                    String result = new String(readBuffer);
                    System.out.println("Read: " + result);
                } catch (IOException e) {
                }

                break;
        }
    }
}