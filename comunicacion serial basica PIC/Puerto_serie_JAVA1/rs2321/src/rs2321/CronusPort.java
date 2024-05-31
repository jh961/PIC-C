package rs2321;

/*
 * CronusPort.java
 *
 * 
 */

import javax.comm.*;
import java.util.*;
/**
 *
 * 
 */
public class CronusPort {
    
    private static SerialPort serialPort;
    /** Creates a new instance of CronusPort */
    /*public CronusPort() {
    }
    */
    public static SerialPort getAbailablePort()
    {
        System.out.println("Cronus Port : Modo de verificacion");

        if (serialPort != null)
            return serialPort;
        CommPortIdentifier portId;
        Enumeration portList;
        portList = CommPortIdentifier.getPortIdentifiers();
        System.out.println("verificacion nombre");
        
        while (portList.hasMoreElements()) {
            
            portId = (CommPortIdentifier) portList.nextElement();
            if (portId.getPortType() == CommPortIdentifier.PORT_SERIAL) {
                
               if (portId.getName().equals("COM2")) {
                    try {
                        serialPort = (SerialPort) portId.open("Ocupado",  2000);
                    } catch (PortInUseException e) {}

                }
            }
        } 
        
        return serialPort;
        
    }
    
}
