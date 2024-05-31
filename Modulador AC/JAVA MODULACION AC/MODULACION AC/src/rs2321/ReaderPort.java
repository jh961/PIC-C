package rs2321;

/*
 * ReaderPort.java
 *
 * 
 */
import java.io.*;
import javax.comm.*;
import java.util.*;
/**
 *
 * 
 */
    public class ReaderPort  implements Runnable, SerialPortEventListener {

        private static ReaderPort readerPort;
        private InputStream inputStream;
        private SerialPort serialPort;
        private Thread readThread;
        private String stringBuffer = "";
        private ArrayList listeners;

    /** Creates a new instance of ReaderPort */
    private ReaderPort(SerialPort serialPort) {
       

        this.serialPort = serialPort;
        
        try {
            inputStream = serialPort.getInputStream();
        } catch (IOException e) {}
	try {
            serialPort.addEventListener(this);
	} catch (TooManyListenersException e) {}
        serialPort.notifyOnDataAvailable(true);
        try {
            serialPort.setSerialPortParams(9600,
                SerialPort.DATABITS_8,
                SerialPort.STOPBITS_1,
                SerialPort.PARITY_NONE);
                
        } catch (UnsupportedCommOperationException e) {}
        readThread = new Thread(this);
        readThread.start();
    }
    
    public static ReaderPort getInstance()
    {
        if (readerPort != null )
            return readerPort;
        
        readerPort = new ReaderPort(CronusPort.getAbailablePort());
        return readerPort;
    }

    public void run() {
        try {
            Thread.sleep(2000);
        } catch (InterruptedException e) {}
    }

  
    
    
    public void serialEvent(SerialPortEvent event) {

        java.awt.event.ActionListener oyente;
        ActionEventPort actionEventPort;
        
        switch(event.getEventType()) {
        case SerialPortEvent.BI:
        case SerialPortEvent.OE:
        case SerialPortEvent.FE:
        case SerialPortEvent.PE:
        case SerialPortEvent.CD:
        case SerialPortEvent.CTS:
        case SerialPortEvent.DSR:
        case SerialPortEvent.RI:
        case SerialPortEvent.OUTPUT_BUFFER_EMPTY:
            break;
        case SerialPortEvent.DATA_AVAILABLE:
            byte[] readBuffer = new byte[50];
            String stringBuffer= "";
            try {
                while (inputStream.available() > 0) {
                    int numBytes = inputStream.read(readBuffer);
                    stringBuffer+= new String(readBuffer,0 ,numBytes );
                }
                actionEventPort = new ActionEventPort(this, 0, "Readed", stringBuffer );
                for (int i =0; i < this.listeners.size(); i++ )
                {
                    oyente = (java.awt.event.ActionListener)this.listeners.get(i);
                    oyente.actionPerformed(actionEventPort);
                }
                               
                
            } catch (IOException e) {}
            break;
        }
    }
    
    
    
    
    public void addActionListener(java.awt.event.ActionListener oyente)
    {
  
        if (this.listeners == null)
        {
            this.listeners = new ArrayList();
        }
        
        this.listeners.add(oyente); 
    }
    
  
}

